/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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




/* Copy the first part of user declarations.  */
#line 10 "p2/parser.y"

#include "ast.h"
#include "icg.h"
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


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 29 "p2/parser.y"
{
    char    *sval;
    ASTNode *node;
}
/* Line 193 of yacc.c.  */
#line 241 "p2/parser.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 254 "p2/parser.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  24
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   808

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  86
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  41
/* YYNRULES -- Number of rules.  */
#define YYNRULES  149
/* YYNRULES -- Number of states.  */
#define YYNSTATES  257

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   316

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    85,     2,     2,     2,    72,    65,     2,
      74,    75,    70,    68,    80,    69,    78,    71,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    62,    83,
      66,    60,    67,    61,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    76,     2,    77,    64,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    81,    63,    82,    84,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    73,    79
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    12,    14,    21,    27,
      35,    42,    44,    48,    52,    55,    59,    61,    63,    65,
      67,    69,    71,    73,    75,    77,    79,    82,    85,    88,
      91,    94,    97,    99,   101,   103,   105,   107,   109,   111,
     114,   118,   120,   123,   127,   129,   133,   135,   138,   143,
     148,   152,   156,   161,   163,   165,   167,   169,   171,   173,
     175,   177,   179,   182,   185,   187,   190,   196,   204,   210,
     218,   225,   233,   240,   248,   251,   255,   257,   261,   263,
     267,   269,   271,   273,   275,   277,   279,   281,   283,   285,
     287,   289,   291,   297,   299,   303,   305,   309,   311,   315,
     317,   321,   323,   327,   329,   333,   337,   339,   343,   347,
     351,   355,   357,   361,   365,   367,   371,   375,   377,   381,
     385,   389,   391,   396,   398,   401,   404,   407,   410,   413,
     416,   419,   422,   427,   430,   432,   437,   441,   446,   450,
     454,   457,   460,   462,   466,   468,   470,   472,   474,   476
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      87,     0,    -1,    88,    -1,    89,    -1,    88,    89,    -1,
      90,    -1,    97,    -1,    93,     3,    74,    91,    75,    95,
      -1,    93,     3,    74,    75,    95,    -1,    93,    70,     3,
      74,    91,    75,    95,    -1,    93,    70,     3,    74,    75,
      95,    -1,    92,    -1,    91,    80,    92,    -1,    91,    80,
      59,    -1,    93,     3,    -1,    93,    70,     3,    -1,    93,
      -1,    23,    -1,    11,    -1,    20,    -1,    16,    -1,    35,
      -1,    24,    -1,    26,    -1,    34,    -1,    27,    -1,    29,
      23,    -1,    12,    23,    -1,    12,    11,    -1,    34,    23,
      -1,    24,    23,    -1,    24,    24,    -1,    23,    -1,    11,
      -1,    20,    -1,    16,    -1,    35,    -1,    24,    -1,    26,
      -1,    81,    82,    -1,    81,    96,    82,    -1,   100,    -1,
      96,   100,    -1,    93,    98,    83,    -1,    99,    -1,    98,
      80,    99,    -1,     3,    -1,    70,     3,    -1,     3,    76,
     108,    77,    -1,     3,    76,     4,    77,    -1,     3,    76,
      77,    -1,     3,    60,   108,    -1,    70,     3,    60,   108,
      -1,   101,    -1,    97,    -1,    95,    -1,   102,    -1,   103,
      -1,   104,    -1,   105,    -1,   106,    -1,   107,    -1,     9,
      83,    -1,    13,    83,    -1,    83,    -1,   108,    83,    -1,
      22,    74,   108,    75,   100,    -1,    22,    74,   108,    75,
     100,    17,   100,    -1,    37,    74,   108,    75,   100,    -1,
      15,   100,    37,    74,   108,    75,    83,    -1,    21,    74,
     102,   102,    75,   100,    -1,    21,    74,   102,   102,   108,
      75,   100,    -1,    21,    74,    97,   102,    75,   100,    -1,
      21,    74,    97,   102,   108,    75,   100,    -1,    25,    83,
      -1,    25,   108,    83,    -1,   109,    -1,   108,    80,   109,
      -1,   111,    -1,   123,   110,   109,    -1,    60,    -1,    49,
      -1,    50,    -1,    51,    -1,    52,    -1,    53,    -1,    54,
      -1,    55,    -1,    56,    -1,    57,    -1,    58,    -1,   112,
      -1,   112,    61,   108,    62,   111,    -1,   113,    -1,   112,
      42,   113,    -1,   114,    -1,   113,    41,   114,    -1,   115,
      -1,   114,    63,   115,    -1,   116,    -1,   115,    64,   116,
      -1,   117,    -1,   116,    65,   117,    -1,   118,    -1,   117,
      43,   118,    -1,   117,    44,   118,    -1,   119,    -1,   118,
      66,   119,    -1,   118,    67,   119,    -1,   118,    45,   119,
      -1,   118,    46,   119,    -1,   120,    -1,   119,    47,   120,
      -1,   119,    48,   120,    -1,   121,    -1,   120,    68,   121,
      -1,   120,    69,   121,    -1,   122,    -1,   121,    70,   122,
      -1,   121,    71,   122,    -1,   121,    72,   122,    -1,   123,
      -1,    74,    94,    75,   122,    -1,   124,    -1,    38,   123,
      -1,    39,   123,    -1,    65,   122,    -1,    70,   122,    -1,
      68,   122,    -1,    69,   122,    -1,    84,   122,    -1,    85,
     122,    -1,    28,    74,    94,    75,    -1,    28,   123,    -1,
     126,    -1,   124,    76,   108,    77,    -1,   124,    74,    75,
      -1,   124,    74,   125,    75,    -1,   124,    78,     3,    -1,
     124,    40,     3,    -1,   124,    38,    -1,   124,    39,    -1,
     109,    -1,   125,    80,   109,    -1,     3,    -1,     4,    -1,
       5,    -1,     6,    -1,     7,    -1,    74,   108,    75,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    94,    94,   103,   104,   116,   117,   122,   130,   138,
     147,   160,   162,   164,   169,   175,   182,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   210,   211,   212,   213,   214,   215,   216,   221,
     222,   226,   227,   232,   254,   256,   261,   263,   268,   275,
     282,   287,   292,   302,   303,   304,   308,   309,   310,   311,
     312,   313,   314,   315,   319,   320,   324,   329,   337,   345,
     353,   360,   365,   372,   380,   381,   390,   391,   399,   400,
     409,   410,   411,   412,   413,   414,   415,   416,   417,   418,
     419,   423,   424,   432,   433,   438,   439,   444,   445,   450,
     451,   456,   457,   462,   463,   465,   470,   471,   473,   475,
     477,   482,   483,   485,   490,   491,   493,   498,   499,   501,
     503,   508,   509,   517,   518,   520,   522,   524,   526,   528,
     530,   532,   534,   539,   544,   545,   550,   555,   560,   565,
     571,   573,   578,   580,   585,   587,   589,   591,   593,   595
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "INT_LITERAL",
  "FLOAT_LITERAL", "STRING_LITERAL", "CHAR_LITERAL", "KW_AUTO", "KW_BREAK",
  "KW_CASE", "KW_CHAR", "KW_CONST", "KW_CONTINUE", "KW_DEFAULT", "KW_DO",
  "KW_DOUBLE", "KW_ELSE", "KW_ENUM", "KW_EXTERN", "KW_FLOAT", "KW_FOR",
  "KW_IF", "KW_INT", "KW_LONG", "KW_RETURN", "KW_SHORT", "KW_SIGNED",
  "KW_SIZEOF", "KW_STATIC", "KW_STRUCT", "KW_SWITCH", "KW_TYPEDEF",
  "KW_UNION", "KW_UNSIGNED", "KW_VOID", "KW_VOLATILE", "KW_WHILE",
  "OP_INC", "OP_DEC", "OP_ARROW", "OP_AND", "OP_OR", "OP_EQ", "OP_NEQ",
  "OP_LEQ", "OP_GEQ", "OP_LSHIFT", "OP_RSHIFT", "OP_PLUS_A", "OP_MINUS_A",
  "OP_MUL_A", "OP_DIV_A", "OP_MOD_A", "OP_AND_A", "OP_XOR_A", "OP_OR_A",
  "OP_LSHIFT_A", "OP_RSHIFT_A", "ELLIPSIS", "'='", "'?'", "':'", "'|'",
  "'^'", "'&'", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'", "'%'", "UPREC",
  "'('", "')'", "'['", "']'", "'.'", "KW_THEN", "','", "'{'", "'}'", "';'",
  "'~'", "'!'", "$accept", "program", "ext_decl_list", "ext_decl",
  "func_def", "param_list", "param_decl", "type_spec", "type_name",
  "compound", "stmt_list", "declaration", "decl_list", "decl_item", "stmt",
  "statement", "expr_stmt", "if_stmt", "while_stmt", "do_stmt", "for_stmt",
  "return_stmt", "expression", "assign_expr", "assign_op", "ternary_expr",
  "or_expr", "and_expr", "bitor_expr", "xor_expr", "bitand_expr",
  "eq_expr", "relat_expr", "shift_expr", "add_expr", "mul_expr",
  "cast_expr", "unary_expr", "postfix_expr", "arg_list", "primary_expr", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
      61,    63,    58,   124,    94,    38,    60,    62,    43,    45,
      42,    47,    37,   315,    40,    41,    91,    93,    46,   316,
      44,   123,   125,    59,   126,    33
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    86,    87,    88,    88,    89,    89,    90,    90,    90,
      90,    91,    91,    91,    92,    92,    92,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    94,    94,    94,    94,    94,    94,    94,    95,
      95,    96,    96,    97,    98,    98,    99,    99,    99,    99,
      99,    99,    99,   100,   100,   100,   101,   101,   101,   101,
     101,   101,   101,   101,   102,   102,   103,   103,   104,   105,
     106,   106,   106,   106,   107,   107,   108,   108,   109,   109,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   111,   111,   112,   112,   113,   113,   114,   114,   115,
     115,   116,   116,   117,   117,   117,   118,   118,   118,   118,
     118,   119,   119,   119,   120,   120,   120,   121,   121,   121,
     121,   122,   122,   123,   123,   123,   123,   123,   123,   123,
     123,   123,   123,   123,   124,   124,   124,   124,   124,   124,
     124,   124,   125,   125,   126,   126,   126,   126,   126,   126
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     6,     5,     7,
       6,     1,     3,     3,     2,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     2,     2,
       2,     2,     1,     1,     1,     1,     1,     1,     1,     2,
       3,     1,     2,     3,     1,     3,     1,     2,     4,     4,
       3,     3,     4,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     1,     2,     5,     7,     5,     7,
       6,     7,     6,     7,     2,     3,     1,     3,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     5,     1,     3,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     3,     1,     3,     3,     3,
       3,     1,     3,     3,     1,     3,     3,     1,     3,     3,
       3,     1,     4,     1,     2,     2,     2,     2,     2,     2,
       2,     2,     4,     2,     1,     4,     3,     4,     3,     3,
       2,     2,     1,     3,     1,     1,     1,     1,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    18,     0,    20,    19,    17,    22,    23,    25,     0,
      24,    21,     0,     2,     3,     5,     0,     6,    28,    27,
      30,    31,    26,    29,     1,     4,    46,     0,     0,    44,
       0,     0,     0,    47,     0,    43,   144,   145,   146,   147,
     148,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    51,    76,    78,    91,    93,    95,    97,    99,   101,
     103,   106,   111,   114,   117,   121,   123,   134,     0,     0,
      11,    16,   145,    50,     0,     0,     0,    46,     0,    45,
       0,   133,     0,   124,   125,   126,   121,   128,   129,   127,
      33,    35,    34,    32,    37,    38,    36,     0,     0,   130,
     131,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    80,     0,   140,   141,     0,     0,     0,     0,     0,
       8,     0,     0,    14,     0,    49,    48,    52,     0,     0,
      47,     0,     0,   149,    77,    94,     0,    96,    98,   100,
     102,   104,   105,   109,   110,   107,   108,   112,   113,   115,
     116,   118,   119,   120,    79,   139,   136,   142,     0,     0,
     138,     0,     0,     0,     0,     0,     0,     0,    39,    64,
       0,    55,     0,    54,    41,    53,    56,    57,    58,    59,
      60,    61,     0,     7,    13,    12,    15,    10,     0,   132,
     122,     0,   137,     0,   135,    62,    63,     0,     0,     0,
      74,     0,     0,    40,    42,    65,     9,    92,   143,     0,
       0,     0,     0,    75,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    66,    68,     0,    72,     0,
      70,     0,     0,    69,    73,    71,    67
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    12,    13,    14,    15,    69,    70,   190,    97,   191,
     192,   193,    28,    29,   194,   195,   196,   197,   198,   199,
     200,   201,   202,    52,   132,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,   178,
      67
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -159
static const yytype_int16 yypact[] =
{
     747,  -159,    17,  -159,  -159,  -159,    14,  -159,  -159,    -5,
      -3,  -159,    12,   747,  -159,  -159,     6,  -159,  -159,  -159,
    -159,  -159,  -159,  -159,  -159,  -159,    -6,    42,    97,  -159,
     637,    32,   460,   -10,    13,  -159,  -159,  -159,  -159,  -159,
    -159,   680,   723,   723,   637,   637,   637,   637,   412,   637,
     637,   -33,  -159,  -159,   -25,    16,     8,     5,    10,    59,
      -4,    99,   141,   188,  -159,   451,   295,  -159,    41,    30,
    -159,    31,    35,  -159,   101,   637,   320,   -11,    74,  -159,
     412,  -159,   637,  -159,  -159,  -159,  -159,  -159,  -159,  -159,
    -159,  -159,  -159,  -159,  -159,  -159,  -159,    49,    34,  -159,
    -159,   637,   637,   637,   637,   637,   637,   637,   637,   637,
     637,   637,   637,   637,   637,   637,   637,   637,   637,   637,
     637,  -159,  -159,  -159,  -159,  -159,  -159,  -159,  -159,  -159,
    -159,  -159,   637,  -159,  -159,   128,   488,   637,   153,   114,
    -159,    41,   228,  -159,   164,  -159,  -159,   -33,    41,    53,
     116,    94,   637,  -159,  -159,    16,   -48,     8,     5,    10,
      59,    -4,    -4,    99,    99,    99,    99,   141,   141,   188,
     188,  -159,  -159,  -159,  -159,  -159,  -159,  -159,    70,   109,
    -159,   102,   104,   291,   120,   126,   536,   131,  -159,  -159,
      13,  -159,   208,  -159,  -159,  -159,  -159,  -159,  -159,  -159,
    -159,  -159,   142,  -159,  -159,  -159,  -159,  -159,    41,  -159,
    -159,   637,  -159,   637,  -159,  -159,  -159,   155,   374,   637,
    -159,   158,   637,  -159,  -159,  -159,  -159,  -159,  -159,   179,
     543,   543,    79,  -159,    80,   637,   586,   629,   291,   291,
      83,   291,    90,   291,    93,   199,  -159,   173,  -159,   291,
    -159,   291,   291,  -159,  -159,  -159,  -159
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -159,  -159,  -159,   248,  -159,   190,   125,     2,   189,   -37,
    -159,     0,  -159,   234,   -77,  -159,  -158,  -159,  -159,  -159,
    -159,  -159,   -29,   -97,  -159,    60,  -159,   168,   170,   167,
     169,   172,   118,    91,   135,   148,   -39,   -20,  -159,  -159,
    -159
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
      17,    51,    16,    74,   154,    85,    87,    88,    89,    26,
      99,   100,    24,    17,   211,    16,    77,   102,    22,    98,
      23,    81,    83,    84,    86,    86,    86,    86,    18,    86,
      86,   140,   101,    71,   143,   174,   103,    20,    21,   177,
      19,   110,   111,     1,     2,    33,   147,   101,     3,    30,
      75,    98,     4,    98,    30,     5,     6,   104,     7,     8,
     231,     9,   112,   113,    76,    32,    10,    11,    31,   106,
      32,   105,   236,   237,   156,   107,    27,   150,    71,   171,
     172,   173,    86,    78,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    86,    86,
      86,   144,   108,   109,   203,   141,   217,    68,   179,   153,
     142,   207,   145,   210,   101,   224,   228,    36,    37,    38,
      39,    40,   139,   181,   152,     1,     2,   182,   208,   183,
       3,   175,    86,   142,     4,   184,   185,     5,     6,   186,
       7,     8,    41,     9,    71,   212,   114,   115,    10,    11,
     213,   187,    42,    43,   238,   239,   180,   221,   247,   101,
     101,   245,   246,   101,   248,   249,   250,   206,   251,   209,
     101,   226,   254,   101,   255,   256,    75,    34,   146,    44,
      35,   101,    45,    46,    47,   215,   214,   216,    48,   101,
     232,    86,   229,   234,   218,   139,   188,   189,    49,    50,
     219,   163,   164,   165,   166,   222,   240,   242,   244,   116,
     117,    36,    37,    38,    39,    40,   252,   181,   230,     1,
       2,   182,   101,   183,     3,   225,   161,   162,     4,   184,
     185,     5,     6,   186,     7,     8,    41,     9,   101,     1,
       2,   233,    10,    11,     3,   187,    42,    43,     4,   167,
     168,     5,     6,   235,     7,     8,   253,     9,   118,   119,
     120,    25,    10,    11,   169,   170,   149,   205,    79,   151,
     155,   227,   158,    44,   157,   159,    45,    46,    47,   160,
       0,     0,    48,     0,     0,     0,     0,   204,     0,   139,
     223,   189,    49,    50,    36,    37,    38,    39,    40,     0,
     181,     0,     1,     2,   182,     0,   183,     3,     0,     0,
       0,     4,   184,   185,     5,     6,   186,     7,     8,    41,
       9,     0,     0,     0,     0,    10,    11,     0,   187,    42,
      43,     1,     2,   133,   134,   135,     3,     0,     0,     0,
       4,     0,     0,     5,     6,     0,     7,     8,     0,     9,
       0,     0,     0,     0,    10,    11,    44,     0,     0,    45,
      46,    47,     0,     0,     0,    48,     0,     0,     0,   136,
       0,   137,   139,   138,   189,    49,    50,    36,    37,    38,
      39,    40,     0,     0,     0,     1,     2,     0,     0,     0,
       3,     0,     0,     0,     4,   148,     0,     5,     6,     0,
       7,     8,    41,     9,     0,     0,     0,     0,    10,    11,
       0,     0,    42,    43,     0,    36,    37,    38,    39,    40,
       0,     0,     0,    90,     0,     0,     0,     0,    91,     0,
       0,     0,    92,     0,     0,    93,    94,     0,    95,    44,
      41,     0,    45,    46,    47,     0,     0,    96,    48,     0,
      42,    43,     0,     0,     0,     0,     0,   189,    49,    50,
       0,     0,     0,    36,    72,    38,    39,    40,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    44,     0,     0,
      45,    46,    47,     0,     0,     0,    48,     0,    41,     0,
       0,    36,    37,    38,    39,    40,    49,    50,    42,    43,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
       0,   131,     0,     0,     0,     0,    41,     0,     0,     0,
       0,     0,     0,     0,     0,    44,    42,    43,    45,    46,
      47,     0,     0,     0,    48,     0,     0,    73,     0,    36,
      37,    38,    39,    40,    49,    50,    36,    37,    38,    39,
      40,     0,     0,    44,     0,     0,    45,    46,    47,     0,
       0,     0,    48,   176,    41,     0,     0,     0,     0,     0,
       0,    41,    49,    50,    42,    43,     0,     0,     0,     0,
       0,    42,    43,     0,     0,     0,     0,     0,     0,    36,
      37,    38,    39,    40,     0,     0,     0,     0,     0,     0,
       0,    44,     0,     0,    45,    46,    47,     0,    44,     0,
      48,    45,    46,    47,    41,     0,     0,    48,     0,   220,
      49,    50,     0,     0,    42,    43,   189,    49,    50,     0,
       0,     0,    36,    37,    38,    39,    40,     0,     0,     0,
      36,    37,    38,    39,    40,     0,     0,     0,     0,     0,
       0,    44,     0,     0,    45,    46,    47,    41,     0,     0,
      48,   241,     0,     0,     0,    41,     0,    42,    43,     0,
      49,    50,     0,     0,     0,    42,    43,     0,     0,     0,
       0,     0,     0,    36,    37,    38,    39,    40,     0,     0,
       0,     0,     0,     0,    44,     0,     0,    45,    46,    47,
       0,     0,    44,    48,   243,    45,    46,    47,    41,     0,
       0,    48,     0,    49,    50,     0,     0,     0,    42,    43,
       0,    49,    50,     0,     0,     0,    36,    37,    38,    39,
      40,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    44,     0,     0,    45,    46,
      47,    41,     0,     0,    80,     0,     0,     0,     1,     2,
       0,    42,    43,     3,    49,    50,     0,     4,     0,     0,
       5,     6,     0,     7,     8,     0,     9,     0,     0,     0,
       0,    10,    11,     0,     0,     0,     0,     0,    44,     0,
       0,    45,    46,    47,     0,     0,     0,    82,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    49,    50
};

static const yytype_int16 yycheck[] =
{
       0,    30,     0,    32,   101,    44,    45,    46,    47,     3,
      49,    50,     0,    13,    62,    13,     3,    42,    23,    48,
      23,    41,    42,    43,    44,    45,    46,    47,    11,    49,
      50,    68,    80,    31,     3,   132,    61,    23,    24,   136,
      23,    45,    46,    11,    12,     3,    75,    80,    16,    60,
      60,    80,    20,    82,    60,    23,    24,    41,    26,    27,
     218,    29,    66,    67,    74,    76,    34,    35,    74,    64,
      76,    63,   230,   231,   103,    65,    70,     3,    76,   118,
     119,   120,   102,    70,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,    70,    43,    44,   141,    75,   183,    75,   137,    75,
      80,   148,    77,   152,    80,   192,   213,     3,     4,     5,
       6,     7,    81,     9,    75,    11,    12,    13,    75,    15,
      16,     3,   152,    80,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,   142,    75,    47,    48,    34,    35,
      80,    37,    38,    39,    75,    75,     3,   186,    75,    80,
      80,   238,   239,    80,   241,    75,   243,     3,    75,    75,
      80,   208,   249,    80,   251,   252,    60,    80,    77,    65,
      83,    80,    68,    69,    70,    83,    77,    83,    74,    80,
     219,   211,    37,   222,    74,    81,    82,    83,    84,    85,
      74,   110,   111,   112,   113,    74,   235,   236,   237,    68,
      69,     3,     4,     5,     6,     7,    17,     9,   218,    11,
      12,    13,    80,    15,    16,    83,   108,   109,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    80,    11,
      12,    83,    34,    35,    16,    37,    38,    39,    20,   114,
     115,    23,    24,    74,    26,    27,    83,    29,    70,    71,
      72,    13,    34,    35,   116,   117,    76,   142,    34,    80,
     102,   211,   105,    65,   104,   106,    68,    69,    70,   107,
      -1,    -1,    74,    -1,    -1,    -1,    -1,    59,    -1,    81,
      82,    83,    84,    85,     3,     4,     5,     6,     7,    -1,
       9,    -1,    11,    12,    13,    -1,    15,    16,    -1,    -1,
      -1,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    -1,    -1,    -1,    -1,    34,    35,    -1,    37,    38,
      39,    11,    12,    38,    39,    40,    16,    -1,    -1,    -1,
      20,    -1,    -1,    23,    24,    -1,    26,    27,    -1,    29,
      -1,    -1,    -1,    -1,    34,    35,    65,    -1,    -1,    68,
      69,    70,    -1,    -1,    -1,    74,    -1,    -1,    -1,    74,
      -1,    76,    81,    78,    83,    84,    85,     3,     4,     5,
       6,     7,    -1,    -1,    -1,    11,    12,    -1,    -1,    -1,
      16,    -1,    -1,    -1,    20,    75,    -1,    23,    24,    -1,
      26,    27,    28,    29,    -1,    -1,    -1,    -1,    34,    35,
      -1,    -1,    38,    39,    -1,     3,     4,     5,     6,     7,
      -1,    -1,    -1,    11,    -1,    -1,    -1,    -1,    16,    -1,
      -1,    -1,    20,    -1,    -1,    23,    24,    -1,    26,    65,
      28,    -1,    68,    69,    70,    -1,    -1,    35,    74,    -1,
      38,    39,    -1,    -1,    -1,    -1,    -1,    83,    84,    85,
      -1,    -1,    -1,     3,     4,     5,     6,     7,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,
      68,    69,    70,    -1,    -1,    -1,    74,    -1,    28,    -1,
      -1,     3,     4,     5,     6,     7,    84,    85,    38,    39,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      -1,    60,    -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    38,    39,    68,    69,
      70,    -1,    -1,    -1,    74,    -1,    -1,    77,    -1,     3,
       4,     5,     6,     7,    84,    85,     3,     4,     5,     6,
       7,    -1,    -1,    65,    -1,    -1,    68,    69,    70,    -1,
      -1,    -1,    74,    75,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    28,    84,    85,    38,    39,    -1,    -1,    -1,    -1,
      -1,    38,    39,    -1,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,     6,     7,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    65,    -1,    -1,    68,    69,    70,    -1,    65,    -1,
      74,    68,    69,    70,    28,    -1,    -1,    74,    -1,    83,
      84,    85,    -1,    -1,    38,    39,    83,    84,    85,    -1,
      -1,    -1,     3,     4,     5,     6,     7,    -1,    -1,    -1,
       3,     4,     5,     6,     7,    -1,    -1,    -1,    -1,    -1,
      -1,    65,    -1,    -1,    68,    69,    70,    28,    -1,    -1,
      74,    75,    -1,    -1,    -1,    28,    -1,    38,    39,    -1,
      84,    85,    -1,    -1,    -1,    38,    39,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,     7,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    -1,    -1,    68,    69,    70,
      -1,    -1,    65,    74,    75,    68,    69,    70,    28,    -1,
      -1,    74,    -1,    84,    85,    -1,    -1,    -1,    38,    39,
      -1,    84,    85,    -1,    -1,    -1,     3,     4,     5,     6,
       7,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    68,    69,
      70,    28,    -1,    -1,    74,    -1,    -1,    -1,    11,    12,
      -1,    38,    39,    16,    84,    85,    -1,    20,    -1,    -1,
      23,    24,    -1,    26,    27,    -1,    29,    -1,    -1,    -1,
      -1,    34,    35,    -1,    -1,    -1,    -1,    -1,    65,    -1,
      -1,    68,    69,    70,    -1,    -1,    -1,    74,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    84,    85
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    11,    12,    16,    20,    23,    24,    26,    27,    29,
      34,    35,    87,    88,    89,    90,    93,    97,    11,    23,
      23,    24,    23,    23,     0,    89,     3,    70,    98,    99,
      60,    74,    76,     3,    80,    83,     3,     4,     5,     6,
       7,    28,    38,    39,    65,    68,    69,    70,    74,    84,
      85,   108,   109,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   126,    75,    91,
      92,    93,     4,    77,   108,    60,    74,     3,    70,    99,
      74,   123,    74,   123,   123,   122,   123,   122,   122,   122,
      11,    16,    20,    23,    24,    26,    35,    94,   108,   122,
     122,    80,    42,    61,    41,    63,    64,    65,    43,    44,
      45,    46,    66,    67,    47,    48,    68,    69,    70,    71,
      72,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    60,   110,    38,    39,    40,    74,    76,    78,    81,
      95,    75,    80,     3,    70,    77,    77,   108,    75,    91,
       3,    94,    75,    75,   109,   113,   108,   114,   115,   116,
     117,   118,   118,   119,   119,   119,   119,   120,   120,   121,
     121,   122,   122,   122,   109,     3,    75,   109,   125,   108,
       3,     9,    13,    15,    21,    22,    25,    37,    82,    83,
      93,    95,    96,    97,   100,   101,   102,   103,   104,   105,
     106,   107,   108,    95,    59,    92,     3,    95,    75,    75,
     122,    62,    75,    80,    77,    83,    83,   100,    74,    74,
      83,   108,    74,    82,   100,    83,    95,   111,   109,    37,
      97,   102,   108,    83,   108,    74,   102,   102,    75,    75,
     108,    75,   108,    75,   108,   100,   100,    75,   100,    75,
     100,    75,    17,    83,   100,   100,   100
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 95 "p2/parser.y"
    {
            (yyval.node) = ast_new(N_PROGRAM,"program",yylineno);
            ast_add((yyval.node),(yyvsp[(1) - (1)].node));
            parse_root = (yyval.node);
        ;}
    break;

  case 3:
#line 103 "p2/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 4:
#line 105 "p2/parser.y"
    {
            if ((yyvsp[(1) - (2)].node) && (yyvsp[(1) - (2)].node)->kind == N_BLOCK) {
                ast_add((yyvsp[(1) - (2)].node),(yyvsp[(2) - (2)].node)); (yyval.node) = (yyvsp[(1) - (2)].node);
            } else {
                (yyval.node) = ast_new(N_BLOCK,NULL,yylineno);
                ast_add((yyval.node),(yyvsp[(1) - (2)].node)); ast_add((yyval.node),(yyvsp[(2) - (2)].node));
            }
        ;}
    break;

  case 5:
#line 116 "p2/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 6:
#line 117 "p2/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 7:
#line 123 "p2/parser.y"
    {
            (yyval.node) = ast_new(N_FUNC_DEF,(yyvsp[(2) - (6)].sval),yylineno);
            ast_add((yyval.node), ast_new(N_TYPE,(yyvsp[(1) - (6)].sval),yylineno));
            ast_add((yyval.node), (yyvsp[(4) - (6)].node));
            ast_add((yyval.node), (yyvsp[(6) - (6)].node));
            free((yyvsp[(1) - (6)].sval)); free((yyvsp[(2) - (6)].sval));
        ;}
    break;

  case 8:
#line 131 "p2/parser.y"
    {
            (yyval.node) = ast_new(N_FUNC_DEF,(yyvsp[(2) - (5)].sval),yylineno);
            ast_add((yyval.node), ast_new(N_TYPE,(yyvsp[(1) - (5)].sval),yylineno));
            ast_add((yyval.node), ast_new(N_PARAM_LIST,"(empty)",yylineno));
            ast_add((yyval.node), (yyvsp[(5) - (5)].node));
            free((yyvsp[(1) - (5)].sval)); free((yyvsp[(2) - (5)].sval));
        ;}
    break;

  case 9:
#line 139 "p2/parser.y"
    {
            char buf[128]; snprintf(buf,sizeof(buf),"*%s",(yyvsp[(3) - (7)].sval));
            (yyval.node) = ast_new(N_FUNC_DEF,buf,yylineno);
            ast_add((yyval.node), ast_new(N_TYPE,(yyvsp[(1) - (7)].sval),yylineno));
            ast_add((yyval.node), (yyvsp[(5) - (7)].node));
            ast_add((yyval.node), (yyvsp[(7) - (7)].node));
            free((yyvsp[(1) - (7)].sval)); free((yyvsp[(3) - (7)].sval));
        ;}
    break;

  case 10:
#line 148 "p2/parser.y"
    {
            char buf[128]; snprintf(buf,sizeof(buf),"*%s",(yyvsp[(3) - (6)].sval));
            (yyval.node) = ast_new(N_FUNC_DEF,buf,yylineno);
            ast_add((yyval.node), ast_new(N_TYPE,(yyvsp[(1) - (6)].sval),yylineno));
            ast_add((yyval.node), ast_new(N_PARAM_LIST,"(empty)",yylineno));
            ast_add((yyval.node), (yyvsp[(6) - (6)].node));
            free((yyvsp[(1) - (6)].sval)); free((yyvsp[(3) - (6)].sval));
        ;}
    break;

  case 11:
#line 161 "p2/parser.y"
    { (yyval.node) = ast_new(N_PARAM_LIST,NULL,yylineno); ast_add((yyval.node),(yyvsp[(1) - (1)].node)); ;}
    break;

  case 12:
#line 163 "p2/parser.y"
    { ast_add((yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node)); (yyval.node)=(yyvsp[(1) - (3)].node); ;}
    break;

  case 13:
#line 165 "p2/parser.y"
    { ast_add((yyvsp[(1) - (3)].node),ast_new(N_PARAM,"...",yylineno)); (yyval.node)=(yyvsp[(1) - (3)].node); ;}
    break;

  case 14:
#line 170 "p2/parser.y"
    {
            (yyval.node) = ast_new(N_PARAM,(yyvsp[(2) - (2)].sval),yylineno);
            ast_add((yyval.node), ast_new(N_TYPE,(yyvsp[(1) - (2)].sval),yylineno));
            free((yyvsp[(1) - (2)].sval)); free((yyvsp[(2) - (2)].sval));
        ;}
    break;

  case 15:
#line 176 "p2/parser.y"
    {
            char buf[128]; snprintf(buf,sizeof(buf),"*%s",(yyvsp[(3) - (3)].sval));
            (yyval.node) = ast_new(N_PARAM,buf,yylineno);
            ast_add((yyval.node), ast_new(N_TYPE,(yyvsp[(1) - (3)].sval),yylineno));
            free((yyvsp[(1) - (3)].sval)); free((yyvsp[(3) - (3)].sval));
        ;}
    break;

  case 16:
#line 183 "p2/parser.y"
    {
            (yyval.node) = ast_new(N_PARAM,"(unnamed)",yylineno);
            ast_add((yyval.node), ast_new(N_TYPE,(yyvsp[(1) - (1)].sval),yylineno));
            free((yyvsp[(1) - (1)].sval));
        ;}
    break;

  case 17:
#line 192 "p2/parser.y"
    { (yyval.sval) = strdup("int");          ;}
    break;

  case 18:
#line 193 "p2/parser.y"
    { (yyval.sval) = strdup("char");         ;}
    break;

  case 19:
#line 194 "p2/parser.y"
    { (yyval.sval) = strdup("float");        ;}
    break;

  case 20:
#line 195 "p2/parser.y"
    { (yyval.sval) = strdup("double");       ;}
    break;

  case 21:
#line 196 "p2/parser.y"
    { (yyval.sval) = strdup("void");         ;}
    break;

  case 22:
#line 197 "p2/parser.y"
    { (yyval.sval) = strdup("long");         ;}
    break;

  case 23:
#line 198 "p2/parser.y"
    { (yyval.sval) = strdup("short");        ;}
    break;

  case 24:
#line 199 "p2/parser.y"
    { (yyval.sval) = strdup("unsigned");     ;}
    break;

  case 25:
#line 200 "p2/parser.y"
    { (yyval.sval) = strdup("signed");       ;}
    break;

  case 26:
#line 201 "p2/parser.y"
    { (yyval.sval) = strdup("static int");   ;}
    break;

  case 27:
#line 202 "p2/parser.y"
    { (yyval.sval) = strdup("const int");    ;}
    break;

  case 28:
#line 203 "p2/parser.y"
    { (yyval.sval) = strdup("const char");   ;}
    break;

  case 29:
#line 204 "p2/parser.y"
    { (yyval.sval) = strdup("unsigned int"); ;}
    break;

  case 30:
#line 205 "p2/parser.y"
    { (yyval.sval) = strdup("long int");     ;}
    break;

  case 31:
#line 206 "p2/parser.y"
    { (yyval.sval) = strdup("long long");    ;}
    break;

  case 32:
#line 210 "p2/parser.y"
    { (yyval.sval) = strdup("int");    ;}
    break;

  case 33:
#line 211 "p2/parser.y"
    { (yyval.sval) = strdup("char");   ;}
    break;

  case 34:
#line 212 "p2/parser.y"
    { (yyval.sval) = strdup("float");  ;}
    break;

  case 35:
#line 213 "p2/parser.y"
    { (yyval.sval) = strdup("double"); ;}
    break;

  case 36:
#line 214 "p2/parser.y"
    { (yyval.sval) = strdup("void");   ;}
    break;

  case 37:
#line 215 "p2/parser.y"
    { (yyval.sval) = strdup("long");   ;}
    break;

  case 38:
#line 216 "p2/parser.y"
    { (yyval.sval) = strdup("short");  ;}
    break;

  case 39:
#line 221 "p2/parser.y"
    { (yyval.node) = ast_new(N_BLOCK,"(empty)",yylineno); ;}
    break;

  case 40:
#line 222 "p2/parser.y"
    { (yyval.node) = (yyvsp[(2) - (3)].node); ;}
    break;

  case 41:
#line 226 "p2/parser.y"
    { (yyval.node) = ast_new(N_BLOCK,NULL,yylineno); ast_add((yyval.node),(yyvsp[(1) - (1)].node)); ;}
    break;

  case 42:
#line 227 "p2/parser.y"
    { ast_add((yyvsp[(1) - (2)].node),(yyvsp[(2) - (2)].node)); (yyval.node)=(yyvsp[(1) - (2)].node); ;}
    break;

  case 43:
#line 233 "p2/parser.y"
    {
            (yyval.node) = (yyvsp[(2) - (3)].node);
            /* attach type to every declarator */
            for (int i=0;i<(yyvsp[(2) - (3)].node)->nchildren;i++) {
                ASTNode *d = (yyvsp[(2) - (3)].node)->children[i];
                ASTNode *tc = ast_new(N_TYPE,(yyvsp[(1) - (3)].sval),d->line);
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
            free((yyvsp[(1) - (3)].sval));
        ;}
    break;

  case 44:
#line 255 "p2/parser.y"
    { (yyval.node) = ast_new(N_BLOCK,"decl-list",yylineno); ast_add((yyval.node),(yyvsp[(1) - (1)].node)); ;}
    break;

  case 45:
#line 257 "p2/parser.y"
    { ast_add((yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node)); (yyval.node)=(yyvsp[(1) - (3)].node); ;}
    break;

  case 46:
#line 262 "p2/parser.y"
    { (yyval.node) = ast_new(N_DECL,(yyvsp[(1) - (1)].sval),yylineno); free((yyvsp[(1) - (1)].sval)); ;}
    break;

  case 47:
#line 264 "p2/parser.y"
    {
            char buf[128]; snprintf(buf,sizeof(buf),"*%s",(yyvsp[(2) - (2)].sval));
            (yyval.node) = ast_new(N_DECL,buf,yylineno); free((yyvsp[(2) - (2)].sval));
        ;}
    break;

  case 48:
#line 269 "p2/parser.y"
    {
            char buf[128]; snprintf(buf,sizeof(buf),"%s[]",(yyvsp[(1) - (4)].sval));
            (yyval.node) = ast_new(N_ARRAY_DECL,buf,yylineno);
            ast_add((yyval.node),(yyvsp[(3) - (4)].node));
            free((yyvsp[(1) - (4)].sval));
        ;}
    break;

  case 49:
#line 276 "p2/parser.y"
    {
            char buf[128]; snprintf(buf,sizeof(buf),"%s",(yyvsp[(1) - (4)].sval));
            (yyval.node) = ast_new(N_ARRAY_DECL,buf,yylineno);
            ast_add((yyval.node), ast_new(N_INT_LIT,(yyvsp[(3) - (4)].sval),yylineno));
            free((yyvsp[(1) - (4)].sval)); free((yyvsp[(3) - (4)].sval));
        ;}
    break;

  case 50:
#line 283 "p2/parser.y"
    {
            char buf[128]; snprintf(buf,sizeof(buf),"%s[]",(yyvsp[(1) - (3)].sval));
            (yyval.node) = ast_new(N_ARRAY_DECL,buf,yylineno); free((yyvsp[(1) - (3)].sval));
        ;}
    break;

  case 51:
#line 288 "p2/parser.y"
    {
            (yyval.node) = ast_new(N_DECL_INIT,(yyvsp[(1) - (3)].sval),yylineno);
            ast_add((yyval.node),(yyvsp[(3) - (3)].node)); free((yyvsp[(1) - (3)].sval));
        ;}
    break;

  case 52:
#line 293 "p2/parser.y"
    {
            char buf[128]; snprintf(buf,sizeof(buf),"*%s",(yyvsp[(2) - (4)].sval));
            (yyval.node) = ast_new(N_DECL_INIT,buf,yylineno);
            ast_add((yyval.node),(yyvsp[(4) - (4)].node)); free((yyvsp[(2) - (4)].sval));
        ;}
    break;

  case 53:
#line 302 "p2/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 54:
#line 303 "p2/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 55:
#line 304 "p2/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 56:
#line 308 "p2/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 57:
#line 309 "p2/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 58:
#line 310 "p2/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 59:
#line 311 "p2/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 60:
#line 312 "p2/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 61:
#line 313 "p2/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 62:
#line 314 "p2/parser.y"
    { (yyval.node) = ast_new(N_BREAK,"break",yylineno);    ;}
    break;

  case 63:
#line 315 "p2/parser.y"
    { (yyval.node) = ast_new(N_CONTINUE,"continue",yylineno); ;}
    break;

  case 64:
#line 319 "p2/parser.y"
    { (yyval.node) = ast_new(N_EXPR_STMT,NULL,yylineno); ;}
    break;

  case 65:
#line 320 "p2/parser.y"
    { (yyval.node) = (yyvsp[(1) - (2)].node); ;}
    break;

  case 66:
#line 325 "p2/parser.y"
    {
            (yyval.node) = ast_new(N_IF,"if",yylineno);
            ast_add((yyval.node),(yyvsp[(3) - (5)].node)); ast_add((yyval.node),(yyvsp[(5) - (5)].node));
        ;}
    break;

  case 67:
#line 330 "p2/parser.y"
    {
            (yyval.node) = ast_new(N_IF,"if-else",yylineno);
            ast_add((yyval.node),(yyvsp[(3) - (7)].node)); ast_add((yyval.node),(yyvsp[(5) - (7)].node)); ast_add((yyval.node),(yyvsp[(7) - (7)].node));
        ;}
    break;

  case 68:
#line 338 "p2/parser.y"
    {
            (yyval.node) = ast_new(N_WHILE,"while",yylineno);
            ast_add((yyval.node),(yyvsp[(3) - (5)].node)); ast_add((yyval.node),(yyvsp[(5) - (5)].node));
        ;}
    break;

  case 69:
#line 346 "p2/parser.y"
    {
            (yyval.node) = ast_new(N_DO_WHILE,"do-while",yylineno);
            ast_add((yyval.node),(yyvsp[(2) - (7)].node)); ast_add((yyval.node),(yyvsp[(5) - (7)].node));
        ;}
    break;

  case 70:
#line 354 "p2/parser.y"
    {
            (yyval.node) = ast_new(N_FOR,"for",yylineno);
            ast_add((yyval.node),(yyvsp[(3) - (6)].node)); ast_add((yyval.node),(yyvsp[(4) - (6)].node));
            ast_add((yyval.node),ast_new(N_EXPR_STMT,NULL,yylineno));
            ast_add((yyval.node),(yyvsp[(6) - (6)].node));
        ;}
    break;

  case 71:
#line 361 "p2/parser.y"
    {
            (yyval.node) = ast_new(N_FOR,"for",yylineno);
            ast_add((yyval.node),(yyvsp[(3) - (7)].node)); ast_add((yyval.node),(yyvsp[(4) - (7)].node)); ast_add((yyval.node),(yyvsp[(5) - (7)].node)); ast_add((yyval.node),(yyvsp[(7) - (7)].node));
        ;}
    break;

  case 72:
#line 366 "p2/parser.y"
    {
            (yyval.node) = ast_new(N_FOR,"for(C99)",yylineno);
            ast_add((yyval.node),(yyvsp[(3) - (6)].node)); ast_add((yyval.node),(yyvsp[(4) - (6)].node));
            ast_add((yyval.node),ast_new(N_EXPR_STMT,NULL,yylineno));
            ast_add((yyval.node),(yyvsp[(6) - (6)].node));
        ;}
    break;

  case 73:
#line 373 "p2/parser.y"
    {
            (yyval.node) = ast_new(N_FOR,"for(C99)",yylineno);
            ast_add((yyval.node),(yyvsp[(3) - (7)].node)); ast_add((yyval.node),(yyvsp[(4) - (7)].node)); ast_add((yyval.node),(yyvsp[(5) - (7)].node)); ast_add((yyval.node),(yyvsp[(7) - (7)].node));
        ;}
    break;

  case 74:
#line 380 "p2/parser.y"
    { (yyval.node) = ast_new(N_RETURN,"return",yylineno); ;}
    break;

  case 75:
#line 382 "p2/parser.y"
    {
            (yyval.node) = ast_new(N_RETURN,"return",yylineno);
            ast_add((yyval.node),(yyvsp[(2) - (3)].node));
        ;}
    break;

  case 76:
#line 390 "p2/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 77:
#line 392 "p2/parser.y"
    {
            (yyval.node) = ast_new(N_BINOP,",",yylineno);
            ast_add((yyval.node),(yyvsp[(1) - (3)].node)); ast_add((yyval.node),(yyvsp[(3) - (3)].node));
        ;}
    break;

  case 78:
#line 399 "p2/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 79:
#line 401 "p2/parser.y"
    {
            (yyval.node) = ast_new(N_ASSIGN,(yyvsp[(2) - (3)].sval),yylineno);
            ast_add((yyval.node),(yyvsp[(1) - (3)].node)); ast_add((yyval.node),(yyvsp[(3) - (3)].node));
            free((yyvsp[(2) - (3)].sval));
        ;}
    break;

  case 80:
#line 409 "p2/parser.y"
    { (yyval.sval) = strdup("=");   ;}
    break;

  case 81:
#line 410 "p2/parser.y"
    { (yyval.sval) = strdup("+=");  ;}
    break;

  case 82:
#line 411 "p2/parser.y"
    { (yyval.sval) = strdup("-=");  ;}
    break;

  case 83:
#line 412 "p2/parser.y"
    { (yyval.sval) = strdup("*=");  ;}
    break;

  case 84:
#line 413 "p2/parser.y"
    { (yyval.sval) = strdup("/=");  ;}
    break;

  case 85:
#line 414 "p2/parser.y"
    { (yyval.sval) = strdup("%=");  ;}
    break;

  case 86:
#line 415 "p2/parser.y"
    { (yyval.sval) = strdup("&=");  ;}
    break;

  case 87:
#line 416 "p2/parser.y"
    { (yyval.sval) = strdup("^=");  ;}
    break;

  case 88:
#line 417 "p2/parser.y"
    { (yyval.sval) = strdup("|=");  ;}
    break;

  case 89:
#line 418 "p2/parser.y"
    { (yyval.sval) = strdup("<<="); ;}
    break;

  case 90:
#line 419 "p2/parser.y"
    { (yyval.sval) = strdup(">>="); ;}
    break;

  case 91:
#line 423 "p2/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 92:
#line 425 "p2/parser.y"
    {
            (yyval.node) = ast_new(N_TERNARY,"?:",yylineno);
            ast_add((yyval.node),(yyvsp[(1) - (5)].node)); ast_add((yyval.node),(yyvsp[(3) - (5)].node)); ast_add((yyval.node),(yyvsp[(5) - (5)].node));
        ;}
    break;

  case 93:
#line 432 "p2/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 94:
#line 434 "p2/parser.y"
    { (yyval.node) = ast_new(N_BINOP,"||",yylineno); ast_add((yyval.node),(yyvsp[(1) - (3)].node)); ast_add((yyval.node),(yyvsp[(3) - (3)].node)); ;}
    break;

  case 95:
#line 438 "p2/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 96:
#line 440 "p2/parser.y"
    { (yyval.node) = ast_new(N_BINOP,"&&",yylineno); ast_add((yyval.node),(yyvsp[(1) - (3)].node)); ast_add((yyval.node),(yyvsp[(3) - (3)].node)); ;}
    break;

  case 97:
#line 444 "p2/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 98:
#line 446 "p2/parser.y"
    { (yyval.node) = ast_new(N_BINOP,"|",yylineno); ast_add((yyval.node),(yyvsp[(1) - (3)].node)); ast_add((yyval.node),(yyvsp[(3) - (3)].node)); ;}
    break;

  case 99:
#line 450 "p2/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 100:
#line 452 "p2/parser.y"
    { (yyval.node) = ast_new(N_BINOP,"^",yylineno); ast_add((yyval.node),(yyvsp[(1) - (3)].node)); ast_add((yyval.node),(yyvsp[(3) - (3)].node)); ;}
    break;

  case 101:
#line 456 "p2/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 102:
#line 458 "p2/parser.y"
    { (yyval.node) = ast_new(N_BINOP,"&",yylineno); ast_add((yyval.node),(yyvsp[(1) - (3)].node)); ast_add((yyval.node),(yyvsp[(3) - (3)].node)); ;}
    break;

  case 103:
#line 462 "p2/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 104:
#line 464 "p2/parser.y"
    { (yyval.node) = ast_new(N_BINOP,"==",yylineno); ast_add((yyval.node),(yyvsp[(1) - (3)].node)); ast_add((yyval.node),(yyvsp[(3) - (3)].node)); ;}
    break;

  case 105:
#line 466 "p2/parser.y"
    { (yyval.node) = ast_new(N_BINOP,"!=",yylineno); ast_add((yyval.node),(yyvsp[(1) - (3)].node)); ast_add((yyval.node),(yyvsp[(3) - (3)].node)); ;}
    break;

  case 106:
#line 470 "p2/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 107:
#line 472 "p2/parser.y"
    { (yyval.node) = ast_new(N_BINOP,"<",yylineno);  ast_add((yyval.node),(yyvsp[(1) - (3)].node)); ast_add((yyval.node),(yyvsp[(3) - (3)].node)); ;}
    break;

  case 108:
#line 474 "p2/parser.y"
    { (yyval.node) = ast_new(N_BINOP,">",yylineno);  ast_add((yyval.node),(yyvsp[(1) - (3)].node)); ast_add((yyval.node),(yyvsp[(3) - (3)].node)); ;}
    break;

  case 109:
#line 476 "p2/parser.y"
    { (yyval.node) = ast_new(N_BINOP,"<=",yylineno); ast_add((yyval.node),(yyvsp[(1) - (3)].node)); ast_add((yyval.node),(yyvsp[(3) - (3)].node)); ;}
    break;

  case 110:
#line 478 "p2/parser.y"
    { (yyval.node) = ast_new(N_BINOP,">=",yylineno); ast_add((yyval.node),(yyvsp[(1) - (3)].node)); ast_add((yyval.node),(yyvsp[(3) - (3)].node)); ;}
    break;

  case 111:
#line 482 "p2/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 112:
#line 484 "p2/parser.y"
    { (yyval.node) = ast_new(N_BINOP,"<<",yylineno); ast_add((yyval.node),(yyvsp[(1) - (3)].node)); ast_add((yyval.node),(yyvsp[(3) - (3)].node)); ;}
    break;

  case 113:
#line 486 "p2/parser.y"
    { (yyval.node) = ast_new(N_BINOP,">>",yylineno); ast_add((yyval.node),(yyvsp[(1) - (3)].node)); ast_add((yyval.node),(yyvsp[(3) - (3)].node)); ;}
    break;

  case 114:
#line 490 "p2/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 115:
#line 492 "p2/parser.y"
    { (yyval.node) = ast_new(N_BINOP,"+",yylineno); ast_add((yyval.node),(yyvsp[(1) - (3)].node)); ast_add((yyval.node),(yyvsp[(3) - (3)].node)); ;}
    break;

  case 116:
#line 494 "p2/parser.y"
    { (yyval.node) = ast_new(N_BINOP,"-",yylineno); ast_add((yyval.node),(yyvsp[(1) - (3)].node)); ast_add((yyval.node),(yyvsp[(3) - (3)].node)); ;}
    break;

  case 117:
#line 498 "p2/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 118:
#line 500 "p2/parser.y"
    { (yyval.node) = ast_new(N_BINOP,"*",yylineno); ast_add((yyval.node),(yyvsp[(1) - (3)].node)); ast_add((yyval.node),(yyvsp[(3) - (3)].node)); ;}
    break;

  case 119:
#line 502 "p2/parser.y"
    { (yyval.node) = ast_new(N_BINOP,"/",yylineno); ast_add((yyval.node),(yyvsp[(1) - (3)].node)); ast_add((yyval.node),(yyvsp[(3) - (3)].node)); ;}
    break;

  case 120:
#line 504 "p2/parser.y"
    { (yyval.node) = ast_new(N_BINOP,"%",yylineno); ast_add((yyval.node),(yyvsp[(1) - (3)].node)); ast_add((yyval.node),(yyvsp[(3) - (3)].node)); ;}
    break;

  case 121:
#line 508 "p2/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 122:
#line 510 "p2/parser.y"
    {
            (yyval.node) = ast_new(N_UNOP,(yyvsp[(2) - (4)].sval),yylineno);
            ast_add((yyval.node),(yyvsp[(4) - (4)].node)); free((yyvsp[(2) - (4)].sval));
        ;}
    break;

  case 123:
#line 517 "p2/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 124:
#line 519 "p2/parser.y"
    { (yyval.node) = ast_new(N_UNOP,"pre++",yylineno); ast_add((yyval.node),(yyvsp[(2) - (2)].node)); ;}
    break;

  case 125:
#line 521 "p2/parser.y"
    { (yyval.node) = ast_new(N_UNOP,"pre--",yylineno); ast_add((yyval.node),(yyvsp[(2) - (2)].node)); ;}
    break;

  case 126:
#line 523 "p2/parser.y"
    { (yyval.node) = ast_new(N_UNOP,"addr",yylineno); ast_add((yyval.node),(yyvsp[(2) - (2)].node)); ;}
    break;

  case 127:
#line 525 "p2/parser.y"
    { (yyval.node) = ast_new(N_UNOP,"deref",yylineno); ast_add((yyval.node),(yyvsp[(2) - (2)].node)); ;}
    break;

  case 128:
#line 527 "p2/parser.y"
    { (yyval.node) = ast_new(N_UNOP,"u+",yylineno); ast_add((yyval.node),(yyvsp[(2) - (2)].node)); ;}
    break;

  case 129:
#line 529 "p2/parser.y"
    { (yyval.node) = ast_new(N_UNOP,"u-",yylineno); ast_add((yyval.node),(yyvsp[(2) - (2)].node)); ;}
    break;

  case 130:
#line 531 "p2/parser.y"
    { (yyval.node) = ast_new(N_UNOP,"~",yylineno); ast_add((yyval.node),(yyvsp[(2) - (2)].node)); ;}
    break;

  case 131:
#line 533 "p2/parser.y"
    { (yyval.node) = ast_new(N_UNOP,"!",yylineno); ast_add((yyval.node),(yyvsp[(2) - (2)].node)); ;}
    break;

  case 132:
#line 535 "p2/parser.y"
    {
            (yyval.node) = ast_new(N_UNOP,"sizeof",yylineno);
            ast_add((yyval.node), ast_new(N_TYPE,(yyvsp[(3) - (4)].sval),yylineno)); free((yyvsp[(3) - (4)].sval));
        ;}
    break;

  case 133:
#line 540 "p2/parser.y"
    { (yyval.node) = ast_new(N_UNOP,"sizeof",yylineno); ast_add((yyval.node),(yyvsp[(2) - (2)].node)); ;}
    break;

  case 134:
#line 544 "p2/parser.y"
    { (yyval.node) = (yyvsp[(1) - (1)].node); ;}
    break;

  case 135:
#line 546 "p2/parser.y"
    {
            (yyval.node) = ast_new(N_INDEX,"[]",yylineno);
            ast_add((yyval.node),(yyvsp[(1) - (4)].node)); ast_add((yyval.node),(yyvsp[(3) - (4)].node));
        ;}
    break;

  case 136:
#line 551 "p2/parser.y"
    {
            (yyval.node) = ast_new(N_CALL,"call",yylineno);
            ast_add((yyval.node),(yyvsp[(1) - (3)].node));
        ;}
    break;

  case 137:
#line 556 "p2/parser.y"
    {
            (yyval.node) = ast_new(N_CALL,"call",yylineno);
            ast_add((yyval.node),(yyvsp[(1) - (4)].node)); ast_add((yyval.node),(yyvsp[(3) - (4)].node));
        ;}
    break;

  case 138:
#line 561 "p2/parser.y"
    {
            (yyval.node) = ast_new(N_UNOP,(yyvsp[(3) - (3)].sval),yylineno);
            ast_add((yyval.node),(yyvsp[(1) - (3)].node)); free((yyvsp[(3) - (3)].sval));
        ;}
    break;

  case 139:
#line 566 "p2/parser.y"
    {
            char buf[128]; snprintf(buf,sizeof(buf),"->%s",(yyvsp[(3) - (3)].sval));
            (yyval.node) = ast_new(N_UNOP,buf,yylineno);
            ast_add((yyval.node),(yyvsp[(1) - (3)].node)); free((yyvsp[(3) - (3)].sval));
        ;}
    break;

  case 140:
#line 572 "p2/parser.y"
    { (yyval.node) = ast_new(N_UNOP,"post++",yylineno); ast_add((yyval.node),(yyvsp[(1) - (2)].node)); ;}
    break;

  case 141:
#line 574 "p2/parser.y"
    { (yyval.node) = ast_new(N_UNOP,"post--",yylineno); ast_add((yyval.node),(yyvsp[(1) - (2)].node)); ;}
    break;

  case 142:
#line 579 "p2/parser.y"
    { (yyval.node) = ast_new(N_ARG_LIST,NULL,yylineno); ast_add((yyval.node),(yyvsp[(1) - (1)].node)); ;}
    break;

  case 143:
#line 581 "p2/parser.y"
    { ast_add((yyvsp[(1) - (3)].node),(yyvsp[(3) - (3)].node)); (yyval.node)=(yyvsp[(1) - (3)].node); ;}
    break;

  case 144:
#line 586 "p2/parser.y"
    { (yyval.node) = ast_new(N_IDENT,(yyvsp[(1) - (1)].sval),yylineno); free((yyvsp[(1) - (1)].sval)); ;}
    break;

  case 145:
#line 588 "p2/parser.y"
    { (yyval.node) = ast_new(N_INT_LIT,(yyvsp[(1) - (1)].sval),yylineno); free((yyvsp[(1) - (1)].sval)); ;}
    break;

  case 146:
#line 590 "p2/parser.y"
    { (yyval.node) = ast_new(N_FLOAT_LIT,(yyvsp[(1) - (1)].sval),yylineno); free((yyvsp[(1) - (1)].sval)); ;}
    break;

  case 147:
#line 592 "p2/parser.y"
    { (yyval.node) = ast_new(N_STRING_LIT,(yyvsp[(1) - (1)].sval),yylineno); free((yyvsp[(1) - (1)].sval)); ;}
    break;

  case 148:
#line 594 "p2/parser.y"
    { (yyval.node) = ast_new(N_CHAR_LIT,(yyvsp[(1) - (1)].sval),yylineno); free((yyvsp[(1) - (1)].sval)); ;}
    break;

  case 149:
#line 596 "p2/parser.y"
    { (yyval.node) = (yyvsp[(2) - (3)].node); ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2705 "p2/parser.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 599 "p2/parser.y"


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

    /* ── PHASE 4: Intermediate Code Generation ──────────────── */
    if (total == 0) {
        section("PHASE 4 — INTERMEDIATE CODE GENERATION");
        ICGCtx *icg_ctx = icg_init();
        icg_generate(icg_ctx, parse_root);
        icg_print(icg_ctx);
        /* Optional: write TAC to file
        icg_write_file(icg_ctx, "output.tac");
        */
        icg_free(icg_ctx);
    } else {
        printf(C_YELLOW "\n  ⚠  Skipping code generation — errors found in semantic analysis.\n\n" C_RESET);
    }

    ast_free(parse_root);
    return (total > 0) ? 1 : 0;
}

