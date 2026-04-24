/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IDENTIFIER = 258,
     INT_LITERAL = 259,
     FLOAT_LITERAL = 260,
     STRING_LITERAL = 261,
     CHAR_LITERAL = 262,
     KW_AUTO = 263,
     KW_BREAK = 264,
     KW_CASE = 265,
     KW_CHAR = 266,
     KW_CONST = 267,
     KW_CONTINUE = 268,
     KW_DEFAULT = 269,
     KW_DO = 270,
     KW_DOUBLE = 271,
     KW_ELSE = 272,
     KW_ENUM = 273,
     KW_EXTERN = 274,
     KW_FLOAT = 275,
     KW_FOR = 276,
     KW_IF = 277,
     KW_INT = 278,
     KW_LONG = 279,
     KW_RETURN = 280,
     KW_SHORT = 281,
     KW_SIGNED = 282,
     KW_SIZEOF = 283,
     KW_STATIC = 284,
     KW_STRUCT = 285,
     KW_SWITCH = 286,
     KW_TYPEDEF = 287,
     KW_UNION = 288,
     KW_UNSIGNED = 289,
     KW_VOID = 290,
     KW_VOLATILE = 291,
     KW_WHILE = 292,
     OP_INC = 293,
     OP_DEC = 294,
     OP_ARROW = 295,
     OP_AND = 296,
     OP_OR = 297,
     OP_EQ = 298,
     OP_NEQ = 299,
     OP_LEQ = 300,
     OP_GEQ = 301,
     OP_LSHIFT = 302,
     OP_RSHIFT = 303,
     OP_PLUS_A = 304,
     OP_MINUS_A = 305,
     OP_MUL_A = 306,
     OP_DIV_A = 307,
     OP_MOD_A = 308,
     OP_AND_A = 309,
     OP_XOR_A = 310,
     OP_OR_A = 311,
     OP_LSHIFT_A = 312,
     OP_RSHIFT_A = 313,
     ELLIPSIS = 314,
     UPREC = 315,
     KW_THEN = 316
   };
#endif
/* Tokens.  */
#define IDENTIFIER 258
#define INT_LITERAL 259
#define FLOAT_LITERAL 260
#define STRING_LITERAL 261
#define CHAR_LITERAL 262
#define KW_AUTO 263
#define KW_BREAK 264
#define KW_CASE 265
#define KW_CHAR 266
#define KW_CONST 267
#define KW_CONTINUE 268
#define KW_DEFAULT 269
#define KW_DO 270
#define KW_DOUBLE 271
#define KW_ELSE 272
#define KW_ENUM 273
#define KW_EXTERN 274
#define KW_FLOAT 275
#define KW_FOR 276
#define KW_IF 277
#define KW_INT 278
#define KW_LONG 279
#define KW_RETURN 280
#define KW_SHORT 281
#define KW_SIGNED 282
#define KW_SIZEOF 283
#define KW_STATIC 284
#define KW_STRUCT 285
#define KW_SWITCH 286
#define KW_TYPEDEF 287
#define KW_UNION 288
#define KW_UNSIGNED 289
#define KW_VOID 290
#define KW_VOLATILE 291
#define KW_WHILE 292
#define OP_INC 293
#define OP_DEC 294
#define OP_ARROW 295
#define OP_AND 296
#define OP_OR 297
#define OP_EQ 298
#define OP_NEQ 299
#define OP_LEQ 300
#define OP_GEQ 301
#define OP_LSHIFT 302
#define OP_RSHIFT 303
#define OP_PLUS_A 304
#define OP_MINUS_A 305
#define OP_MUL_A 306
#define OP_DIV_A 307
#define OP_MOD_A 308
#define OP_AND_A 309
#define OP_XOR_A 310
#define OP_OR_A 311
#define OP_LSHIFT_A 312
#define OP_RSHIFT_A 313
#define ELLIPSIS 314
#define UPREC 315
#define KW_THEN 316




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 30 "src/parser.y"
{
    char    *sval;
    ASTNode *node;
}
/* Line 1529 of yacc.c.  */
#line 176 "build/parser.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

