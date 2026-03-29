/*
 * ============================================================
 *  parser.y  —  Phase 2 + Phase 3
 *  Parser + AST Builder + Semantic Analyser
 *  Compiler Design Project | GEU
 *  Build: see Makefile
 * ============================================================
 */

%{
#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int  yylineno;
extern int  yylex(void);
extern FILE *yyin;

void yyerror(const char *msg);

static int      syn_errors  = 0;
static int      syn_ok      = 1;
static ASTNode *parse_root  = NULL;
%}

/* ── value union ─────────────────────────────────────────────*/
%union {
    char    *sval;
    ASTNode *node;
}

/* ── tokens ──────────────────────────────────────────────────*/
%token <sval> IDENTIFIER INT_LITERAL FLOAT_LITERAL
%token <sval> STRING_LITERAL CHAR_LITERAL

%token KW_AUTO KW_BREAK KW_CASE KW_CHAR KW_CONST KW_CONTINUE
%token KW_DEFAULT KW_DO KW_DOUBLE KW_ELSE KW_ENUM KW_EXTERN
%token KW_FLOAT KW_FOR KW_IF KW_INT KW_LONG KW_RETURN
%token KW_SHORT KW_SIGNED KW_SIZEOF KW_STATIC KW_STRUCT
%token KW_SWITCH KW_TYPEDEF KW_UNION KW_UNSIGNED KW_VOID
%token KW_VOLATILE KW_WHILE

%token OP_INC OP_DEC OP_ARROW OP_AND OP_OR
%token OP_EQ OP_NEQ OP_LEQ OP_GEQ OP_LSHIFT OP_RSHIFT
%token OP_PLUS_A OP_MINUS_A OP_MUL_A OP_DIV_A OP_MOD_A
%token OP_AND_A  OP_XOR_A   OP_OR_A
%token OP_LSHIFT_A OP_RSHIFT_A
%token ELLIPSIS

/* ── non-terminal types ──────────────────────────────────────*/
%type <node> program
%type <node> ext_decl_list ext_decl
%type <node> func_def
%type <node> param_list param_decl
%type <node> compound stmt stmt_list
%type <node> declaration decl_list decl_item
%type <node> statement expr_stmt if_stmt while_stmt
%type <node> do_stmt for_stmt return_stmt
%type <node> expression assign_expr ternary_expr
%type <node> or_expr and_expr bitor_expr xor_expr bitand_expr
%type <node> eq_expr relat_expr shift_expr add_expr mul_expr
%type <node> cast_expr unary_expr postfix_expr primary_expr
%type <node> arg_list
%type <sval> type_spec type_name assign_op

/* ── precedence ──────────────────────────────────────────────*/
%right '=' OP_PLUS_A OP_MINUS_A OP_MUL_A OP_DIV_A OP_MOD_A
%right OP_AND_A OP_XOR_A OP_OR_A OP_LSHIFT_A OP_RSHIFT_A

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
%right UPREC
%left  OP_INC OP_DEC '(' ')' '[' ']' '.' OP_ARROW

%right KW_THEN KW_ELSE

%start program

%%

/* ── TOP LEVEL ───────────────────────────────────────────────*/
program
    : ext_decl_list
        {
            $$ = ast_new(N_PROGRAM,"program",yylineno);
            ast_add($$,$1);
            parse_root = $$;
        }
    ;

ext_decl_list
    : ext_decl              { $$ = $1; }
    | ext_decl_list ext_decl
        {
            if ($1 && $1->kind == N_BLOCK) {
                ast_add($1,$2); $$ = $1;
            } else {
                $$ = ast_new(N_BLOCK,NULL,yylineno);
                ast_add($$,$1); ast_add($$,$2);
            }
        }
    ;

ext_decl
    : func_def      { $$ = $1; }
    | declaration   { $$ = $1; }
    ;

/* ── FUNCTION ────────────────────────────────────────────────*/
func_def
    : type_spec IDENTIFIER '(' param_list ')' compound
        {
            $$ = ast_new(N_FUNC_DEF,$2,yylineno);
            ast_add($$, ast_new(N_TYPE,$1,yylineno));
            ast_add($$, $4);
            ast_add($$, $6);
            free($1); free($2);
        }
    | type_spec IDENTIFIER '(' ')' compound
        {
            $$ = ast_new(N_FUNC_DEF,$2,yylineno);
            ast_add($$, ast_new(N_TYPE,$1,yylineno));
            ast_add($$, ast_new(N_PARAM_LIST,"(empty)",yylineno));
            ast_add($$, $5);
            free($1); free($2);
        }
    | type_spec '*' IDENTIFIER '(' param_list ')' compound
        {
            char buf[128]; snprintf(buf,sizeof(buf),"*%s",$3);
            $$ = ast_new(N_FUNC_DEF,buf,yylineno);
            ast_add($$, ast_new(N_TYPE,$1,yylineno));
            ast_add($$, $5);
            ast_add($$, $7);
            free($1); free($3);
        }
    | type_spec '*' IDENTIFIER '(' ')' compound
        {
            char buf[128]; snprintf(buf,sizeof(buf),"*%s",$3);
            $$ = ast_new(N_FUNC_DEF,buf,yylineno);
            ast_add($$, ast_new(N_TYPE,$1,yylineno));
            ast_add($$, ast_new(N_PARAM_LIST,"(empty)",yylineno));
            ast_add($$, $6);
            free($1); free($3);
        }
    ;

/* ── PARAMETERS ─────────────────────────────────────────────*/
param_list
    : param_decl
        { $$ = ast_new(N_PARAM_LIST,NULL,yylineno); ast_add($$,$1); }
    | param_list ',' param_decl
        { ast_add($1,$3); $$=$1; }
    | param_list ',' ELLIPSIS
        { ast_add($1,ast_new(N_PARAM,"...",yylineno)); $$=$1; }
    ;

param_decl
    : type_spec IDENTIFIER
        {
            $$ = ast_new(N_PARAM,$2,yylineno);
            ast_add($$, ast_new(N_TYPE,$1,yylineno));
            free($1); free($2);
        }
    | type_spec '*' IDENTIFIER
        {
            char buf[128]; snprintf(buf,sizeof(buf),"*%s",$3);
            $$ = ast_new(N_PARAM,buf,yylineno);
            ast_add($$, ast_new(N_TYPE,$1,yylineno));
            free($1); free($3);
        }
    | type_spec
        {
            $$ = ast_new(N_PARAM,"(unnamed)",yylineno);
            ast_add($$, ast_new(N_TYPE,$1,yylineno));
            free($1);
        }
    ;

/* ── TYPE SPECIFIERS ─────────────────────────────────────────*/
type_spec
    : KW_INT             { $$ = strdup("int");          }
    | KW_CHAR            { $$ = strdup("char");         }
    | KW_FLOAT           { $$ = strdup("float");        }
    | KW_DOUBLE          { $$ = strdup("double");       }
    | KW_VOID            { $$ = strdup("void");         }
    | KW_LONG            { $$ = strdup("long");         }
    | KW_SHORT           { $$ = strdup("short");        }
    | KW_UNSIGNED        { $$ = strdup("unsigned");     }
    | KW_SIGNED          { $$ = strdup("signed");       }
    | KW_STATIC KW_INT   { $$ = strdup("static int");   }
    | KW_CONST KW_INT    { $$ = strdup("const int");    }
    | KW_CONST KW_CHAR   { $$ = strdup("const char");   }
    | KW_UNSIGNED KW_INT { $$ = strdup("unsigned int"); }
    | KW_LONG KW_INT     { $$ = strdup("long int");     }
    | KW_LONG KW_LONG    { $$ = strdup("long long");    }
    ;

type_name
    : KW_INT    { $$ = strdup("int");    }
    | KW_CHAR   { $$ = strdup("char");   }
    | KW_FLOAT  { $$ = strdup("float");  }
    | KW_DOUBLE { $$ = strdup("double"); }
    | KW_VOID   { $$ = strdup("void");   }
    | KW_LONG   { $$ = strdup("long");   }
    | KW_SHORT  { $$ = strdup("short");  }
    ;

/* ── COMPOUND STATEMENT ─────────────────────────────────────*/
compound
    : '{' '}'           { $$ = ast_new(N_BLOCK,"(empty)",yylineno); }
    | '{' stmt_list '}' { $$ = $2; }
    ;

stmt_list
    : stmt              { $$ = ast_new(N_BLOCK,NULL,yylineno); ast_add($$,$1); }
    | stmt_list stmt    { ast_add($1,$2); $$=$1; }
    ;

/* ── DECLARATIONS ────────────────────────────────────────────*/
declaration
    : type_spec decl_list ';'
        {
            $$ = $2;
            /* attach type to every declarator */
            for (int i=0;i<$2->nchildren;i++) {
                ASTNode *d = $2->children[i];
                ASTNode *tc = ast_new(N_TYPE,$1,d->line);
                d->nchildren++;
                if (d->nchildren > d->cap) {
                    d->cap *= 2;
                    d->children = (ASTNode**)realloc(d->children,
                                      d->cap*sizeof(ASTNode*));
                }
                memmove(&d->children[1],&d->children[0],
                        (d->nchildren-1)*sizeof(ASTNode*));
                d->children[0] = tc;
            }
            free($1);
        }
    ;

decl_list
    : decl_item
        { $$ = ast_new(N_BLOCK,"decl-list",yylineno); ast_add($$,$1); }
    | decl_list ',' decl_item
        { ast_add($1,$3); $$=$1; }
    ;

decl_item
    : IDENTIFIER
        { $$ = ast_new(N_DECL,$1,yylineno); free($1); }
    | '*' IDENTIFIER
        {
            char buf[128]; snprintf(buf,sizeof(buf),"*%s",$2);
            $$ = ast_new(N_DECL,buf,yylineno); free($2);
        }
    | IDENTIFIER '[' expression ']'
        {
            char buf[128]; snprintf(buf,sizeof(buf),"%s[]",$1);
            $$ = ast_new(N_ARRAY_DECL,buf,yylineno);
            ast_add($$,$3);
            free($1);
        }
    | IDENTIFIER '[' INT_LITERAL ']'
        {
            char buf[128]; snprintf(buf,sizeof(buf),"%s",$1);
            $$ = ast_new(N_ARRAY_DECL,buf,yylineno);
            ast_add($$, ast_new(N_INT_LIT,$3,yylineno));
            free($1); free($3);
        }
    | IDENTIFIER '[' ']'
        {
            char buf[128]; snprintf(buf,sizeof(buf),"%s[]",$1);
            $$ = ast_new(N_ARRAY_DECL,buf,yylineno); free($1);
        }
    | IDENTIFIER '=' expression
        {
            $$ = ast_new(N_DECL_INIT,$1,yylineno);
            ast_add($$,$3); free($1);
        }
    | '*' IDENTIFIER '=' expression
        {
            char buf[128]; snprintf(buf,sizeof(buf),"*%s",$2);
            $$ = ast_new(N_DECL_INIT,buf,yylineno);
            ast_add($$,$4); free($2);
        }
    ;

/* ── STATEMENTS ──────────────────────────────────────────────*/
stmt
    : statement     { $$ = $1; }
    | declaration   { $$ = $1; }
    | compound      { $$ = $1; }
    ;

statement
    : expr_stmt     { $$ = $1; }
    | if_stmt       { $$ = $1; }
    | while_stmt    { $$ = $1; }
    | do_stmt       { $$ = $1; }
    | for_stmt      { $$ = $1; }
    | return_stmt   { $$ = $1; }
    | KW_BREAK ';'    { $$ = ast_new(N_BREAK,"break",yylineno);    }
    | KW_CONTINUE ';' { $$ = ast_new(N_CONTINUE,"continue",yylineno); }
    ;

expr_stmt
    : ';'              { $$ = ast_new(N_EXPR_STMT,NULL,yylineno); }
    | expression ';'   { $$ = $1; }
    ;

if_stmt
    : KW_IF '(' expression ')' stmt %prec KW_THEN
        {
            $$ = ast_new(N_IF,"if",yylineno);
            ast_add($$,$3); ast_add($$,$5);
        }
    | KW_IF '(' expression ')' stmt KW_ELSE stmt
        {
            $$ = ast_new(N_IF,"if-else",yylineno);
            ast_add($$,$3); ast_add($$,$5); ast_add($$,$7);
        }
    ;

while_stmt
    : KW_WHILE '(' expression ')' stmt
        {
            $$ = ast_new(N_WHILE,"while",yylineno);
            ast_add($$,$3); ast_add($$,$5);
        }
    ;

do_stmt
    : KW_DO stmt KW_WHILE '(' expression ')' ';'
        {
            $$ = ast_new(N_DO_WHILE,"do-while",yylineno);
            ast_add($$,$2); ast_add($$,$5);
        }
    ;

for_stmt
    : KW_FOR '(' expr_stmt expr_stmt ')' stmt
        {
            $$ = ast_new(N_FOR,"for",yylineno);
            ast_add($$,$3); ast_add($$,$4);
            ast_add($$,ast_new(N_EXPR_STMT,NULL,yylineno));
            ast_add($$,$6);
        }
    | KW_FOR '(' expr_stmt expr_stmt expression ')' stmt
        {
            $$ = ast_new(N_FOR,"for",yylineno);
            ast_add($$,$3); ast_add($$,$4); ast_add($$,$5); ast_add($$,$7);
        }
    | KW_FOR '(' declaration expr_stmt ')' stmt
        {
            $$ = ast_new(N_FOR,"for(C99)",yylineno);
            ast_add($$,$3); ast_add($$,$4);
            ast_add($$,ast_new(N_EXPR_STMT,NULL,yylineno));
            ast_add($$,$6);
        }
    | KW_FOR '(' declaration expr_stmt expression ')' stmt
        {
            $$ = ast_new(N_FOR,"for(C99)",yylineno);
            ast_add($$,$3); ast_add($$,$4); ast_add($$,$5); ast_add($$,$7);
        }
    ;

return_stmt
    : KW_RETURN ';'            { $$ = ast_new(N_RETURN,"return",yylineno); }
    | KW_RETURN expression ';'
        {
            $$ = ast_new(N_RETURN,"return",yylineno);
            ast_add($$,$2);
        }
    ;

/* ── EXPRESSIONS ─────────────────────────────────────────────*/
expression
    : assign_expr           { $$ = $1; }
    | expression ',' assign_expr
        {
            $$ = ast_new(N_BINOP,",",yylineno);
            ast_add($$,$1); ast_add($$,$3);
        }
    ;

assign_expr
    : ternary_expr          { $$ = $1; }
    | unary_expr assign_op assign_expr
        {
            $$ = ast_new(N_ASSIGN,$2,yylineno);
            ast_add($$,$1); ast_add($$,$3);
            free($2);
        }
    ;

assign_op
    : '='         { $$ = strdup("=");   }
    | OP_PLUS_A   { $$ = strdup("+=");  }
    | OP_MINUS_A  { $$ = strdup("-=");  }
    | OP_MUL_A    { $$ = strdup("*=");  }
    | OP_DIV_A    { $$ = strdup("/=");  }
    | OP_MOD_A    { $$ = strdup("%=");  }
    | OP_AND_A    { $$ = strdup("&=");  }
    | OP_XOR_A    { $$ = strdup("^=");  }
    | OP_OR_A     { $$ = strdup("|=");  }
    | OP_LSHIFT_A { $$ = strdup("<<="); }
    | OP_RSHIFT_A { $$ = strdup(">>="); }
    ;

ternary_expr
    : or_expr               { $$ = $1; }
    | or_expr '?' expression ':' ternary_expr
        {
            $$ = ast_new(N_TERNARY,"?:",yylineno);
            ast_add($$,$1); ast_add($$,$3); ast_add($$,$5);
        }
    ;

or_expr
    : and_expr              { $$ = $1; }
    | or_expr OP_OR and_expr
        { $$ = ast_new(N_BINOP,"||",yylineno); ast_add($$,$1); ast_add($$,$3); }
    ;

and_expr
    : bitor_expr            { $$ = $1; }
    | and_expr OP_AND bitor_expr
        { $$ = ast_new(N_BINOP,"&&",yylineno); ast_add($$,$1); ast_add($$,$3); }
    ;

bitor_expr
    : xor_expr              { $$ = $1; }
    | bitor_expr '|' xor_expr
        { $$ = ast_new(N_BINOP,"|",yylineno); ast_add($$,$1); ast_add($$,$3); }
    ;

xor_expr
    : bitand_expr           { $$ = $1; }
    | xor_expr '^' bitand_expr
        { $$ = ast_new(N_BINOP,"^",yylineno); ast_add($$,$1); ast_add($$,$3); }
    ;

bitand_expr
    : eq_expr               { $$ = $1; }
    | bitand_expr '&' eq_expr
        { $$ = ast_new(N_BINOP,"&",yylineno); ast_add($$,$1); ast_add($$,$3); }
    ;

eq_expr
    : relat_expr            { $$ = $1; }
    | eq_expr OP_EQ  relat_expr
        { $$ = ast_new(N_BINOP,"==",yylineno); ast_add($$,$1); ast_add($$,$3); }
    | eq_expr OP_NEQ relat_expr
        { $$ = ast_new(N_BINOP,"!=",yylineno); ast_add($$,$1); ast_add($$,$3); }
    ;

relat_expr
    : shift_expr            { $$ = $1; }
    | relat_expr '<'   shift_expr
        { $$ = ast_new(N_BINOP,"<",yylineno);  ast_add($$,$1); ast_add($$,$3); }
    | relat_expr '>'   shift_expr
        { $$ = ast_new(N_BINOP,">",yylineno);  ast_add($$,$1); ast_add($$,$3); }
    | relat_expr OP_LEQ shift_expr
        { $$ = ast_new(N_BINOP,"<=",yylineno); ast_add($$,$1); ast_add($$,$3); }
    | relat_expr OP_GEQ shift_expr
        { $$ = ast_new(N_BINOP,">=",yylineno); ast_add($$,$1); ast_add($$,$3); }
    ;

shift_expr
    : add_expr              { $$ = $1; }
    | shift_expr OP_LSHIFT add_expr
        { $$ = ast_new(N_BINOP,"<<",yylineno); ast_add($$,$1); ast_add($$,$3); }
    | shift_expr OP_RSHIFT add_expr
        { $$ = ast_new(N_BINOP,">>",yylineno); ast_add($$,$1); ast_add($$,$3); }
    ;

add_expr
    : mul_expr              { $$ = $1; }
    | add_expr '+' mul_expr
        { $$ = ast_new(N_BINOP,"+",yylineno); ast_add($$,$1); ast_add($$,$3); }
    | add_expr '-' mul_expr
        { $$ = ast_new(N_BINOP,"-",yylineno); ast_add($$,$1); ast_add($$,$3); }
    ;

mul_expr
    : cast_expr             { $$ = $1; }
    | mul_expr '*' cast_expr
        { $$ = ast_new(N_BINOP,"*",yylineno); ast_add($$,$1); ast_add($$,$3); }
    | mul_expr '/' cast_expr
        { $$ = ast_new(N_BINOP,"/",yylineno); ast_add($$,$1); ast_add($$,$3); }
    | mul_expr '%' cast_expr
        { $$ = ast_new(N_BINOP,"%",yylineno); ast_add($$,$1); ast_add($$,$3); }
    ;

cast_expr
    : unary_expr            { $$ = $1; }
    | '(' type_name ')' cast_expr
        {
            $$ = ast_new(N_UNOP,$2,yylineno);
            ast_add($$,$4); free($2);
        }
    ;

unary_expr
    : postfix_expr          { $$ = $1; }
    | OP_INC unary_expr
        { $$ = ast_new(N_UNOP,"pre++",yylineno); ast_add($$,$2); }
    | OP_DEC unary_expr
        { $$ = ast_new(N_UNOP,"pre--",yylineno); ast_add($$,$2); }
    | '&' cast_expr %prec UPREC
        { $$ = ast_new(N_UNOP,"addr",yylineno); ast_add($$,$2); }
    | '*' cast_expr %prec UPREC
        { $$ = ast_new(N_UNOP,"deref",yylineno); ast_add($$,$2); }
    | '+' cast_expr %prec UPREC
        { $$ = ast_new(N_UNOP,"u+",yylineno); ast_add($$,$2); }
    | '-' cast_expr %prec UPREC
        { $$ = ast_new(N_UNOP,"u-",yylineno); ast_add($$,$2); }
    | '~' cast_expr %prec UPREC
        { $$ = ast_new(N_UNOP,"~",yylineno); ast_add($$,$2); }
    | '!' cast_expr %prec UPREC
        { $$ = ast_new(N_UNOP,"!",yylineno); ast_add($$,$2); }
    | KW_SIZEOF '(' type_name ')'
        {
            $$ = ast_new(N_UNOP,"sizeof",yylineno);
            ast_add($$, ast_new(N_TYPE,$3,yylineno)); free($3);
        }
    | KW_SIZEOF unary_expr
        { $$ = ast_new(N_UNOP,"sizeof",yylineno); ast_add($$,$2); }
    ;

postfix_expr
    : primary_expr          { $$ = $1; }
    | postfix_expr '[' expression ']'
        {
            $$ = ast_new(N_INDEX,"[]",yylineno);
            ast_add($$,$1); ast_add($$,$3);
        }
    | postfix_expr '(' ')'
        {
            $$ = ast_new(N_CALL,"call",yylineno);
            ast_add($$,$1);
        }
    | postfix_expr '(' arg_list ')'
        {
            $$ = ast_new(N_CALL,"call",yylineno);
            ast_add($$,$1); ast_add($$,$3);
        }
    | postfix_expr '.' IDENTIFIER
        {
            $$ = ast_new(N_UNOP,$3,yylineno);
            ast_add($$,$1); free($3);
        }
    | postfix_expr OP_ARROW IDENTIFIER
        {
            char buf[128]; snprintf(buf,sizeof(buf),"->%s",$3);
            $$ = ast_new(N_UNOP,buf,yylineno);
            ast_add($$,$1); free($3);
        }
    | postfix_expr OP_INC
        { $$ = ast_new(N_UNOP,"post++",yylineno); ast_add($$,$1); }
    | postfix_expr OP_DEC
        { $$ = ast_new(N_UNOP,"post--",yylineno); ast_add($$,$1); }
    ;

arg_list
    : assign_expr
        { $$ = ast_new(N_ARG_LIST,NULL,yylineno); ast_add($$,$1); }
    | arg_list ',' assign_expr
        { ast_add($1,$3); $$=$1; }
    ;

primary_expr
    : IDENTIFIER
        { $$ = ast_new(N_IDENT,$1,yylineno); free($1); }
    | INT_LITERAL
        { $$ = ast_new(N_INT_LIT,$1,yylineno); free($1); }
    | FLOAT_LITERAL
        { $$ = ast_new(N_FLOAT_LIT,$1,yylineno); free($1); }
    | STRING_LITERAL
        { $$ = ast_new(N_STRING_LIT,$1,yylineno); free($1); }
    | CHAR_LITERAL
        { $$ = ast_new(N_CHAR_LIT,$1,yylineno); free($1); }
    | '(' expression ')'
        { $$ = $2; }
    ;

%%

/* ── error handler ───────────────────────────────────────────*/
void yyerror(const char *msg)
{
    fprintf(stderr,
        C_RED "  [SYNTAX ERROR] line %d: %s\n" C_RESET, yylineno, msg);
    syn_errors++;
    syn_ok = 0;
}

/* ── banner ──────────────────────────────────────────────────*/
static void banner(const char *file)
{
    printf("\n");
    printf(C_BOLD "  ╔══════════════════════════════════════════════════════════╗\n" C_RESET);
    printf(C_BOLD "  ║    PHASE 2 + 3 — PARSER · AST · SEMANTIC ANALYSER      ║\n" C_RESET);
    printf(C_BOLD "  ║    Compiler Design Project | GEU                       ║\n" C_RESET);
    printf(C_BOLD "  ╚══════════════════════════════════════════════════════════╝\n" C_RESET);
    printf(C_GRAY "  File: %s\n" C_RESET, file);
}

/* ── section header ──────────────────────────────────────────*/
static void section(const char *title)
{
    printf("\n" C_BOLD C_CYAN
           "  ══════════════════════════════════════════════════════════\n"
           "  %s\n"
           "  ══════════════════════════════════════════════════════════\n"
           C_RESET, title);
}

/* ── main ────────────────────────────────────────────────────*/
int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr,"\n  Usage: %s <file.c>\n\n",argv[0]);
        return 1;
    }
    FILE *fp = fopen(argv[1],"r");
    if (!fp) {
        fprintf(stderr,"\n  Cannot open '%s'\n\n",argv[1]);
        return 1;
    }

    banner(argv[1]);

    /* ── PHASE 2: Parse ────────────────────────────────────── */
    section("PHASE 2 — SYNTAX ANALYSIS");
    yyin = fp;
    yyparse();
    fclose(fp);

    printf("\n  Syntax errors: %s%d%s\n",
           syn_errors>0 ? C_RED : C_GREEN,
           syn_errors, C_RESET);

    if (!syn_ok || !parse_root) {
        printf(C_RED "\n  Cannot proceed — fix syntax errors first.\n\n" C_RESET);
        return 1;
    }
    printf(C_GREEN "  ✔  Syntax analysis PASSED.\n" C_RESET);

    /* ── AST ───────────────────────────────────────────────── */
    section("ABSTRACT SYNTAX TREE (AST)");
    ast_print(parse_root);

    /* ── PHASE 3: Semantic Analysis ────────────────────────── */
    section("PHASE 3 — SEMANTIC ANALYSIS");

    SemCtx ctx;
    sem_init(&ctx);
    sem_walk(&ctx, parse_root);

    /* Symbol table */
    sym_print(&ctx.sym);

    /* Issues */
    printf("\n" C_BOLD C_BLUE "  Semantic Issues Found\n" C_RESET);
    printf(C_GRAY "  ─────────────────────────────────────────────────────────────\n" C_RESET);
    issue_print(&ctx.issues);
    printf(C_GRAY "  ─────────────────────────────────────────────────────────────\n" C_RESET);

    /* Summary */
    printf("\n" C_BOLD "  ANALYSIS SUMMARY\n" C_RESET);
    printf("  Syntax errors   : %s%d%s\n",
           syn_errors   ? C_RED : C_GREEN, syn_errors,          C_RESET);
    printf("  Semantic errors : %s%d%s\n",
           ctx.issues.errors   ? C_RED : C_GREEN, ctx.issues.errors,   C_RESET);
    printf("  Warnings        : %s%d%s\n",
           ctx.issues.warnings ? C_YELLOW : C_GREEN, ctx.issues.warnings, C_RESET);

    int total = syn_errors + ctx.issues.errors;
    printf("\n");
    if (total == 0 && ctx.issues.warnings == 0)
        printf(C_GREEN "  ✔  Program is semantically CLEAN — no issues found.\n\n" C_RESET);
    else if (total == 0)
        printf(C_YELLOW "  ⚠  Program parsed OK but has %d warning(s).\n\n" C_RESET,
               ctx.issues.warnings);
    else
        printf(C_RED "  ✘  Program has %d error(s) — fix them before compilation.\n\n" C_RESET,
               total);

    ast_free(parse_root);
    return (total > 0) ? 1 : 0;
}
