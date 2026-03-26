%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char name[20];
    struct node *left, *right;
} node;

node* createNode(char *name, node *l, node *r) {
    node *n = malloc(sizeof(node));
    strcpy(n->name, name);
    n->left = l;
    n->right = r;
    return n;
}

void printTree(node *t, int level) {
    if (!t) return;
    for(int i=0;i<level;i++) printf("  ");
    printf("%s\n", t->name);
    printTree(t->left, level+1);
    printTree(t->right, level+1);
}

void yyerror(const char *s);
int yylex();
%}

%union {
    char *str;
    struct node *nd;
}

%token <str> ID NUM STRING
%token INT FLOAT CHAR IF ELSE WHILE FOR RETURN
%token RELOP AND OR

%type <nd> program stmt block expr decl assign cond

%%

program:
      program stmt
    | stmt
;

stmt:
      decl ';'           { printTree($1,0); }
    | assign ';'         { printTree($1,0); }
    | block
    | IF '(' cond ')' stmt
    | IF '(' cond ')' stmt ELSE stmt
    | WHILE '(' cond ')' stmt
    | FOR '(' assign ';' cond ';' assign ')' stmt
    | RETURN expr ';'
;

block:
    '{' program '}'
;

decl:
      INT ID             { $$ = createNode("DECL", createNode($2,NULL,NULL), NULL); }
    | INT ID '=' expr    { $$ = createNode("DECL_ASSIGN", createNode($2,NULL,NULL), $4); }
;

assign:
    ID '=' expr {
        $$ = createNode("ASSIGN", createNode($1,NULL,NULL), $3);
    }
;

cond:
    expr RELOP expr {
        $$ = createNode("COND", $1, $3);
    }
;

expr:
      expr '+' expr { $$ = createNode("+",$1,$3); }
    | expr '-' expr { $$ = createNode("-",$1,$3); }
    | expr '*' expr { $$ = createNode("*",$1,$3); }
    | expr '/' expr { $$ = createNode("/",$1,$3); }
    | expr AND expr { $$ = createNode("AND",$1,$3); }
    | expr OR expr  { $$ = createNode("OR",$1,$3); }
    | NUM           { $$ = createNode($1,NULL,NULL); }
    | ID            { $$ = createNode($1,NULL,NULL); }
    | '(' expr ')'  { $$ = $2; }
;

%%

void yyerror(const char *s) {
    printf("Syntax Error: %s\n", s);
}

int main() {
    printf("---- ADVANCED PARSER ----\n\n");
    yyparse();
    return 0;
}