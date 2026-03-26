/*
 * ============================================================
 *  lexer.l  —  Phase 1: Lexical Analyser for a Subset of C
 *  Tool   : Flex (GNU Flex 2.6+)
 *  Build  : flex lexer.l && gcc lex.yy.c -lfl -o lexer
 *  Run    : ./lexer input.c
 * ============================================================
 */

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ── token-type labels ─────────────────────────────────────── */
#define COL_RESET   "\033[0m"
#define COL_KW      "\033[1;34m"   /* bold blue   – keywords    */
#define COL_ID      "\033[0;37m"   /* white       – identifiers */
#define COL_NUM     "\033[0;32m"   /* green       – numbers     */
#define COL_STR     "\033[0;33m"   /* yellow      – strings     */
#define COL_OP      "\033[0;35m"   /* magenta     – operators   */
#define COL_SYM     "\033[0;36m"   /* cyan        – symbols     */
#define COL_CMT     "\033[0;90m"   /* dark grey   – comments    */
#define COL_PRE     "\033[0;94m"   /* light blue  – preprocessor*/
#define COL_ERR     "\033[1;31m"   /* bold red    – errors      */

/* running line counter (Flex resets yylineno per file) */
int line_num   = 1;
int token_count = 0;
int error_count = 0;

/* helper: print one token row */
static void print_token(const char *colour,
                         const char *type,
                         const char *value)
{
    token_count++;
    printf("  %-5d  %s%-20s%s  %s\n",
           line_num, colour, type, COL_RESET, value);
}
%}

/* ── Flex options ────────────────────────────────────────────*/
%option noyywrap
%option nounput
%option noinput

/* ── exclusive start conditions ─────────────────────────────*/
%x BLOCK_COMMENT
%x LINE_COMMENT
%x STRING_LIT
%x CHAR_LIT
%x PREPROC

/* ── named definitions ───────────────────────────────────────*/
DIGIT        [0-9]
LETTER       [a-zA-Z_]
ALNUM        [a-zA-Z0-9_]
HEX_DIGIT    [0-9a-fA-F]
OCT_DIGIT    [0-7]
EXP          ([eE][+-]?{DIGIT}+)
FLOAT_SUFFIX [fFlL]
INT_SUFFIX   ([uU][lL]?|[lL][uU]?|[lL][lL][uU]?|[uU][lL][lL]?)

%%

 /* ══════════════════════════════════════════════════
  *  1. PREPROCESSOR DIRECTIVES  (#include, #define …)
  * ══════════════════════════════════════════════════ */
^[ \t]*"#"                  { BEGIN(PREPROC); print_token(COL_PRE, "PREPROCESSOR", "#"); }
<PREPROC>[^\n\\]+           { print_token(COL_PRE, "PREPROCESSOR", yytext); }
<PREPROC>"\\\n"             { line_num++; /* line continuation */ }
<PREPROC>"\n"               { line_num++; BEGIN(INITIAL); }

 /* ══════════════════════════════════════════════════
  *  2. BLOCK COMMENTS  /* … */
  * ══════════════════════════════════════════════════ */
"/*"                        { BEGIN(BLOCK_COMMENT);
                              print_token(COL_CMT, "COMMENT_START", "/*"); }
<BLOCK_COMMENT>"*/"         { print_token(COL_CMT, "COMMENT_END", "*/");
                              BEGIN(INITIAL); }
<BLOCK_COMMENT>"\n"         { line_num++; }
<BLOCK_COMMENT>[^*\n]+      { /* consume comment body silently */ }
<BLOCK_COMMENT>"*"          { /* consume lone asterisk */ }
<BLOCK_COMMENT><<EOF>>      {
    fprintf(stderr,
        COL_ERR "  ERROR [line %d]: Unclosed block comment\n" COL_RESET,
        line_num);
    error_count++;
    BEGIN(INITIAL);
}

 /* ══════════════════════════════════════════════════
  *  3. LINE COMMENTS  // …
  * ══════════════════════════════════════════════════ */
"//"                        { BEGIN(LINE_COMMENT);
                              print_token(COL_CMT, "COMMENT_START", "//"); }
<LINE_COMMENT>[^\n]+        { /* consume comment body silently */ }
<LINE_COMMENT>"\n"          { line_num++; BEGIN(INITIAL); }

 /* ══════════════════════════════════════════════════
  *  4. STRING LITERALS  "…"
  * ══════════════════════════════════════════════════ */
"\""                        { BEGIN(STRING_LIT); }
<STRING_LIT>"\\\""          { /* escaped quote inside string */ }
<STRING_LIT>"\\\\"          { /* escaped backslash          */ }
<STRING_LIT>"\\n"           { /* escape sequences           */ }
<STRING_LIT>"\\t"           { }
<STRING_LIT>"\\r"           { }
<STRING_LIT>"\\0"           { }
<STRING_LIT>[^"\\\n]+       { /* string body */ }
<STRING_LIT>"\""            { print_token(COL_STR, "STRING_LITERAL", yytext);
                              BEGIN(INITIAL); }
<STRING_LIT>"\n"            {
    fprintf(stderr,
        COL_ERR "  ERROR [line %d]: Unterminated string literal\n" COL_RESET,
        line_num);
    error_count++;
    line_num++;
    BEGIN(INITIAL);
}
<STRING_LIT><<EOF>>         {
    fprintf(stderr,
        COL_ERR "  ERROR [line %d]: Unterminated string literal at EOF\n" COL_RESET,
        line_num);
    error_count++;
    BEGIN(INITIAL);
}

 /* ══════════════════════════════════════════════════
  *  5. CHARACTER LITERALS  '…'
  * ══════════════════════════════════════════════════ */
"'"[^'\n]"'"                { print_token(COL_STR, "CHAR_LITERAL",  yytext); }
"'\\'"[^'\n]"'"             { print_token(COL_STR, "CHAR_LITERAL",  yytext); }
"'\\n'"                     { print_token(COL_STR, "CHAR_LITERAL",  yytext); }
"'\\t'"                     { print_token(COL_STR, "CHAR_LITERAL",  yytext); }
"'\\\\'"                    { print_token(COL_STR, "CHAR_LITERAL",  yytext); }
"'\\0'"                     { print_token(COL_STR, "CHAR_LITERAL",  yytext); }

 /* ══════════════════════════════════════════════════
  *  6. KEYWORDS  (must appear before IDENTIFIER rule)
  * ══════════════════════════════════════════════════ */
"auto"         { print_token(COL_KW, "KEYWORD", yytext); }
"break"        { print_token(COL_KW, "KEYWORD", yytext); }
"case"         { print_token(COL_KW, "KEYWORD", yytext); }
"char"         { print_token(COL_KW, "KEYWORD", yytext); }
"const"        { print_token(COL_KW, "KEYWORD", yytext); }
"continue"     { print_token(COL_KW, "KEYWORD", yytext); }
"default"      { print_token(COL_KW, "KEYWORD", yytext); }
"do"           { print_token(COL_KW, "KEYWORD", yytext); }
"double"       { print_token(COL_KW, "KEYWORD", yytext); }
"else"         { print_token(COL_KW, "KEYWORD", yytext); }
"enum"         { print_token(COL_KW, "KEYWORD", yytext); }
"extern"       { print_token(COL_KW, "KEYWORD", yytext); }
"float"        { print_token(COL_KW, "KEYWORD", yytext); }
"for"          { print_token(COL_KW, "KEYWORD", yytext); }
"goto"         { print_token(COL_KW, "KEYWORD", yytext); }
"if"           { print_token(COL_KW, "KEYWORD", yytext); }
"int"          { print_token(COL_KW, "KEYWORD", yytext); }
"long"         { print_token(COL_KW, "KEYWORD", yytext); }
"register"     { print_token(COL_KW, "KEYWORD", yytext); }
"return"       { print_token(COL_KW, "KEYWORD", yytext); }
"short"        { print_token(COL_KW, "KEYWORD", yytext); }
"signed"       { print_token(COL_KW, "KEYWORD", yytext); }
"sizeof"       { print_token(COL_KW, "KEYWORD", yytext); }
"static"       { print_token(COL_KW, "KEYWORD", yytext); }
"struct"       { print_token(COL_KW, "KEYWORD", yytext); }
"switch"       { print_token(COL_KW, "KEYWORD", yytext); }
"typedef"      { print_token(COL_KW, "KEYWORD", yytext); }
"union"        { print_token(COL_KW, "KEYWORD", yytext); }
"unsigned"     { print_token(COL_KW, "KEYWORD", yytext); }
"void"         { print_token(COL_KW, "KEYWORD", yytext); }
"volatile"     { print_token(COL_KW, "KEYWORD", yytext); }
"while"        { print_token(COL_KW, "KEYWORD", yytext); }

 /* ══════════════════════════════════════════════════
  *  7. IDENTIFIERS
  * ══════════════════════════════════════════════════ */
{LETTER}{ALNUM}*            { print_token(COL_ID, "IDENTIFIER", yytext); }

 /* ══════════════════════════════════════════════════
  *  8. NUMERIC LITERALS
  *     order: hex → octal → float → integer
  * ══════════════════════════════════════════════════ */
"0"[xX]{HEX_DIGIT}+{INT_SUFFIX}?   { print_token(COL_NUM, "HEX_INTEGER",   yytext); }
"0"{OCT_DIGIT}+{INT_SUFFIX}?        { print_token(COL_NUM, "OCT_INTEGER",   yytext); }
{DIGIT}+"."{DIGIT}*{EXP}?{FLOAT_SUFFIX}?  { print_token(COL_NUM, "FLOAT_NUMBER", yytext); }
"."{DIGIT}+{EXP}?{FLOAT_SUFFIX}?          { print_token(COL_NUM, "FLOAT_NUMBER", yytext); }
{DIGIT}+{EXP}{FLOAT_SUFFIX}?              { print_token(COL_NUM, "FLOAT_NUMBER", yytext); }
{DIGIT}+{INT_SUFFIX}?                     { print_token(COL_NUM, "INT_NUMBER",   yytext); }

 /* ══════════════════════════════════════════════════
  *  9. OPERATORS  (multi-char must precede single-char)
  * ══════════════════════════════════════════════════ */
"<<="   { print_token(COL_OP, "OP_ASSIGN",  yytext); }
">>="   { print_token(COL_OP, "OP_ASSIGN",  yytext); }
"+="    { print_token(COL_OP, "OP_ASSIGN",  yytext); }
"-="    { print_token(COL_OP, "OP_ASSIGN",  yytext); }
"*="    { print_token(COL_OP, "OP_ASSIGN",  yytext); }
"/="    { print_token(COL_OP, "OP_ASSIGN",  yytext); }
"%="    { print_token(COL_OP, "OP_ASSIGN",  yytext); }
"&="    { print_token(COL_OP, "OP_ASSIGN",  yytext); }
"^="    { print_token(COL_OP, "OP_ASSIGN",  yytext); }
"|="    { print_token(COL_OP, "OP_ASSIGN",  yytext); }
"&&"    { print_token(COL_OP, "OP_LOGICAL", yytext); }
"||"    { print_token(COL_OP, "OP_LOGICAL", yytext); }
"=="    { print_token(COL_OP, "OP_RELAT",   yytext); }
"!="    { print_token(COL_OP, "OP_RELAT",   yytext); }
"<="    { print_token(COL_OP, "OP_RELAT",   yytext); }
">="    { print_token(COL_OP, "OP_RELAT",   yytext); }
"<<"    { print_token(COL_OP, "OP_SHIFT",   yytext); }
">>"    { print_token(COL_OP, "OP_SHIFT",   yytext); }
"++"    { print_token(COL_OP, "OP_INCDEC",  yytext); }
"--"    { print_token(COL_OP, "OP_INCDEC",  yytext); }
"->"    { print_token(COL_OP, "OP_ARROW",   yytext); }
"+"     { print_token(COL_OP, "OP_ARITH",   yytext); }
"-"     { print_token(COL_OP, "OP_ARITH",   yytext); }
"*"     { print_token(COL_OP, "OP_ARITH",   yytext); }
"/"     { print_token(COL_OP, "OP_ARITH",   yytext); }
"%"     { print_token(COL_OP, "OP_ARITH",   yytext); }
"<"     { print_token(COL_OP, "OP_RELAT",   yytext); }
">"     { print_token(COL_OP, "OP_RELAT",   yytext); }
"="     { print_token(COL_OP, "OP_ASSIGN",  yytext); }
"!"     { print_token(COL_OP, "OP_LOGICAL", yytext); }
"&"     { print_token(COL_OP, "OP_BITWISE", yytext); }
"|"     { print_token(COL_OP, "OP_BITWISE", yytext); }
"^"     { print_token(COL_OP, "OP_BITWISE", yytext); }
"~"     { print_token(COL_OP, "OP_BITWISE", yytext); }
"?"     { print_token(COL_OP, "OP_TERNARY", yytext); }

 /* ══════════════════════════════════════════════════
  *  10. SYMBOLS / PUNCTUATION
  * ══════════════════════════════════════════════════ */
"("     { print_token(COL_SYM, "LPAREN",    yytext); }
")"     { print_token(COL_SYM, "RPAREN",    yytext); }
"{"     { print_token(COL_SYM, "LBRACE",    yytext); }
"}"     { print_token(COL_SYM, "RBRACE",    yytext); }
"["     { print_token(COL_SYM, "LBRACKET",  yytext); }
"]"     { print_token(COL_SYM, "RBRACKET",  yytext); }
";"     { print_token(COL_SYM, "SEMICOLON", yytext); }
":"     { print_token(COL_SYM, "COLON",     yytext); }
","     { print_token(COL_SYM, "COMMA",     yytext); }
"."     { print_token(COL_SYM, "DOT",       yytext); }
"..."   { print_token(COL_SYM, "ELLIPSIS",  yytext); }

 /* ══════════════════════════════════════════════════
  *  11. WHITESPACE & NEWLINES  (silently consumed)
  * ══════════════════════════════════════════════════ */
"\n"                        { line_num++; }
[ \t\r\f\v]+                { /* skip whitespace */ }

 /* ══════════════════════════════════════════════════
  *  12. CATCH-ALL: lexical error
  * ══════════════════════════════════════════════════ */
.                           {
    fprintf(stderr,
        COL_ERR "  ERROR [line %d]: Unrecognised character '%s'\n" COL_RESET,
        line_num, yytext);
    error_count++;
}

%%

/* ── print_header / print_footer ────────────────────────────*/
static void print_header(const char *filename)
{
    printf("\n");
    printf("  ╔══════════════════════════════════════════════════════╗\n");
    printf("  ║        LEXICAL ANALYSER  —  Phase 1 Output          ║\n");
    printf("  ║  File : %-44s║\n", filename);
    printf("  ╚══════════════════════════════════════════════════════╝\n");
    printf("\n");
    printf("  %-5s  %-20s  %s\n", "LINE", "TOKEN TYPE", "VALUE");
    printf("  %s\n", "─────────────────────────────────────────────────────");
}

static void print_footer(void)
{
    printf("  %s\n", "─────────────────────────────────────────────────────");
    printf("\n");
    printf("  Total tokens : %d\n", token_count);
    printf("  Lexical errors: %d\n", error_count);
    printf("\n");
    if (error_count == 0)
        printf("  ✔  Lexical analysis completed successfully.\n\n");
    else
        printf("  ✘  Lexical analysis completed with errors.\n\n");
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

    print_header(argv[1]);
    yyin = fp;
    yylex();
    fclose(fp);
    print_footer();

    return (error_count > 0) ? EXIT_FAILURE : EXIT_SUCCESS;
}
