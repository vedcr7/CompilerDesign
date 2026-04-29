%{
#include "ast.h"
#include "parser.tab.h"
#include <string.h>
#include <stdlib.h>

static char sbuf[4096];
static int  slen;

void yyerror(const char *s);
%}

%option noyywrap
%option nounput
%option noinput
%option yylineno

%x BLOCK_CMT
%x LINE_CMT
%x STR_LIT

DIGIT   [0-9]
LETTER  [a-zA-Z_]
ALNUM   [a-zA-Z0-9_]
HEX     [0-9a-fA-F]
EXP     ([eE][+-]?{DIGIT}+)

%%

 /* block comments */
"/*"                { BEGIN(BLOCK_CMT); }
<BLOCK_CMT>"*/"     { BEGIN(INITIAL); }
<BLOCK_CMT>\n       { }
<BLOCK_CMT>.        { }
<BLOCK_CMT><<EOF>>  { yyerror("Unclosed block comment"); BEGIN(INITIAL); }

 /* line comments */
"//"                { BEGIN(LINE_CMT); }
<LINE_CMT>\n        { BEGIN(INITIAL); }
<LINE_CMT>.         { }

 /* preprocessor - skip whole line */
^[ \t]*"#"[^\n]*    { }

 /* string literals */
\"                  { slen=0; BEGIN(STR_LIT); }
<STR_LIT>\\\"       { sbuf[slen++]='"'; }
<STR_LIT>\\\\       { sbuf[slen++]='\\'; }
<STR_LIT>\\n        { sbuf[slen++]='\n'; }
<STR_LIT>\\t        { sbuf[slen++]='\t'; }
<STR_LIT>[^"\\\n]+  { int l=yyleng; if(slen+l<4090){memcpy(sbuf+slen,yytext,l);slen+=l;} }
<STR_LIT>\"         { sbuf[slen]='\0'; yylval.sval=strdup(sbuf); BEGIN(INITIAL); return STRING_LITERAL; }
<STR_LIT>\n         { yyerror("Unterminated string"); BEGIN(INITIAL); }
<STR_LIT><<EOF>>    { yyerror("Unterminated string"); BEGIN(INITIAL); }

 /* char literals */
\'[^\'\\\n]\'       { yylval.sval=strdup(yytext); return CHAR_LITERAL; }
\'\\[ntr0\\\']\'    { yylval.sval=strdup(yytext); return CHAR_LITERAL; }

 /* keywords */
auto        { return KW_AUTO; }
break       { return KW_BREAK; }
case        { return KW_CASE; }
char        { return KW_CHAR; }
const       { return KW_CONST; }
continue    { return KW_CONTINUE; }
default     { return KW_DEFAULT; }
do          { return KW_DO; }
double      { return KW_DOUBLE; }
else        { return KW_ELSE; }
enum        { return KW_ENUM; }
extern      { return KW_EXTERN; }
float       { return KW_FLOAT; }
for         { return KW_FOR; }
if          { return KW_IF; }
int         { return KW_INT; }
long        { return KW_LONG; }
return      { return KW_RETURN; }
short       { return KW_SHORT; }
signed      { return KW_SIGNED; }
sizeof      { return KW_SIZEOF; }
static      { return KW_STATIC; }
struct      { return KW_STRUCT; }
switch      { return KW_SWITCH; }
typedef     { return KW_TYPEDEF; }
union       { return KW_UNION; }
unsigned    { return KW_UNSIGNED; }
void        { return KW_VOID; }
volatile    { return KW_VOLATILE; }
while       { return KW_WHILE; }

 /* identifier */
{LETTER}{ALNUM}*    { yylval.sval=strdup(yytext); return IDENTIFIER; }

 /* numbers */
0[xX]{HEX}+                  { yylval.sval=strdup(yytext); return INT_LITERAL; }
0[0-7]+                       { yylval.sval=strdup(yytext); return INT_LITERAL; }
{DIGIT}+"."{DIGIT}*{EXP}?    { yylval.sval=strdup(yytext); return FLOAT_LITERAL; }
"."{DIGIT}+{EXP}?             { yylval.sval=strdup(yytext); return FLOAT_LITERAL; }
{DIGIT}+{EXP}                 { yylval.sval=strdup(yytext); return FLOAT_LITERAL; }
{DIGIT}+                      { yylval.sval=strdup(yytext); return INT_LITERAL; }

 /* multi-char operators */
"<<="   { return OP_LSHIFT_A; }
">>="   { return OP_RSHIFT_A; }
"+="    { return OP_PLUS_A; }
"-="    { return OP_MINUS_A; }
"*="    { return OP_MUL_A; }
"/="    { return OP_DIV_A; }
"%="    { return OP_MOD_A; }
"&="    { return OP_AND_A; }
"^="    { return OP_XOR_A; }
"|="    { return OP_OR_A; }
"&&"    { return OP_AND; }
"||"    { return OP_OR; }
"=="    { return OP_EQ; }
"!="    { return OP_NEQ; }
"<="    { return OP_LEQ; }
">="    { return OP_GEQ; }
"<<"    { return OP_LSHIFT; }
">>"    { return OP_RSHIFT; }
"++"    { return OP_INC; }
"--"    { return OP_DEC; }
"->"    { return OP_ARROW; }
"..."   { return ELLIPSIS; }

 /* single-char operators and symbols */
"+"  { return '+'; }
"-"  { return '-'; }
"*"  { return '*'; }
"/"  { return '/'; }
"%"  { return '%'; }
"<"  { return '<'; }
">"  { return '>'; }
"="  { return '='; }
"!"  { return '!'; }
"&"  { return '&'; }
"|"  { return '|'; }
"^"  { return '^'; }
"~"  { return '~'; }
"?"  { return '?'; }
"("  { return '('; }
")"  { return ')'; }
"{"  { return '{'; }
"}"  { return '}'; }
"["  { return '['; }
"]"  { return ']'; }
";"  { return ';'; }
":"  { return ':'; }
","  { return ','; }
"."  { return '.'; }

 /* whitespace */
[ \t\r\f\n]+  { }

 /* catch-all */
.   { char m[64]; snprintf(m,sizeof(m),"Unknown character '%s'",yytext); yyerror(m); }

%%
