/*
 * ============================================================
 *  ast.h  —  AST Nodes + Symbol Table + Semantic Analyser
 *  Compiler Design Project | GEU
 * ============================================================
 */
#ifndef AST_H
#define AST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ── ANSI colours ────────────────────────────────────────────*/
#define C_RESET   "\033[0m"
#define C_BOLD    "\033[1m"
#define C_RED     "\033[1;31m"
#define C_GREEN   "\033[0;32m"
#define C_YELLOW  "\033[0;33m"
#define C_BLUE    "\033[1;34m"
#define C_MAGENTA "\033[0;35m"
#define C_CYAN    "\033[1;36m"
#define C_GRAY    "\033[0;90m"
#define C_WHITE   "\033[0;37m"
#define C_ORANGE  "\033[0;33m"

/* ════════════════════════════════════════════════════════════
 *  AST NODE KINDS
 * ════════════════════════════════════════════════════════════*/
typedef enum {
    /* program structure */
    N_PROGRAM, N_FUNC_DEF, N_BLOCK,
    /* declarations */
    N_DECL, N_DECL_INIT, N_ARRAY_DECL, N_ARRAY_DECL_INIT,
    /* statements */
    N_ASSIGN, N_IF, N_WHILE, N_DO_WHILE, N_FOR,
    N_RETURN, N_BREAK, N_CONTINUE, N_EXPR_STMT,
    /* expressions */
    N_BINOP, N_UNOP, N_CALL, N_INDEX, N_TERNARY,
    /* leaves */
    N_IDENT, N_INT_LIT, N_FLOAT_LIT, N_STRING_LIT, N_CHAR_LIT,
    /* type / param helpers */
    N_TYPE, N_PARAM, N_PARAM_LIST, N_ARG_LIST,
} NodeKind;

static const char *NODE_NAMES[] = {
    "PROGRAM","FUNC_DEF","BLOCK",
    "DECL","DECL_INIT","ARRAY_DECL","ARRAY_DECL_INIT",
    "ASSIGN","IF","WHILE","DO_WHILE","FOR",
    "RETURN","BREAK","CONTINUE","EXPR_STMT",
    "BINOP","UNOP","CALL","INDEX","TERNARY",
    "IDENT","INT_LIT","FLOAT_LIT","STRING_LIT","CHAR_LIT",
    "TYPE","PARAM","PARAM_LIST","ARG_LIST",
};

/* ── ASTNode ─────────────────────────────────────────────────*/
typedef struct ASTNode {
    NodeKind        kind;
    char           *value;
    int             line;
    struct ASTNode **children;
    int             nchildren;
    int             cap;
} ASTNode;

static inline ASTNode *ast_new(NodeKind k, const char *v, int ln)
{
    ASTNode *n = (ASTNode*)calloc(1, sizeof(ASTNode));
    n->kind    = k;
    n->value   = v ? strdup(v) : NULL;
    n->line    = ln;
    n->cap     = 4;
    n->children = (ASTNode**)malloc(n->cap * sizeof(ASTNode*));
    return n;
}

static inline void ast_add(ASTNode *p, ASTNode *c)
{
    if (!p || !c) return;
    if (p->nchildren == p->cap) {
        p->cap *= 2;
        p->children = (ASTNode**)realloc(p->children,
                          p->cap * sizeof(ASTNode*));
    }
    p->children[p->nchildren++] = c;
}

static inline void ast_free(ASTNode *n)
{
    if (!n) return;
    for (int i = 0; i < n->nchildren; i++) ast_free(n->children[i]);
    free(n->children);
    free(n->value);
    free(n);
}

/* ── AST pretty printer ─────────────────────────────────────*/
static void ast_print_r(const ASTNode *n, const char *pfx, int last)
{
    if (!n) return;

    /* pick colour by category */
    const char *col = C_CYAN;
    if (n->kind == N_IDENT)                    col = C_WHITE;
    else if (n->kind == N_INT_LIT  ||
             n->kind == N_FLOAT_LIT)           col = C_GREEN;
    else if (n->kind == N_STRING_LIT ||
             n->kind == N_CHAR_LIT)            col = C_YELLOW;
    else if (n->kind == N_TYPE)                col = C_BLUE;
    else if (n->kind == N_ASSIGN ||
             n->kind == N_BINOP  ||
             n->kind == N_UNOP)                col = C_MAGENTA;
    else if (n->kind == N_IF     ||
             n->kind == N_WHILE  ||
             n->kind == N_FOR    ||
             n->kind == N_DO_WHILE)            col = C_ORANGE;
    else if (n->kind == N_FUNC_DEF)            col = C_BOLD;

    printf("%s%s%s%s%s%s",
           C_GRAY, pfx, last ? "└── " : "├── ",
           col, NODE_NAMES[n->kind], C_RESET);

    if (n->value && n->value[0])
        printf("  " C_YELLOW "(%s)" C_RESET, n->value);

    printf("  " C_GRAY "[line %d]" C_RESET "\n", n->line);

    char np[1024];
    snprintf(np, sizeof(np), "%s%s", pfx, last ? "    " : "│   ");
    for (int i = 0; i < n->nchildren; i++)
        ast_print_r(n->children[i], np, i == n->nchildren - 1);
}

static inline void ast_print(const ASTNode *root)
{
    if (!root) { printf("  (empty tree)\n"); return; }
    printf("\n" C_BOLD C_GREEN "  Abstract Syntax Tree\n" C_RESET);
    printf(C_GRAY "  ─────────────────────────────────────────────────\n" C_RESET);
    for (int i = 0; i < root->nchildren; i++)
        ast_print_r(root->children[i], "  ", i == root->nchildren - 1);
    printf("\n");
}

/* ════════════════════════════════════════════════════════════
 *  SYMBOL TABLE
 * ════════════════════════════════════════════════════════════*/
#define SYM_VAR   0
#define SYM_FUNC  1
#define SYM_ARRAY 2
#define SYM_PARAM 3

#define MAX_SYMBOLS 512
#define MAX_SCOPES   64
#define MAX_PARAMS   32

typedef struct {
    char  name[64];
    char  type[32];
    int   kind;        /* SYM_VAR / SYM_FUNC / SYM_ARRAY / SYM_PARAM */
    int   scope;       /* nesting depth */
    int   line;        /* declaration line */
    int   used;        /* has it been used after declaration? */
    int   initialized; /* was it assigned before first use? */
    int   param_count; /* for functions */
    char  param_types[MAX_PARAMS][32];
    int   array_size;  /* for arrays, -1 = unknown */
} Symbol;

typedef struct {
    Symbol table[MAX_SYMBOLS];
    int    count;
    int    scope;       /* current scope depth */
    int    scope_stack[MAX_SCOPES];
    int    scope_top;
} SymTable;

static inline void sym_init(SymTable *st)
{
    memset(st, 0, sizeof(*st));
    st->scope = 0;
}

static inline void sym_push_scope(SymTable *st)
{
    st->scope++;
}

static inline void sym_pop_scope(SymTable *st)
{
    st->scope--;
}

/* lookup in current + enclosing scopes */
static inline Symbol *sym_lookup(SymTable *st, const char *name)
{
    for (int i = st->count - 1; i >= 0; i--)
        if (strcmp(st->table[i].name, name) == 0 &&
            st->table[i].scope <= st->scope)
            return &st->table[i];
    return NULL;
}

/* lookup in current scope only */
static inline Symbol *sym_lookup_cur(SymTable *st, const char *name)
{
    for (int i = st->count - 1; i >= 0; i--)
        if (strcmp(st->table[i].name, name) == 0 &&
            st->table[i].scope == st->scope)
            return &st->table[i];
    return NULL;
}

static inline Symbol *sym_add(SymTable *st, const char *name,
                               const char *type, int kind, int line)
{
    if (st->count >= MAX_SYMBOLS) return NULL;
    Symbol *s = &st->table[st->count++];
    strncpy(s->name, name, sizeof(s->name)-1);
    strncpy(s->type, type, sizeof(s->type)-1);
    s->kind  = kind;
    s->scope = st->scope;
    s->line  = line;
    s->used  = 0;
    s->initialized = 0;
    s->param_count = 0;
    s->array_size  = -1;
    return s;
}

/* ════════════════════════════════════════════════════════════
 *  SEMANTIC ERROR / WARNING REPORTING
 * ════════════════════════════════════════════════════════════*/
#define MAX_ISSUES 256

typedef enum {
    SEV_ERROR,
    SEV_WARNING,
    SEV_INFO,
} Severity;

typedef struct {
    Severity sev;
    int      line;
    char     msg[256];
    char     hint[256];
} Issue;

typedef struct {
    Issue issues[MAX_ISSUES];
    int   count;
    int   errors;
    int   warnings;
} IssueList;

static inline void issue_add(IssueList *il, Severity sev,
                              int line, const char *msg, const char *hint)
{
    if (il->count >= MAX_ISSUES) return;
    Issue *is = &il->issues[il->count++];
    is->sev  = sev;
    is->line = line;
    strncpy(is->msg,  msg,  sizeof(is->msg)-1);
    strncpy(is->hint, hint ? hint : "", sizeof(is->hint)-1);
    if (sev == SEV_ERROR)   il->errors++;
    if (sev == SEV_WARNING) il->warnings++;
}

static inline void issue_print(const IssueList *il)
{
    if (il->count == 0) {
        printf(C_GREEN "  No semantic issues found.\n" C_RESET);
        return;
    }
    for (int i = 0; i < il->count; i++) {
        const Issue *is = &il->issues[i];
        const char *tag, *col;
        if      (is->sev == SEV_ERROR)   { tag = "ERROR  "; col = C_RED;    }
        else if (is->sev == SEV_WARNING) { tag = "WARNING"; col = C_YELLOW; }
        else                             { tag = "INFO   "; col = C_CYAN;   }
        printf("  %s[%s]%s line %-4d  %s\n",
               col, tag, C_RESET, is->line, is->msg);
        if (is->hint[0])
            printf("           %s→ Hint: %s%s\n", C_GRAY, is->hint, C_RESET);
    }
}

/* ════════════════════════════════════════════════════════════
 *  SEMANTIC ANALYSER
 *  Walks the AST, populates symbol table, emits issues.
 * ════════════════════════════════════════════════════════════*/
typedef struct {
    SymTable  sym;
    IssueList issues;
    char      cur_func[64];     /* function we're currently inside */
    int       has_return;       /* did current function return?    */
    char      cur_func_type[32];
} SemCtx;

static inline void sem_init(SemCtx *ctx)
{
    sym_init(&ctx->sym);
    memset(&ctx->issues, 0, sizeof(ctx->issues));
    ctx->cur_func[0]      = '\0';
    ctx->cur_func_type[0] = '\0';
    ctx->has_return = 0;
}

/* forward declaration */
static void sem_walk(SemCtx *ctx, ASTNode *n);

/* resolve type of an expression node (simple version) */
static const char *sem_type_of(SemCtx *ctx, ASTNode *n)
{
    if (!n) return "void";
    if (n->kind == N_INT_LIT)   return "int";
    if (n->kind == N_FLOAT_LIT) return "float";
    if (n->kind == N_STRING_LIT)return "char*";
    if (n->kind == N_CHAR_LIT)  return "char";
    if (n->kind == N_IDENT) {
        Symbol *s = sym_lookup(&ctx->sym, n->value);
        return s ? s->type : "unknown";
    }
    if (n->kind == N_BINOP) {
        const char *lt = sem_type_of(ctx, n->nchildren>0?n->children[0]:NULL);
        const char *rt = sem_type_of(ctx, n->nchildren>1?n->children[1]:NULL);
        if (strcmp(lt,"float")==0 || strcmp(rt,"float")==0) return "float";
        return "int";
    }
    if (n->kind == N_CALL) {
        if (n->nchildren > 0) {
            Symbol *s = sym_lookup(&ctx->sym,
                n->children[0]->value ? n->children[0]->value : "");
            return s ? s->type : "unknown";
        }
    }
    return "int";
}

static void sem_walk(SemCtx *ctx, ASTNode *n)
{
    if (!n) return;
    SymTable  *st = &ctx->sym;
    IssueList *il = &ctx->issues;

    switch (n->kind) {

    /* ── PROGRAM / BLOCK ──────────────────────────────────── */
    case N_PROGRAM:
        for (int i=0;i<n->nchildren;i++) sem_walk(ctx,n->children[i]);
        break;

    case N_BLOCK:
        sym_push_scope(st);
        for (int i=0;i<n->nchildren;i++) sem_walk(ctx,n->children[i]);
        /* check for unused variables in this scope */
        for (int i=0;i<st->count;i++) {
            Symbol *s = &st->table[i];
            if (s->scope == st->scope && s->kind == SYM_VAR && !s->used) {
                char msg[256], hint[256];
                snprintf(msg,  sizeof(msg),
                    "Variable '%s' declared at line %d but never used.",
                    s->name, s->line);
                snprintf(hint, sizeof(hint),
                    "Remove '%s' or use it — unused variables waste memory.", s->name);
                issue_add(il, SEV_WARNING, s->line, msg, hint);
            }
        }
        sym_pop_scope(st);
        break;

    /* ── FUNCTION DEFINITION ─────────────────────────────── */
    case N_FUNC_DEF: {
        /* children: [TYPE, PARAM_LIST, BLOCK] */
        const char *fname = n->value ? n->value : "?";
        const char *ftype = (n->nchildren>0 && n->children[0]->value)
                             ? n->children[0]->value : "int";

        /* check redefinition */
        if (sym_lookup_cur(st, fname)) {
            char msg[256];
            snprintf(msg,sizeof(msg),"Function '%s' redefined.",fname);
            issue_add(il,SEV_ERROR,n->line,msg,
                "Remove the duplicate function definition.");
        } else {
            Symbol *fs = sym_add(st, fname, ftype, SYM_FUNC, n->line);
            /* register parameters */
            if (n->nchildren > 1 && n->children[1]->kind == N_PARAM_LIST) {
                ASTNode *pl = n->children[1];
                fs->param_count = pl->nchildren;
                for (int i=0;i<pl->nchildren;i++) {
                    ASTNode *pm = pl->children[i];
                    const char *pt = (pm->nchildren>0&&pm->children[0]->value)
                                      ? pm->children[0]->value : "int";
                    strncpy(fs->param_types[i], pt,
                            sizeof(fs->param_types[i])-1);
                }
            }
        }

        strncpy(ctx->cur_func, fname, sizeof(ctx->cur_func)-1);
        strncpy(ctx->cur_func_type, ftype, sizeof(ctx->cur_func_type)-1);
        ctx->has_return = 0;

        sym_push_scope(st);
        /* add params to inner scope */
        if (n->nchildren > 1 && n->children[1]->kind == N_PARAM_LIST) {
            ASTNode *pl = n->children[1];
            for (int i=0;i<pl->nchildren;i++) {
                ASTNode *pm = pl->children[i];
                const char *pname = pm->value ? pm->value : "?";
                const char *ptype = (pm->nchildren>0&&pm->children[0]->value)
                                     ? pm->children[0]->value : "int";
                sym_add(st, pname, ptype, SYM_PARAM, pm->line);
            }
        }
        /* walk body */
        if (n->nchildren > 2) sem_walk(ctx, n->children[2]);
        else if (n->nchildren > 1 &&
                 n->children[n->nchildren-1]->kind == N_BLOCK)
            sem_walk(ctx, n->children[n->nchildren-1]);

        sym_pop_scope(st);

        /* missing return check */
        if (strcmp(ctx->cur_func_type,"void")!=0 && !ctx->has_return) {
            char msg[256];
            snprintf(msg,sizeof(msg),
                "Function '%s' returns '%s' but has no return statement.",
                fname, ftype);
            issue_add(il,SEV_WARNING,n->line,msg,
                "Add a return statement at the end of the function.");
        }
        ctx->cur_func[0]='\0';
        ctx->has_return = 0;
        break;
    }

    /* ── DECLARATIONS ─────────────────────────────────────── */
    case N_DECL:
    case N_DECL_INIT: {
        /* children[0] = TYPE, remaining may be initialiser */
        const char *vname = n->value ? n->value : "?";
        const char *vtype = (n->nchildren>0 && n->children[0] &&
                             n->children[0]->value)
                             ? n->children[0]->value : "int";

        /* duplicate in same scope */
        if (sym_lookup_cur(st, vname)) {
            char msg[256];
            snprintf(msg,sizeof(msg),
                "Variable '%s' already declared in this scope.", vname);
            issue_add(il,SEV_ERROR,n->line,msg,
                "Use a different name or remove the duplicate declaration.");
        } else {
            Symbol *sv = sym_add(st, vname, vtype, SYM_VAR, n->line);
            if (n->kind == N_DECL_INIT) {
                sv->initialized = 1;
                /* walk initialiser expression */
                for (int i=1;i<n->nchildren;i++)
                    sem_walk(ctx, n->children[i]);
            }
        }
        break;
    }

    case N_ARRAY_DECL:
    case N_ARRAY_DECL_INIT: {
        const char *aname = n->value ? n->value : "?";
        const char *atype = (n->nchildren>0 && n->children[0] &&
                             n->children[0]->value)
                             ? n->children[0]->value : "int";
        if (sym_lookup_cur(st, aname)) {
            char msg[256];
            snprintf(msg,sizeof(msg),
                "Array '%s' already declared in this scope.", aname);
            issue_add(il,SEV_ERROR,n->line,msg,NULL);
        } else {
            Symbol *sa = sym_add(st, aname, atype, SYM_ARRAY, n->line);
            /* children[1] might be the size expression */
            if (n->nchildren>1 && n->children[1] &&
                n->children[1]->kind == N_INT_LIT)
                sa->array_size = atoi(n->children[1]->value);
        }
        for (int i=1;i<n->nchildren;i++) sem_walk(ctx,n->children[i]);
        break;
    }

    /* ── ASSIGNMENT ───────────────────────────────────────── */
    case N_ASSIGN: {
        /* children[0]=lhs  children[1]=rhs */
        if (n->nchildren >= 2) {
            ASTNode *lhs = n->children[0];
            ASTNode *rhs = n->children[1];
            sem_walk(ctx, rhs);

            if (lhs->kind == N_IDENT) {
                Symbol *sv = sym_lookup(st, lhs->value);
                if (!sv) {
                    char msg[256];
                    snprintf(msg,sizeof(msg),
                        "Assignment to undeclared variable '%s'.", lhs->value);
                    issue_add(il,SEV_ERROR,n->line,msg,
                        "Declare the variable before assigning to it.");
                } else {
                    sv->initialized = 1;
                    sv->used = 1;

                    /* type mismatch warning */
                    const char *rtype = sem_type_of(ctx, rhs);
                    if (strcmp(sv->type,"int")==0 &&
                        strcmp(rtype,"float")==0) {
                        char msg[256];
                        snprintf(msg,sizeof(msg),
                            "Assigning float to int variable '%s' — possible data loss.",
                            sv->name);
                        issue_add(il,SEV_WARNING,n->line,msg,
                            "Cast explicitly: (int)expr, or change the variable type to float.");
                    }
                    if (strcmp(sv->type,"int")==0 &&
                        strcmp(rtype,"char*")==0) {
                        char msg[256];
                        snprintf(msg,sizeof(msg),
                            "Assigning string to int variable '%s'.", sv->name);
                        issue_add(il,SEV_ERROR,n->line,msg,NULL);
                    }
                }
            } else if (lhs->kind == N_INDEX) {
                /* array index assignment: walk both sides */
                sem_walk(ctx, lhs);
            }
        }
        break;
    }

    /* ── IDENTIFIER USE ───────────────────────────────────── */
    case N_IDENT: {
        Symbol *sv = sym_lookup(st, n->value);
        if (!sv) {
            char msg[256];
            snprintf(msg,sizeof(msg),
                "Use of undeclared identifier '%s'.", n->value);
            issue_add(il,SEV_ERROR,n->line,msg,
                "Declare the variable or fix the spelling.");
        } else {
            if (!sv->initialized && sv->kind == SYM_VAR) {
                char msg[256];
                snprintf(msg,sizeof(msg),
                    "Variable '%s' used before being initialised.", sv->name);
                issue_add(il,SEV_WARNING,n->line,msg,
                    "Assign a value to the variable before using it.");
            }
            sv->used = 1;
        }
        break;
    }

    /* ── ARRAY INDEX ──────────────────────────────────────── */
    case N_INDEX: {
        /* children[0]=array  children[1]=index expr */
        if (n->nchildren >= 1) {
            ASTNode *arr = n->children[0];
            if (arr->kind == N_IDENT) {
                Symbol *sa = sym_lookup(st, arr->value);
                if (!sa) {
                    char msg[256];
                    snprintf(msg,sizeof(msg),
                        "Use of undeclared array '%s'.", arr->value);
                    issue_add(il,SEV_ERROR,n->line,msg,NULL);
                } else {
                    sa->used = 1;
                    /* out-of-bounds check on integer literal index */
                    if (n->nchildren >= 2 &&
                        n->children[1]->kind == N_INT_LIT &&
                        sa->array_size > 0) {
                        int idx = atoi(n->children[1]->value);
                        if (idx < 0 || idx >= sa->array_size) {
                            char msg[256];
                            snprintf(msg,sizeof(msg),
                                "Array '%s[%d]': index %d is out of bounds (size=%d).",
                                sa->name, sa->array_size, idx, sa->array_size);
                            issue_add(il,SEV_ERROR,n->line,msg,
                                "Array indices must be 0 to size-1.");
                        }
                    }
                }
            }
        }
        for (int i=0;i<n->nchildren;i++) sem_walk(ctx,n->children[i]);
        break;
    }

    /* ── FUNCTION CALL ────────────────────────────────────── */
    case N_CALL: {
        /* children[0]=func-name-ident  [children[1]=ARG_LIST] */
        if (n->nchildren >= 1 && n->children[0]->kind == N_IDENT) {
            const char *fname = n->children[0]->value;
            Symbol *fs = sym_lookup(st, fname);

            /* known standard library functions — skip redecl check */
            int is_stdlib = (strcmp(fname,"printf")==0  ||
                             strcmp(fname,"scanf")==0   ||
                             strcmp(fname,"malloc")==0  ||
                             strcmp(fname,"free")==0    ||
                             strcmp(fname,"strlen")==0  ||
                             strcmp(fname,"strcpy")==0  ||
                             strcmp(fname,"memset")==0);

            if (!fs && !is_stdlib) {
                char msg[256];
                snprintf(msg,sizeof(msg),
                    "Call to undeclared function '%s'.", fname);
                issue_add(il,SEV_ERROR,n->line,msg,
                    "Declare or define the function before calling it.");
            } else if (fs && fs->kind == SYM_FUNC) {
                fs->used = 1;
                /* argument count check */
                int nargs = 0;
                if (n->nchildren >= 2 &&
                    n->children[1]->kind == N_ARG_LIST)
                    nargs = n->children[1]->nchildren;
                if (fs->param_count > 0 &&
                    nargs != fs->param_count) {
                    char msg[256];
                    snprintf(msg,sizeof(msg),
                        "Function '%s' expects %d argument(s) but called with %d.",
                        fname, fs->param_count, nargs);
                    issue_add(il,SEV_ERROR,n->line,msg,
                        "Check the function signature and provide the correct number of arguments.");
                }
            }
        }
        /* walk arguments */
        for (int i=1;i<n->nchildren;i++) sem_walk(ctx,n->children[i]);
        break;
    }

    /* ── RETURN ───────────────────────────────────────────── */
    case N_RETURN:
        ctx->has_return = 1;
        if (n->nchildren > 0) {
            sem_walk(ctx, n->children[0]);
            /* return type mismatch */
            if (ctx->cur_func[0]) {
                const char *rtype = sem_type_of(ctx, n->children[0]);
                if (strcmp(ctx->cur_func_type,"void")==0 &&
                    strcmp(rtype,"void")!=0) {
                    char msg[256];
                    snprintf(msg,sizeof(msg),
                        "Function '%s' is void but returns a value.",
                        ctx->cur_func);
                    issue_add(il,SEV_ERROR,n->line,msg,
                        "Remove the return value or change the return type.");
                }
            }
        } else if (ctx->cur_func[0] &&
                   strcmp(ctx->cur_func_type,"void")!=0) {
            char msg[256];
            snprintf(msg,sizeof(msg),
                "Function '%s' should return '%s' but bare return found.",
                ctx->cur_func, ctx->cur_func_type);
            issue_add(il,SEV_WARNING,n->line,msg,
                "Provide a return value matching the function's declared type.");
        }
        break;

    /* ── CONTROL FLOW ─────────────────────────────────────── */
    case N_IF:
        /* children[0]=cond  [1]=then  [2]=else */
        for (int i=0;i<n->nchildren;i++) sem_walk(ctx,n->children[i]);
        break;

    case N_WHILE:
    case N_DO_WHILE:
        for (int i=0;i<n->nchildren;i++) sem_walk(ctx,n->children[i]);
        break;

    case N_FOR:
        for (int i=0;i<n->nchildren;i++) sem_walk(ctx,n->children[i]);
        break;

    /* ── BINARY OPERATION ─────────────────────────────────── */
    case N_BINOP: {
        for (int i=0;i<n->nchildren;i++) sem_walk(ctx,n->children[i]);
        /* division by zero */
        if (n->value && strcmp(n->value,"/")==0 &&
            n->nchildren==2 &&
            n->children[1]->kind == N_INT_LIT &&
            strcmp(n->children[1]->value,"0")==0) {
            issue_add(il,SEV_ERROR,n->line,
                "Division by zero detected.",
                "The divisor is the integer literal 0 — this causes undefined behaviour.");
        }
        /* modulo by zero */
        if (n->value && strcmp(n->value,"%")==0 &&
            n->nchildren==2 &&
            n->children[1]->kind == N_INT_LIT &&
            strcmp(n->children[1]->value,"0")==0) {
            issue_add(il,SEV_ERROR,n->line,
                "Modulo by zero detected.",
                "The divisor is 0 — this causes undefined behaviour.");
        }
        break;
    }

    /* ── UNARY ────────────────────────────────────────────── */
    case N_UNOP:
        for (int i=0;i<n->nchildren;i++) sem_walk(ctx,n->children[i]);
        break;

    /* ── EVERYTHING ELSE ──────────────────────────────────── */
    default:
        for (int i=0;i<n->nchildren;i++) sem_walk(ctx,n->children[i]);
        break;
    }
}

/* ── Symbol table printer ────────────────────────────────────*/
static inline void sym_print(const SymTable *st)
{
    const char *kinds[] = {"VAR","FUNC","ARRAY","PARAM"};
    printf("\n" C_BOLD C_BLUE "  Symbol Table\n" C_RESET);
    printf(C_GRAY "  ─────────────────────────────────────────────────────────────\n" C_RESET);
    printf(C_BOLD "  %-16s %-10s %-7s %-6s %-6s %-5s %-5s\n" C_RESET,
           "NAME","TYPE","KIND","SCOPE","LINE","USED","INIT");
    printf(C_GRAY "  ─────────────────────────────────────────────────────────────\n" C_RESET);
    for (int i=0;i<st->count;i++) {
        const Symbol *s = &st->table[i];
        const char *col = (s->kind==SYM_FUNC) ? C_CYAN :
                          (s->kind==SYM_ARRAY) ? C_YELLOW :
                          (s->kind==SYM_PARAM) ? C_MAGENTA : C_WHITE;
        printf("  %s%-16s%s %-10s %-7s %-6d %-6d %-5s %-5s\n",
               col, s->name, C_RESET,
               s->type,
               kinds[s->kind],
               s->scope, s->line,
               s->used ? C_GREEN"yes"C_RESET : C_RED"no"C_RESET,
               s->initialized ? C_GREEN"yes"C_RESET : C_YELLOW"no"C_RESET);
        if (s->kind == SYM_FUNC && s->param_count > 0) {
            printf("     " C_GRAY "params(%d): ", s->param_count);
            for (int j=0;j<s->param_count;j++)
                printf("%s%s", s->param_types[j],
                       j<s->param_count-1?", ":"");
            printf(C_RESET "\n");
        }
        if (s->kind == SYM_ARRAY && s->array_size > 0)
            printf("     " C_GRAY "size: %d" C_RESET "\n", s->array_size);
    }
    printf(C_GRAY "  ─────────────────────────────────────────────────────────────\n" C_RESET);
}

#endif /* AST_H */
