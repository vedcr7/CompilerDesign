%{
/*
 * ============================================================
 *  PHASE 1 — Lexical Analyser
 *  Compiler Design Project | GEU
 *  Tool: Flex
 *  Build: flex lexer.l && gcc lex.yy.c -lfl -o lexer
 *  Run:   ./lexer input.c
 * ============================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ANSI colours */
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define RED     "\033[1;31m"
#define GREEN   "\033[0;32m"
#define YELLOW  "\033[0;33m"
#define BLUE    "\033[1;34m"
#define MAGENTA "\033[0;35m"
#define CYAN    "\033[0;36m"
#define GRAY    "\033[0;90m"
#define WHITE   "\033[0;37m"
#define LBLUE   "\033[0;94m"

int line_num    = 1;
int token_count = 0;
int error_count = 0;

/* token category counters */
int cnt_kw=0, cnt_id=0, cnt_num=0, cnt_str=0,
    cnt_op=0, cnt_sym=0, cnt_cmt=0, cnt_pre=0;

static void print_token(const char *col, const char *type,
                        const char *val, const char *cat)
{
    token_count++;
    printf("  %s%-4d%s  %s%-18s%s  %s%-14s%s  %s\n",
           GRAY,  line_num, RESET,
           col,   type,     RESET,
           GRAY,  cat,      RESET,
           val);
}
%}

%option noyywrap
%option nounput
%option noinput

%x BLOCK_CMT
%x LINE_CMT
%x STR_LIT

DIGIT   [0-9]
LETTER  [a-zA-Z_]
ALNUM   [a-zA-Z0-9_]
HEX     [0-9a-fA-F]
EXP     ([eE][+-]?{DIGIT}+)

%%

 /* preprocessor */
^[ \t]*"#"[^\n]*  { cnt_pre++; print_token(LBLUE,"PREPROCESSOR",yytext,"directive"); }

 /* block comment */
"/*"              { cnt_cmt++; BEGIN(BLOCK_CMT);
                    print_token(GRAY,"COMMENT","/*","block-start"); }
<BLOCK_CMT>"*/"   { print_token(GRAY,"COMMENT","*/","block-end"); BEGIN(INITIAL); }
<BLOCK_CMT>"\n"   { line_num++; }
<BLOCK_CMT>[^*\n]+ { }
<BLOCK_CMT>"*"    { }
<BLOCK_CMT><<EOF>> {
    fprintf(stderr, RED "  ERROR line %d: Unclosed block comment\n" RESET, line_num);
    error_count++; BEGIN(INITIAL);
}

 /* line comment */
"//"              { cnt_cmt++; BEGIN(LINE_CMT);
                    print_token(GRAY,"COMMENT","//","line-start"); }
<LINE_CMT>[^\n]+  { }
<LINE_CMT>"\n"    { line_num++; BEGIN(INITIAL); }

 /* string literal */
"\""              { BEGIN(STR_LIT); }
<STR_LIT>"\\\""   { }
<STR_LIT>"\\\\"   { }
<STR_LIT>"\\n"    { }
<STR_LIT>"\\t"    { }
<STR_LIT>[^"\\\n]+ { }
<STR_LIT>"\""     { cnt_str++;
                    print_token(YELLOW,"STRING_LITERAL",yytext,"literal");
                    BEGIN(INITIAL); }
<STR_LIT>"\n"     {
    fprintf(stderr, RED "  ERROR line %d: Unterminated string\n" RESET, line_num);
    error_count++; line_num++; BEGIN(INITIAL);
}
<STR_LIT><<EOF>>  {
    fprintf(stderr, RED "  ERROR line %d: Unterminated string at EOF\n" RESET, line_num);
    error_count++; BEGIN(INITIAL);
}

 /* char literal */
"'"[^'\\\n]"'"     { cnt_str++; print_token(YELLOW,"CHAR_LITERAL",yytext,"literal"); }
"'\\n'"            { cnt_str++; print_token(YELLOW,"CHAR_LITERAL",yytext,"literal"); }
"'\\t'"            { cnt_str++; print_token(YELLOW,"CHAR_LITERAL",yytext,"literal"); }
"'\\\\'"           { cnt_str++; print_token(YELLOW,"CHAR_LITERAL",yytext,"literal"); }
"'\\0'"            { cnt_str++; print_token(YELLOW,"CHAR_LITERAL",yytext,"literal"); }

 /* keywords */
"auto"      { cnt_kw++; print_token(BLUE,"KEYWORD",yytext,"keyword"); }
"break"     { cnt_kw++; print_token(BLUE,"KEYWORD",yytext,"keyword"); }
"case"      { cnt_kw++; print_token(BLUE,"KEYWORD",yytext,"keyword"); }
"char"      { cnt_kw++; print_token(BLUE,"KEYWORD",yytext,"keyword"); }
"const"     { cnt_kw++; print_token(BLUE,"KEYWORD",yytext,"keyword"); }
"continue"  { cnt_kw++; print_token(BLUE,"KEYWORD",yytext,"keyword"); }
"default"   { cnt_kw++; print_token(BLUE,"KEYWORD",yytext,"keyword"); }
"do"        { cnt_kw++; print_token(BLUE,"KEYWORD",yytext,"keyword"); }
"double"    { cnt_kw++; print_token(BLUE,"KEYWORD",yytext,"keyword"); }
"else"      { cnt_kw++; print_token(BLUE,"KEYWORD",yytext,"keyword"); }
"enum"      { cnt_kw++; print_token(BLUE,"KEYWORD",yytext,"keyword"); }
"extern"    { cnt_kw++; print_token(BLUE,"KEYWORD",yytext,"keyword"); }
"float"     { cnt_kw++; print_token(BLUE,"KEYWORD",yytext,"keyword"); }
"for"       { cnt_kw++; print_token(BLUE,"KEYWORD",yytext,"keyword"); }
"if"        { cnt_kw++; print_token(BLUE,"KEYWORD",yytext,"keyword"); }
"int"       { cnt_kw++; print_token(BLUE,"KEYWORD",yytext,"keyword"); }
"long"      { cnt_kw++; print_token(BLUE,"KEYWORD",yytext,"keyword"); }
"return"    { cnt_kw++; print_token(BLUE,"KEYWORD",yytext,"keyword"); }
"short"     { cnt_kw++; print_token(BLUE,"KEYWORD",yytext,"keyword"); }
"signed"    { cnt_kw++; print_token(BLUE,"KEYWORD",yytext,"keyword"); }
"sizeof"    { cnt_kw++; print_token(BLUE,"KEYWORD",yytext,"keyword"); }
"static"    { cnt_kw++; print_token(BLUE,"KEYWORD",yytext,"keyword"); }
"struct"    { cnt_kw++; print_token(BLUE,"KEYWORD",yytext,"keyword"); }
"switch"    { cnt_kw++; print_token(BLUE,"KEYWORD",yytext,"keyword"); }
"typedef"   { cnt_kw++; print_token(BLUE,"KEYWORD",yytext,"keyword"); }
"union"     { cnt_kw++; print_token(BLUE,"KEYWORD",yytext,"keyword"); }
"unsigned"  { cnt_kw++; print_token(BLUE,"KEYWORD",yytext,"keyword"); }
"void"      { cnt_kw++; print_token(BLUE,"KEYWORD",yytext,"keyword"); }
"volatile"  { cnt_kw++; print_token(BLUE,"KEYWORD",yytext,"keyword"); }
"while"     { cnt_kw++; print_token(BLUE,"KEYWORD",yytext,"keyword"); }

 /* identifiers */
{LETTER}{ALNUM}*  { cnt_id++; print_token(WHITE,"IDENTIFIER",yytext,"identifier"); }

 /* numbers */
"0"[xX]{HEX}+               { cnt_num++; print_token(GREEN,"HEX_INTEGER",yytext,"literal"); }
"0"[0-7]+                    { cnt_num++; print_token(GREEN,"OCT_INTEGER",yytext,"literal"); }
{DIGIT}+"."{DIGIT}*{EXP}?   { cnt_num++; print_token(GREEN,"FLOAT",yytext,"literal"); }
"."{DIGIT}+{EXP}?            { cnt_num++; print_token(GREEN,"FLOAT",yytext,"literal"); }
{DIGIT}+{EXP}                { cnt_num++; print_token(GREEN,"FLOAT",yytext,"literal"); }
{DIGIT}+                     { cnt_num++; print_token(GREEN,"INTEGER",yytext,"literal"); }

 /* operators */
"<<=" { cnt_op++; print_token(MAGENTA,"OP_ASSIGN",yytext,"operator"); }
">>=" { cnt_op++; print_token(MAGENTA,"OP_ASSIGN",yytext,"operator"); }
"+="  { cnt_op++; print_token(MAGENTA,"OP_ASSIGN",yytext,"operator"); }
"-="  { cnt_op++; print_token(MAGENTA,"OP_ASSIGN",yytext,"operator"); }
"*="  { cnt_op++; print_token(MAGENTA,"OP_ASSIGN",yytext,"operator"); }
"/="  { cnt_op++; print_token(MAGENTA,"OP_ASSIGN",yytext,"operator"); }
"%="  { cnt_op++; print_token(MAGENTA,"OP_ASSIGN",yytext,"operator"); }
"&="  { cnt_op++; print_token(MAGENTA,"OP_ASSIGN",yytext,"operator"); }
"^="  { cnt_op++; print_token(MAGENTA,"OP_ASSIGN",yytext,"operator"); }
"|="  { cnt_op++; print_token(MAGENTA,"OP_ASSIGN",yytext,"operator"); }
"&&"  { cnt_op++; print_token(MAGENTA,"OP_LOGICAL",yytext,"operator"); }
"||"  { cnt_op++; print_token(MAGENTA,"OP_LOGICAL",yytext,"operator"); }
"=="  { cnt_op++; print_token(MAGENTA,"OP_RELAT",yytext,"operator"); }
"!="  { cnt_op++; print_token(MAGENTA,"OP_RELAT",yytext,"operator"); }
"<="  { cnt_op++; print_token(MAGENTA,"OP_RELAT",yytext,"operator"); }
">="  { cnt_op++; print_token(MAGENTA,"OP_RELAT",yytext,"operator"); }
"<<"  { cnt_op++; print_token(MAGENTA,"OP_SHIFT",yytext,"operator"); }
">>"  { cnt_op++; print_token(MAGENTA,"OP_SHIFT",yytext,"operator"); }
"++"  { cnt_op++; print_token(MAGENTA,"OP_INCDEC",yytext,"operator"); }
"--"  { cnt_op++; print_token(MAGENTA,"OP_INCDEC",yytext,"operator"); }
"->"  { cnt_op++; print_token(MAGENTA,"OP_ARROW",yytext,"operator"); }
"+"   { cnt_op++; print_token(MAGENTA,"OP_ARITH",yytext,"operator"); }
"-"   { cnt_op++; print_token(MAGENTA,"OP_ARITH",yytext,"operator"); }
"*"   { cnt_op++; print_token(MAGENTA,"OP_ARITH",yytext,"operator"); }
"/"   { cnt_op++; print_token(MAGENTA,"OP_ARITH",yytext,"operator"); }
"%"   { cnt_op++; print_token(MAGENTA,"OP_ARITH",yytext,"operator"); }
"<"   { cnt_op++; print_token(MAGENTA,"OP_RELAT",yytext,"operator"); }
">"   { cnt_op++; print_token(MAGENTA,"OP_RELAT",yytext,"operator"); }
"="   { cnt_op++; print_token(MAGENTA,"OP_ASSIGN",yytext,"operator"); }
"!"   { cnt_op++; print_token(MAGENTA,"OP_LOGICAL",yytext,"operator"); }
"&"   { cnt_op++; print_token(MAGENTA,"OP_BITWISE",yytext,"operator"); }
"|"   { cnt_op++; print_token(MAGENTA,"OP_BITWISE",yytext,"operator"); }
"^"   { cnt_op++; print_token(MAGENTA,"OP_BITWISE",yytext,"operator"); }
"~"   { cnt_op++; print_token(MAGENTA,"OP_BITWISE",yytext,"operator"); }
"?"   { cnt_op++; print_token(MAGENTA,"OP_TERNARY",yytext,"operator"); }

 /* symbols */
"("   { cnt_sym++; print_token(CYAN,"LPAREN",yytext,"symbol"); }
")"   { cnt_sym++; print_token(CYAN,"RPAREN",yytext,"symbol"); }
"{"   { cnt_sym++; print_token(CYAN,"LBRACE",yytext,"symbol"); }
"}"   { cnt_sym++; print_token(CYAN,"RBRACE",yytext,"symbol"); }
"["   { cnt_sym++; print_token(CYAN,"LBRACKET",yytext,"symbol"); }
"]"   { cnt_sym++; print_token(CYAN,"RBRACKET",yytext,"symbol"); }
";"   { cnt_sym++; print_token(CYAN,"SEMICOLON",yytext,"symbol"); }
":"   { cnt_sym++; print_token(CYAN,"COLON",yytext,"symbol"); }
","   { cnt_sym++; print_token(CYAN,"COMMA",yytext,"symbol"); }
"..."  { cnt_sym++; print_token(CYAN,"ELLIPSIS",yytext,"symbol"); }
"."   { cnt_sym++; print_token(CYAN,"DOT",yytext,"symbol"); }

"\n"         { line_num++; }
[ \t\r\f]+   { }

.   {
    fprintf(stderr, RED "  ERROR line %d: Unknown character '%s'\n" RESET,
            line_num, yytext);
    error_count++;
}

%%

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "\n  Usage: %s <file.c>\n\n", argv[0]);
        return 1;
    }
    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        fprintf(stderr, "\n  Cannot open '%s'\n\n", argv[1]);
        return 1;
    }

    printf("\n");
    printf(BOLD "  ╔══════════════════════════════════════════════════════════╗\n" RESET);
    printf(BOLD "  ║         PHASE 1 — LEXICAL ANALYSER OUTPUT               ║\n" RESET);
    printf(BOLD "  ║         Compiler Design Project | GEU                   ║\n" RESET);
    printf(BOLD "  ╚══════════════════════════════════════════════════════════╝\n" RESET);
    printf("\n");
    printf(BOLD "  %-4s  %-18s  %-14s  %s\n" RESET,
           "LINE","TOKEN TYPE","CATEGORY","VALUE");
    printf("  %s\n","─────────────────────────────────────────────────────────");

    yyin = fp;
    yylex();
    fclose(fp);

    printf("  %s\n\n","─────────────────────────────────────────────────────────");
    printf(BOLD "  TOKEN SUMMARY\n" RESET);
    printf("  %-20s %d\n", "Keywords:",   cnt_kw);
    printf("  %-20s %d\n", "Identifiers:",cnt_id);
    printf("  %-20s %d\n", "Numbers:",    cnt_num);
    printf("  %-20s %d\n", "Strings:",    cnt_str);
    printf("  %-20s %d\n", "Operators:",  cnt_op);
    printf("  %-20s %d\n", "Symbols:",    cnt_sym);
    printf("  %-20s %d\n", "Comments:",   cnt_cmt);
    printf("  %-20s %d\n", "Preprocessor:",cnt_pre);
    printf("  ─────────────────────────\n");
    printf("  %-20s " BOLD "%d\n" RESET, "Total tokens:", token_count);
    printf("  %-20s " RED  "%d\n" RESET, "Lexical errors:", error_count);
    printf("\n");
    if (error_count == 0)
        printf(GREEN "  ✔  Lexical analysis PASSED — no errors found.\n\n" RESET);
    else
        printf(RED   "  ✘  Lexical analysis completed WITH errors.\n\n" RESET);

    return (error_count > 0) ? 1 : 0;
}
