%{
#include <stdio.h>

int line = 1;
int tokens = 0;
int errors = 0;
FILE *yyin;

void print_token(const char *type, const char *val) {
    tokens++;
    printf("Line %d: %-12s %s\n", line, type, val);
}
%}

%option noyywrap

DIGIT   [0-9]
LETTER  [a-zA-Z_]

%%

"int"|"float"|"char"|"if"|"else"|"for"|"while"|"return" {
    print_token("KEYWORD", yytext);
}

{LETTER}({LETTER}|{DIGIT})* {
    print_token("IDENTIFIER", yytext);
}

{DIGIT}+ {
    print_token("NUMBER", yytext);
}

"=="|"!="|">="|"<=" {
    print_token("OPERATOR", yytext);
}

[+\-*/=<>] {
    print_token("OPERATOR", yytext);
}

[;(){}\[\],.] {
    print_token("SYMBOL", yytext);
}

\n { line++; }

[ \t\r]+ { }

. {
    printf("Line %d: ERROR %s\n", line, yytext);
    errors++;
}

%%

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s input.c\n", argv[0]);
        return 1;
    }

    yyin = fopen(argv[1], "r");
    yylex();

    printf("\nTokens: %d\nErrors: %d\n", tokens, errors);
    return 0;
}