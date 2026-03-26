%{
#include "parser.tab.h"
#include <string.h>
%}

%option noyywrap

DIGIT   [0-9]
LETTER  [a-zA-Z_]

%%

"int"      { return INT; }
"float"    { return FLOAT; }
"char"     { return CHAR; }
"if"       { return IF; }
"else"     { return ELSE; }
"while"    { return WHILE; }
"for"      { return FOR; }
"return"   { return RETURN; }

"=="|"!="|">="|"<="|">"|"<" { return RELOP; }
"&&" { return AND; }
"||" { return OR; }

"+"|"-"|"*"|"/" { return yytext[0]; }
"=" { return '='; }

";" { return ';'; }
"," { return ','; }
"(" { return '('; }
")" { return ')'; }
"{" { return '{'; }
"}" { return '}'; }

{LETTER}({LETTER}|{DIGIT})* {
    yylval.str = strdup(yytext);
    return ID;
}

{DIGIT}+ {
    yylval.str = strdup(yytext);
    return NUM;
}

\"([^\\\n]|\\.)*\" { return STRING; }

[ \t\r\n]+ ;

. { printf("Invalid: %s\n", yytext); }

%%