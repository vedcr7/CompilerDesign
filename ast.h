/*
 * ============================================================
 *  ast.h  —  Abstract Syntax Tree node definitions
 *  Used by both parser.y and any future tree-walking passes
 * ============================================================
 */

#ifndef AST_H
#define AST_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* ── node kinds ──────────────────────────────────────────────*/
typedef enum {
    /* Statements */
    NODE_PROGRAM,       /* root: list of top-level declarations     */
    NODE_FUNC_DEF,      /* function definition                       */
    NODE_BLOCK,         /* compound statement  { … }                */
    NODE_DECL,          /* variable declaration  int x;             */
    NODE_DECL_INIT,     /* declaration with initialiser  int x = 5; */
    NODE_ASSIGN,        /* assignment  x = expr                     */
    NODE_IF,            /* if (cond) then [else]                    */
    NODE_WHILE,         /* while (cond) body                        */
    NODE_DO_WHILE,      /* do body while (cond)                     */
    NODE_FOR,           /* for (init; cond; update) body            */
    NODE_RETURN,        /* return [expr]                            */
    NODE_BREAK,         /* break                                    */
    NODE_CONTINUE,      /* continue                                 */
    /* Expressions */
    NODE_BINOP,         /* binary operation  left OP right          */
    NODE_UNOP,          /* unary operation   OP operand             */
    NODE_CALL,          /* function call  f(args…)                  */
    NODE_INDEX,         /* array index  a[i]                        */
    NODE_MEMBER,        /* struct member  s.field  or  p->field     */
    NODE_TERNARY,       /* cond ? then : else                       */
    NODE_CAST,          /* (type) expr                              */
    /* Leaves */
    NODE_IDENT,         /* identifier                               */
    NODE_INT_LIT,       /* integer literal                          */
    NODE_FLOAT_LIT,     /* float literal                            */
    NODE_STRING_LIT,    /* string literal                           */
    NODE_CHAR_LIT,      /* character literal                        */
    NODE_TYPE,          /* type specifier node (int, char, …)       */
    NODE_PARAM,         /* function parameter                       */
    NODE_PARAM_LIST,    /* list of parameters                       */
    NODE_ARG_LIST,      /* list of call arguments                   */
} NodeKind;

/* ── string names (for printing) ────────────────────────────*/
static const char *node_kind_name[] = {
    "PROGRAM",    "FUNC_DEF",    "BLOCK",      "DECL",       "DECL_INIT",
    "ASSIGN",     "IF",          "WHILE",      "DO_WHILE",   "FOR",
    "RETURN",     "BREAK",       "CONTINUE",
    "BINOP",      "UNOP",        "CALL",       "INDEX",      "MEMBER",
    "TERNARY",    "CAST",
    "IDENT",      "INT_LIT",     "FLOAT_LIT",  "STRING_LIT", "CHAR_LIT",
    "TYPE",       "PARAM",       "PARAM_LIST", "ARG_LIST",
};

/* ── ASTNode ─────────────────────────────────────────────────*/
typedef struct ASTNode {
    NodeKind        kind;
    char           *value;        /* token text where applicable    */
    int             line;         /* source line number             */
    struct ASTNode **children;    /* dynamic array of child pointers*/
    int             child_count;
    int             child_cap;
} ASTNode;

/* ── allocation helpers ──────────────────────────────────────*/
static inline ASTNode *ast_new(NodeKind kind, const char *value, int line)
{
    ASTNode *n   = (ASTNode *)calloc(1, sizeof(ASTNode));
    n->kind      = kind;
    n->value     = value ? strdup(value) : NULL;
    n->line      = line;
    n->child_cap = 4;
    n->children  = (ASTNode **)malloc(n->child_cap * sizeof(ASTNode *));
    n->child_count = 0;
    return n;
}

static inline void ast_add_child(ASTNode *parent, ASTNode *child)
{
    if (!parent || !child) return;
    if (parent->child_count == parent->child_cap) {
        parent->child_cap *= 2;
        parent->children = (ASTNode **)realloc(parent->children,
                               parent->child_cap * sizeof(ASTNode *));
    }
    parent->children[parent->child_count++] = child;
}

/* ── recursive free ──────────────────────────────────────────*/
static inline void ast_free(ASTNode *n)
{
    if (!n) return;
    for (int i = 0; i < n->child_count; i++)
        ast_free(n->children[i]);
    free(n->children);
    free(n->value);
    free(n);
}

/* ── pretty-printer ──────────────────────────────────────────*/
/*   prefix  = already-printed prefix for this line            */
/*   is_last = whether this node is last sibling               */
static void ast_print_recursive(const ASTNode *n,
                                const char    *prefix,
                                int            is_last)
{
    if (!n) return;

    /* ANSI colours */
    const char *C_KIND  = "\033[1;36m";   /* cyan bold   */
    const char *C_VAL   = "\033[0;33m";   /* yellow      */
    const char *C_LINE  = "\033[0;90m";   /* dark grey   */
    const char *C_RESET = "\033[0m";
    const char *C_TREE  = "\033[0;90m";   /* tree lines  */

    /* connector for this node */
    printf("%s%s%s%s%s%s",
           C_TREE,
           prefix,
           is_last ? "└── " : "├── ",
           C_KIND,
           node_kind_name[n->kind],
           C_RESET);

    if (n->value && n->value[0])
        printf("  %s%s%s", C_VAL, n->value, C_RESET);

    printf("  %s(line %d)%s\n", C_LINE, n->line, C_RESET);

    /* build child prefix */
    char child_prefix[512];
    snprintf(child_prefix, sizeof(child_prefix), "%s%s",
             prefix, is_last ? "    " : "│   ");

    for (int i = 0; i < n->child_count; i++) {
        int last = (i == n->child_count - 1);
        ast_print_recursive(n->children[i], child_prefix, last);
    }
}

static inline void ast_print(const ASTNode *root)
{
    if (!root) { printf("  (empty tree)\n"); return; }
    const char *C_ROOT  = "\033[1;32m";
    const char *C_RESET = "\033[0m";
    printf("\n%s  AST Root%s\n", C_ROOT, C_RESET);
    /* print all top-level children as siblings */
    for (int i = 0; i < root->child_count; i++) {
        int last = (i == root->child_count - 1);
        ast_print_recursive(root->children[i], "  ", last);
    }
    printf("\n");
}

#endif /* AST_H */
