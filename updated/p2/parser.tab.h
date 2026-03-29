/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IDENTIFIER = 258,              /* IDENTIFIER  */
    INT_LITERAL = 259,             /* INT_LITERAL  */
    FLOAT_LITERAL = 260,           /* FLOAT_LITERAL  */
    STRING_LITERAL = 261,          /* STRING_LITERAL  */
    CHAR_LITERAL = 262,            /* CHAR_LITERAL  */
    KW_AUTO = 263,                 /* KW_AUTO  */
    KW_BREAK = 264,                /* KW_BREAK  */
    KW_CASE = 265,                 /* KW_CASE  */
    KW_CHAR = 266,                 /* KW_CHAR  */
    KW_CONST = 267,                /* KW_CONST  */
    KW_CONTINUE = 268,             /* KW_CONTINUE  */
    KW_DEFAULT = 269,              /* KW_DEFAULT  */
    KW_DO = 270,                   /* KW_DO  */
    KW_DOUBLE = 271,               /* KW_DOUBLE  */
    KW_ELSE = 272,                 /* KW_ELSE  */
    KW_ENUM = 273,                 /* KW_ENUM  */
    KW_EXTERN = 274,               /* KW_EXTERN  */
    KW_FLOAT = 275,                /* KW_FLOAT  */
    KW_FOR = 276,                  /* KW_FOR  */
    KW_IF = 277,                   /* KW_IF  */
    KW_INT = 278,                  /* KW_INT  */
    KW_LONG = 279,                 /* KW_LONG  */
    KW_RETURN = 280,               /* KW_RETURN  */
    KW_SHORT = 281,                /* KW_SHORT  */
    KW_SIGNED = 282,               /* KW_SIGNED  */
    KW_SIZEOF = 283,               /* KW_SIZEOF  */
    KW_STATIC = 284,               /* KW_STATIC  */
    KW_STRUCT = 285,               /* KW_STRUCT  */
    KW_SWITCH = 286,               /* KW_SWITCH  */
    KW_TYPEDEF = 287,              /* KW_TYPEDEF  */
    KW_UNION = 288,                /* KW_UNION  */
    KW_UNSIGNED = 289,             /* KW_UNSIGNED  */
    KW_VOID = 290,                 /* KW_VOID  */
    KW_VOLATILE = 291,             /* KW_VOLATILE  */
    KW_WHILE = 292,                /* KW_WHILE  */
    OP_INC = 293,                  /* OP_INC  */
    OP_DEC = 294,                  /* OP_DEC  */
    OP_ARROW = 295,                /* OP_ARROW  */
    OP_AND = 296,                  /* OP_AND  */
    OP_OR = 297,                   /* OP_OR  */
    OP_EQ = 298,                   /* OP_EQ  */
    OP_NEQ = 299,                  /* OP_NEQ  */
    OP_LEQ = 300,                  /* OP_LEQ  */
    OP_GEQ = 301,                  /* OP_GEQ  */
    OP_LSHIFT = 302,               /* OP_LSHIFT  */
    OP_RSHIFT = 303,               /* OP_RSHIFT  */
    OP_PLUS_A = 304,               /* OP_PLUS_A  */
    OP_MINUS_A = 305,              /* OP_MINUS_A  */
    OP_MUL_A = 306,                /* OP_MUL_A  */
    OP_DIV_A = 307,                /* OP_DIV_A  */
    OP_MOD_A = 308,                /* OP_MOD_A  */
    OP_AND_A = 309,                /* OP_AND_A  */
    OP_XOR_A = 310,                /* OP_XOR_A  */
    OP_OR_A = 311,                 /* OP_OR_A  */
    OP_LSHIFT_A = 312,             /* OP_LSHIFT_A  */
    OP_RSHIFT_A = 313,             /* OP_RSHIFT_A  */
    ELLIPSIS = 314,                /* ELLIPSIS  */
    UPREC = 315,                   /* UPREC  */
    KW_THEN = 316                  /* KW_THEN  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 28 "parser.y"

    char    *sval;
    ASTNode *node;

#line 130 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
