/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 10 "parser.y"

#include "ast.h"
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

#line 88 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IDENTIFIER = 3,                 /* IDENTIFIER  */
  YYSYMBOL_INT_LITERAL = 4,                /* INT_LITERAL  */
  YYSYMBOL_FLOAT_LITERAL = 5,              /* FLOAT_LITERAL  */
  YYSYMBOL_STRING_LITERAL = 6,             /* STRING_LITERAL  */
  YYSYMBOL_CHAR_LITERAL = 7,               /* CHAR_LITERAL  */
  YYSYMBOL_KW_AUTO = 8,                    /* KW_AUTO  */
  YYSYMBOL_KW_BREAK = 9,                   /* KW_BREAK  */
  YYSYMBOL_KW_CASE = 10,                   /* KW_CASE  */
  YYSYMBOL_KW_CHAR = 11,                   /* KW_CHAR  */
  YYSYMBOL_KW_CONST = 12,                  /* KW_CONST  */
  YYSYMBOL_KW_CONTINUE = 13,               /* KW_CONTINUE  */
  YYSYMBOL_KW_DEFAULT = 14,                /* KW_DEFAULT  */
  YYSYMBOL_KW_DO = 15,                     /* KW_DO  */
  YYSYMBOL_KW_DOUBLE = 16,                 /* KW_DOUBLE  */
  YYSYMBOL_KW_ELSE = 17,                   /* KW_ELSE  */
  YYSYMBOL_KW_ENUM = 18,                   /* KW_ENUM  */
  YYSYMBOL_KW_EXTERN = 19,                 /* KW_EXTERN  */
  YYSYMBOL_KW_FLOAT = 20,                  /* KW_FLOAT  */
  YYSYMBOL_KW_FOR = 21,                    /* KW_FOR  */
  YYSYMBOL_KW_IF = 22,                     /* KW_IF  */
  YYSYMBOL_KW_INT = 23,                    /* KW_INT  */
  YYSYMBOL_KW_LONG = 24,                   /* KW_LONG  */
  YYSYMBOL_KW_RETURN = 25,                 /* KW_RETURN  */
  YYSYMBOL_KW_SHORT = 26,                  /* KW_SHORT  */
  YYSYMBOL_KW_SIGNED = 27,                 /* KW_SIGNED  */
  YYSYMBOL_KW_SIZEOF = 28,                 /* KW_SIZEOF  */
  YYSYMBOL_KW_STATIC = 29,                 /* KW_STATIC  */
  YYSYMBOL_KW_STRUCT = 30,                 /* KW_STRUCT  */
  YYSYMBOL_KW_SWITCH = 31,                 /* KW_SWITCH  */
  YYSYMBOL_KW_TYPEDEF = 32,                /* KW_TYPEDEF  */
  YYSYMBOL_KW_UNION = 33,                  /* KW_UNION  */
  YYSYMBOL_KW_UNSIGNED = 34,               /* KW_UNSIGNED  */
  YYSYMBOL_KW_VOID = 35,                   /* KW_VOID  */
  YYSYMBOL_KW_VOLATILE = 36,               /* KW_VOLATILE  */
  YYSYMBOL_KW_WHILE = 37,                  /* KW_WHILE  */
  YYSYMBOL_OP_INC = 38,                    /* OP_INC  */
  YYSYMBOL_OP_DEC = 39,                    /* OP_DEC  */
  YYSYMBOL_OP_ARROW = 40,                  /* OP_ARROW  */
  YYSYMBOL_OP_AND = 41,                    /* OP_AND  */
  YYSYMBOL_OP_OR = 42,                     /* OP_OR  */
  YYSYMBOL_OP_EQ = 43,                     /* OP_EQ  */
  YYSYMBOL_OP_NEQ = 44,                    /* OP_NEQ  */
  YYSYMBOL_OP_LEQ = 45,                    /* OP_LEQ  */
  YYSYMBOL_OP_GEQ = 46,                    /* OP_GEQ  */
  YYSYMBOL_OP_LSHIFT = 47,                 /* OP_LSHIFT  */
  YYSYMBOL_OP_RSHIFT = 48,                 /* OP_RSHIFT  */
  YYSYMBOL_OP_PLUS_A = 49,                 /* OP_PLUS_A  */
  YYSYMBOL_OP_MINUS_A = 50,                /* OP_MINUS_A  */
  YYSYMBOL_OP_MUL_A = 51,                  /* OP_MUL_A  */
  YYSYMBOL_OP_DIV_A = 52,                  /* OP_DIV_A  */
  YYSYMBOL_OP_MOD_A = 53,                  /* OP_MOD_A  */
  YYSYMBOL_OP_AND_A = 54,                  /* OP_AND_A  */
  YYSYMBOL_OP_XOR_A = 55,                  /* OP_XOR_A  */
  YYSYMBOL_OP_OR_A = 56,                   /* OP_OR_A  */
  YYSYMBOL_OP_LSHIFT_A = 57,               /* OP_LSHIFT_A  */
  YYSYMBOL_OP_RSHIFT_A = 58,               /* OP_RSHIFT_A  */
  YYSYMBOL_ELLIPSIS = 59,                  /* ELLIPSIS  */
  YYSYMBOL_60_ = 60,                       /* '='  */
  YYSYMBOL_61_ = 61,                       /* '?'  */
  YYSYMBOL_62_ = 62,                       /* ':'  */
  YYSYMBOL_63_ = 63,                       /* '|'  */
  YYSYMBOL_64_ = 64,                       /* '^'  */
  YYSYMBOL_65_ = 65,                       /* '&'  */
  YYSYMBOL_66_ = 66,                       /* '<'  */
  YYSYMBOL_67_ = 67,                       /* '>'  */
  YYSYMBOL_68_ = 68,                       /* '+'  */
  YYSYMBOL_69_ = 69,                       /* '-'  */
  YYSYMBOL_70_ = 70,                       /* '*'  */
  YYSYMBOL_71_ = 71,                       /* '/'  */
  YYSYMBOL_72_ = 72,                       /* '%'  */
  YYSYMBOL_UPREC = 73,                     /* UPREC  */
  YYSYMBOL_74_ = 74,                       /* '('  */
  YYSYMBOL_75_ = 75,                       /* ')'  */
  YYSYMBOL_76_ = 76,                       /* '['  */
  YYSYMBOL_77_ = 77,                       /* ']'  */
  YYSYMBOL_78_ = 78,                       /* '.'  */
  YYSYMBOL_KW_THEN = 79,                   /* KW_THEN  */
  YYSYMBOL_80_ = 80,                       /* ','  */
  YYSYMBOL_81_ = 81,                       /* '{'  */
  YYSYMBOL_82_ = 82,                       /* '}'  */
  YYSYMBOL_83_ = 83,                       /* ';'  */
  YYSYMBOL_84_ = 84,                       /* '~'  */
  YYSYMBOL_85_ = 85,                       /* '!'  */
  YYSYMBOL_YYACCEPT = 86,                  /* $accept  */
  YYSYMBOL_program = 87,                   /* program  */
  YYSYMBOL_ext_decl_list = 88,             /* ext_decl_list  */
  YYSYMBOL_ext_decl = 89,                  /* ext_decl  */
  YYSYMBOL_func_def = 90,                  /* func_def  */
  YYSYMBOL_param_list = 91,                /* param_list  */
  YYSYMBOL_param_decl = 92,                /* param_decl  */
  YYSYMBOL_type_spec = 93,                 /* type_spec  */
  YYSYMBOL_type_name = 94,                 /* type_name  */
  YYSYMBOL_compound = 95,                  /* compound  */
  YYSYMBOL_stmt_list = 96,                 /* stmt_list  */
  YYSYMBOL_declaration = 97,               /* declaration  */
  YYSYMBOL_decl_list = 98,                 /* decl_list  */
  YYSYMBOL_decl_item = 99,                 /* decl_item  */
  YYSYMBOL_stmt = 100,                     /* stmt  */
  YYSYMBOL_statement = 101,                /* statement  */
  YYSYMBOL_expr_stmt = 102,                /* expr_stmt  */
  YYSYMBOL_if_stmt = 103,                  /* if_stmt  */
  YYSYMBOL_while_stmt = 104,               /* while_stmt  */
  YYSYMBOL_do_stmt = 105,                  /* do_stmt  */
  YYSYMBOL_for_stmt = 106,                 /* for_stmt  */
  YYSYMBOL_return_stmt = 107,              /* return_stmt  */
  YYSYMBOL_expression = 108,               /* expression  */
  YYSYMBOL_assign_expr = 109,              /* assign_expr  */
  YYSYMBOL_assign_op = 110,                /* assign_op  */
  YYSYMBOL_ternary_expr = 111,             /* ternary_expr  */
  YYSYMBOL_or_expr = 112,                  /* or_expr  */
  YYSYMBOL_and_expr = 113,                 /* and_expr  */
  YYSYMBOL_bitor_expr = 114,               /* bitor_expr  */
  YYSYMBOL_xor_expr = 115,                 /* xor_expr  */
  YYSYMBOL_bitand_expr = 116,              /* bitand_expr  */
  YYSYMBOL_eq_expr = 117,                  /* eq_expr  */
  YYSYMBOL_relat_expr = 118,               /* relat_expr  */
  YYSYMBOL_shift_expr = 119,               /* shift_expr  */
  YYSYMBOL_add_expr = 120,                 /* add_expr  */
  YYSYMBOL_mul_expr = 121,                 /* mul_expr  */
  YYSYMBOL_cast_expr = 122,                /* cast_expr  */
  YYSYMBOL_unary_expr = 123,               /* unary_expr  */
  YYSYMBOL_postfix_expr = 124,             /* postfix_expr  */
  YYSYMBOL_arg_list = 125,                 /* arg_list  */
  YYSYMBOL_primary_expr = 126              /* primary_expr  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

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
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  257

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   316


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    93,    93,   102,   103,   115,   116,   121,   129,   137,
     146,   159,   161,   163,   168,   174,   181,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,   205,   209,   210,   211,   212,   213,   214,   215,   220,
     221,   225,   226,   231,   253,   255,   260,   262,   267,   274,
     281,   286,   291,   301,   302,   303,   307,   308,   309,   310,
     311,   312,   313,   314,   318,   319,   323,   328,   336,   344,
     352,   359,   364,   371,   379,   380,   389,   390,   398,   399,
     408,   409,   410,   411,   412,   413,   414,   415,   416,   417,
     418,   422,   423,   431,   432,   437,   438,   443,   444,   449,
     450,   455,   456,   461,   462,   464,   469,   470,   472,   474,
     476,   481,   482,   484,   489,   490,   492,   497,   498,   500,
     502,   507,   508,   516,   517,   519,   521,   523,   525,   527,
     529,   531,   533,   538,   543,   544,   549,   554,   559,   564,
     570,   572,   577,   579,   584,   586,   588,   590,   592,   594
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IDENTIFIER",
  "INT_LITERAL", "FLOAT_LITERAL", "STRING_LITERAL", "CHAR_LITERAL",
  "KW_AUTO", "KW_BREAK", "KW_CASE", "KW_CHAR", "KW_CONST", "KW_CONTINUE",
  "KW_DEFAULT", "KW_DO", "KW_DOUBLE", "KW_ELSE", "KW_ENUM", "KW_EXTERN",
  "KW_FLOAT", "KW_FOR", "KW_IF", "KW_INT", "KW_LONG", "KW_RETURN",
  "KW_SHORT", "KW_SIGNED", "KW_SIZEOF", "KW_STATIC", "KW_STRUCT",
  "KW_SWITCH", "KW_TYPEDEF", "KW_UNION", "KW_UNSIGNED", "KW_VOID",
  "KW_VOLATILE", "KW_WHILE", "OP_INC", "OP_DEC", "OP_ARROW", "OP_AND",
  "OP_OR", "OP_EQ", "OP_NEQ", "OP_LEQ", "OP_GEQ", "OP_LSHIFT", "OP_RSHIFT",
  "OP_PLUS_A", "OP_MINUS_A", "OP_MUL_A", "OP_DIV_A", "OP_MOD_A",
  "OP_AND_A", "OP_XOR_A", "OP_OR_A", "OP_LSHIFT_A", "OP_RSHIFT_A",
  "ELLIPSIS", "'='", "'?'", "':'", "'|'", "'^'", "'&'", "'<'", "'>'",
  "'+'", "'-'", "'*'", "'/'", "'%'", "UPREC", "'('", "')'", "'['", "']'",
  "'.'", "KW_THEN", "','", "'{'", "'}'", "';'", "'~'", "'!'", "$accept",
  "program", "ext_decl_list", "ext_decl", "func_def", "param_list",
  "param_decl", "type_spec", "type_name", "compound", "stmt_list",
  "declaration", "decl_list", "decl_item", "stmt", "statement",
  "expr_stmt", "if_stmt", "while_stmt", "do_stmt", "for_stmt",
  "return_stmt", "expression", "assign_expr", "assign_op", "ternary_expr",
  "or_expr", "and_expr", "bitor_expr", "xor_expr", "bitand_expr",
  "eq_expr", "relat_expr", "shift_expr", "add_expr", "mul_expr",
  "cast_expr", "unary_expr", "postfix_expr", "arg_list", "primary_expr", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-159)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
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

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
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

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -159,  -159,  -159,   248,  -159,   190,   125,     2,   189,   -37,
    -159,     0,  -159,   234,   -77,  -159,  -158,  -159,  -159,  -159,
    -159,  -159,   -29,   -97,  -159,    60,  -159,   168,   170,   167,
     169,   172,   118,    91,   135,   148,   -39,   -20,  -159,  -159,
    -159
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    12,    13,    14,    15,    69,    70,   190,    97,   191,
     192,   193,    28,    29,   194,   195,   196,   197,   198,   199,
     200,   201,   202,    52,   132,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,   178,
      67
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
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

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
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

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
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

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
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


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: ext_decl_list  */
#line 94 "parser.y"
        {
            (yyval.node) = ast_new(N_PROGRAM,"program",yylineno);
            ast_add((yyval.node),(yyvsp[0].node));
            parse_root = (yyval.node);
        }
#line 1502 "parser.tab.c"
    break;

  case 3: /* ext_decl_list: ext_decl  */
#line 102 "parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 1508 "parser.tab.c"
    break;

  case 4: /* ext_decl_list: ext_decl_list ext_decl  */
#line 104 "parser.y"
        {
            if ((yyvsp[-1].node) && (yyvsp[-1].node)->kind == N_BLOCK) {
                ast_add((yyvsp[-1].node),(yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node);
            } else {
                (yyval.node) = ast_new(N_BLOCK,NULL,yylineno);
                ast_add((yyval.node),(yyvsp[-1].node)); ast_add((yyval.node),(yyvsp[0].node));
            }
        }
#line 1521 "parser.tab.c"
    break;

  case 5: /* ext_decl: func_def  */
#line 115 "parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 1527 "parser.tab.c"
    break;

  case 6: /* ext_decl: declaration  */
#line 116 "parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 1533 "parser.tab.c"
    break;

  case 7: /* func_def: type_spec IDENTIFIER '(' param_list ')' compound  */
#line 122 "parser.y"
        {
            (yyval.node) = ast_new(N_FUNC_DEF,(yyvsp[-4].sval),yylineno);
            ast_add((yyval.node), ast_new(N_TYPE,(yyvsp[-5].sval),yylineno));
            ast_add((yyval.node), (yyvsp[-2].node));
            ast_add((yyval.node), (yyvsp[0].node));
            free((yyvsp[-5].sval)); free((yyvsp[-4].sval));
        }
#line 1545 "parser.tab.c"
    break;

  case 8: /* func_def: type_spec IDENTIFIER '(' ')' compound  */
#line 130 "parser.y"
        {
            (yyval.node) = ast_new(N_FUNC_DEF,(yyvsp[-3].sval),yylineno);
            ast_add((yyval.node), ast_new(N_TYPE,(yyvsp[-4].sval),yylineno));
            ast_add((yyval.node), ast_new(N_PARAM_LIST,"(empty)",yylineno));
            ast_add((yyval.node), (yyvsp[0].node));
            free((yyvsp[-4].sval)); free((yyvsp[-3].sval));
        }
#line 1557 "parser.tab.c"
    break;

  case 9: /* func_def: type_spec '*' IDENTIFIER '(' param_list ')' compound  */
#line 138 "parser.y"
        {
            char buf[128]; snprintf(buf,sizeof(buf),"*%s",(yyvsp[-4].sval));
            (yyval.node) = ast_new(N_FUNC_DEF,buf,yylineno);
            ast_add((yyval.node), ast_new(N_TYPE,(yyvsp[-6].sval),yylineno));
            ast_add((yyval.node), (yyvsp[-2].node));
            ast_add((yyval.node), (yyvsp[0].node));
            free((yyvsp[-6].sval)); free((yyvsp[-4].sval));
        }
#line 1570 "parser.tab.c"
    break;

  case 10: /* func_def: type_spec '*' IDENTIFIER '(' ')' compound  */
#line 147 "parser.y"
        {
            char buf[128]; snprintf(buf,sizeof(buf),"*%s",(yyvsp[-3].sval));
            (yyval.node) = ast_new(N_FUNC_DEF,buf,yylineno);
            ast_add((yyval.node), ast_new(N_TYPE,(yyvsp[-5].sval),yylineno));
            ast_add((yyval.node), ast_new(N_PARAM_LIST,"(empty)",yylineno));
            ast_add((yyval.node), (yyvsp[0].node));
            free((yyvsp[-5].sval)); free((yyvsp[-3].sval));
        }
#line 1583 "parser.tab.c"
    break;

  case 11: /* param_list: param_decl  */
#line 160 "parser.y"
        { (yyval.node) = ast_new(N_PARAM_LIST,NULL,yylineno); ast_add((yyval.node),(yyvsp[0].node)); }
#line 1589 "parser.tab.c"
    break;

  case 12: /* param_list: param_list ',' param_decl  */
#line 162 "parser.y"
        { ast_add((yyvsp[-2].node),(yyvsp[0].node)); (yyval.node)=(yyvsp[-2].node); }
#line 1595 "parser.tab.c"
    break;

  case 13: /* param_list: param_list ',' ELLIPSIS  */
#line 164 "parser.y"
        { ast_add((yyvsp[-2].node),ast_new(N_PARAM,"...",yylineno)); (yyval.node)=(yyvsp[-2].node); }
#line 1601 "parser.tab.c"
    break;

  case 14: /* param_decl: type_spec IDENTIFIER  */
#line 169 "parser.y"
        {
            (yyval.node) = ast_new(N_PARAM,(yyvsp[0].sval),yylineno);
            ast_add((yyval.node), ast_new(N_TYPE,(yyvsp[-1].sval),yylineno));
            free((yyvsp[-1].sval)); free((yyvsp[0].sval));
        }
#line 1611 "parser.tab.c"
    break;

  case 15: /* param_decl: type_spec '*' IDENTIFIER  */
#line 175 "parser.y"
        {
            char buf[128]; snprintf(buf,sizeof(buf),"*%s",(yyvsp[0].sval));
            (yyval.node) = ast_new(N_PARAM,buf,yylineno);
            ast_add((yyval.node), ast_new(N_TYPE,(yyvsp[-2].sval),yylineno));
            free((yyvsp[-2].sval)); free((yyvsp[0].sval));
        }
#line 1622 "parser.tab.c"
    break;

  case 16: /* param_decl: type_spec  */
#line 182 "parser.y"
        {
            (yyval.node) = ast_new(N_PARAM,"(unnamed)",yylineno);
            ast_add((yyval.node), ast_new(N_TYPE,(yyvsp[0].sval),yylineno));
            free((yyvsp[0].sval));
        }
#line 1632 "parser.tab.c"
    break;

  case 17: /* type_spec: KW_INT  */
#line 191 "parser.y"
                         { (yyval.sval) = strdup("int");          }
#line 1638 "parser.tab.c"
    break;

  case 18: /* type_spec: KW_CHAR  */
#line 192 "parser.y"
                         { (yyval.sval) = strdup("char");         }
#line 1644 "parser.tab.c"
    break;

  case 19: /* type_spec: KW_FLOAT  */
#line 193 "parser.y"
                         { (yyval.sval) = strdup("float");        }
#line 1650 "parser.tab.c"
    break;

  case 20: /* type_spec: KW_DOUBLE  */
#line 194 "parser.y"
                         { (yyval.sval) = strdup("double");       }
#line 1656 "parser.tab.c"
    break;

  case 21: /* type_spec: KW_VOID  */
#line 195 "parser.y"
                         { (yyval.sval) = strdup("void");         }
#line 1662 "parser.tab.c"
    break;

  case 22: /* type_spec: KW_LONG  */
#line 196 "parser.y"
                         { (yyval.sval) = strdup("long");         }
#line 1668 "parser.tab.c"
    break;

  case 23: /* type_spec: KW_SHORT  */
#line 197 "parser.y"
                         { (yyval.sval) = strdup("short");        }
#line 1674 "parser.tab.c"
    break;

  case 24: /* type_spec: KW_UNSIGNED  */
#line 198 "parser.y"
                         { (yyval.sval) = strdup("unsigned");     }
#line 1680 "parser.tab.c"
    break;

  case 25: /* type_spec: KW_SIGNED  */
#line 199 "parser.y"
                         { (yyval.sval) = strdup("signed");       }
#line 1686 "parser.tab.c"
    break;

  case 26: /* type_spec: KW_STATIC KW_INT  */
#line 200 "parser.y"
                         { (yyval.sval) = strdup("static int");   }
#line 1692 "parser.tab.c"
    break;

  case 27: /* type_spec: KW_CONST KW_INT  */
#line 201 "parser.y"
                         { (yyval.sval) = strdup("const int");    }
#line 1698 "parser.tab.c"
    break;

  case 28: /* type_spec: KW_CONST KW_CHAR  */
#line 202 "parser.y"
                         { (yyval.sval) = strdup("const char");   }
#line 1704 "parser.tab.c"
    break;

  case 29: /* type_spec: KW_UNSIGNED KW_INT  */
#line 203 "parser.y"
                         { (yyval.sval) = strdup("unsigned int"); }
#line 1710 "parser.tab.c"
    break;

  case 30: /* type_spec: KW_LONG KW_INT  */
#line 204 "parser.y"
                         { (yyval.sval) = strdup("long int");     }
#line 1716 "parser.tab.c"
    break;

  case 31: /* type_spec: KW_LONG KW_LONG  */
#line 205 "parser.y"
                         { (yyval.sval) = strdup("long long");    }
#line 1722 "parser.tab.c"
    break;

  case 32: /* type_name: KW_INT  */
#line 209 "parser.y"
                { (yyval.sval) = strdup("int");    }
#line 1728 "parser.tab.c"
    break;

  case 33: /* type_name: KW_CHAR  */
#line 210 "parser.y"
                { (yyval.sval) = strdup("char");   }
#line 1734 "parser.tab.c"
    break;

  case 34: /* type_name: KW_FLOAT  */
#line 211 "parser.y"
                { (yyval.sval) = strdup("float");  }
#line 1740 "parser.tab.c"
    break;

  case 35: /* type_name: KW_DOUBLE  */
#line 212 "parser.y"
                { (yyval.sval) = strdup("double"); }
#line 1746 "parser.tab.c"
    break;

  case 36: /* type_name: KW_VOID  */
#line 213 "parser.y"
                { (yyval.sval) = strdup("void");   }
#line 1752 "parser.tab.c"
    break;

  case 37: /* type_name: KW_LONG  */
#line 214 "parser.y"
                { (yyval.sval) = strdup("long");   }
#line 1758 "parser.tab.c"
    break;

  case 38: /* type_name: KW_SHORT  */
#line 215 "parser.y"
                { (yyval.sval) = strdup("short");  }
#line 1764 "parser.tab.c"
    break;

  case 39: /* compound: '{' '}'  */
#line 220 "parser.y"
                        { (yyval.node) = ast_new(N_BLOCK,"(empty)",yylineno); }
#line 1770 "parser.tab.c"
    break;

  case 40: /* compound: '{' stmt_list '}'  */
#line 221 "parser.y"
                        { (yyval.node) = (yyvsp[-1].node); }
#line 1776 "parser.tab.c"
    break;

  case 41: /* stmt_list: stmt  */
#line 225 "parser.y"
                        { (yyval.node) = ast_new(N_BLOCK,NULL,yylineno); ast_add((yyval.node),(yyvsp[0].node)); }
#line 1782 "parser.tab.c"
    break;

  case 42: /* stmt_list: stmt_list stmt  */
#line 226 "parser.y"
                        { ast_add((yyvsp[-1].node),(yyvsp[0].node)); (yyval.node)=(yyvsp[-1].node); }
#line 1788 "parser.tab.c"
    break;

  case 43: /* declaration: type_spec decl_list ';'  */
#line 232 "parser.y"
        {
            (yyval.node) = (yyvsp[-1].node);
            /* attach type to every declarator */
            for (int i=0;i<(yyvsp[-1].node)->nchildren;i++) {
                ASTNode *d = (yyvsp[-1].node)->children[i];
                ASTNode *tc = ast_new(N_TYPE,(yyvsp[-2].sval),d->line);
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
            free((yyvsp[-2].sval));
        }
#line 1811 "parser.tab.c"
    break;

  case 44: /* decl_list: decl_item  */
#line 254 "parser.y"
        { (yyval.node) = ast_new(N_BLOCK,"decl-list",yylineno); ast_add((yyval.node),(yyvsp[0].node)); }
#line 1817 "parser.tab.c"
    break;

  case 45: /* decl_list: decl_list ',' decl_item  */
#line 256 "parser.y"
        { ast_add((yyvsp[-2].node),(yyvsp[0].node)); (yyval.node)=(yyvsp[-2].node); }
#line 1823 "parser.tab.c"
    break;

  case 46: /* decl_item: IDENTIFIER  */
#line 261 "parser.y"
        { (yyval.node) = ast_new(N_DECL,(yyvsp[0].sval),yylineno); free((yyvsp[0].sval)); }
#line 1829 "parser.tab.c"
    break;

  case 47: /* decl_item: '*' IDENTIFIER  */
#line 263 "parser.y"
        {
            char buf[128]; snprintf(buf,sizeof(buf),"*%s",(yyvsp[0].sval));
            (yyval.node) = ast_new(N_DECL,buf,yylineno); free((yyvsp[0].sval));
        }
#line 1838 "parser.tab.c"
    break;

  case 48: /* decl_item: IDENTIFIER '[' expression ']'  */
#line 268 "parser.y"
        {
            char buf[128]; snprintf(buf,sizeof(buf),"%s[]",(yyvsp[-3].sval));
            (yyval.node) = ast_new(N_ARRAY_DECL,buf,yylineno);
            ast_add((yyval.node),(yyvsp[-1].node));
            free((yyvsp[-3].sval));
        }
#line 1849 "parser.tab.c"
    break;

  case 49: /* decl_item: IDENTIFIER '[' INT_LITERAL ']'  */
#line 275 "parser.y"
        {
            char buf[128]; snprintf(buf,sizeof(buf),"%s",(yyvsp[-3].sval));
            (yyval.node) = ast_new(N_ARRAY_DECL,buf,yylineno);
            ast_add((yyval.node), ast_new(N_INT_LIT,(yyvsp[-1].sval),yylineno));
            free((yyvsp[-3].sval)); free((yyvsp[-1].sval));
        }
#line 1860 "parser.tab.c"
    break;

  case 50: /* decl_item: IDENTIFIER '[' ']'  */
#line 282 "parser.y"
        {
            char buf[128]; snprintf(buf,sizeof(buf),"%s[]",(yyvsp[-2].sval));
            (yyval.node) = ast_new(N_ARRAY_DECL,buf,yylineno); free((yyvsp[-2].sval));
        }
#line 1869 "parser.tab.c"
    break;

  case 51: /* decl_item: IDENTIFIER '=' expression  */
#line 287 "parser.y"
        {
            (yyval.node) = ast_new(N_DECL_INIT,(yyvsp[-2].sval),yylineno);
            ast_add((yyval.node),(yyvsp[0].node)); free((yyvsp[-2].sval));
        }
#line 1878 "parser.tab.c"
    break;

  case 52: /* decl_item: '*' IDENTIFIER '=' expression  */
#line 292 "parser.y"
        {
            char buf[128]; snprintf(buf,sizeof(buf),"*%s",(yyvsp[-2].sval));
            (yyval.node) = ast_new(N_DECL_INIT,buf,yylineno);
            ast_add((yyval.node),(yyvsp[0].node)); free((yyvsp[-2].sval));
        }
#line 1888 "parser.tab.c"
    break;

  case 53: /* stmt: statement  */
#line 301 "parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 1894 "parser.tab.c"
    break;

  case 54: /* stmt: declaration  */
#line 302 "parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 1900 "parser.tab.c"
    break;

  case 55: /* stmt: compound  */
#line 303 "parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 1906 "parser.tab.c"
    break;

  case 56: /* statement: expr_stmt  */
#line 307 "parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 1912 "parser.tab.c"
    break;

  case 57: /* statement: if_stmt  */
#line 308 "parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 1918 "parser.tab.c"
    break;

  case 58: /* statement: while_stmt  */
#line 309 "parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 1924 "parser.tab.c"
    break;

  case 59: /* statement: do_stmt  */
#line 310 "parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 1930 "parser.tab.c"
    break;

  case 60: /* statement: for_stmt  */
#line 311 "parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 1936 "parser.tab.c"
    break;

  case 61: /* statement: return_stmt  */
#line 312 "parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 1942 "parser.tab.c"
    break;

  case 62: /* statement: KW_BREAK ';'  */
#line 313 "parser.y"
                      { (yyval.node) = ast_new(N_BREAK,"break",yylineno);    }
#line 1948 "parser.tab.c"
    break;

  case 63: /* statement: KW_CONTINUE ';'  */
#line 314 "parser.y"
                      { (yyval.node) = ast_new(N_CONTINUE,"continue",yylineno); }
#line 1954 "parser.tab.c"
    break;

  case 64: /* expr_stmt: ';'  */
#line 318 "parser.y"
                       { (yyval.node) = ast_new(N_EXPR_STMT,NULL,yylineno); }
#line 1960 "parser.tab.c"
    break;

  case 65: /* expr_stmt: expression ';'  */
#line 319 "parser.y"
                       { (yyval.node) = (yyvsp[-1].node); }
#line 1966 "parser.tab.c"
    break;

  case 66: /* if_stmt: KW_IF '(' expression ')' stmt  */
#line 324 "parser.y"
        {
            (yyval.node) = ast_new(N_IF,"if",yylineno);
            ast_add((yyval.node),(yyvsp[-2].node)); ast_add((yyval.node),(yyvsp[0].node));
        }
#line 1975 "parser.tab.c"
    break;

  case 67: /* if_stmt: KW_IF '(' expression ')' stmt KW_ELSE stmt  */
#line 329 "parser.y"
        {
            (yyval.node) = ast_new(N_IF,"if-else",yylineno);
            ast_add((yyval.node),(yyvsp[-4].node)); ast_add((yyval.node),(yyvsp[-2].node)); ast_add((yyval.node),(yyvsp[0].node));
        }
#line 1984 "parser.tab.c"
    break;

  case 68: /* while_stmt: KW_WHILE '(' expression ')' stmt  */
#line 337 "parser.y"
        {
            (yyval.node) = ast_new(N_WHILE,"while",yylineno);
            ast_add((yyval.node),(yyvsp[-2].node)); ast_add((yyval.node),(yyvsp[0].node));
        }
#line 1993 "parser.tab.c"
    break;

  case 69: /* do_stmt: KW_DO stmt KW_WHILE '(' expression ')' ';'  */
#line 345 "parser.y"
        {
            (yyval.node) = ast_new(N_DO_WHILE,"do-while",yylineno);
            ast_add((yyval.node),(yyvsp[-5].node)); ast_add((yyval.node),(yyvsp[-2].node));
        }
#line 2002 "parser.tab.c"
    break;

  case 70: /* for_stmt: KW_FOR '(' expr_stmt expr_stmt ')' stmt  */
#line 353 "parser.y"
        {
            (yyval.node) = ast_new(N_FOR,"for",yylineno);
            ast_add((yyval.node),(yyvsp[-3].node)); ast_add((yyval.node),(yyvsp[-2].node));
            ast_add((yyval.node),ast_new(N_EXPR_STMT,NULL,yylineno));
            ast_add((yyval.node),(yyvsp[0].node));
        }
#line 2013 "parser.tab.c"
    break;

  case 71: /* for_stmt: KW_FOR '(' expr_stmt expr_stmt expression ')' stmt  */
#line 360 "parser.y"
        {
            (yyval.node) = ast_new(N_FOR,"for",yylineno);
            ast_add((yyval.node),(yyvsp[-4].node)); ast_add((yyval.node),(yyvsp[-3].node)); ast_add((yyval.node),(yyvsp[-2].node)); ast_add((yyval.node),(yyvsp[0].node));
        }
#line 2022 "parser.tab.c"
    break;

  case 72: /* for_stmt: KW_FOR '(' declaration expr_stmt ')' stmt  */
#line 365 "parser.y"
        {
            (yyval.node) = ast_new(N_FOR,"for(C99)",yylineno);
            ast_add((yyval.node),(yyvsp[-3].node)); ast_add((yyval.node),(yyvsp[-2].node));
            ast_add((yyval.node),ast_new(N_EXPR_STMT,NULL,yylineno));
            ast_add((yyval.node),(yyvsp[0].node));
        }
#line 2033 "parser.tab.c"
    break;

  case 73: /* for_stmt: KW_FOR '(' declaration expr_stmt expression ')' stmt  */
#line 372 "parser.y"
        {
            (yyval.node) = ast_new(N_FOR,"for(C99)",yylineno);
            ast_add((yyval.node),(yyvsp[-4].node)); ast_add((yyval.node),(yyvsp[-3].node)); ast_add((yyval.node),(yyvsp[-2].node)); ast_add((yyval.node),(yyvsp[0].node));
        }
#line 2042 "parser.tab.c"
    break;

  case 74: /* return_stmt: KW_RETURN ';'  */
#line 379 "parser.y"
                               { (yyval.node) = ast_new(N_RETURN,"return",yylineno); }
#line 2048 "parser.tab.c"
    break;

  case 75: /* return_stmt: KW_RETURN expression ';'  */
#line 381 "parser.y"
        {
            (yyval.node) = ast_new(N_RETURN,"return",yylineno);
            ast_add((yyval.node),(yyvsp[-1].node));
        }
#line 2057 "parser.tab.c"
    break;

  case 76: /* expression: assign_expr  */
#line 389 "parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 2063 "parser.tab.c"
    break;

  case 77: /* expression: expression ',' assign_expr  */
#line 391 "parser.y"
        {
            (yyval.node) = ast_new(N_BINOP,",",yylineno);
            ast_add((yyval.node),(yyvsp[-2].node)); ast_add((yyval.node),(yyvsp[0].node));
        }
#line 2072 "parser.tab.c"
    break;

  case 78: /* assign_expr: ternary_expr  */
#line 398 "parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 2078 "parser.tab.c"
    break;

  case 79: /* assign_expr: unary_expr assign_op assign_expr  */
#line 400 "parser.y"
        {
            (yyval.node) = ast_new(N_ASSIGN,(yyvsp[-1].sval),yylineno);
            ast_add((yyval.node),(yyvsp[-2].node)); ast_add((yyval.node),(yyvsp[0].node));
            free((yyvsp[-1].sval));
        }
#line 2088 "parser.tab.c"
    break;

  case 80: /* assign_op: '='  */
#line 408 "parser.y"
                  { (yyval.sval) = strdup("=");   }
#line 2094 "parser.tab.c"
    break;

  case 81: /* assign_op: OP_PLUS_A  */
#line 409 "parser.y"
                  { (yyval.sval) = strdup("+=");  }
#line 2100 "parser.tab.c"
    break;

  case 82: /* assign_op: OP_MINUS_A  */
#line 410 "parser.y"
                  { (yyval.sval) = strdup("-=");  }
#line 2106 "parser.tab.c"
    break;

  case 83: /* assign_op: OP_MUL_A  */
#line 411 "parser.y"
                  { (yyval.sval) = strdup("*=");  }
#line 2112 "parser.tab.c"
    break;

  case 84: /* assign_op: OP_DIV_A  */
#line 412 "parser.y"
                  { (yyval.sval) = strdup("/=");  }
#line 2118 "parser.tab.c"
    break;

  case 85: /* assign_op: OP_MOD_A  */
#line 413 "parser.y"
                  { (yyval.sval) = strdup("%=");  }
#line 2124 "parser.tab.c"
    break;

  case 86: /* assign_op: OP_AND_A  */
#line 414 "parser.y"
                  { (yyval.sval) = strdup("&=");  }
#line 2130 "parser.tab.c"
    break;

  case 87: /* assign_op: OP_XOR_A  */
#line 415 "parser.y"
                  { (yyval.sval) = strdup("^=");  }
#line 2136 "parser.tab.c"
    break;

  case 88: /* assign_op: OP_OR_A  */
#line 416 "parser.y"
                  { (yyval.sval) = strdup("|=");  }
#line 2142 "parser.tab.c"
    break;

  case 89: /* assign_op: OP_LSHIFT_A  */
#line 417 "parser.y"
                  { (yyval.sval) = strdup("<<="); }
#line 2148 "parser.tab.c"
    break;

  case 90: /* assign_op: OP_RSHIFT_A  */
#line 418 "parser.y"
                  { (yyval.sval) = strdup(">>="); }
#line 2154 "parser.tab.c"
    break;

  case 91: /* ternary_expr: or_expr  */
#line 422 "parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 2160 "parser.tab.c"
    break;

  case 92: /* ternary_expr: or_expr '?' expression ':' ternary_expr  */
#line 424 "parser.y"
        {
            (yyval.node) = ast_new(N_TERNARY,"?:",yylineno);
            ast_add((yyval.node),(yyvsp[-4].node)); ast_add((yyval.node),(yyvsp[-2].node)); ast_add((yyval.node),(yyvsp[0].node));
        }
#line 2169 "parser.tab.c"
    break;

  case 93: /* or_expr: and_expr  */
#line 431 "parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 2175 "parser.tab.c"
    break;

  case 94: /* or_expr: or_expr OP_OR and_expr  */
#line 433 "parser.y"
        { (yyval.node) = ast_new(N_BINOP,"||",yylineno); ast_add((yyval.node),(yyvsp[-2].node)); ast_add((yyval.node),(yyvsp[0].node)); }
#line 2181 "parser.tab.c"
    break;

  case 95: /* and_expr: bitor_expr  */
#line 437 "parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 2187 "parser.tab.c"
    break;

  case 96: /* and_expr: and_expr OP_AND bitor_expr  */
#line 439 "parser.y"
        { (yyval.node) = ast_new(N_BINOP,"&&",yylineno); ast_add((yyval.node),(yyvsp[-2].node)); ast_add((yyval.node),(yyvsp[0].node)); }
#line 2193 "parser.tab.c"
    break;

  case 97: /* bitor_expr: xor_expr  */
#line 443 "parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 2199 "parser.tab.c"
    break;

  case 98: /* bitor_expr: bitor_expr '|' xor_expr  */
#line 445 "parser.y"
        { (yyval.node) = ast_new(N_BINOP,"|",yylineno); ast_add((yyval.node),(yyvsp[-2].node)); ast_add((yyval.node),(yyvsp[0].node)); }
#line 2205 "parser.tab.c"
    break;

  case 99: /* xor_expr: bitand_expr  */
#line 449 "parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 2211 "parser.tab.c"
    break;

  case 100: /* xor_expr: xor_expr '^' bitand_expr  */
#line 451 "parser.y"
        { (yyval.node) = ast_new(N_BINOP,"^",yylineno); ast_add((yyval.node),(yyvsp[-2].node)); ast_add((yyval.node),(yyvsp[0].node)); }
#line 2217 "parser.tab.c"
    break;

  case 101: /* bitand_expr: eq_expr  */
#line 455 "parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 2223 "parser.tab.c"
    break;

  case 102: /* bitand_expr: bitand_expr '&' eq_expr  */
#line 457 "parser.y"
        { (yyval.node) = ast_new(N_BINOP,"&",yylineno); ast_add((yyval.node),(yyvsp[-2].node)); ast_add((yyval.node),(yyvsp[0].node)); }
#line 2229 "parser.tab.c"
    break;

  case 103: /* eq_expr: relat_expr  */
#line 461 "parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 2235 "parser.tab.c"
    break;

  case 104: /* eq_expr: eq_expr OP_EQ relat_expr  */
#line 463 "parser.y"
        { (yyval.node) = ast_new(N_BINOP,"==",yylineno); ast_add((yyval.node),(yyvsp[-2].node)); ast_add((yyval.node),(yyvsp[0].node)); }
#line 2241 "parser.tab.c"
    break;

  case 105: /* eq_expr: eq_expr OP_NEQ relat_expr  */
#line 465 "parser.y"
        { (yyval.node) = ast_new(N_BINOP,"!=",yylineno); ast_add((yyval.node),(yyvsp[-2].node)); ast_add((yyval.node),(yyvsp[0].node)); }
#line 2247 "parser.tab.c"
    break;

  case 106: /* relat_expr: shift_expr  */
#line 469 "parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 2253 "parser.tab.c"
    break;

  case 107: /* relat_expr: relat_expr '<' shift_expr  */
#line 471 "parser.y"
        { (yyval.node) = ast_new(N_BINOP,"<",yylineno);  ast_add((yyval.node),(yyvsp[-2].node)); ast_add((yyval.node),(yyvsp[0].node)); }
#line 2259 "parser.tab.c"
    break;

  case 108: /* relat_expr: relat_expr '>' shift_expr  */
#line 473 "parser.y"
        { (yyval.node) = ast_new(N_BINOP,">",yylineno);  ast_add((yyval.node),(yyvsp[-2].node)); ast_add((yyval.node),(yyvsp[0].node)); }
#line 2265 "parser.tab.c"
    break;

  case 109: /* relat_expr: relat_expr OP_LEQ shift_expr  */
#line 475 "parser.y"
        { (yyval.node) = ast_new(N_BINOP,"<=",yylineno); ast_add((yyval.node),(yyvsp[-2].node)); ast_add((yyval.node),(yyvsp[0].node)); }
#line 2271 "parser.tab.c"
    break;

  case 110: /* relat_expr: relat_expr OP_GEQ shift_expr  */
#line 477 "parser.y"
        { (yyval.node) = ast_new(N_BINOP,">=",yylineno); ast_add((yyval.node),(yyvsp[-2].node)); ast_add((yyval.node),(yyvsp[0].node)); }
#line 2277 "parser.tab.c"
    break;

  case 111: /* shift_expr: add_expr  */
#line 481 "parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 2283 "parser.tab.c"
    break;

  case 112: /* shift_expr: shift_expr OP_LSHIFT add_expr  */
#line 483 "parser.y"
        { (yyval.node) = ast_new(N_BINOP,"<<",yylineno); ast_add((yyval.node),(yyvsp[-2].node)); ast_add((yyval.node),(yyvsp[0].node)); }
#line 2289 "parser.tab.c"
    break;

  case 113: /* shift_expr: shift_expr OP_RSHIFT add_expr  */
#line 485 "parser.y"
        { (yyval.node) = ast_new(N_BINOP,">>",yylineno); ast_add((yyval.node),(yyvsp[-2].node)); ast_add((yyval.node),(yyvsp[0].node)); }
#line 2295 "parser.tab.c"
    break;

  case 114: /* add_expr: mul_expr  */
#line 489 "parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 2301 "parser.tab.c"
    break;

  case 115: /* add_expr: add_expr '+' mul_expr  */
#line 491 "parser.y"
        { (yyval.node) = ast_new(N_BINOP,"+",yylineno); ast_add((yyval.node),(yyvsp[-2].node)); ast_add((yyval.node),(yyvsp[0].node)); }
#line 2307 "parser.tab.c"
    break;

  case 116: /* add_expr: add_expr '-' mul_expr  */
#line 493 "parser.y"
        { (yyval.node) = ast_new(N_BINOP,"-",yylineno); ast_add((yyval.node),(yyvsp[-2].node)); ast_add((yyval.node),(yyvsp[0].node)); }
#line 2313 "parser.tab.c"
    break;

  case 117: /* mul_expr: cast_expr  */
#line 497 "parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 2319 "parser.tab.c"
    break;

  case 118: /* mul_expr: mul_expr '*' cast_expr  */
#line 499 "parser.y"
        { (yyval.node) = ast_new(N_BINOP,"*",yylineno); ast_add((yyval.node),(yyvsp[-2].node)); ast_add((yyval.node),(yyvsp[0].node)); }
#line 2325 "parser.tab.c"
    break;

  case 119: /* mul_expr: mul_expr '/' cast_expr  */
#line 501 "parser.y"
        { (yyval.node) = ast_new(N_BINOP,"/",yylineno); ast_add((yyval.node),(yyvsp[-2].node)); ast_add((yyval.node),(yyvsp[0].node)); }
#line 2331 "parser.tab.c"
    break;

  case 120: /* mul_expr: mul_expr '%' cast_expr  */
#line 503 "parser.y"
        { (yyval.node) = ast_new(N_BINOP,"%",yylineno); ast_add((yyval.node),(yyvsp[-2].node)); ast_add((yyval.node),(yyvsp[0].node)); }
#line 2337 "parser.tab.c"
    break;

  case 121: /* cast_expr: unary_expr  */
#line 507 "parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 2343 "parser.tab.c"
    break;

  case 122: /* cast_expr: '(' type_name ')' cast_expr  */
#line 509 "parser.y"
        {
            (yyval.node) = ast_new(N_UNOP,(yyvsp[-2].sval),yylineno);
            ast_add((yyval.node),(yyvsp[0].node)); free((yyvsp[-2].sval));
        }
#line 2352 "parser.tab.c"
    break;

  case 123: /* unary_expr: postfix_expr  */
#line 516 "parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 2358 "parser.tab.c"
    break;

  case 124: /* unary_expr: OP_INC unary_expr  */
#line 518 "parser.y"
        { (yyval.node) = ast_new(N_UNOP,"pre++",yylineno); ast_add((yyval.node),(yyvsp[0].node)); }
#line 2364 "parser.tab.c"
    break;

  case 125: /* unary_expr: OP_DEC unary_expr  */
#line 520 "parser.y"
        { (yyval.node) = ast_new(N_UNOP,"pre--",yylineno); ast_add((yyval.node),(yyvsp[0].node)); }
#line 2370 "parser.tab.c"
    break;

  case 126: /* unary_expr: '&' cast_expr  */
#line 522 "parser.y"
        { (yyval.node) = ast_new(N_UNOP,"addr",yylineno); ast_add((yyval.node),(yyvsp[0].node)); }
#line 2376 "parser.tab.c"
    break;

  case 127: /* unary_expr: '*' cast_expr  */
#line 524 "parser.y"
        { (yyval.node) = ast_new(N_UNOP,"deref",yylineno); ast_add((yyval.node),(yyvsp[0].node)); }
#line 2382 "parser.tab.c"
    break;

  case 128: /* unary_expr: '+' cast_expr  */
#line 526 "parser.y"
        { (yyval.node) = ast_new(N_UNOP,"u+",yylineno); ast_add((yyval.node),(yyvsp[0].node)); }
#line 2388 "parser.tab.c"
    break;

  case 129: /* unary_expr: '-' cast_expr  */
#line 528 "parser.y"
        { (yyval.node) = ast_new(N_UNOP,"u-",yylineno); ast_add((yyval.node),(yyvsp[0].node)); }
#line 2394 "parser.tab.c"
    break;

  case 130: /* unary_expr: '~' cast_expr  */
#line 530 "parser.y"
        { (yyval.node) = ast_new(N_UNOP,"~",yylineno); ast_add((yyval.node),(yyvsp[0].node)); }
#line 2400 "parser.tab.c"
    break;

  case 131: /* unary_expr: '!' cast_expr  */
#line 532 "parser.y"
        { (yyval.node) = ast_new(N_UNOP,"!",yylineno); ast_add((yyval.node),(yyvsp[0].node)); }
#line 2406 "parser.tab.c"
    break;

  case 132: /* unary_expr: KW_SIZEOF '(' type_name ')'  */
#line 534 "parser.y"
        {
            (yyval.node) = ast_new(N_UNOP,"sizeof",yylineno);
            ast_add((yyval.node), ast_new(N_TYPE,(yyvsp[-1].sval),yylineno)); free((yyvsp[-1].sval));
        }
#line 2415 "parser.tab.c"
    break;

  case 133: /* unary_expr: KW_SIZEOF unary_expr  */
#line 539 "parser.y"
        { (yyval.node) = ast_new(N_UNOP,"sizeof",yylineno); ast_add((yyval.node),(yyvsp[0].node)); }
#line 2421 "parser.tab.c"
    break;

  case 134: /* postfix_expr: primary_expr  */
#line 543 "parser.y"
                            { (yyval.node) = (yyvsp[0].node); }
#line 2427 "parser.tab.c"
    break;

  case 135: /* postfix_expr: postfix_expr '[' expression ']'  */
#line 545 "parser.y"
        {
            (yyval.node) = ast_new(N_INDEX,"[]",yylineno);
            ast_add((yyval.node),(yyvsp[-3].node)); ast_add((yyval.node),(yyvsp[-1].node));
        }
#line 2436 "parser.tab.c"
    break;

  case 136: /* postfix_expr: postfix_expr '(' ')'  */
#line 550 "parser.y"
        {
            (yyval.node) = ast_new(N_CALL,"call",yylineno);
            ast_add((yyval.node),(yyvsp[-2].node));
        }
#line 2445 "parser.tab.c"
    break;

  case 137: /* postfix_expr: postfix_expr '(' arg_list ')'  */
#line 555 "parser.y"
        {
            (yyval.node) = ast_new(N_CALL,"call",yylineno);
            ast_add((yyval.node),(yyvsp[-3].node)); ast_add((yyval.node),(yyvsp[-1].node));
        }
#line 2454 "parser.tab.c"
    break;

  case 138: /* postfix_expr: postfix_expr '.' IDENTIFIER  */
#line 560 "parser.y"
        {
            (yyval.node) = ast_new(N_UNOP,(yyvsp[0].sval),yylineno);
            ast_add((yyval.node),(yyvsp[-2].node)); free((yyvsp[0].sval));
        }
#line 2463 "parser.tab.c"
    break;

  case 139: /* postfix_expr: postfix_expr OP_ARROW IDENTIFIER  */
#line 565 "parser.y"
        {
            char buf[128]; snprintf(buf,sizeof(buf),"->%s",(yyvsp[0].sval));
            (yyval.node) = ast_new(N_UNOP,buf,yylineno);
            ast_add((yyval.node),(yyvsp[-2].node)); free((yyvsp[0].sval));
        }
#line 2473 "parser.tab.c"
    break;

  case 140: /* postfix_expr: postfix_expr OP_INC  */
#line 571 "parser.y"
        { (yyval.node) = ast_new(N_UNOP,"post++",yylineno); ast_add((yyval.node),(yyvsp[-1].node)); }
#line 2479 "parser.tab.c"
    break;

  case 141: /* postfix_expr: postfix_expr OP_DEC  */
#line 573 "parser.y"
        { (yyval.node) = ast_new(N_UNOP,"post--",yylineno); ast_add((yyval.node),(yyvsp[-1].node)); }
#line 2485 "parser.tab.c"
    break;

  case 142: /* arg_list: assign_expr  */
#line 578 "parser.y"
        { (yyval.node) = ast_new(N_ARG_LIST,NULL,yylineno); ast_add((yyval.node),(yyvsp[0].node)); }
#line 2491 "parser.tab.c"
    break;

  case 143: /* arg_list: arg_list ',' assign_expr  */
#line 580 "parser.y"
        { ast_add((yyvsp[-2].node),(yyvsp[0].node)); (yyval.node)=(yyvsp[-2].node); }
#line 2497 "parser.tab.c"
    break;

  case 144: /* primary_expr: IDENTIFIER  */
#line 585 "parser.y"
        { (yyval.node) = ast_new(N_IDENT,(yyvsp[0].sval),yylineno); free((yyvsp[0].sval)); }
#line 2503 "parser.tab.c"
    break;

  case 145: /* primary_expr: INT_LITERAL  */
#line 587 "parser.y"
        { (yyval.node) = ast_new(N_INT_LIT,(yyvsp[0].sval),yylineno); free((yyvsp[0].sval)); }
#line 2509 "parser.tab.c"
    break;

  case 146: /* primary_expr: FLOAT_LITERAL  */
#line 589 "parser.y"
        { (yyval.node) = ast_new(N_FLOAT_LIT,(yyvsp[0].sval),yylineno); free((yyvsp[0].sval)); }
#line 2515 "parser.tab.c"
    break;

  case 147: /* primary_expr: STRING_LITERAL  */
#line 591 "parser.y"
        { (yyval.node) = ast_new(N_STRING_LIT,(yyvsp[0].sval),yylineno); free((yyvsp[0].sval)); }
#line 2521 "parser.tab.c"
    break;

  case 148: /* primary_expr: CHAR_LITERAL  */
#line 593 "parser.y"
        { (yyval.node) = ast_new(N_CHAR_LIT,(yyvsp[0].sval),yylineno); free((yyvsp[0].sval)); }
#line 2527 "parser.tab.c"
    break;

  case 149: /* primary_expr: '(' expression ')'  */
#line 595 "parser.y"
        { (yyval.node) = (yyvsp[-1].node); }
#line 2533 "parser.tab.c"
    break;


#line 2537 "parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
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

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 598 "parser.y"


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

    ast_free(parse_root);
    return (total > 0) ? 1 : 0;
}
