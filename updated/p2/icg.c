/*
 * ============================================================
 *  icg.c  —  Phase 4: Intermediate Code Generation
 *  Three-Address Code (TAC) from the AST
 *  Compiler Design Project | GEU
 *
 *  Plug-in to existing pipeline:
 *    1. Parse + semantic analysis runs first (parser.y / ast.h)
 *    2. Call  icg_generate(parse_root)  after sem_walk()
 *    3. The TAC instruction list is printed with  icg_print()
 *
 *  TAC instruction forms produced:
 *    t0 = a op b          (binary)
 *    t0 = op a            (unary)
 *    t0 = a               (copy / load literal)
 *    a  = t0              (store / assign)
 *    t0 = a[i]            (array load)
 *    a[i] = t0            (array store)
 *    param  t0            (push call argument)
 *    t0 = call f, n       (function call with n args)
 *    call   f, n          (void call)
 *    ifFalse t goto Lx    (conditional branch)
 *    goto   Lx            (unconditional branch)
 *    Lx:                  (label)
 *    BeginFunc f          (function prologue)
 *    EndFunc              (function epilogue)
 *    return t0            (return with value)
 *    return               (void return)
 * ============================================================
 */

#include "icg.h"
#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ════════════════════════════════════════════════════════════
 *  TAC INSTRUCTION
 * ════════════════════════════════════════════════════════════*/
typedef enum {
    TAC_ASSIGN,        /* result = arg1                   */
    TAC_BINOP,         /* result = arg1 op arg2           */
    TAC_UNOP,          /* result = op arg1                */
    TAC_COPY,          /* result = arg1  (plain copy)     */
    TAC_ARR_LOAD,      /* result = arg1[arg2]             */
    TAC_ARR_STORE,     /* result[arg2] = arg1             */
    TAC_PARAM,         /* param arg1                      */
    TAC_CALL,          /* result = call arg1, n  (or void)*/
    TAC_LABEL,         /* Lx:                             */
    TAC_GOTO,          /* goto Lx                         */
    TAC_IF_FALSE,      /* ifFalse arg1 goto Lx            */
    TAC_BEGIN_FUNC,    /* BeginFunc name                  */
    TAC_END_FUNC,      /* EndFunc                         */
    TAC_RETURN,        /* return [arg1]                   */
} TACKind;

typedef struct TACInstr {
    TACKind  kind;
    char    *result;   /* destination operand / label name */
    char    *arg1;     /* left operand / condition          */
    char    *arg2;     /* right operand / index             */
    char    *op;       /* operator string                   */
    int      n_args;   /* arg count for calls               */
    struct TACInstr *next;
} TACInstr;

/* ════════════════════════════════════════════════════════════
 *  ICG CONTEXT
 * ════════════════════════════════════════════════════════════*/
struct ICGCtx {
    TACInstr *head;        /* instruction list (head)  */
    TACInstr *tail;        /* instruction list (tail)  */
    int       temp_cnt;    /* next temp number  t0, t1 */
    int       label_cnt;   /* next label number L0, L1 */
    int       instr_cnt;   /* total instructions emitted */
};

/* ── allocate a fresh string ─────────────────────────────── */
static char *xdup(const char *s)
{
    return s ? strdup(s) : strdup("");
}

/* ── new temp name: t0, t1, ... ──────────────────────────── */
static char *new_temp(ICGCtx *ctx)
{
    char buf[32];
    snprintf(buf, sizeof(buf), "t%d", ctx->temp_cnt++);
    return strdup(buf);
}

/* ── new label name: L0, L1, ... ─────────────────────────── */
static char *new_label(ICGCtx *ctx)
{
    char buf[32];
    snprintf(buf, sizeof(buf), "L%d", ctx->label_cnt++);
    return strdup(buf);
}

/* ── append one instruction ──────────────────────────────── */
static TACInstr *emit(ICGCtx *ctx, TACKind kind,
                      const char *result, const char *arg1,
                      const char *arg2,   const char *op,
                      int n_args)
{
    TACInstr *ins = (TACInstr*)calloc(1, sizeof(TACInstr));
    ins->kind   = kind;
    ins->result = result ? strdup(result) : NULL;
    ins->arg1   = arg1   ? strdup(arg1)   : NULL;
    ins->arg2   = arg2   ? strdup(arg2)   : NULL;
    ins->op     = op     ? strdup(op)     : NULL;
    ins->n_args = n_args;

    if (!ctx->head) ctx->head = ctx->tail = ins;
    else { ctx->tail->next = ins; ctx->tail = ins; }
    ctx->instr_cnt++;
    return ins;
}

/* ════════════════════════════════════════════════════════════
 *  FORWARD DECLARATION
 * ════════════════════════════════════════════════════════════*/
static char *icg_expr (ICGCtx *ctx, ASTNode *n);
static void  icg_stmt (ICGCtx *ctx, ASTNode *n);
static void  icg_node (ICGCtx *ctx, ASTNode *n);

/* ════════════════════════════════════════════════════════════
 *  EXPRESSION → returns the name of the result operand
 * ════════════════════════════════════════════════════════════*/
static char *icg_expr(ICGCtx *ctx, ASTNode *n)
{
    if (!n) return strdup("(null)");

    switch (n->kind) {

    /* ── literals ──────────────────────────────────────── */
    case N_INT_LIT:
    case N_FLOAT_LIT:
    case N_CHAR_LIT:
    case N_STRING_LIT:
        return xdup(n->value);

    /* ── identifier ────────────────────────────────────── */
    case N_IDENT:
        return xdup(n->value);

    /* ── binary operation ──────────────────────────────── */
    case N_BINOP: {
        char *l = icg_expr(ctx, n->children[0]);
        char *r = icg_expr(ctx, n->children[1]);
        char *t = new_temp(ctx);
        emit(ctx, TAC_BINOP, t, l, r, n->value, 0);
        free(l); free(r);
        return t;   /* caller must free */
    }

    /* ── unary operation ───────────────────────────────── */
    case N_UNOP: {
        char *a = icg_expr(ctx, n->children[0]);
        char *t = new_temp(ctx);
        emit(ctx, TAC_UNOP, t, a, NULL, n->value, 0);
        free(a);
        return t;
    }

    /* ── array index  a[i] ─────────────────────────────── */
    case N_INDEX: {
        char *base = icg_expr(ctx, n->children[0]);
        char *idx  = icg_expr(ctx, n->children[1]);
        char *t    = new_temp(ctx);
        emit(ctx, TAC_ARR_LOAD, t, base, idx, NULL, 0);
        free(base); free(idx);
        return t;
    }

    /* ── assignment expression ─────────────────────────── */
    case N_ASSIGN: {
        /* children[0] = lhs  children[1] = rhs */
        char *rhs = icg_expr(ctx, n->children[1]);

        ASTNode *lhs = n->children[0];
        if (lhs->kind == N_INDEX) {
            /* array store: base[idx] = rhs */
            char *base = icg_expr(ctx, lhs->children[0]);
            char *idx  = icg_expr(ctx, lhs->children[1]);
            emit(ctx, TAC_ARR_STORE, base, rhs, idx, NULL, 0);
            free(base); free(idx);
        } else {
            /* simple assign: lhs = rhs */
            char *lname = xdup(lhs->value ? lhs->value : "?");
            emit(ctx, TAC_ASSIGN, lname, rhs, NULL, NULL, 0);
            free(lname);
        }
        char *ret = xdup(rhs);  /* expression value = rhs */
        free(rhs);
        return ret;
    }

    /* ── function call ─────────────────────────────────── */
    case N_CALL: {
        /* children[0] = function name ident
           children[1] = ARG_LIST (optional)              */
        const char *fname = n->children[0]->value;
        int nargs = 0;
        if (n->nchildren >= 2 && n->children[1]->kind == N_ARG_LIST) {
            ASTNode *al = n->children[1];
            nargs = al->nchildren;
            for (int i = 0; i < nargs; i++) {
                char *av = icg_expr(ctx, al->children[i]);
                emit(ctx, TAC_PARAM, NULL, av, NULL, NULL, 0);
                free(av);
            }
        }
        char *t = new_temp(ctx);
        emit(ctx, TAC_CALL, t, fname, NULL, NULL, nargs);
        return t;
    }

    /* ── ternary  cond ? then : else ───────────────────── */
    case N_TERNARY: {
        /* children: [0]=cond [1]=then [2]=else */
        char *cond  = icg_expr(ctx, n->children[0]);
        char *lelse = new_label(ctx);
        char *lend  = new_label(ctx);
        char *tres  = new_temp(ctx);

        emit(ctx, TAC_IF_FALSE, lelse, cond, NULL, NULL, 0);
        free(cond);

        char *tv = icg_expr(ctx, n->children[1]);
        emit(ctx, TAC_COPY, tres, tv, NULL, NULL, 0);
        free(tv);
        emit(ctx, TAC_GOTO, lend, NULL, NULL, NULL, 0);

        emit(ctx, TAC_LABEL, lelse, NULL, NULL, NULL, 0);
        free(lelse);

        char *fv = icg_expr(ctx, n->children[2]);
        emit(ctx, TAC_COPY, tres, fv, NULL, NULL, 0);
        free(fv);

        emit(ctx, TAC_LABEL, lend, NULL, NULL, NULL, 0);
        free(lend);
        return tres;
    }

    default:
        /* for any unhandled expression sub-node, recurse and
           return the last temp produced (best-effort)       */
        {
            char *last = strdup("?");
            for (int i = 0; i < n->nchildren; i++) {
                char *v = icg_expr(ctx, n->children[i]);
                free(last);
                last = v;
            }
            return last;
        }
    }
}

/* ════════════════════════════════════════════════════════════
 *  STATEMENT  (no return value needed)
 * ════════════════════════════════════════════════════════════*/
static void icg_stmt(ICGCtx *ctx, ASTNode *n)
{
    if (!n) return;

    switch (n->kind) {

    /* ── expression statement ──────────────────────────── */
    case N_EXPR_STMT: {
        char *v = icg_expr(ctx, n->children[0]);
        free(v);
        break;
    }

    /* ── declaration with initialiser ─────────────────── */
    case N_DECL_INIT: {
        /* children[0]=TYPE  [1]=IDENT  [2]=init-expr  OR
           children may vary; value holds the var name     */
        /* find init child (skip TYPE nodes)               */
        for (int i = 0; i < n->nchildren; i++) {
            if (n->children[i]->kind == N_TYPE) continue;
            if (n->children[i]->kind == N_IDENT) continue;
            /* this child is the initialiser               */
            char *rhs = icg_expr(ctx, n->children[i]);
            emit(ctx, TAC_ASSIGN, n->value, rhs, NULL, NULL, 0);
            free(rhs);
            break;
        }
        break;
    }

    /* ── plain declaration (no init) ──────────────────── */
    case N_DECL:
    case N_ARRAY_DECL:
        /* nothing to emit; just a symbol table entry      */
        break;

    case N_ARRAY_DECL_INIT: {
        for (int i = 0; i < n->nchildren; i++) {
            if (n->children[i]->kind == N_TYPE) continue;
            char *rhs = icg_expr(ctx, n->children[i]);
            emit(ctx, TAC_ASSIGN, n->value, rhs, NULL, NULL, 0);
            free(rhs);
            break;
        }
        break;
    }

    /* ── assignment statement (N_ASSIGN can appear here) ─*/
    case N_ASSIGN: {
        char *v = icg_expr(ctx, n);
        free(v);
        break;
    }

    /* ── return ────────────────────────────────────────── */
    case N_RETURN: {
        if (n->nchildren > 0) {
            char *rv = icg_expr(ctx, n->children[0]);
            emit(ctx, TAC_RETURN, NULL, rv, NULL, NULL, 0);
            free(rv);
        } else {
            emit(ctx, TAC_RETURN, NULL, NULL, NULL, NULL, 0);
        }
        break;
    }

    /* ── break / continue (simplified — no target loops) ─*/
    case N_BREAK:
        emit(ctx, TAC_GOTO, "BREAK", NULL, NULL, NULL, 0);
        break;
    case N_CONTINUE:
        emit(ctx, TAC_GOTO, "CONTINUE", NULL, NULL, NULL, 0);
        break;

    /* ── if  [else] ────────────────────────────────────── */
    case N_IF: {
        /*  children[0]=cond  [1]=then  [2]=else(optional) */
        char *cond  = icg_expr(ctx, n->children[0]);
        char *lelse = new_label(ctx);
        char *lend  = new_label(ctx);

        emit(ctx, TAC_IF_FALSE, lelse, cond, NULL, NULL, 0);
        free(cond);

        icg_stmt(ctx, n->children[1]);   /* then branch */

        if (n->nchildren >= 3) {
            emit(ctx, TAC_GOTO, lend, NULL, NULL, NULL, 0);
            emit(ctx, TAC_LABEL, lelse, NULL, NULL, NULL, 0);
            icg_stmt(ctx, n->children[2]); /* else branch */
            emit(ctx, TAC_LABEL, lend, NULL, NULL, NULL, 0);
        } else {
            emit(ctx, TAC_LABEL, lelse, NULL, NULL, NULL, 0);
        }

        free(lelse); free(lend);
        break;
    }

    /* ── while ─────────────────────────────────────────── */
    case N_WHILE: {
        /* children[0]=cond  [1]=body */
        char *ltest = new_label(ctx);
        char *lend  = new_label(ctx);

        emit(ctx, TAC_LABEL, ltest, NULL, NULL, NULL, 0);

        char *cond = icg_expr(ctx, n->children[0]);
        emit(ctx, TAC_IF_FALSE, lend, cond, NULL, NULL, 0);
        free(cond);

        icg_stmt(ctx, n->children[1]);

        emit(ctx, TAC_GOTO, ltest, NULL, NULL, NULL, 0);
        emit(ctx, TAC_LABEL, lend, NULL, NULL, NULL, 0);

        free(ltest); free(lend);
        break;
    }

    /* ── do-while ──────────────────────────────────────── */
    case N_DO_WHILE: {
        /* children[0]=body  [1]=cond */
        char *lstart = new_label(ctx);

        emit(ctx, TAC_LABEL, lstart, NULL, NULL, NULL, 0);
        icg_stmt(ctx, n->children[0]);

        char *cond = icg_expr(ctx, n->children[1]);
        emit(ctx, TAC_IF_FALSE, lstart, cond, NULL, NULL, 0);
        /* re-entering is done by IF_FALSE falling through  */
        /* (we invert: ifTrue → goto lstart)                */
        free(cond); free(lstart);
        break;
    }

    /* ── for ───────────────────────────────────────────── */
    case N_FOR: {
        /*  children[0]=init  [1]=cond  [2]=incr  [3]=body
            Any of init/cond/incr may be NULL nodes        */
        char *ltest = new_label(ctx);
        char *lincr = new_label(ctx);
        char *lend  = new_label(ctx);

        /* init */
        if (n->children[0]) icg_stmt(ctx, n->children[0]);

        emit(ctx, TAC_LABEL, ltest, NULL, NULL, NULL, 0);

        /* condition */
        if (n->children[1]) {
            char *cond = icg_expr(ctx, n->children[1]);
            emit(ctx, TAC_IF_FALSE, lend, cond, NULL, NULL, 0);
            free(cond);
        }

        /* body */
        if (n->nchildren >= 4) icg_stmt(ctx, n->children[3]);

        /* increment */
        emit(ctx, TAC_LABEL, lincr, NULL, NULL, NULL, 0);
        if (n->children[2]) {
            char *iv = icg_expr(ctx, n->children[2]);
            free(iv);
        }
        emit(ctx, TAC_GOTO, ltest, NULL, NULL, NULL, 0);
        emit(ctx, TAC_LABEL, lend, NULL, NULL, NULL, 0);

        free(ltest); free(lincr); free(lend);
        break;
    }

    /* ── block / compound ──────────────────────────────── */
    case N_BLOCK: {
        for (int i = 0; i < n->nchildren; i++)
            icg_node(ctx, n->children[i]);
        break;
    }

    /* ── function call as statement ────────────────────── */
    case N_CALL: {
        char *v = icg_expr(ctx, n);
        /* discard return value – void call                 */
        /* re-tag the last TAC_CALL as void (no result)    */
        if (ctx->tail && ctx->tail->kind == TAC_CALL) {
            free(ctx->tail->result);
            ctx->tail->result = NULL;
        }
        free(v);
        break;
    }

    default:
        /* catch-all: walk children */
        for (int i = 0; i < n->nchildren; i++)
            icg_node(ctx, n->children[i]);
        break;
    }
}

/* ════════════════════════════════════════════════════════════
 *  DISPATCH  (top-level per-node router)
 * ════════════════════════════════════════════════════════════*/
static void icg_node(ICGCtx *ctx, ASTNode *n)
{
    if (!n) return;

    switch (n->kind) {

    /* ── function definition ────────────────────────────── */
    case N_FUNC_DEF: {
        /* value = function name
           children[0]=TYPE  [1]=PARAM_LIST  [2]=BLOCK      */
        emit(ctx, TAC_BEGIN_FUNC, n->value, NULL, NULL, NULL, 0);
        /* body is always the last child                     */
        icg_stmt(ctx, n->children[n->nchildren - 1]);
        emit(ctx, TAC_END_FUNC, n->value, NULL, NULL, NULL, 0);
        break;
    }

    /* ── top-level block / program ─────────────────────── */
    case N_PROGRAM:
    case N_BLOCK: {
        for (int i = 0; i < n->nchildren; i++)
            icg_node(ctx, n->children[i]);
        break;
    }

    /* ── top-level declaration ──────────────────────────── */
    case N_DECL:
    case N_DECL_INIT:
    case N_ARRAY_DECL:
    case N_ARRAY_DECL_INIT:
        icg_stmt(ctx, n);
        break;

    default:
        icg_stmt(ctx, n);
        break;
    }
}

/* ════════════════════════════════════════════════════════════
 *  PUBLIC API
 * ════════════════════════════════════════════════════════════*/

/* Initialise the ICG context */
ICGCtx *icg_init(void)
{
    ICGCtx *ctx = (ICGCtx*)calloc(1, sizeof(ICGCtx));
    return ctx;
}

/* Generate TAC from AST root */
void icg_generate(ICGCtx *ctx, ASTNode *root)
{
    if (!ctx) return;
    icg_node(ctx, root);
}

/* ── pretty printer ──────────────────────────────────────── */
void icg_print(const ICGCtx *ctx)
{
    printf("\n" C_BOLD C_CYAN
           "  ══════════════════════════════════════════════════════════\n"
           "  PHASE 4 — INTERMEDIATE CODE GENERATION (Three-Address)\n"
           "  ══════════════════════════════════════════════════════════\n"
           C_RESET);

    printf(C_GRAY "  Total instructions: %d\n\n" C_RESET, ctx->instr_cnt);

    int line = 1;
    for (TACInstr *ins = ctx->head; ins; ins = ins->next, line++) {

        /* line number */
        printf(C_GRAY "  %3d  " C_RESET, line);

        switch (ins->kind) {

        case TAC_BEGIN_FUNC:
            printf(C_BOLD C_BLUE "BeginFunc " C_WHITE "%s\n" C_RESET,
                   ins->result ? ins->result : "?");
            printf(C_GRAY "       ─────────────────────────────\n" C_RESET);
            break;

        case TAC_END_FUNC:
            printf(C_GRAY "       ─────────────────────────────\n" C_RESET);
            printf(C_BOLD C_BLUE "EndFunc   " C_WHITE "%s\n\n" C_RESET,
                   ins->result ? ins->result : "?");
            break;

        case TAC_LABEL:
            printf(C_YELLOW "%s:\n" C_RESET,
                   ins->result ? ins->result : "?");
            break;

        case TAC_GOTO:
            printf(C_MAGENTA "       goto " C_WHITE "%s\n" C_RESET,
                   ins->result ? ins->result : "?");
            break;

        case TAC_IF_FALSE:
            printf(C_MAGENTA "       ifFalse " C_WHITE "%s" C_MAGENTA
                   " goto " C_WHITE "%s\n" C_RESET,
                   ins->arg1   ? ins->arg1   : "?",
                   ins->result ? ins->result : "?");
            break;

        case TAC_ASSIGN:
            printf("       " C_WHITE "%s" C_RESET " = " C_GREEN "%s\n" C_RESET,
                   ins->result ? ins->result : "?",
                   ins->arg1   ? ins->arg1   : "?");
            break;

        case TAC_COPY:
            printf("       " C_WHITE "%s" C_RESET " = " C_GREEN "%s\n" C_RESET,
                   ins->result ? ins->result : "?",
                   ins->arg1   ? ins->arg1   : "?");
            break;

        case TAC_BINOP:
            printf("       " C_CYAN "%s" C_RESET " = " C_WHITE "%s" C_RESET
                   " " C_RED "%s" C_RESET " " C_WHITE "%s\n" C_RESET,
                   ins->result ? ins->result : "?",
                   ins->arg1   ? ins->arg1   : "?",
                   ins->op     ? ins->op     : "?",
                   ins->arg2   ? ins->arg2   : "?");
            break;

        case TAC_UNOP:
            printf("       " C_CYAN "%s" C_RESET " = " C_RED "%s" C_RESET
                   " " C_WHITE "%s\n" C_RESET,
                   ins->result ? ins->result : "?",
                   ins->op     ? ins->op     : "?",
                   ins->arg1   ? ins->arg1   : "?");
            break;

        case TAC_ARR_LOAD:
            printf("       " C_CYAN "%s" C_RESET " = " C_WHITE "%s"
                   C_GRAY "[" C_WHITE "%s" C_GRAY "]\n" C_RESET,
                   ins->result ? ins->result : "?",
                   ins->arg1   ? ins->arg1   : "?",
                   ins->arg2   ? ins->arg2   : "?");
            break;

        case TAC_ARR_STORE:
            printf("       " C_WHITE "%s" C_GRAY "[" C_WHITE "%s"
                   C_GRAY "]" C_RESET " = " C_GREEN "%s\n" C_RESET,
                   ins->result ? ins->result : "?",
                   ins->arg2   ? ins->arg2   : "?",
                   ins->arg1   ? ins->arg1   : "?");
            break;

        case TAC_PARAM:
            printf(C_MAGENTA "       param  " C_WHITE "%s\n" C_RESET,
                   ins->arg1 ? ins->arg1 : "?");
            break;

        case TAC_CALL:
            if (ins->result)
                printf("       " C_CYAN "%s" C_RESET " = " C_BLUE "call "
                       C_WHITE "%s" C_GRAY ", %d\n" C_RESET,
                       ins->result,
                       ins->arg1 ? ins->arg1 : "?",
                       ins->n_args);
            else
                printf("       " C_BLUE "call   " C_WHITE "%s"
                       C_GRAY ", %d\n" C_RESET,
                       ins->arg1 ? ins->arg1 : "?",
                       ins->n_args);
            break;

        case TAC_RETURN:
            if (ins->arg1)
                printf(C_MAGENTA "       return " C_WHITE "%s\n" C_RESET,
                       ins->arg1);
            else
                printf(C_MAGENTA "       return\n" C_RESET);
            break;
        }
    }
    printf("\n");
}

/* ── free all instructions ───────────────────────────────── */
void icg_free(ICGCtx *ctx)
{
    if (!ctx) return;
    TACInstr *cur = ctx->head;
    while (cur) {
        TACInstr *nxt = cur->next;
        free(cur->result);
        free(cur->arg1);
        free(cur->arg2);
        free(cur->op);
        free(cur);
        cur = nxt;
    }
    ctx->head = ctx->tail = NULL;
    free(ctx);
}

/* ════════════════════════════════════════════════════════════
 *  FILE OUTPUT
 * ════════════════════════════════════════════════════════════*/

void icg_write_file(const ICGCtx *ctx, const char *path)
{
    FILE *fp = fopen(path, "w");
    if (!fp) { perror("icg_write_file"); return; }

    fprintf(fp, "; Three-Address Code — generated by icg.c\n\n");
    int line = 1;
    for (TACInstr *ins = ctx->head; ins; ins = ins->next, line++) {
        switch (ins->kind) {
        case TAC_BEGIN_FUNC:
            fprintf(fp, "\nBeginFunc %s\n", ins->result ? ins->result : "?");
            break;
        case TAC_END_FUNC:
            fprintf(fp, "EndFunc %s\n\n", ins->result ? ins->result : "?");
            break;
        case TAC_LABEL:
            fprintf(fp, "%s:\n", ins->result ? ins->result : "?");
            break;
        case TAC_GOTO:
            fprintf(fp, "    goto %s\n", ins->result ? ins->result : "?");
            break;
        case TAC_IF_FALSE:
            fprintf(fp, "    ifFalse %s goto %s\n",
                    ins->arg1   ? ins->arg1   : "?",
                    ins->result ? ins->result : "?");
            break;
        case TAC_ASSIGN:
        case TAC_COPY:
            fprintf(fp, "    %s = %s\n",
                    ins->result ? ins->result : "?",
                    ins->arg1   ? ins->arg1   : "?");
            break;
        case TAC_BINOP:
            fprintf(fp, "    %s = %s %s %s\n",
                    ins->result ? ins->result : "?",
                    ins->arg1   ? ins->arg1   : "?",
                    ins->op     ? ins->op     : "?",
                    ins->arg2   ? ins->arg2   : "?");
            break;
        case TAC_UNOP:
            fprintf(fp, "    %s = %s %s\n",
                    ins->result ? ins->result : "?",
                    ins->op     ? ins->op     : "?",
                    ins->arg1   ? ins->arg1   : "?");
            break;
        case TAC_ARR_LOAD:
            fprintf(fp, "    %s = %s[%s]\n",
                    ins->result ? ins->result : "?",
                    ins->arg1   ? ins->arg1   : "?",
                    ins->arg2   ? ins->arg2   : "?");
            break;
        case TAC_ARR_STORE:
            fprintf(fp, "    %s[%s] = %s\n",
                    ins->result ? ins->result : "?",
                    ins->arg2   ? ins->arg2   : "?",
                    ins->arg1   ? ins->arg1   : "?");
            break;
        case TAC_PARAM:
            fprintf(fp, "    param %s\n", ins->arg1 ? ins->arg1 : "?");
            break;
        case TAC_CALL:
            if (ins->result)
                fprintf(fp, "    %s = call %s, %d\n",
                        ins->result, ins->arg1 ? ins->arg1 : "?", ins->n_args);
            else
                fprintf(fp, "    call %s, %d\n",
                        ins->arg1 ? ins->arg1 : "?", ins->n_args);
            break;
        case TAC_RETURN:
            if (ins->arg1)
                fprintf(fp, "    return %s\n", ins->arg1);
            else
                fprintf(fp, "    return\n");
            break;
        }
    }
    fclose(fp);
    printf(C_GREEN "  TAC written to: %s\n" C_RESET, path);
}
