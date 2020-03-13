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
     integer = 258,
     id = 259,
     real = 260,
     string = 261,
     If = 262,
     Else = 263,
     While = 264,
     For = 265,
     Function = 266,
     Return = 267,
     Break = 268,
     Continue = 269,
     and = 270,
     not = 271,
     or = 272,
     local = 273,
     True = 274,
     False = 275,
     nil = 276,
     assign = 277,
     plus = 278,
     minus = 279,
     multiply = 280,
     division = 281,
     mod = 282,
     equal = 283,
     n_equal = 284,
     plus_plus = 285,
     minus_minus = 286,
     greater = 287,
     less = 288,
     g_equal = 289,
     l_equal = 290,
     left_curle_bracket = 291,
     right_curle_bracket = 292,
     left_bracket = 293,
     right_bracket = 294,
     left_parenthesis = 295,
     right_parenthesis = 296,
     semicolon = 297,
     comma = 298,
     colon = 299,
     double_colons = 300,
     dot = 301,
     double_dots = 302,
     other = 303,
     Uminus = 304
   };
#endif
/* Tokens.  */
#define integer 258
#define id 259
#define real 260
#define string 261
#define If 262
#define Else 263
#define While 264
#define For 265
#define Function 266
#define Return 267
#define Break 268
#define Continue 269
#define and 270
#define not 271
#define or 272
#define local 273
#define True 274
#define False 275
#define nil 276
#define assign 277
#define plus 278
#define minus 279
#define multiply 280
#define division 281
#define mod 282
#define equal 283
#define n_equal 284
#define plus_plus 285
#define minus_minus 286
#define greater 287
#define less 288
#define g_equal 289
#define l_equal 290
#define left_curle_bracket 291
#define right_curle_bracket 292
#define left_bracket 293
#define right_bracket 294
#define left_parenthesis 295
#define right_parenthesis 296
#define semicolon 297
#define comma 298
#define colon 299
#define double_colons 300
#define dot 301
#define double_dots 302
#define other 303
#define Uminus 304




/* Copy the first part of user declarations.  */
#line 1 "parser.y"


#include "dataStructs/linkedList.h"
#include "dataStructs/commentStack.h"
#include "dataStructs/symb.h"
#include "utilities/parserUtilities.h"


int yyerror(char *yaccProvideMessage);
int yylex(void);
  
int scopeCounter = 0;
extern int yylineno;
extern char* yytext;
extern FILE* yyin;





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
#line 23 "parser.y"
{
    int intVal;
    char* strVal;
    double doubleVal;
}
/* Line 193 of yacc.c.  */
#line 220 "parser.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 233 "parser.c"

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   578

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  31
/* YYNRULES -- Number of rules.  */
#define YYNRULES  89
/* YYNRULES -- Number of states.  */
#define YYNSTATES  169

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   304

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      45,    46,    47,    48,    49
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,     9,    12,    14,    16,    18,
      20,    23,    26,    28,    30,    32,    34,    38,    42,    46,
      50,    54,    58,    62,    66,    70,    74,    78,    82,    86,
      88,    92,    95,    98,   101,   104,   107,   110,   112,   116,
     118,   120,   122,   126,   128,   130,   133,   136,   138,   142,
     147,   151,   156,   161,   164,   171,   173,   175,   179,   185,
     188,   189,   193,   194,   198,   202,   205,   209,   210,   211,
     218,   219,   224,   227,   232,   234,   236,   238,   240,   242,
     244,   247,   248,   252,   253,   259,   267,   273,   283,   286
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      51,     0,    -1,    52,    -1,    52,    53,    -1,    -1,    54,
      42,    -1,    77,    -1,    78,    -1,    79,    -1,    80,    -1,
      13,    42,    -1,    14,    42,    -1,    71,    -1,    73,    -1,
      42,    -1,    56,    -1,    54,    23,    54,    -1,    54,    24,
      54,    -1,    54,    25,    54,    -1,    54,    26,    54,    -1,
      54,    15,    54,    -1,    54,    17,    54,    -1,    54,    27,
      54,    -1,    54,    28,    54,    -1,    54,    29,    54,    -1,
      54,    32,    54,    -1,    54,    33,    54,    -1,    54,    34,
      54,    -1,    54,    35,    54,    -1,    55,    -1,    40,    54,
      41,    -1,    24,    54,    -1,    16,    54,    -1,    30,    58,
      -1,    58,    30,    -1,    31,    58,    -1,    58,    31,    -1,
      57,    -1,    58,    22,    54,    -1,    58,    -1,    60,    -1,
      66,    -1,    40,    73,    41,    -1,    74,    -1,     4,    -1,
      18,     4,    -1,    45,     4,    -1,    59,    -1,    58,    46,
       4,    -1,    58,    38,    54,    39,    -1,    60,    46,     4,
      -1,    60,    38,    54,    39,    -1,    60,    40,    64,    41,
      -1,    58,    61,    -1,    40,    73,    41,    40,    64,    41,
      -1,    62,    -1,    63,    -1,    40,    64,    41,    -1,    47,
       4,    40,    64,    41,    -1,    54,    65,    -1,    -1,    43,
      54,    65,    -1,    -1,    38,    64,    39,    -1,    38,    67,
      39,    -1,    69,    68,    -1,    68,    43,    69,    -1,    -1,
      -1,    36,    70,    54,    44,    54,    37,    -1,    -1,    36,
      72,    52,    37,    -1,    11,     4,    -1,    11,    40,    75,
      41,    -1,     3,    -1,     5,    -1,     6,    -1,    21,    -1,
      19,    -1,    20,    -1,     4,    76,    -1,    -1,    76,    43,
       4,    -1,    -1,     7,    40,    54,    41,    53,    -1,     7,
      40,    54,    41,    53,     8,    53,    -1,     9,    40,    54,
      41,    53,    -1,    10,    40,    64,    42,    54,    42,    64,
      41,    53,    -1,    12,    42,    -1,    12,    54,    42,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   115,   115,   118,   119,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     153,   154,   155,   156,   157,   158,   159,   160,   163,   169,
     170,   171,   172,   173,   179,   186,   187,   188,   192,   193,
     194,   195,   199,   200,   201,   206,   207,   210,   215,   220,
     221,   224,   225,   228,   229,   233,   236,   237,   240,   240,
     247,   247,   256,   257,   262,   263,   264,   265,   266,   267,
     272,   273,   276,   277,   283,   284,   287,   290,   294,   295
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "integer", "id", "real", "string", "If",
  "Else", "While", "For", "Function", "Return", "Break", "Continue", "and",
  "not", "or", "local", "True", "False", "nil", "assign", "plus", "minus",
  "multiply", "division", "mod", "equal", "n_equal", "plus_plus",
  "minus_minus", "greater", "less", "g_equal", "l_equal",
  "left_curle_bracket", "right_curle_bracket", "left_bracket",
  "right_bracket", "left_parenthesis", "right_parenthesis", "semicolon",
  "comma", "colon", "double_colons", "dot", "double_dots", "other",
  "Uminus", "$accept", "program", "States", "Stmt", "Expression", "Term",
  "Assignexpression", "Primary", "Lvalue", "Member", "Call", "Callsuffix",
  "Normalcall", "Methodcall", "Elist", "Multy_exp", "Objectdef", "Indexed",
  "Multy_ind", "Indexedelement", "@1", "Block", "@2", "Funcdef", "Const",
  "Idlist", "Multy_id", "Ifstmt", "Whilestmt", "Forstmt", "Returnstmt", 0
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
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    50,    51,    52,    52,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      55,    55,    55,    55,    55,    55,    55,    55,    56,    57,
      57,    57,    57,    57,    58,    58,    58,    58,    59,    59,
      59,    59,    60,    60,    60,    61,    61,    62,    63,    64,
      64,    65,    65,    66,    66,    67,    68,    68,    70,    69,
      72,    71,    73,    73,    74,    74,    74,    74,    74,    74,
      75,    75,    76,    76,    77,    77,    78,    79,    80,    80
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     2,     1,     1,     1,     1,
       2,     2,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       3,     2,     2,     2,     2,     2,     2,     1,     3,     1,
       1,     1,     3,     1,     1,     2,     2,     1,     3,     4,
       3,     4,     4,     2,     6,     1,     1,     3,     5,     2,
       0,     3,     0,     3,     3,     2,     3,     0,     0,     6,
       0,     4,     2,     4,     1,     1,     1,     1,     1,     1,
       2,     0,     3,     0,     5,     7,     5,     9,     2,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     2,     1,    74,    44,    75,    76,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    78,    79,    77,
       0,     0,     0,    70,    60,     0,    14,     0,     3,     0,
      29,    15,    37,    39,    47,    40,    41,    12,    13,    43,
       6,     7,     8,     9,     0,     0,    60,    72,    81,    88,
       0,    10,    11,    32,    45,    31,     0,    33,     0,    35,
       4,    68,    62,     0,     0,    67,     0,     0,    46,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     5,     0,    34,    36,     0,    60,     0,     0,
      53,    55,    56,     0,    60,     0,     0,     0,     0,    83,
       0,    89,     0,     0,     0,     0,    59,    63,    64,    65,
      30,    42,    20,    21,    16,    17,    18,    19,    22,    23,
      24,    25,    26,    27,    28,    38,     0,     0,    48,     0,
       0,     0,    50,     0,     0,     0,    80,    73,     0,    71,
       0,    62,     0,    60,    49,    57,    60,    51,    52,    84,
      86,     0,     0,     0,    61,    66,     0,     0,     0,    60,
      82,     0,    54,    58,    85,     0,    69,     0,    87
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    28,    62,    30,    31,    32,    33,    34,
      35,    90,    91,    92,    63,   106,    36,    64,   109,    65,
     104,    37,    60,    38,    39,   100,   136,    40,    41,    42,
      43
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -109
static const yytype_int16 yypact[] =
{
    -109,     4,   157,  -109,  -109,  -109,  -109,  -109,   -31,   -24,
     -16,     1,    16,   -41,    -4,   246,    41,  -109,  -109,  -109,
     246,    -1,    -1,  -109,   200,   223,  -109,    48,  -109,   313,
    -109,  -109,  -109,   108,  -109,    11,  -109,  -109,  -109,  -109,
    -109,  -109,  -109,  -109,   246,   246,   246,  -109,    49,  -109,
     334,  -109,  -109,  -109,  -109,  -109,    51,   -32,    11,   -32,
    -109,  -109,   292,    21,    24,  -109,   376,    23,  -109,   246,
     246,   246,   246,   246,   246,   246,   246,   246,   246,   246,
     246,   246,  -109,   246,  -109,  -109,   246,   246,    61,    76,
    -109,  -109,  -109,   246,   246,    78,   397,   418,    50,  -109,
      25,  -109,    42,   105,   246,   246,  -109,  -109,  -109,    47,
    -109,    53,   530,   517,     2,     2,  -109,  -109,  -109,   543,
     543,    62,    62,    62,    62,   502,   439,    57,  -109,    59,
     460,    64,  -109,   157,   157,   246,    63,  -109,    53,  -109,
     270,   292,    77,   246,  -109,  -109,   246,  -109,  -109,    92,
    -109,   355,   118,   246,  -109,  -109,    86,    87,   157,   246,
    -109,   481,  -109,  -109,  -109,    93,  -109,   157,  -109
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -109,  -109,    80,  -108,    -2,  -109,  -109,  -109,   -10,  -109,
       9,  -109,  -109,  -109,   -39,     3,  -109,  -109,  -109,    -5,
    -109,  -109,  -109,   -23,  -109,  -109,  -109,  -109,  -109,  -109,
    -109
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_int16 yytable[] =
{
      29,    51,    67,     5,     3,    47,    86,    98,    87,    44,
      50,    57,    59,    53,    88,    89,    45,    16,    55,     4,
       5,     6,     7,    66,    46,   149,   150,    73,    74,    75,
      58,    58,    15,   102,    16,    17,    18,    19,    52,    56,
      20,    48,    96,    97,    27,    54,    21,    22,   127,    93,
     164,    94,    68,    99,    24,   131,    25,    95,    49,   168,
     107,    27,    11,   108,   111,   128,   137,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     129,   125,   132,   138,   126,    71,    72,    73,    74,    75,
     142,   130,   135,   143,    -1,    -1,    -1,    -1,   145,   146,
     158,    29,   140,   141,   156,   148,   152,   157,     4,     5,
       6,     7,     8,    61,     9,    10,    11,    12,    13,    14,
     165,    15,   160,    16,    17,    18,    19,   162,   163,    20,
      83,    29,    29,   151,   167,    21,    22,   155,    84,    85,
     103,    23,   139,    24,   154,    25,    86,    26,    87,     0,
      27,   161,     0,     0,    88,    89,    29,     0,     0,     0,
       4,     5,     6,     7,     8,    29,     9,    10,    11,    12,
      13,    14,     0,    15,     0,    16,    17,    18,    19,     0,
       0,    20,     0,     0,     0,     0,     0,    21,    22,     0,
       0,     0,     0,    23,     0,    24,     0,    25,     0,    26,
       0,     0,    27,     4,     5,     6,     7,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    15,     0,    16,    17,
      18,    19,     0,     0,    20,     0,     4,     5,     6,     7,
      21,    22,     0,     0,    11,     0,    61,     0,    24,    15,
      25,    16,    17,    18,    19,    27,     0,    20,     0,     4,
       5,     6,     7,    21,    22,     0,     0,     0,     0,     0,
       0,    24,    15,    25,    16,    17,    18,    19,    27,     0,
      20,     0,     0,     0,     0,     0,    21,    22,     0,     0,
       0,     0,     0,     0,    24,    69,    25,    70,     0,     0,
       0,    27,     0,    71,    72,    73,    74,    75,    76,    77,
       0,     0,    78,    79,    80,    81,     0,    69,     0,    70,
       0,     0,     0,     0,   153,    71,    72,    73,    74,    75,
      76,    77,     0,     0,    78,    79,    80,    81,    69,     0,
      70,     0,     0,     0,     0,   105,    71,    72,    73,    74,
      75,    76,    77,     0,     0,    78,    79,    80,    81,    69,
       0,    70,     0,     0,     0,    82,     0,    71,    72,    73,
      74,    75,    76,    77,     0,     0,    78,    79,    80,    81,
      69,     0,    70,     0,     0,     0,   101,     0,    71,    72,
      73,    74,    75,    76,    77,     0,     0,    78,    79,    80,
      81,    69,     0,    70,     0,     0,     0,   159,     0,    71,
      72,    73,    74,    75,    76,    77,     0,     0,    78,    79,
      80,    81,    69,     0,    70,     0,     0,   110,     0,     0,
      71,    72,    73,    74,    75,    76,    77,     0,     0,    78,
      79,    80,    81,    69,     0,    70,     0,     0,   133,     0,
       0,    71,    72,    73,    74,    75,    76,    77,     0,     0,
      78,    79,    80,    81,    69,     0,    70,     0,     0,   134,
       0,     0,    71,    72,    73,    74,    75,    76,    77,     0,
       0,    78,    79,    80,    81,    69,     0,    70,   144,     0,
       0,     0,     0,    71,    72,    73,    74,    75,    76,    77,
       0,     0,    78,    79,    80,    81,    69,     0,    70,   147,
       0,     0,     0,     0,    71,    72,    73,    74,    75,    76,
      77,     0,     0,    78,    79,    80,    81,    69,   166,    70,
       0,     0,     0,     0,     0,    71,    72,    73,    74,    75,
      76,    77,    69,     0,    78,    79,    80,    81,     0,     0,
      71,    72,    73,    74,    75,    76,    77,     0,     0,    78,
      79,    80,    81,    71,    72,    73,    74,    75,    76,    77,
       0,     0,    78,    79,    80,    81,    71,    72,    73,    74,
      75,    -1,    -1,     0,     0,    78,    79,    80,    81
};

static const yytype_int16 yycheck[] =
{
       2,    42,    25,     4,     0,     4,    38,    46,    40,    40,
      12,    21,    22,    15,    46,    47,    40,    18,    20,     3,
       4,     5,     6,    25,    40,   133,   134,    25,    26,    27,
      21,    22,    16,    56,    18,    19,    20,    21,    42,    40,
      24,    40,    44,    45,    45,     4,    30,    31,    87,    38,
     158,    40,     4,     4,    38,    94,    40,    46,    42,   167,
      39,    45,    11,    39,    41,     4,    41,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
       4,    83,     4,    41,    86,    23,    24,    25,    26,    27,
      43,    93,    42,    40,    32,    33,    34,    35,    41,    40,
       8,   103,   104,   105,   143,    41,    43,   146,     3,     4,
       5,     6,     7,    36,     9,    10,    11,    12,    13,    14,
     159,    16,     4,    18,    19,    20,    21,    41,    41,    24,
      22,   133,   134,   135,    41,    30,    31,   142,    30,    31,
      60,    36,    37,    38,   141,    40,    38,    42,    40,    -1,
      45,   153,    -1,    -1,    46,    47,   158,    -1,    -1,    -1,
       3,     4,     5,     6,     7,   167,     9,    10,    11,    12,
      13,    14,    -1,    16,    -1,    18,    19,    20,    21,    -1,
      -1,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,    -1,
      -1,    -1,    -1,    36,    -1,    38,    -1,    40,    -1,    42,
      -1,    -1,    45,     3,     4,     5,     6,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    16,    -1,    18,    19,
      20,    21,    -1,    -1,    24,    -1,     3,     4,     5,     6,
      30,    31,    -1,    -1,    11,    -1,    36,    -1,    38,    16,
      40,    18,    19,    20,    21,    45,    -1,    24,    -1,     3,
       4,     5,     6,    30,    31,    -1,    -1,    -1,    -1,    -1,
      -1,    38,    16,    40,    18,    19,    20,    21,    45,    -1,
      24,    -1,    -1,    -1,    -1,    -1,    30,    31,    -1,    -1,
      -1,    -1,    -1,    -1,    38,    15,    40,    17,    -1,    -1,
      -1,    45,    -1,    23,    24,    25,    26,    27,    28,    29,
      -1,    -1,    32,    33,    34,    35,    -1,    15,    -1,    17,
      -1,    -1,    -1,    -1,    44,    23,    24,    25,    26,    27,
      28,    29,    -1,    -1,    32,    33,    34,    35,    15,    -1,
      17,    -1,    -1,    -1,    -1,    43,    23,    24,    25,    26,
      27,    28,    29,    -1,    -1,    32,    33,    34,    35,    15,
      -1,    17,    -1,    -1,    -1,    42,    -1,    23,    24,    25,
      26,    27,    28,    29,    -1,    -1,    32,    33,    34,    35,
      15,    -1,    17,    -1,    -1,    -1,    42,    -1,    23,    24,
      25,    26,    27,    28,    29,    -1,    -1,    32,    33,    34,
      35,    15,    -1,    17,    -1,    -1,    -1,    42,    -1,    23,
      24,    25,    26,    27,    28,    29,    -1,    -1,    32,    33,
      34,    35,    15,    -1,    17,    -1,    -1,    41,    -1,    -1,
      23,    24,    25,    26,    27,    28,    29,    -1,    -1,    32,
      33,    34,    35,    15,    -1,    17,    -1,    -1,    41,    -1,
      -1,    23,    24,    25,    26,    27,    28,    29,    -1,    -1,
      32,    33,    34,    35,    15,    -1,    17,    -1,    -1,    41,
      -1,    -1,    23,    24,    25,    26,    27,    28,    29,    -1,
      -1,    32,    33,    34,    35,    15,    -1,    17,    39,    -1,
      -1,    -1,    -1,    23,    24,    25,    26,    27,    28,    29,
      -1,    -1,    32,    33,    34,    35,    15,    -1,    17,    39,
      -1,    -1,    -1,    -1,    23,    24,    25,    26,    27,    28,
      29,    -1,    -1,    32,    33,    34,    35,    15,    37,    17,
      -1,    -1,    -1,    -1,    -1,    23,    24,    25,    26,    27,
      28,    29,    15,    -1,    32,    33,    34,    35,    -1,    -1,
      23,    24,    25,    26,    27,    28,    29,    -1,    -1,    32,
      33,    34,    35,    23,    24,    25,    26,    27,    28,    29,
      -1,    -1,    32,    33,    34,    35,    23,    24,    25,    26,
      27,    28,    29,    -1,    -1,    32,    33,    34,    35
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    51,    52,     0,     3,     4,     5,     6,     7,     9,
      10,    11,    12,    13,    14,    16,    18,    19,    20,    21,
      24,    30,    31,    36,    38,    40,    42,    45,    53,    54,
      55,    56,    57,    58,    59,    60,    66,    71,    73,    74,
      77,    78,    79,    80,    40,    40,    40,     4,    40,    42,
      54,    42,    42,    54,     4,    54,    40,    58,    60,    58,
      72,    36,    54,    64,    67,    69,    54,    73,     4,    15,
      17,    23,    24,    25,    26,    27,    28,    29,    32,    33,
      34,    35,    42,    22,    30,    31,    38,    40,    46,    47,
      61,    62,    63,    38,    40,    46,    54,    54,    64,     4,
      75,    42,    73,    52,    70,    43,    65,    39,    39,    68,
      41,    41,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    64,     4,     4,
      54,    64,     4,    41,    41,    42,    76,    41,    41,    37,
      54,    54,    43,    40,    39,    41,    40,    39,    41,    53,
      53,    54,    43,    44,    65,    69,    64,    64,     8,    42,
       4,    54,    41,    41,    53,    64,    37,    41,    53
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
#line 115 "parser.y"
    {;}
    break;

  case 3:
#line 118 "parser.y"
    {;}
    break;

  case 5:
#line 122 "parser.y"
    {;}
    break;

  case 6:
#line 123 "parser.y"
    {;}
    break;

  case 7:
#line 124 "parser.y"
    {;}
    break;

  case 8:
#line 125 "parser.y"
    {;}
    break;

  case 9:
#line 126 "parser.y"
    {;}
    break;

  case 10:
#line 127 "parser.y"
    {;}
    break;

  case 11:
#line 128 "parser.y"
    {;}
    break;

  case 12:
#line 129 "parser.y"
    {;}
    break;

  case 13:
#line 130 "parser.y"
    {;}
    break;

  case 14:
#line 131 "parser.y"
    {;}
    break;

  case 15:
#line 135 "parser.y"
    {;}
    break;

  case 16:
#line 136 "parser.y"
    {printf("eimai edw!\n");}
    break;

  case 17:
#line 137 "parser.y"
    {;}
    break;

  case 18:
#line 138 "parser.y"
    {;}
    break;

  case 19:
#line 139 "parser.y"
    {;}
    break;

  case 20:
#line 140 "parser.y"
    {;}
    break;

  case 21:
#line 141 "parser.y"
    {;}
    break;

  case 22:
#line 142 "parser.y"
    {;}
    break;

  case 23:
#line 143 "parser.y"
    {;}
    break;

  case 24:
#line 144 "parser.y"
    {;}
    break;

  case 25:
#line 145 "parser.y"
    {;}
    break;

  case 26:
#line 146 "parser.y"
    {;}
    break;

  case 27:
#line 147 "parser.y"
    {;}
    break;

  case 28:
#line 148 "parser.y"
    {;}
    break;

  case 29:
#line 149 "parser.y"
    {;}
    break;

  case 30:
#line 153 "parser.y"
    {;}
    break;

  case 31:
#line 154 "parser.y"
    {;}
    break;

  case 32:
#line 155 "parser.y"
    {;}
    break;

  case 33:
#line 156 "parser.y"
    {;}
    break;

  case 34:
#line 157 "parser.y"
    {;}
    break;

  case 35:
#line 158 "parser.y"
    {;}
    break;

  case 36:
#line 159 "parser.y"
    {;}
    break;

  case 37:
#line 160 "parser.y"
    {;}
    break;

  case 38:
#line 163 "parser.y"
    {;}
    break;

  case 39:
#line 169 "parser.y"
    {;}
    break;

  case 40:
#line 170 "parser.y"
    {;}
    break;

  case 41:
#line 171 "parser.y"
    {;}
    break;

  case 42:
#line 172 "parser.y"
    {;}
    break;

  case 43:
#line 173 "parser.y"
    {;}
    break;

  case 44:
#line 179 "parser.y"
    {fprintf(stderr,"Id %s on line %d\n",(yyvsp[(1) - (1)].strVal),yylineno);
        if(!isLibraryFunction((yyvsp[(1) - (1)].strVal))){
                item* new = newItem((yyvsp[(1) - (1)].strVal),"id", scopeCounter , yylineno );
                insert_symTable(new);
        }
        
        }
    break;

  case 45:
#line 186 "parser.y"
    {;}
    break;

  case 46:
#line 187 "parser.y"
    {;}
    break;

  case 47:
#line 188 "parser.y"
    {;}
    break;

  case 48:
#line 192 "parser.y"
    {;}
    break;

  case 49:
#line 193 "parser.y"
    {;}
    break;

  case 50:
#line 194 "parser.y"
    {;}
    break;

  case 51:
#line 195 "parser.y"
    {;}
    break;

  case 52:
#line 199 "parser.y"
    {;}
    break;

  case 53:
#line 200 "parser.y"
    {;}
    break;

  case 54:
#line 201 "parser.y"
    {;}
    break;

  case 55:
#line 206 "parser.y"
    {;}
    break;

  case 56:
#line 207 "parser.y"
    {;}
    break;

  case 57:
#line 210 "parser.y"
    {;}
    break;

  case 58:
#line 215 "parser.y"
    {;}
    break;

  case 59:
#line 220 "parser.y"
    {;}
    break;

  case 60:
#line 221 "parser.y"
    {;}
    break;

  case 61:
#line 224 "parser.y"
    {;}
    break;

  case 62:
#line 225 "parser.y"
    {;}
    break;

  case 63:
#line 228 "parser.y"
    {;}
    break;

  case 64:
#line 229 "parser.y"
    {;}
    break;

  case 65:
#line 233 "parser.y"
    {;}
    break;

  case 66:
#line 236 "parser.y"
    {;}
    break;

  case 67:
#line 237 "parser.y"
    {;}
    break;

  case 68:
#line 240 "parser.y"
    {scopeCounter++;
                if(scopeCounter > maxScope) maxScope = scopeCounter;
                printf("Scope ++ %d\n" , scopeCounter);}
    break;

  case 69:
#line 243 "parser.y"
    {scopeCounter--; printf("Scope -- %d\n" , scopeCounter);}
    break;

  case 70:
#line 247 "parser.y"
    {scopeCounter++;
        if(scopeCounter > maxScope) maxScope = scopeCounter;
        printf("Scope ++ %d\n" , scopeCounter);}
    break;

  case 71:
#line 250 "parser.y"
    {scopeCounter--;printf("Scope -- %d\n" , scopeCounter);}
    break;

  case 72:
#line 256 "parser.y"
    {;}
    break;

  case 73:
#line 257 "parser.y"
    {;}
    break;

  case 74:
#line 262 "parser.y"
    {fprintf(stderr,"integer %d on line %d\n",(yyvsp[(1) - (1)].intVal),yylineno);;}
    break;

  case 75:
#line 263 "parser.y"
    {;}
    break;

  case 76:
#line 264 "parser.y"
    {;}
    break;

  case 77:
#line 265 "parser.y"
    {;}
    break;

  case 78:
#line 266 "parser.y"
    {;}
    break;

  case 79:
#line 267 "parser.y"
    {;}
    break;

  case 80:
#line 272 "parser.y"
    {;}
    break;

  case 81:
#line 273 "parser.y"
    {;}
    break;

  case 82:
#line 276 "parser.y"
    {;}
    break;

  case 83:
#line 277 "parser.y"
    {;}
    break;

  case 84:
#line 283 "parser.y"
    {;}
    break;

  case 85:
#line 284 "parser.y"
    {;}
    break;

  case 86:
#line 287 "parser.y"
    {;}
    break;

  case 87:
#line 290 "parser.y"
    {;}
    break;

  case 88:
#line 294 "parser.y"
    {;}
    break;

  case 89:
#line 295 "parser.y"
    {;}
    break;


/* Line 1267 of yacc.c.  */
#line 2105 "parser.c"
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


#line 300 "parser.y"



//tin ftiaxoyme

int yyerror (char * YaccProvidedMessage){
        fprintf(stderr,"%s\n",YaccProvidedMessage);
        return 0;
}


int main(int argc, char** argv)
{
  maxScope = 0;   
  init_symTable();   
  if(argc > 1){
    if (!(yyin = fopen(argv[1], "r"))){
        fprintf(stderr,"Cannot read file: %s\n", argv[1]);
	return 1;
    }
  }
    yyparse();
    printSymTable();
}

