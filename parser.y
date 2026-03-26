/*
 * ============================================================
 *  parser.y  —  Phase 2: Bison Parser + AST Builder
 *  Grammar  : subset of C  (declarations, expressions,
 *             control flow, functions)
 *  Build    : see Makefile
 * ============================================================
 */

%{
#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* from lexer */
extern int  yylineno;
extern int  yylex(void);
extern FILE *yyin;

void yyerror(const char *msg);

static int  error_count = 0;
static int  syntax_ok   = 1;

/* the completed tree */
static ASTNode *parse_result = NULL;
%}

/* ── value union ─────────────────────────────────────────────*/
%union {
    char    *sval;    /* string value (identifier, literal)   */
    ASTNode *node;    /* AST node pointer                     */
}

/* ── token declarations ──────────────────────────────────────*/
%token <sval> IDENTIFIER
%token <sval> INT_LITERAL FLOAT_LITERAL STRING_LITERAL CHAR_LITERAL

%token KW_AUTO KW_BREAK KW_CASE KW_CHAR KW_CONST KW_CONTINUE
%token KW_DEFAULT KW_DO KW_DOUBLE KW_ELSE KW_ENUM KW_EXTERN
%token KW_FLOAT KW_FOR KW_GOTO KW_IF KW_INT KW_LONG
%token KW_REGISTER KW_RETURN KW_SHORT KW_SIGNED KW_SIZEOF
%token KW_STATIC KW_STRUCT KW_SWITCH KW_TYPEDEF KW_UNION
%token KW_UNSIGNED KW_VOID KW_VOLATILE KW_WHILE

%token OP_INC OP_DEC OP_ARROW OP_AND OP_OR
%token OP_EQ OP_NEQ OP_LEQ OP_GEQ OP_LSHIFT OP_RSHIFT
%token OP_PLUS_ASSIGN  OP_MINUS_ASSIGN OP_MUL_ASSIGN
%token OP_DIV_ASSIGN   OP_MOD_ASSIGN   OP_AND_ASSIGN
%token OP_XOR_ASSIGN   OP_OR_ASSIGN
%token OP_LSHIFT_ASSIGN OP_RSHIFT_ASSIGN
%token ELLIPSIS

/* ── non-terminal types ──────────────────────────────────────*/
%type <node> program
%type <node> translation_unit external_decl
%type <node> function_def
%type <node> declaration declaration_list
%type <node> declarator_init_list declarator_init
%type <node> type_specifier
%type <node> param_list param_decl
%type <node> compound_stmt statement_list statement
%type <node> expr_stmt if_stmt while_stmt do_stmt for_stmt
%type <node> return_stmt break_stmt continue_stmt
%type <node> expression assign_expr
%type <node> ternary_expr or_expr and_expr
%type <node> bitor_expr xor_expr bitand_expr
%type <node> eq_expr relat_expr shift_expr
%type <node> add_expr mul_expr cast_expr unary_expr
%type <node> postfix_expr primary_expr
%type <node> arg_list
%type <sval> assign_op type_name

/* ── precedence (lowest → highest) ─────────────────────────-*/
/* Bison resolves s/r conflicts by these declarations.
   We declare them for safety but the grammar is largely
   unambiguous. */
%right '=' OP_PLUS_ASSIGN OP_MINUS_ASSIGN OP_MUL_ASSIGN \
           OP_DIV_ASSIGN  OP_MOD_ASSIGN   OP_AND_ASSIGN \
           OP_XOR_ASSIGN  OP_OR_ASSIGN \
           OP_LSHIFT_ASSIGN OP_RSHIFT_ASSIGN
%right '?' ':'
%left  OP_OR
%left  OP_AND
%left  '|'
%left  '^'
%left  '&'
%left  OP_EQ OP_NEQ
%left  '<' '>' OP_LEQ OP_GEQ
%left  OP_LSHIFT OP_RSHIFT
%left  '+' '-'
%left  '*' '/' '%'
%right UNARY_PREC   /* placeholder for unary minus, !, ~ */
%right OP_INC OP_DEC
%left  '(' ')' '[' ']' '.' OP_ARROW

/* dangling-else resolved in favour of the nearest if */
%right KW_THEN KW_ELSE

%start program

%%

/* ══════════════════════════════════════════════════════════════
 *  TOP LEVEL
 * ══════════════════════════════════════════════════════════════*/
program
    : translation_unit
        {
            $$ = ast_new(NODE_PROGRAM, "program", yylineno);
            ast_add_child($$, $1);
            parse_result = $$;
        }
    ;

translation_unit
    : external_decl
        {
            $$ = $1;
        }
    | translation_unit external_decl
        {
            /* flatten into the parent caller via program rule;
               link siblings through a temporary list node */
            if ($1 && $1->kind == NODE_BLOCK) {
                ast_add_child($1, $2);
                $$ = $1;
            } else {
                $$ = ast_new(NODE_BLOCK, NULL, yylineno);
                ast_add_child($$, $1);
                ast_add_child($$, $2);
            }
        }
    ;

external_decl
    : function_def      { $$ = $1; }
    | declaration       { $$ = $1; }
    ;

/* ══════════════════════════════════════════════════════════════
 *  FUNCTION DEFINITION
 * ══════════════════════════════════════════════════════════════*/
function_def
    : type_specifier IDENTIFIER '(' param_list ')' compound_stmt
        {
            $$ = ast_new(NODE_FUNC_DEF, $2, yylineno);
            ast_add_child($$, $1);          /* return type   */
            ast_add_child($$, $4);          /* param list    */
            ast_add_child($$, $6);          /* body          */
            free($2);
        }
    | type_specifier IDENTIFIER '(' ')' compound_stmt
        {
            $$ = ast_new(NODE_FUNC_DEF, $2, yylineno);
            ast_add_child($$, $1);
            ast_add_child($$, ast_new(NODE_PARAM_LIST, "(empty)", yylineno));
            ast_add_child($$, $5);
            free($2);
        }
    | type_specifier '*' IDENTIFIER '(' param_list ')' compound_stmt
        {
            char buf[256];
            snprintf(buf, sizeof(buf), "*%s", $3);
            $$ = ast_new(NODE_FUNC_DEF, buf, yylineno);
            ast_add_child($$, $1);
            ast_add_child($$, $5);
            ast_add_child($$, $7);
            free($3);
        }
    | type_specifier '*' IDENTIFIER '(' ')' compound_stmt
        {
            char buf[256];
            snprintf(buf, sizeof(buf), "*%s", $3);
            $$ = ast_new(NODE_FUNC_DEF, buf, yylineno);
            ast_add_child($$, $1);
            ast_add_child($$, ast_new(NODE_PARAM_LIST, "(empty)", yylineno));
            ast_add_child($$, $6);
            free($3);
        }
    ;

/* ══════════════════════════════════════════════════════════════
 *  PARAMETERS
 * ══════════════════════════════════════════════════════════════*/
param_list
    : param_decl
        {
            $$ = ast_new(NODE_PARAM_LIST, NULL, yylineno);
            ast_add_child($$, $1);
        }
    | param_list ',' param_decl
        {
            ast_add_child($1, $3);
            $$ = $1;
        }
    | param_list ',' ELLIPSIS
        {
            ast_add_child($1, ast_new(NODE_PARAM, "...", yylineno));
            $$ = $1;
        }
    ;

param_decl
    : type_specifier IDENTIFIER
        {
            $$ = ast_new(NODE_PARAM, $2, yylineno);
            ast_add_child($$, $1);
            free($2);
        }
    | type_specifier '*' IDENTIFIER
        {
            char buf[256];
            snprintf(buf, sizeof(buf), "*%s", $3);
            $$ = ast_new(NODE_PARAM, buf, yylineno);
            ast_add_child($$, $1);
            free($3);
        }
    | type_specifier
        {
            $$ = ast_new(NODE_PARAM, "(unnamed)", yylineno);
            ast_add_child($$, $1);
        }
    ;

/* ══════════════════════════════════════════════════════════════
 *  TYPE SPECIFIERS
 * ══════════════════════════════════════════════════════════════*/
type_specifier
    : KW_INT             { $$ = ast_new(NODE_TYPE, "int",      yylineno); }
    | KW_CHAR            { $$ = ast_new(NODE_TYPE, "char",     yylineno); }
    | KW_FLOAT           { $$ = ast_new(NODE_TYPE, "float",    yylineno); }
    | KW_DOUBLE          { $$ = ast_new(NODE_TYPE, "double",   yylineno); }
    | KW_VOID            { $$ = ast_new(NODE_TYPE, "void",     yylineno); }
    | KW_LONG            { $$ = ast_new(NODE_TYPE, "long",     yylineno); }
    | KW_SHORT           { $$ = ast_new(NODE_TYPE, "short",    yylineno); }
    | KW_UNSIGNED        { $$ = ast_new(NODE_TYPE, "unsigned", yylineno); }
    | KW_SIGNED          { $$ = ast_new(NODE_TYPE, "signed",   yylineno); }
    | KW_STATIC KW_INT   { $$ = ast_new(NODE_TYPE, "static int",  yylineno); }
    | KW_CONST KW_INT    { $$ = ast_new(NODE_TYPE, "const int",   yylineno); }
    | KW_CONST KW_CHAR   { $$ = ast_new(NODE_TYPE, "const char",  yylineno); }
    | KW_UNSIGNED KW_INT { $$ = ast_new(NODE_TYPE, "unsigned int",yylineno); }
    | KW_LONG KW_INT     { $$ = ast_new(NODE_TYPE, "long int",    yylineno); }
    | KW_LONG KW_LONG    { $$ = ast_new(NODE_TYPE, "long long",   yylineno); }
    ;

type_name
    : KW_INT      { $$ = strdup("int");    }
    | KW_CHAR     { $$ = strdup("char");   }
    | KW_FLOAT    { $$ = strdup("float");  }
    | KW_DOUBLE   { $$ = strdup("double"); }
    | KW_VOID     { $$ = strdup("void");   }
    | KW_LONG     { $$ = strdup("long");   }
    | KW_SHORT    { $$ = strdup("short");  }
    ;

/* ══════════════════════════════════════════════════════════════
 *  DECLARATIONS
 * ══════════════════════════════════════════════════════════════*/
declaration
    : type_specifier declarator_init_list ';'
        {
            /* attach type to every child of the init list */
            $$ = $2;
            for (int i = 0; i < $2->child_count; i++) {
                ASTNode *copy = ast_new(NODE_TYPE,
                                        $1->value ? $1->value : "",
                                        $1->line);
                /* prepend type as first child of each declarator */
                /* We rebuild by inserting: shift children right */
                ASTNode *decl = $2->children[i];
                decl->child_count++;
                if (decl->child_count > decl->child_cap) {
                    decl->child_cap *= 2;
                    decl->children = (ASTNode **)realloc(decl->children,
                        decl->child_cap * sizeof(ASTNode *));
                }
                memmove(&decl->children[1], &decl->children[0],
                        (decl->child_count - 1) * sizeof(ASTNode *));
                decl->children[0] = copy;
            }
            ast_free($1);
        }
    ;

declarator_init_list
    : declarator_init
        {
            $$ = ast_new(NODE_BLOCK, "decl-list", yylineno);
            ast_add_child($$, $1);
        }
    | declarator_init_list ',' declarator_init
        {
            ast_add_child($1, $3);
            $$ = $1;
        }
    ;

declarator_init
    : IDENTIFIER
        {
            $$ = ast_new(NODE_DECL, $1, yylineno);
            free($1);
        }
    | '*' IDENTIFIER
        {
            char buf[256];
            snprintf(buf, sizeof(buf), "*%s", $2);
            $$ = ast_new(NODE_DECL, buf, yylineno);
            free($2);
        }
    | IDENTIFIER '[' expression ']'
        {
            char buf[256];
            snprintf(buf, sizeof(buf), "%s[]", $1);
            $$ = ast_new(NODE_DECL, buf, yylineno);
            ast_add_child($$, $3);
            free($1);
        }
    | IDENTIFIER '[' ']'
        {
            char buf[256];
            snprintf(buf, sizeof(buf), "%s[]", $1);
            $$ = ast_new(NODE_DECL, buf, yylineno);
            free($1);
        }
    | IDENTIFIER '=' expression
        {
            $$ = ast_new(NODE_DECL_INIT, $1, yylineno);
            ast_add_child($$, $3);
            free($1);
        }
    | '*' IDENTIFIER '=' expression
        {
            char buf[256];
            snprintf(buf, sizeof(buf), "*%s", $2);
            $$ = ast_new(NODE_DECL_INIT, buf, yylineno);
            ast_add_child($$, $4);
            free($2);
        }
    ;

declaration_list
    : declaration
        {
            $$ = $1;
        }
    | declaration_list declaration
        {
            if ($1->kind == NODE_BLOCK) {
                ast_add_child($1, $2);
                $$ = $1;
            } else {
                $$ = ast_new(NODE_BLOCK, "decls", yylineno);
                ast_add_child($$, $1);
                ast_add_child($$, $2);
            }
        }
    ;

/* ══════════════════════════════════════════════════════════════
 *  COMPOUND STATEMENT  { decls… stmts… }
 * ══════════════════════════════════════════════════════════════*/
compound_stmt
    : '{' '}'
        {
            $$ = ast_new(NODE_BLOCK, "(empty)", yylineno);
        }
    | '{' statement_list '}'
        {
            $$ = $2;
        }
    | '{' declaration_list '}'
        {
            $$ = ast_new(NODE_BLOCK, NULL, yylineno);
            ast_add_child($$, $2);
        }
    | '{' declaration_list statement_list '}'
        {
            $$ = ast_new(NODE_BLOCK, NULL, yylineno);
            ast_add_child($$, $2);
            ast_add_child($$, $3);
        }
    ;

statement_list
    : statement
        {
            $$ = ast_new(NODE_BLOCK, "stmts", yylineno);
            ast_add_child($$, $1);
        }
    | statement_list statement
        {
            ast_add_child($1, $2);
            $$ = $1;
        }
    ;

/* ══════════════════════════════════════════════════════════════
 *  STATEMENTS
 * ══════════════════════════════════════════════════════════════*/
statement
    : expr_stmt     { $$ = $1; }
    | if_stmt       { $$ = $1; }
    | while_stmt    { $$ = $1; }
    | do_stmt       { $$ = $1; }
    | for_stmt      { $$ = $1; }
    | return_stmt   { $$ = $1; }
    | break_stmt    { $$ = $1; }
    | continue_stmt { $$ = $1; }
    | compound_stmt { $$ = $1; }
    | declaration   { $$ = $1; }  /* C99: mixed decls/stmts */
    ;

expr_stmt
    : ';'
        {
            $$ = ast_new(NODE_BLOCK, "(empty-stmt)", yylineno);
        }
    | expression ';'
        {
            $$ = $1;
        }
    ;

if_stmt
    : KW_IF '(' expression ')' statement %prec KW_THEN
        {
            $$ = ast_new(NODE_IF, "if", yylineno);
            ast_add_child($$, $3);   /* condition */
            ast_add_child($$, $5);   /* then      */
        }
    | KW_IF '(' expression ')' statement KW_ELSE statement
        {
            $$ = ast_new(NODE_IF, "if-else", yylineno);
            ast_add_child($$, $3);   /* condition */
            ast_add_child($$, $5);   /* then      */
            ast_add_child($$, $7);   /* else      */
        }
    ;

while_stmt
    : KW_WHILE '(' expression ')' statement
        {
            $$ = ast_new(NODE_WHILE, "while", yylineno);
            ast_add_child($$, $3);   /* condition */
            ast_add_child($$, $5);   /* body      */
        }
    ;

do_stmt
    : KW_DO statement KW_WHILE '(' expression ')' ';'
        {
            $$ = ast_new(NODE_DO_WHILE, "do-while", yylineno);
            ast_add_child($$, $2);   /* body      */
            ast_add_child($$, $5);   /* condition */
        }
    ;

for_stmt
    : KW_FOR '(' expr_stmt expr_stmt ')' statement
        {
            $$ = ast_new(NODE_FOR, "for", yylineno);
            ast_add_child($$, $3);                              /* init   */
            ast_add_child($$, $4);                              /* cond   */
            ast_add_child($$, ast_new(NODE_BLOCK, "(no-update)", yylineno));
            ast_add_child($$, $6);                              /* body   */
        }
    | KW_FOR '(' expr_stmt expr_stmt expression ')' statement
        {
            $$ = ast_new(NODE_FOR, "for", yylineno);
            ast_add_child($$, $3);   /* init   */
            ast_add_child($$, $4);   /* cond   */
            ast_add_child($$, $5);   /* update */
            ast_add_child($$, $7);   /* body   */
        }
    | KW_FOR '(' declaration expr_stmt ')' statement
        {
            $$ = ast_new(NODE_FOR, "for(C99)", yylineno);
            ast_add_child($$, $3);
            ast_add_child($$, $4);
            ast_add_child($$, ast_new(NODE_BLOCK, "(no-update)", yylineno));
            ast_add_child($$, $6);
        }
    | KW_FOR '(' declaration expr_stmt expression ')' statement
        {
            $$ = ast_new(NODE_FOR, "for(C99)", yylineno);
            ast_add_child($$, $3);
            ast_add_child($$, $4);
            ast_add_child($$, $5);
            ast_add_child($$, $7);
        }
    ;

return_stmt
    : KW_RETURN ';'
        {
            $$ = ast_new(NODE_RETURN, "return", yylineno);
        }
    | KW_RETURN expression ';'
        {
            $$ = ast_new(NODE_RETURN, "return", yylineno);
            ast_add_child($$, $2);
        }
    ;

break_stmt
    : KW_BREAK ';'
        {
            $$ = ast_new(NODE_BREAK, "break", yylineno);
        }
    ;

continue_stmt
    : KW_CONTINUE ';'
        {
            $$ = ast_new(NODE_CONTINUE, "continue", yylineno);
        }
    ;

/* ══════════════════════════════════════════════════════════════
 *  EXPRESSIONS  (full C precedence hierarchy)
 * ══════════════════════════════════════════════════════════════*/
expression
    : assign_expr               { $$ = $1; }
    | expression ',' assign_expr
        {
            $$ = ast_new(NODE_BINOP, ",", yylineno);
            ast_add_child($$, $1);
            ast_add_child($$, $3);
        }
    ;

assign_expr
    : ternary_expr              { $$ = $1; }
    | unary_expr assign_op assign_expr
        {
            $$ = ast_new(NODE_ASSIGN, $2, yylineno);
            ast_add_child($$, $1);
            ast_add_child($$, $3);
            free($2);
        }
    ;

assign_op
    : '='               { $$ = strdup("=");   }
    | OP_PLUS_ASSIGN    { $$ = strdup("+=");  }
    | OP_MINUS_ASSIGN   { $$ = strdup("-=");  }
    | OP_MUL_ASSIGN     { $$ = strdup("*=");  }
    | OP_DIV_ASSIGN     { $$ = strdup("/=");  }
    | OP_MOD_ASSIGN     { $$ = strdup("%=");  }
    | OP_AND_ASSIGN     { $$ = strdup("&=");  }
    | OP_XOR_ASSIGN     { $$ = strdup("^=");  }
    | OP_OR_ASSIGN      { $$ = strdup("|=");  }
    | OP_LSHIFT_ASSIGN  { $$ = strdup("<<="); }
    | OP_RSHIFT_ASSIGN  { $$ = strdup(">>="); }
    ;

ternary_expr
    : or_expr           { $$ = $1; }
    | or_expr '?' expression ':' ternary_expr
        {
            $$ = ast_new(NODE_TERNARY, "?:", yylineno);
            ast_add_child($$, $1);
            ast_add_child($$, $3);
            ast_add_child($$, $5);
        }
    ;

or_expr
    : and_expr          { $$ = $1; }
    | or_expr OP_OR and_expr
        {
            $$ = ast_new(NODE_BINOP, "||", yylineno);
            ast_add_child($$, $1);
            ast_add_child($$, $3);
        }
    ;

and_expr
    : bitor_expr        { $$ = $1; }
    | and_expr OP_AND bitor_expr
        {
            $$ = ast_new(NODE_BINOP, "&&", yylineno);
            ast_add_child($$, $1);
            ast_add_child($$, $3);
        }
    ;

bitor_expr
    : xor_expr          { $$ = $1; }
    | bitor_expr '|' xor_expr
        {
            $$ = ast_new(NODE_BINOP, "|", yylineno);
            ast_add_child($$, $1);
            ast_add_child($$, $3);
        }
    ;

xor_expr
    : bitand_expr       { $$ = $1; }
    | xor_expr '^' bitand_expr
        {
            $$ = ast_new(NODE_BINOP, "^", yylineno);
            ast_add_child($$, $1);
            ast_add_child($$, $3);
        }
    ;

bitand_expr
    : eq_expr           { $$ = $1; }
    | bitand_expr '&' eq_expr
        {
            $$ = ast_new(NODE_BINOP, "&", yylineno);
            ast_add_child($$, $1);
            ast_add_child($$, $3);
        }
    ;

eq_expr
    : relat_expr        { $$ = $1; }
    | eq_expr OP_EQ  relat_expr
        {
            $$ = ast_new(NODE_BINOP, "==", yylineno);
            ast_add_child($$, $1);
            ast_add_child($$, $3);
        }
    | eq_expr OP_NEQ relat_expr
        {
            $$ = ast_new(NODE_BINOP, "!=", yylineno);
            ast_add_child($$, $1);
            ast_add_child($$, $3);
        }
    ;

relat_expr
    : shift_expr        { $$ = $1; }
    | relat_expr '<'    shift_expr
        {
            $$ = ast_new(NODE_BINOP, "<",  yylineno);
            ast_add_child($$, $1); ast_add_child($$, $3);
        }
    | relat_expr '>'    shift_expr
        {
            $$ = ast_new(NODE_BINOP, ">",  yylineno);
            ast_add_child($$, $1); ast_add_child($$, $3);
        }
    | relat_expr OP_LEQ shift_expr
        {
            $$ = ast_new(NODE_BINOP, "<=", yylineno);
            ast_add_child($$, $1); ast_add_child($$, $3);
        }
    | relat_expr OP_GEQ shift_expr
        {
            $$ = ast_new(NODE_BINOP, ">=", yylineno);
            ast_add_child($$, $1); ast_add_child($$, $3);
        }
    ;

shift_expr
    : add_expr          { $$ = $1; }
    | shift_expr OP_LSHIFT add_expr
        {
            $$ = ast_new(NODE_BINOP, "<<", yylineno);
            ast_add_child($$, $1); ast_add_child($$, $3);
        }
    | shift_expr OP_RSHIFT add_expr
        {
            $$ = ast_new(NODE_BINOP, ">>", yylineno);
            ast_add_child($$, $1); ast_add_child($$, $3);
        }
    ;

add_expr
    : mul_expr          { $$ = $1; }
    | add_expr '+' mul_expr
        {
            $$ = ast_new(NODE_BINOP, "+", yylineno);
            ast_add_child($$, $1); ast_add_child($$, $3);
        }
    | add_expr '-' mul_expr
        {
            $$ = ast_new(NODE_BINOP, "-", yylineno);
            ast_add_child($$, $1); ast_add_child($$, $3);
        }
    ;

mul_expr
    : cast_expr         { $$ = $1; }
    | mul_expr '*' cast_expr
        {
            $$ = ast_new(NODE_BINOP, "*", yylineno);
            ast_add_child($$, $1); ast_add_child($$, $3);
        }
    | mul_expr '/' cast_expr
        {
            $$ = ast_new(NODE_BINOP, "/", yylineno);
            ast_add_child($$, $1); ast_add_child($$, $3);
        }
    | mul_expr '%' cast_expr
        {
            $$ = ast_new(NODE_BINOP, "%", yylineno);
            ast_add_child($$, $1); ast_add_child($$, $3);
        }
    ;

cast_expr
    : unary_expr                { $$ = $1; }
    | '(' type_name ')' cast_expr
        {
            $$ = ast_new(NODE_CAST, $2, yylineno);
            ast_add_child($$, $4);
            free($2);
        }
    ;

unary_expr
    : postfix_expr              { $$ = $1; }
    | OP_INC unary_expr
        {
            $$ = ast_new(NODE_UNOP, "pre++", yylineno);
            ast_add_child($$, $2);
        }
    | OP_DEC unary_expr
        {
            $$ = ast_new(NODE_UNOP, "pre--", yylineno);
            ast_add_child($$, $2);
        }
    | '&' cast_expr %prec UNARY_PREC
        {
            $$ = ast_new(NODE_UNOP, "addr-of", yylineno);
            ast_add_child($$, $2);
        }
    | '*' cast_expr %prec UNARY_PREC
        {
            $$ = ast_new(NODE_UNOP, "deref", yylineno);
            ast_add_child($$, $2);
        }
    | '+' cast_expr %prec UNARY_PREC
        {
            $$ = ast_new(NODE_UNOP, "unary+", yylineno);
            ast_add_child($$, $2);
        }
    | '-' cast_expr %prec UNARY_PREC
        {
            $$ = ast_new(NODE_UNOP, "unary-", yylineno);
            ast_add_child($$, $2);
        }
    | '~' cast_expr %prec UNARY_PREC
        {
            $$ = ast_new(NODE_UNOP, "~", yylineno);
            ast_add_child($$, $2);
        }
    | '!' cast_expr %prec UNARY_PREC
        {
            $$ = ast_new(NODE_UNOP, "!", yylineno);
            ast_add_child($$, $2);
        }
    | KW_SIZEOF '(' type_name ')'
        {
            $$ = ast_new(NODE_UNOP, "sizeof", yylineno);
            ast_add_child($$, ast_new(NODE_TYPE, $3, yylineno));
            free($3);
        }
    | KW_SIZEOF unary_expr
        {
            $$ = ast_new(NODE_UNOP, "sizeof", yylineno);
            ast_add_child($$, $2);
        }
    ;

postfix_expr
    : primary_expr              { $$ = $1; }
    | postfix_expr '[' expression ']'
        {
            $$ = ast_new(NODE_INDEX, "[]", yylineno);
            ast_add_child($$, $1);
            ast_add_child($$, $3);
        }
    | postfix_expr '(' ')'
        {
            $$ = ast_new(NODE_CALL, "call", yylineno);
            ast_add_child($$, $1);
        }
    | postfix_expr '(' arg_list ')'
        {
            $$ = ast_new(NODE_CALL, "call", yylineno);
            ast_add_child($$, $1);
            ast_add_child($$, $3);
        }
    | postfix_expr '.' IDENTIFIER
        {
            $$ = ast_new(NODE_MEMBER, $3, yylineno);
            ast_add_child($$, $1);
            free($3);
        }
    | postfix_expr OP_ARROW IDENTIFIER
        {
            char buf[256];
            snprintf(buf, sizeof(buf), "->%s", $3);
            $$ = ast_new(NODE_MEMBER, buf, yylineno);
            ast_add_child($$, $1);
            free($3);
        }
    | postfix_expr OP_INC
        {
            $$ = ast_new(NODE_UNOP, "post++", yylineno);
            ast_add_child($$, $1);
        }
    | postfix_expr OP_DEC
        {
            $$ = ast_new(NODE_UNOP, "post--", yylineno);
            ast_add_child($$, $1);
        }
    ;

arg_list
    : assign_expr
        {
            $$ = ast_new(NODE_ARG_LIST, NULL, yylineno);
            ast_add_child($$, $1);
        }
    | arg_list ',' assign_expr
        {
            ast_add_child($1, $3);
            $$ = $1;
        }
    ;

primary_expr
    : IDENTIFIER
        {
            $$ = ast_new(NODE_IDENT, $1, yylineno);
            free($1);
        }
    | INT_LITERAL
        {
            $$ = ast_new(NODE_INT_LIT, $1, yylineno);
            free($1);
        }
    | FLOAT_LITERAL
        {
            $$ = ast_new(NODE_FLOAT_LIT, $1, yylineno);
            free($1);
        }
    | STRING_LITERAL
        {
            $$ = ast_new(NODE_STRING_LIT, $1, yylineno);
            free($1);
        }
    | CHAR_LITERAL
        {
            $$ = ast_new(NODE_CHAR_LIT, $1, yylineno);
            free($1);
        }
    | '(' expression ')'
        {
            $$ = $2;   /* transparent grouping */
        }
    ;

%%

/* ── error handler ───────────────────────────────────────────*/
void yyerror(const char *msg)
{
    fprintf(stderr,
        "\033[1;31m  SYNTAX ERROR [line %d]: %s\033[0m\n",
        yylineno, msg);
    error_count++;
    syntax_ok = 0;
}

/* ── print_banner ────────────────────────────────────────────*/
static void print_banner(const char *filename)
{
    printf("\n");
    printf("  ╔══════════════════════════════════════════════════════╗\n");
    printf("  ║     PARSER + AST GENERATOR  —  Phase 2 Output       ║\n");
    printf("  ║  File : %-44s║\n", filename);
    printf("  ╚══════════════════════════════════════════════════════╝\n");
}

/* ── main ────────────────────────────────────────────────────*/
int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr,
            "\n  Usage: %s <source_file.c>\n\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        fprintf(stderr,
            "\n  Error: Cannot open file '%s'\n\n", argv[1]);
        return EXIT_FAILURE;
    }

    print_banner(argv[1]);
    yyin = fp;
    yyparse();
    fclose(fp);

    printf("\n");
    printf("  ─────────────────────────────────────────────────────\n");
    printf("  Syntax errors : %d\n", error_count);

    if (syntax_ok && parse_result) {
        printf("  ✔  Syntax analysis passed.\n");
        printf("  ─────────────────────────────────────────────────────\n");
        printf("\n  Abstract Syntax Tree:\n");
        ast_print(parse_result);
    } else if (!syntax_ok) {
        printf("  ✘  Syntax analysis failed — AST not generated.\n");
        printf("  ─────────────────────────────────────────────────────\n\n");
    }

    if (parse_result) ast_free(parse_result);
    return syntax_ok ? EXIT_SUCCESS : EXIT_FAILURE;
}
