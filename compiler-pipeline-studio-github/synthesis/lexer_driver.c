#include "ast.h"
#include "../build/parser.tab.h"
#include <stdio.h>
#include <stdlib.h>

extern FILE *yyin;
extern int yylex(void);
extern int yylineno;
extern char *yytext;
YYSTYPE yylval;

void yyerror(const char *msg) {
    fprintf(stderr, "LEXER ERROR (line %d): %s\n", yylineno, msg);
}

static const char *token_name(int tok) {
    switch (tok) {
        case IDENTIFIER: return "IDENTIFIER";
        case INT_LITERAL: return "INT_LITERAL";
        case FLOAT_LITERAL: return "FLOAT_LITERAL";
        case STRING_LITERAL: return "STRING_LITERAL";
        case CHAR_LITERAL: return "CHAR_LITERAL";
        case KW_AUTO: return "KW_AUTO";
        case KW_BREAK: return "KW_BREAK";
        case KW_CASE: return "KW_CASE";
        case KW_CHAR: return "KW_CHAR";
        case KW_CONST: return "KW_CONST";
        case KW_CONTINUE: return "KW_CONTINUE";
        case KW_DEFAULT: return "KW_DEFAULT";
        case KW_DO: return "KW_DO";
        case KW_DOUBLE: return "KW_DOUBLE";
        case KW_ELSE: return "KW_ELSE";
        case KW_ENUM: return "KW_ENUM";
        case KW_EXTERN: return "KW_EXTERN";
        case KW_FLOAT: return "KW_FLOAT";
        case KW_FOR: return "KW_FOR";
        case KW_IF: return "KW_IF";
        case KW_INT: return "KW_INT";
        case KW_LONG: return "KW_LONG";
        case KW_RETURN: return "KW_RETURN";
        case KW_SHORT: return "KW_SHORT";
        case KW_SIGNED: return "KW_SIGNED";
        case KW_SIZEOF: return "KW_SIZEOF";
        case KW_STATIC: return "KW_STATIC";
        case KW_STRUCT: return "KW_STRUCT";
        case KW_SWITCH: return "KW_SWITCH";
        case KW_TYPEDEF: return "KW_TYPEDEF";
        case KW_UNION: return "KW_UNION";
        case KW_UNSIGNED: return "KW_UNSIGNED";
        case KW_VOID: return "KW_VOID";
        case KW_VOLATILE: return "KW_VOLATILE";
        case KW_WHILE: return "KW_WHILE";
        case OP_INC: return "OP_INC";
        case OP_DEC: return "OP_DEC";
        case OP_ARROW: return "OP_ARROW";
        case OP_AND: return "OP_AND";
        case OP_OR: return "OP_OR";
        case OP_EQ: return "OP_EQ";
        case OP_NEQ: return "OP_NEQ";
        case OP_LEQ: return "OP_LEQ";
        case OP_GEQ: return "OP_GEQ";
        case OP_LSHIFT: return "OP_LSHIFT";
        case OP_RSHIFT: return "OP_RSHIFT";
        case OP_PLUS_A: return "OP_PLUS_A";
        case OP_MINUS_A: return "OP_MINUS_A";
        case OP_MUL_A: return "OP_MUL_A";
        case OP_DIV_A: return "OP_DIV_A";
        case OP_MOD_A: return "OP_MOD_A";
        case OP_AND_A: return "OP_AND_A";
        case OP_XOR_A: return "OP_XOR_A";
        case OP_OR_A: return "OP_OR_A";
        case OP_LSHIFT_A: return "OP_LSHIFT_A";
        case OP_RSHIFT_A: return "OP_RSHIFT_A";
        case ELLIPSIS: return "ELLIPSIS";
        default: return "SYMBOL";
    }
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file.c>\n", argv[0]);
        return 1;
    }

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        perror("Cannot open input file");
        return 1;
    }

    int tok;
    while ((tok = yylex()) != 0) {
        printf("%d\t%s\t%s\n", yylineno, token_name(tok), yytext);
    }

    fclose(yyin);
    return 0;
}
