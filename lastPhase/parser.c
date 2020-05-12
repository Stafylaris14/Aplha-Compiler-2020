/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"


#include "utilities/quad.h"
#include "dataStructs/linkedList.h"
#include "dataStructs/commentStack.h"





int yyerror(char *yaccProvideMessage);
int yylex(void);
int offset = 0;
int scopeCounter = 0;
int formal_flag  =0 ;
extern int yylineno;
int returnFlag = 0;
extern char* yytext;
extern FILE* yyin;
int functionCounter = 0; /* for no name functions */
int functionFlag  = 0;  /*1 if is inside a function for RETURN stmt*/
int callFlag =0; // an exw call
int objectHide = 1;//na min kanei hide an einai se object
int assign_flag = 0;
stack1 *loopcounterstack; //krataei poses anakikloseis exoun anoi3ei
/* iopcode op; */



expr *result;


int loopFlag = 0;       /*1 if its inside a loop (for break and Continue)*/
int libcheck = 0;
char* functionName ; /* used to ADD formal arguments to linked list */

#line 107 "parser.c"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
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
    uminus = 304
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
#define uminus 304

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 40 "parser.y"

    struct expression* EXPR;
    int intVal;
    char* strVal;
    double doubleVal;
    struct Item *item; 
    int opcode;                         /* gia ta arithimika  STAF */
    int ifs;                            /* gia ta sigritika einai ayto STAF */
    int boolop ;                         /* gia ta boolean STAF */
    int label_jumps;                       /* gia ta jumps */
    struct for_call *for_call;
    struct for_init *for_init;
    struct indexstr *indexstr;

#line 272 "parser.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */



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
typedef yytype_uint8 yy_state_t;

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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   552

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  61
/* YYNRULES -- Number of rules.  */
#define YYNRULES  120
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  205

#define YYUNDEFTOK  2
#define YYMAXUTOK   304


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   161,   161,   164,   165,   169,   176,   179,   197,   198,
     199,   200,   204,   211,   218,   219,   220,   226,   227,   231,
     236,   240,   244,   244,   269,   269,   295,   299,   308,   317,
     326,   335,   344,   353,   360,   361,   367,   387,   410,   433,
     456,   478,   481,   481,   515,   516,   517,   518,   522,   528,
     538,   546,   552,   556,   559,   566,   566,   567,   567,   571,
     571,   572,   572,   580,   580,   589,   593,   599,   599,   606,
     606,   613,   617,   620,   624,   627,   627,   640,   640,   655,
     661,   673,   676,   676,   689,   689,   699,   710,   724,   727,
     735,   735,   738,   744,   747,   751,   753,   754,   755,   756,
     757,   762,   771,   774,   780,   786,   791,   798,   816,   822,
     827,   844,   844,   859,   859,   876,   892,   896,   901,   907,
     907
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
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
  "uminus", "$accept", "program", "States", "Stmts", "Stmt", "Expression",
  "$@1", "$@2", "Term", "Assignexpression", "$@3", "Primary", "Lvalue",
  "Member", "$@4", "$@5", "Call", "$@6", "$@7", "$@8", "Callsuffix",
  "Normalcall", "$@9", "Methodcall", "$@10", "Elist", "Multy_exp",
  "Objectdef", "$@11", "$@12", "Indexed", "Multy_ind", "Indexedelement",
  "$@13", "Block", "$@14", "Funcdef", "Funcprefix", "Funcname", "Funcargs",
  "$@15", "Funcbody", "Funcblockstart", "Funcblockend", "Const", "Idlist",
  "Multy_id", "Ifstmt", "ifFix", "elseFix", "Whilestart", "whilecont",
  "Whilestmt", "$@16", "Forstmt", "$@17", "ForFix", "M", "N", "Returnstmt",
  "$@18", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304
};
# endif

#define YYPACT_NINF (-182)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-78)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -182,     6,   197,  -182,  -182,  -182,  -182,  -182,   -18,  -182,
     -15,    26,    -1,     8,    10,   263,    35,  -182,  -182,  -182,
     263,    -3,    -3,  -182,    12,   240,  -182,    49,  -182,   308,
    -182,  -182,  -182,   -14,  -182,    42,  -182,  -182,  -182,    14,
    -182,  -182,   197,    28,  -182,  -182,  -182,  -182,   263,   263,
    -182,  -182,  -182,   263,  -182,  -182,  -182,  -182,  -182,    51,
     -19,    -9,   -19,  -182,   263,    48,   371,    44,  -182,  -182,
    -182,   263,   263,   263,   263,   263,   263,   263,   263,   263,
     263,   263,  -182,  -182,  -182,   263,    82,    65,   -33,    43,
      52,    54,  -182,  -182,    83,   263,  -182,   263,   392,   287,
      50,   329,    55,   154,    56,  -182,    59,    60,  -182,    64,
    -182,  -182,   -16,   -16,  -182,  -182,  -182,   504,   504,   265,
     265,   265,   265,   434,  -182,   263,  -182,  -182,  -182,  -182,
    -182,   101,   263,   263,   102,    79,  -182,   197,   413,   197,
      75,  -182,   263,  -182,  -182,  -182,  -182,  -182,  -182,  -182,
     263,  -182,    48,  -182,    81,   263,   263,  -182,    32,   263,
     118,  -182,   455,    84,  -182,    86,  -182,  -182,  -182,  -182,
    -182,  -182,   287,   263,    85,    60,   263,   517,   491,    87,
      91,  -182,  -182,    89,  -182,  -182,  -182,  -182,   350,   263,
    -182,    92,  -182,   263,   122,   197,  -182,   476,  -182,    93,
    -182,  -182,  -182,  -182,  -182
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     2,     1,    95,    49,    96,    97,     0,   109,
       0,    89,   119,     0,     0,     0,     0,    99,   100,    98,
       0,     0,     0,    84,    75,     0,    16,     0,     3,     0,
      33,    17,    41,    44,    52,    45,    46,    14,    15,     0,
      48,     8,     0,     0,     9,    10,   117,    11,     0,    72,
      88,    87,   118,     0,    12,    13,    36,    50,    35,     0,
      37,    55,    39,     6,    72,     0,     0,     0,    51,    22,
      24,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     7,    38,    40,     0,     0,     0,     0,     0,
       0,     0,    90,    93,   105,     0,   111,    72,     0,    74,
       0,     0,     0,     0,     0,    82,     0,    81,    34,    47,
     116,   116,    18,    19,    20,    21,    26,    27,    28,    29,
      30,    31,    32,     0,    53,     0,    67,    69,    62,    65,
      66,     0,     0,    72,   102,     0,   108,     0,     0,     0,
       0,   107,     0,    71,   116,   120,    63,    85,     5,    76,
       0,    78,     0,    79,     0,     0,     0,    54,    43,    72,
       0,    56,     0,     0,   104,     0,    92,    94,   106,   110,
     112,   113,    74,     0,     0,    81,    72,    23,    25,     0,
       0,    58,    60,   101,    91,    86,   117,    73,     0,     0,
      80,     0,    68,    72,     0,     0,   115,     0,    64,     0,
     103,   117,    83,    70,   114
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -182,  -182,  -182,  -182,   -40,    -2,  -182,  -182,  -182,  -182,
    -182,  -182,    13,  -182,  -182,  -182,    22,  -182,  -182,  -182,
    -182,  -182,  -182,  -182,  -182,   -52,   -36,  -182,  -182,  -182,
    -182,   -37,   -13,  -182,     7,  -182,   -21,  -182,  -182,  -182,
    -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,
    -182,  -182,  -182,  -182,  -182,  -182,  -182,  -108,  -181,  -182,
    -182
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,   103,    28,    99,   110,   111,    30,    31,
      87,    32,    33,    34,    89,    90,    35,    91,    88,   154,
     128,   129,   159,   130,   160,   100,   143,    36,    64,    65,
     106,   153,   107,   150,    37,    63,    38,    39,    51,    93,
     134,   167,   135,   185,    40,   165,   183,    41,    42,   137,
      43,    96,    44,   139,    45,   186,    46,   155,    97,    47,
      53
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      29,     5,    94,   156,    67,   195,     3,   126,   -42,    73,
      74,    75,   104,    56,   127,    16,    83,    84,    58,    85,
     204,   -61,    48,    66,    85,    49,   -61,    86,   -61,   -57,
      50,   -59,    86,   -61,    60,    62,   173,    59,   102,    57,
      29,    52,    27,    61,    61,   140,    98,    69,   -77,    70,
      54,   101,    55,    68,    92,    71,    72,    73,    74,    75,
      76,    77,    11,   148,    78,    79,    80,    81,    95,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     -57,   163,   -59,   123,   105,   109,   124,   125,   -55,   131,
     132,   136,   144,   138,   133,   149,   146,   168,   151,   170,
      69,    29,    70,   152,   -63,   161,   164,   179,    71,    72,
      73,    74,    75,    76,    77,    23,   171,    78,    79,    80,
      81,   176,   180,   158,   191,   182,   200,   184,   192,   189,
     162,   193,   194,   198,   203,    29,   187,    29,   190,   175,
     172,   199,   166,     0,     0,     0,     0,     0,   174,     0,
       0,     0,     0,   177,   178,   201,     0,     4,     5,     6,
       7,     8,     0,     9,    10,    11,    12,    13,    14,     0,
      15,   188,    16,    17,    18,    19,     0,     0,    20,     0,
       0,     0,     0,     0,    21,    22,     0,   197,     0,     0,
      23,   147,    24,    29,    25,     0,    26,     0,     0,    27,
       4,     5,     6,     7,     8,     0,     9,    10,    11,    12,
      13,    14,     0,    15,     0,    16,    17,    18,    19,     0,
       0,    20,     0,     0,     0,     0,     0,    21,    22,     0,
       0,     0,     0,    23,     0,    24,     0,    25,     0,    26,
       0,     0,    27,     4,     5,     6,     7,     0,     0,     0,
       0,    11,     0,     0,     0,     0,    15,     0,    16,    17,
      18,    19,     0,     0,    20,     0,     4,     5,     6,     7,
      21,    22,     0,     0,     0,     0,     0,     0,    24,    15,
      25,    16,    17,    18,    19,    27,     0,    20,    71,    72,
      73,    74,    75,    21,    22,     0,     0,   -78,   -78,   -78,
     -78,    24,    69,    25,    70,     0,     0,     0,    27,     0,
      71,    72,    73,    74,    75,    76,    77,     0,     0,    78,
      79,    80,    81,    69,     0,    70,     0,     0,     0,     0,
     142,    71,    72,    73,    74,    75,    76,    77,     0,     0,
      78,    79,    80,    81,    69,     0,    70,     0,     0,     0,
      82,     0,    71,    72,    73,    74,    75,    76,    77,     0,
       0,    78,    79,    80,    81,    69,     0,    70,     0,     0,
       0,   145,     0,    71,    72,    73,    74,    75,    76,    77,
       0,     0,    78,    79,    80,    81,    69,     0,    70,     0,
       0,     0,   196,     0,    71,    72,    73,    74,    75,    76,
      77,     0,     0,    78,    79,    80,    81,    69,     0,    70,
       0,     0,   108,     0,     0,    71,    72,    73,    74,    75,
      76,    77,     0,     0,    78,    79,    80,    81,    69,     0,
      70,     0,     0,   141,     0,     0,    71,    72,    73,    74,
      75,    76,    77,     0,     0,    78,    79,    80,    81,    69,
       0,    70,     0,     0,   169,     0,     0,    71,    72,    73,
      74,    75,    76,    77,     0,     0,    78,    79,    80,    81,
      69,     0,    70,   157,     0,     0,     0,     0,    71,    72,
      73,    74,    75,    76,    77,     0,     0,    78,    79,    80,
      81,    69,     0,    70,   181,     0,     0,     0,     0,    71,
      72,    73,    74,    75,    76,    77,    69,     0,    78,    79,
      80,    81,     0,   202,    71,    72,    73,    74,    75,    76,
      77,     0,     0,    78,    79,    80,    81,    71,    72,    73,
      74,    75,   -78,   -78,     0,     0,    78,    79,    80,    81,
      71,    72,    73,    74,    75,    76,    77,     0,     0,    78,
      79,    80,    81
};

static const yytype_int16 yycheck[] =
{
       2,     4,    42,   111,    25,   186,     0,    40,    22,    25,
      26,    27,    64,    15,    47,    18,    30,    31,    20,    38,
     201,    40,    40,    25,    38,    40,    40,    46,    47,    38,
       4,    40,    46,    47,    21,    22,   144,    40,    59,     4,
      42,    42,    45,    21,    22,    97,    48,    15,    36,    17,
      42,    53,    42,     4,    40,    23,    24,    25,    26,    27,
      28,    29,    11,   103,    32,    33,    34,    35,    40,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      38,   133,    40,    85,    36,    41,     4,    22,    46,    46,
      38,     8,    42,    95,    40,    39,    41,   137,    39,   139,
      15,   103,    17,    43,    40,     4,     4,   159,    23,    24,
      25,    26,    27,    28,    29,    36,    41,    32,    33,    34,
      35,    40,     4,   125,   176,    41,     4,    41,    41,    44,
     132,    40,    43,    41,    41,   137,   172,   139,   175,   152,
     142,   193,   135,    -1,    -1,    -1,    -1,    -1,   150,    -1,
      -1,    -1,    -1,   155,   156,   195,    -1,     3,     4,     5,
       6,     7,    -1,     9,    10,    11,    12,    13,    14,    -1,
      16,   173,    18,    19,    20,    21,    -1,    -1,    24,    -1,
      -1,    -1,    -1,    -1,    30,    31,    -1,   189,    -1,    -1,
      36,    37,    38,   195,    40,    -1,    42,    -1,    -1,    45,
       3,     4,     5,     6,     7,    -1,     9,    10,    11,    12,
      13,    14,    -1,    16,    -1,    18,    19,    20,    21,    -1,
      -1,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,    -1,
      -1,    -1,    -1,    36,    -1,    38,    -1,    40,    -1,    42,
      -1,    -1,    45,     3,     4,     5,     6,    -1,    -1,    -1,
      -1,    11,    -1,    -1,    -1,    -1,    16,    -1,    18,    19,
      20,    21,    -1,    -1,    24,    -1,     3,     4,     5,     6,
      30,    31,    -1,    -1,    -1,    -1,    -1,    -1,    38,    16,
      40,    18,    19,    20,    21,    45,    -1,    24,    23,    24,
      25,    26,    27,    30,    31,    -1,    -1,    32,    33,    34,
      35,    38,    15,    40,    17,    -1,    -1,    -1,    45,    -1,
      23,    24,    25,    26,    27,    28,    29,    -1,    -1,    32,
      33,    34,    35,    15,    -1,    17,    -1,    -1,    -1,    -1,
      43,    23,    24,    25,    26,    27,    28,    29,    -1,    -1,
      32,    33,    34,    35,    15,    -1,    17,    -1,    -1,    -1,
      42,    -1,    23,    24,    25,    26,    27,    28,    29,    -1,
      -1,    32,    33,    34,    35,    15,    -1,    17,    -1,    -1,
      -1,    42,    -1,    23,    24,    25,    26,    27,    28,    29,
      -1,    -1,    32,    33,    34,    35,    15,    -1,    17,    -1,
      -1,    -1,    42,    -1,    23,    24,    25,    26,    27,    28,
      29,    -1,    -1,    32,    33,    34,    35,    15,    -1,    17,
      -1,    -1,    41,    -1,    -1,    23,    24,    25,    26,    27,
      28,    29,    -1,    -1,    32,    33,    34,    35,    15,    -1,
      17,    -1,    -1,    41,    -1,    -1,    23,    24,    25,    26,
      27,    28,    29,    -1,    -1,    32,    33,    34,    35,    15,
      -1,    17,    -1,    -1,    41,    -1,    -1,    23,    24,    25,
      26,    27,    28,    29,    -1,    -1,    32,    33,    34,    35,
      15,    -1,    17,    39,    -1,    -1,    -1,    -1,    23,    24,
      25,    26,    27,    28,    29,    -1,    -1,    32,    33,    34,
      35,    15,    -1,    17,    39,    -1,    -1,    -1,    -1,    23,
      24,    25,    26,    27,    28,    29,    15,    -1,    32,    33,
      34,    35,    -1,    37,    23,    24,    25,    26,    27,    28,
      29,    -1,    -1,    32,    33,    34,    35,    23,    24,    25,
      26,    27,    28,    29,    -1,    -1,    32,    33,    34,    35,
      23,    24,    25,    26,    27,    28,    29,    -1,    -1,    32,
      33,    34,    35
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    51,    52,     0,     3,     4,     5,     6,     7,     9,
      10,    11,    12,    13,    14,    16,    18,    19,    20,    21,
      24,    30,    31,    36,    38,    40,    42,    45,    54,    55,
      58,    59,    61,    62,    63,    66,    77,    84,    86,    87,
      94,    97,    98,   100,   102,   104,   106,   109,    40,    40,
       4,    88,    42,   110,    42,    42,    55,     4,    55,    40,
      62,    66,    62,    85,    78,    79,    55,    86,     4,    15,
      17,    23,    24,    25,    26,    27,    28,    29,    32,    33,
      34,    35,    42,    30,    31,    38,    46,    60,    68,    64,
      65,    67,    40,    89,    54,    40,   101,   108,    55,    55,
      75,    55,    86,    53,    75,    36,    80,    82,    41,    41,
      56,    57,    55,    55,    55,    55,    55,    55,    55,    55,
      55,    55,    55,    55,     4,    22,    40,    47,    70,    71,
      73,    46,    38,    40,    90,    92,     8,    99,    55,   103,
      75,    41,    43,    76,    42,    42,    41,    37,    54,    39,
      83,    39,    43,    81,    69,   107,   107,    39,    55,    72,
      74,     4,    55,    75,     4,    95,    84,    91,    54,    41,
      54,    41,    55,   107,    55,    82,    40,    55,    55,    75,
       4,    39,    41,    96,    41,    93,   105,    76,    55,    44,
      81,    75,    41,    40,    43,   108,    42,    55,    41,    75,
       4,    54,    37,    41,   108
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    50,    51,    52,    52,    53,    53,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    55,    55,    55,
      55,    55,    56,    55,    57,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    58,    58,    58,    58,    58,    58,
      58,    58,    60,    59,    61,    61,    61,    61,    61,    62,
      62,    62,    62,    63,    63,    64,    63,    65,    63,    67,
      66,    68,    66,    69,    66,    70,    70,    72,    71,    74,
      73,    75,    75,    76,    76,    78,    77,    79,    77,    80,
      81,    81,    83,    82,    85,    84,    86,    87,    88,    88,
      90,    89,    91,    92,    93,    94,    94,    94,    94,    94,
      94,    95,    95,    96,    96,    97,    97,    98,    99,   100,
     101,   103,   102,   105,   104,   106,   107,   108,   109,   110,
     109
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     2,     0,     2,     1,     1,
       1,     1,     2,     2,     1,     1,     1,     1,     3,     3,
       3,     3,     0,     5,     0,     5,     3,     3,     3,     3,
       3,     3,     3,     1,     3,     2,     2,     2,     2,     2,
       2,     1,     0,     4,     1,     1,     1,     3,     1,     1,
       2,     2,     1,     3,     4,     0,     4,     0,     5,     0,
       5,     0,     3,     0,     7,     1,     1,     0,     4,     0,
       6,     2,     0,     3,     0,     0,     4,     0,     4,     2,
       3,     0,     0,     6,     0,     4,     5,     2,     1,     0,
       0,     4,     1,     0,     0,     1,     1,     1,     1,     1,
       1,     2,     0,     3,     0,     2,     4,     4,     1,     1,
       3,     0,     4,     0,     8,     7,     0,     0,     2,     0,
       4
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
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

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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
  case 3:
#line 164 "parser.y"
                    {;}
#line 1677 "parser.c"
    break;

  case 5:
#line 169 "parser.y"
                 {
        
        (yyval.EXPR) = (yyvsp[0].EXPR);
        (yyval.EXPR)->breaklist = mergelist((yyvsp[-1].EXPR)->breaklist,(yyvsp[0].EXPR)->breaklist);
        (yyval.EXPR)->contlist = mergelist((yyvsp[-1].EXPR)->contlist,(yyvsp[0].EXPR)->contlist);
        (yyval.EXPR)->returnlist = mergelist((yyvsp[-1].EXPR)->returnlist,(yyvsp[0].EXPR)->returnlist);
}
#line 1689 "parser.c"
    break;

  case 6:
#line 176 "parser.y"
  {(yyval.EXPR) = malloc(sizeof(expr));}
#line 1695 "parser.c"
    break;

  case 7:
#line 179 "parser.y"
                           {
        libcheck =0;
        if(assign_flag ==1){
        emit(ASSIGN,newexpr_constbool(1),NULL,(yyvsp[-1].EXPR),-1);
        emit(JUMP,NULL,NULL,NULL,nextquad() +3);
        emit(ASSIGN,newexpr_constbool(0),NULL,(yyvsp[-1].EXPR),-1);

        backpatch((yyvsp[-1].EXPR)->truelist, nextquad()-2);
        backpatch((yyvsp[-1].EXPR)->falselist, nextquad());

        assign_flag = 0;
        }else if(assign_flag ==2){
                backpatch((yyvsp[-1].EXPR)->truelist, nextquad()-2);
                backpatch((yyvsp[-1].EXPR)->falselist, nextquad());
                assign_flag = 0;
        }
        (yyval.EXPR) = (yyvsp[-1].EXPR);
    }
#line 1718 "parser.c"
    break;

  case 8:
#line 197 "parser.y"
             {(yyval.EXPR) = (yyvsp[0].EXPR);}
#line 1724 "parser.c"
    break;

  case 9:
#line 198 "parser.y"
                {(yyval.EXPR) = (yyvsp[0].EXPR);}
#line 1730 "parser.c"
    break;

  case 10:
#line 199 "parser.y"
              {(yyval.EXPR) = (yyvsp[0].EXPR);}
#line 1736 "parser.c"
    break;

  case 11:
#line 200 "parser.y"
                 {
            (yyval.EXPR) = (yyvsp[0].EXPR);
            if(functionFlag == 0)error("no function to return" , yylineno);
            }
#line 1745 "parser.c"
    break;

  case 12:
#line 204 "parser.y"
                      {
            libcheck =0;
            (yyval.EXPR) = malloc(sizeof(expr));
            if(loopFlag == 0)error("no loop to break" , yylineno);
            (yyval.EXPR)->breaklist = new_list(nextquad());
            emit(JUMP,NULL,NULL,NULL,-1);
            }
#line 1757 "parser.c"
    break;

  case 13:
#line 211 "parser.y"
                         {
            libcheck =0;
            (yyval.EXPR) = malloc(sizeof(expr));
            if(loopFlag == 0)error("no loop to Continue" , yylineno);
            (yyval.EXPR)->contlist = new_list(nextquad());
            emit(JUMP,NULL,NULL,NULL,-1);
            }
#line 1769 "parser.c"
    break;

  case 14:
#line 218 "parser.y"
            {(yyval.EXPR) = (yyvsp[0].EXPR);}
#line 1775 "parser.c"
    break;

  case 15:
#line 219 "parser.y"
              {(yyval.EXPR)=  malloc(sizeof(expr));}
#line 1781 "parser.c"
    break;

  case 16:
#line 220 "parser.y"
                {libcheck =0;(yyval.EXPR) = malloc(sizeof(expr));}
#line 1787 "parser.c"
    break;

  case 17:
#line 226 "parser.y"
                             {(yyval.EXPR) = (yyvsp[0].EXPR);}
#line 1793 "parser.c"
    break;

  case 18:
#line 227 "parser.y"
                                         {                     
                (yyval.EXPR) = new_expression(arthmexp_ );  
                (yyval.EXPR)->sym = tmp_item();
                emit(ADD , (yyvsp[-2].EXPR) , (yyvsp[0].EXPR) , (yyval.EXPR) , -1);}
#line 1802 "parser.c"
    break;

  case 19:
#line 231 "parser.y"
                                          {
                (yyval.EXPR) = new_expression(arthmexp_ );  
                (yyval.EXPR)->sym = tmp_item();
                emit(SUB , (yyvsp[-2].EXPR) , (yyvsp[0].EXPR) , (yyval.EXPR) , -1);
            }
#line 1812 "parser.c"
    break;

  case 20:
#line 236 "parser.y"
                                             {              
                (yyval.EXPR) = new_expression(arthmexp_ );  
                (yyval.EXPR)->sym = tmp_item();
                emit(MUL , (yyvsp[-2].EXPR) , (yyvsp[0].EXPR) , (yyval.EXPR) , -1);}
#line 1821 "parser.c"
    break;

  case 21:
#line 240 "parser.y"
                                             {
                (yyval.EXPR) = new_expression(arthmexp_ );  
                (yyval.EXPR)->sym = tmp_item();
                emit(DIV , (yyvsp[-2].EXPR) , (yyvsp[0].EXPR) , (yyval.EXPR) , -1);}
#line 1830 "parser.c"
    break;

  case 22:
#line 244 "parser.y"
                             {if((yyvsp[-1].EXPR)->type != boolexpr_ ) {
                emit(IF_EQ , (yyvsp[-1].EXPR) , newexpr_constbool(1) , NULL , -1);
                emit(JUMP,NULL,NULL,NULL,-1);

                (yyvsp[-1].EXPR)->truelist = new_list(nextquad()-2);
                (yyvsp[-1].EXPR)->falselist = new_list(nextquad()-1);
        }}
#line 1842 "parser.c"
    break;

  case 23:
#line 250 "parser.y"
                        {
                (yyval.EXPR)  =  new_expression(boolexpr_ );
                (yyval.EXPR)->sym = tmp_item();

                if((yyvsp[0].EXPR)->type != boolexpr_ ){
                    emit(IF_EQ , (yyvsp[0].EXPR) , newexpr_constbool(1) , NULL, -1);
                    emit(JUMP,NULL,NULL,NULL,-1);
                    (yyvsp[0].EXPR)->truelist = new_list(nextquad()-2);
                    (yyvsp[0].EXPR)->falselist = new_list(nextquad()-1);
                }
                backpatch((yyvsp[-4].EXPR)->truelist, (yyvsp[-1].label_jumps)+1); // + 1 einai to swsto mallon

                (yyval.EXPR)->truelist = (yyvsp[0].EXPR)->truelist;
                (yyval.EXPR)->falselist = mergelist((yyvsp[-4].EXPR)->falselist,(yyvsp[0].EXPR)->falselist);
                
                if(assign_flag !=2)
                assign_flag = 1;

            }
#line 1866 "parser.c"
    break;

  case 24:
#line 269 "parser.y"
                             {if((yyvsp[-1].EXPR)->type != boolexpr_ ) {

                emit(IF_EQ , (yyvsp[-1].EXPR) , newexpr_constbool(1) , NULL , -1);
                emit(JUMP,NULL,NULL,NULL,-1);

                (yyvsp[-1].EXPR)->truelist = new_list(nextquad()-2);
                (yyvsp[-1].EXPR)->falselist = new_list(nextquad()-1);
        }}
#line 1879 "parser.c"
    break;

  case 25:
#line 276 "parser.y"
                         {
                (yyval.EXPR)  =  new_expression(boolexpr_ );
                (yyval.EXPR)->sym = tmp_item();

                if((yyvsp[0].EXPR)->type != boolexpr_ ){
                    emit(IF_EQ , (yyvsp[0].EXPR) , newexpr_constbool(1) , NULL, -1);
                    emit(JUMP,NULL,NULL,NULL,-1);
                    (yyvsp[0].EXPR)->truelist = new_list(nextquad()-2);
                    (yyvsp[0].EXPR)->falselist = new_list(nextquad()-1);
                }

                backpatch((yyvsp[-4].EXPR)->falselist,(yyvsp[-1].label_jumps)+1);

                (yyval.EXPR)->truelist = mergelist((yyvsp[-4].EXPR)->truelist, (yyvsp[0].EXPR)->truelist);
                (yyval.EXPR)->falselist = (yyvsp[0].EXPR)->falselist;

                 if(assign_flag !=2)
                assign_flag = 1;           
                }
#line 1903 "parser.c"
    break;

  case 26:
#line 295 "parser.y"
                                        {
                 (yyval.EXPR) = new_expression(arthmexp_ );  
                (yyval.EXPR)->sym = tmp_item();
                emit(MOD , (yyvsp[-2].EXPR) , (yyvsp[0].EXPR) , (yyval.EXPR) , -1);}
#line 1912 "parser.c"
    break;

  case 27:
#line 299 "parser.y"
                                          {
                (yyval.EXPR) = new_expression(boolexpr_);
                (yyval.EXPR)->sym = tmp_item();
                emit(IF_EQ , (yyvsp[-2].EXPR) , (yyvsp[0].EXPR) ,NULL , -1);
                emit(JUMP,NULL,NULL,NULL,-1);
                (yyval.EXPR)->truelist = new_list(nextquad()-2);
                (yyval.EXPR)->falselist = new_list(nextquad()-1);
                assign_flag = 1; 
                    }
#line 1926 "parser.c"
    break;

  case 28:
#line 308 "parser.y"
                                            {
                (yyval.EXPR) = new_expression(boolexpr_);
                (yyval.EXPR)->sym = tmp_item();
                emit(IF_NOTEQ , (yyvsp[-2].EXPR) , (yyvsp[0].EXPR) ,NULL , -1);
                emit(JUMP,NULL,NULL,NULL,-1);
                (yyval.EXPR)->truelist = new_list(nextquad()-2);
                (yyval.EXPR)->falselist = new_list(nextquad()-1);
                assign_flag = 1; 
            }
#line 1940 "parser.c"
    break;

  case 29:
#line 317 "parser.y"
                                            {
                (yyval.EXPR) = new_expression(boolexpr_);
                (yyval.EXPR)->sym = tmp_item();
                emit(IF_GREATER , (yyvsp[-2].EXPR) , (yyvsp[0].EXPR) ,NULL , -1);
                emit(JUMP,NULL,NULL,NULL,-1);
                (yyval.EXPR)->truelist = new_list(nextquad()-2);
                (yyval.EXPR)->falselist = new_list(nextquad()-1);
                assign_flag = 1;     
                    }
#line 1954 "parser.c"
    break;

  case 30:
#line 326 "parser.y"
                                         {
                (yyval.EXPR) = new_expression(boolexpr_);
                (yyval.EXPR)->sym = tmp_item();
                emit(IF_LESS , (yyvsp[-2].EXPR) , (yyvsp[0].EXPR) ,NULL , -1);
                emit(JUMP,NULL,NULL,NULL,-1);
                (yyval.EXPR)->truelist = new_list(nextquad()-2);
                (yyval.EXPR)->falselist = new_list(nextquad()-1);
                assign_flag = 1; 
            }
#line 1968 "parser.c"
    break;

  case 31:
#line 335 "parser.y"
                                            {
                (yyval.EXPR) = new_expression(boolexpr_);
                (yyval.EXPR)->sym = tmp_item();
                emit(IF_GREATEREQ , (yyvsp[-2].EXPR) , (yyvsp[0].EXPR) ,NULL , -1);
                emit(JUMP,NULL,NULL,NULL,-1);
                (yyval.EXPR)->truelist = new_list(nextquad()-2);
                (yyval.EXPR)->falselist = new_list(nextquad()-1);
                assign_flag = 1; 
            }
#line 1982 "parser.c"
    break;

  case 32:
#line 344 "parser.y"
                                            {
                (yyval.EXPR) = new_expression(boolexpr_);
                (yyval.EXPR)->sym = tmp_item();
                emit(IF_LESSEQ , (yyvsp[-2].EXPR) , (yyvsp[0].EXPR) ,NULL , -1);
                emit(JUMP,NULL,NULL,NULL,-1);
                (yyval.EXPR)->truelist = new_list(nextquad()-2);
                (yyval.EXPR)->falselist = new_list(nextquad()-1);
                assign_flag = 1;               
            }
#line 1996 "parser.c"
    break;

  case 33:
#line 353 "parser.y"
                   {(yyval.EXPR) = (yyvsp[0].EXPR);}
#line 2002 "parser.c"
    break;

  case 34:
#line 360 "parser.y"
                                                      {(yyval.EXPR) = (yyvsp[-1].EXPR);}
#line 2008 "parser.c"
    break;

  case 35:
#line 361 "parser.y"
                                        {
                check_arith((yyvsp[0].EXPR),"uminus");
                (yyval.EXPR) = newexpr(arthmexp_);
                (yyval.EXPR)->sym = istempexpr((yyvsp[0].EXPR)) ? (yyvsp[0].EXPR)->sym: tmp_item();
                emit(UMINUS,(yyvsp[0].EXPR),NULL,(yyval.EXPR),-1);
        }
#line 2019 "parser.c"
    break;

  case 36:
#line 367 "parser.y"
                         {
                (yyval.EXPR) = newexpr(boolexpr_); 
                (yyval.EXPR)->sym = tmp_item();

                emit(IF_EQ,(yyvsp[0].EXPR),newexpr_constbool(1),NULL,nextquad()+5);
                emit(JUMP,NULL,NULL,NULL,nextquad()+2);

                 (yyval.EXPR)->truelist = new_list(nextquad()-1);
                 (yyval.EXPR)->falselist = new_list(nextquad()-2);

                emit(ASSIGN,newexpr_constbool(1),NULL,(yyval.EXPR) , -1);
                emit(JUMP,NULL,NULL,NULL , nextquad() + 3);
                emit(ASSIGN,newexpr_constbool(0),NULL,(yyval.EXPR) , -1); 

                backpatch((yyvsp[0].EXPR)->truelist, nextquad() -2);
                backpatch((yyvsp[0].EXPR)->falselist, nextquad());
                                

                assign_flag = 2;
        }
#line 2044 "parser.c"
    break;

  case 37:
#line 387 "parser.y"
                           {
                if(libcheck == 1){
                        error("Den boreis na kaneis pra3eis me synartiseis", yylineno); 
                        libcheck=0;
                }
                check_arith((yyvsp[0].EXPR),"++ lvalue");
                if((yyvsp[0].EXPR)->type == tableitem_){


                         (yyval.EXPR) = newexpr(var_);
                         (yyval.EXPR)->sym = tmp_item();
                         emit(TABLEGETELEM, (yyvsp[0].EXPR), (yyvsp[0].EXPR)->index, (yyval.EXPR), -1);

                        emit(ADD,(yyval.EXPR),newexpr_constnum(1),(yyval.EXPR),-1);
                        emit(TABLESETELEM,(yyvsp[0].EXPR)->index,(yyval.EXPR),(yyvsp[0].EXPR),-1);
                }else{
                        emit(ADD,(yyvsp[0].EXPR),newexpr_constnum(1),(yyvsp[0].EXPR),-1);
                        (yyval.EXPR) = newexpr(arthmexp_);
                        (yyval.EXPR)->sym = tmp_item();
                        emit(ASSIGN,(yyvsp[0].EXPR),NULL,(yyval.EXPR),-1);
                }
                        
        }
#line 2072 "parser.c"
    break;

  case 38:
#line 410 "parser.y"
                           {
                if(libcheck == 1){
                error("Den boreis na kaneis pra3eis me synartiseis", yylineno); 
                libcheck=0;}
                check_arith((yyvsp[-1].EXPR),"lvalue ++");
                (yyval.EXPR) = newexpr(boolexpr_); 
                (yyval.EXPR)->sym = tmp_item();
                if((yyvsp[-1].EXPR)->type==tableitem_){

                        expr *val = newexpr(var_);
                        val->sym = tmp_item();
                        emit(TABLEGETELEM, (yyvsp[-1].EXPR), (yyvsp[-1].EXPR)->index, val, -1);

                        emit(ASSIGN,val,NULL,(yyval.EXPR),-1);
                        emit(ADD,val,newexpr_constnum(1),val , -1);
                        emit(TABLESETELEM,(yyvsp[-1].EXPR)->index,val,(yyvsp[-1].EXPR) , -1);

                }else{
                        emit(ASSIGN,(yyvsp[-1].EXPR),NULL,(yyval.EXPR),-1);
                        emit(ADD,(yyvsp[-1].EXPR),newexpr_constnum(1),(yyvsp[-1].EXPR),-1);
                }

        }
#line 2100 "parser.c"
    break;

  case 39:
#line 433 "parser.y"
                             {
                if(libcheck == 1){
                        error("Den boreis na kaneis pra3eis me synartiseis", yylineno); 
                        libcheck=0;
                        }
                check_arith((yyvsp[0].EXPR),"-- lvalue");
                if((yyvsp[0].EXPR)->type == tableitem_){

                        (yyval.EXPR) = newexpr(var_);
                        (yyval.EXPR)->sym = tmp_item();
                        emit(TABLEGETELEM, (yyvsp[0].EXPR), (yyvsp[0].EXPR)->index, (yyval.EXPR), -1);


                        emit(SUB,(yyval.EXPR),newexpr_constnum(1),(yyval.EXPR) ,-1);
                        emit(TABLESETELEM,(yyvsp[0].EXPR)->index,(yyval.EXPR),(yyvsp[0].EXPR) , -1);
                }else{
                        emit(SUB,(yyvsp[0].EXPR),newexpr_constnum(1),(yyvsp[0].EXPR) , -1);
                        (yyval.EXPR) = newexpr(arthmexp_);
                        (yyval.EXPR)->sym = tmp_item();
                        emit(ASSIGN,(yyvsp[0].EXPR),NULL,(yyval.EXPR) , -1);
                }
                
        }
#line 2128 "parser.c"
    break;

  case 40:
#line 456 "parser.y"
                             {
                if(libcheck == 1){
                        error("Den boreis na kaneis pra3eis me synartiseis", yylineno);
                        libcheck=0;
                }
              check_arith((yyvsp[-1].EXPR),"lvalue --");
                (yyval.EXPR) = newexpr(boolexpr_); 
                (yyval.EXPR)->sym = tmp_item();
                if((yyvsp[-1].EXPR)->type==tableitem_){
                        expr *val = newexpr(var_);
                        val->sym = tmp_item();
                        emit(TABLEGETELEM, (yyvsp[-1].EXPR), (yyvsp[-1].EXPR)->index, val, -1);

                        emit(ASSIGN,val,NULL,(yyval.EXPR),-1);
                        emit(SUB,val,newexpr_constnum(1),val , -1);
                        emit(TABLESETELEM,(yyvsp[-1].EXPR)->index,val,(yyvsp[-1].EXPR) , -1);
                }else{
                        emit(ASSIGN,(yyvsp[-1].EXPR),NULL,(yyval.EXPR) , -1);
                        emit(SUB,(yyvsp[-1].EXPR),newexpr_constnum(1),(yyvsp[-1].EXPR) ,-1);
                }
                
        }
#line 2155 "parser.c"
    break;

  case 41:
#line 478 "parser.y"
                  {(yyval.EXPR) = (yyvsp[0].EXPR);}
#line 2161 "parser.c"
    break;

  case 42:
#line 481 "parser.y"
                         {if(libcheck == 1){error("Den boreis na kaneis pra3eis me synartiseis", yylineno); libcheck=0;}}
#line 2167 "parser.c"
    break;

  case 43:
#line 481 "parser.y"
                                                                                                                                            {
        
                if((yyvsp[-3].EXPR)->type == tableitem_){ 
                        emit(TABLESETELEM, (yyvsp[-3].EXPR)->index,(yyvsp[0].EXPR) , (yyvsp[-3].EXPR) , -1);
                        (yyval.EXPR) = emit_iftableitem((yyvsp[-3].EXPR));
                        (yyval.EXPR)->type = assignexp_;
                }else{
                        (yyval.EXPR) = newexpr(assignexp_);
                        (yyval.EXPR)->sym = tmp_item();
                        if((yyvsp[0].EXPR)->type == boolexpr_){
                        if(assign_flag==1){
                                emit(ASSIGN,newexpr_constbool(1),NULL,(yyval.EXPR) , -1);
                                emit(JUMP,NULL,NULL,NULL , nextquad() + 3);
                                emit(ASSIGN,newexpr_constbool(0),NULL,(yyval.EXPR) , -1); 
                                backpatch((yyvsp[0].EXPR)->truelist, nextquad() -2);
                                backpatch((yyvsp[0].EXPR)->falselist, nextquad());
                                assign_flag = 0;
                        }else if(assign_flag==2){
                                backpatch((yyvsp[0].EXPR)->truelist, nextquad() -2);
                                backpatch((yyvsp[0].EXPR)->falselist, nextquad());

                        }
                        }
                        emit(ASSIGN,(yyvsp[0].EXPR),NULL,(yyvsp[-3].EXPR) , -1);
                        emit(ASSIGN,(yyvsp[-3].EXPR),NULL,(yyval.EXPR) , -1);
                        
                }    

                }
#line 2201 "parser.c"
    break;

  case 44:
#line 515 "parser.y"
                {(yyval.EXPR) = emit_iftableitem((yyvsp[0].EXPR));}
#line 2207 "parser.c"
    break;

  case 45:
#line 516 "parser.y"
               {callFlag =1; (yyval.EXPR) = (yyvsp[0].EXPR);}
#line 2213 "parser.c"
    break;

  case 46:
#line 517 "parser.y"
                    {(yyval.EXPR) = (yyvsp[0].EXPR);}
#line 2219 "parser.c"
    break;

  case 47:
#line 518 "parser.y"
                                                     {
                (yyval.EXPR)=newexpr(pfunc_);
                (yyval.EXPR)->sym = (yyvsp[-1].item);
        }
#line 2228 "parser.c"
    break;

  case 48:
#line 522 "parser.y"
                {(yyval.EXPR) = (yyvsp[0].EXPR);}
#line 2234 "parser.c"
    break;

  case 49:
#line 528 "parser.y"
           {   
                                if(isLibraryFunction((yyvsp[0].strVal))){libcheck =1;}
                                if(isFA((yyvsp[0].strVal)))libcheck =1;
                                item* new;
                                if(scopeCounter == 0){new = newItem((yyvsp[0].strVal),"global variable", scopeCounter , yylineno);new_check(new); }
                                else {new = newItem((yyvsp[0].strVal),"local variable", scopeCounter , yylineno );new_check(new);}
                                (yyval.EXPR) = lvalue_expr(new);
                                 

        }
#line 2249 "parser.c"
    break;

  case 50:
#line 538 "parser.y"
                   {
                                if(isLibraryFunction((yyvsp[0].strVal)))libcheck =1;
                              //  if(isFA($2))libcheck =1;
                                item* new = NULL;
                                new = newItem((yyvsp[0].strVal),"local", scopeCounter , yylineno );
                                new_check(new);
                                (yyval.EXPR) = lvalue_expr(new);
        }
#line 2262 "parser.c"
    break;

  case 51:
#line 546 "parser.y"
                           {
                                if(isFA((yyvsp[0].strVal)))libcheck =1;
                                item* tmp = lookupScope((yyvsp[0].strVal) , 0);
                                if(tmp == NULL){error("Cant find Global " , yylineno);} 
                                (yyval.EXPR) = lvalue_expr(tmp);               
        }
#line 2273 "parser.c"
    break;

  case 52:
#line 552 "parser.y"
                 {(yyval.EXPR) = (yyvsp[0].EXPR);}
#line 2279 "parser.c"
    break;

  case 53:
#line 556 "parser.y"
                      {libcheck = 0;
            (yyval.EXPR) = member_item((yyvsp[-2].EXPR),(yyvsp[0].strVal));    
        }
#line 2287 "parser.c"
    break;

  case 54:
#line 559 "parser.y"
                                                       {
                libcheck = 0;
                (yyvsp[-3].EXPR) = emit_iftableitem((yyvsp[-3].EXPR));
                (yyval.EXPR) = newexpr(tableitem_);
                (yyval.EXPR)->sym = (yyvsp[-3].EXPR)->sym;
                (yyval.EXPR)->index = (yyvsp[-1].EXPR);
                }
#line 2299 "parser.c"
    break;

  case 55:
#line 566 "parser.y"
               {callFlag =1;libcheck =0;}
#line 2305 "parser.c"
    break;

  case 56:
#line 566 "parser.y"
                                                 {callFlag =0;libcheck = 0;}
#line 2311 "parser.c"
    break;

  case 57:
#line 567 "parser.y"
               {callFlag =1;libcheck=0;}
#line 2317 "parser.c"
    break;

  case 58:
#line 567 "parser.y"
                                                                               {callFlag =0;libcheck = 0;}
#line 2323 "parser.c"
    break;

  case 59:
#line 571 "parser.y"
           {callFlag =1;libcheck = 0;}
#line 2329 "parser.c"
    break;

  case 60:
#line 571 "parser.y"
                                                                                {(yyval.EXPR)=make_call((yyvsp[-4].EXPR),(yyvsp[-1].EXPR));callFlag =0;}
#line 2335 "parser.c"
    break;

  case 61:
#line 572 "parser.y"
                  {callFlag =1;libcheck = 0;}
#line 2341 "parser.c"
    break;

  case 62:
#line 572 "parser.y"
                                                         {
                if((yyvsp[0].for_call)->method){
                        expr* t = (yyvsp[-2].EXPR);
                        (yyvsp[-2].EXPR) = emit_iftableitem(member_item(t,(yyvsp[0].for_call)->name));
                        (yyvsp[0].for_call)->elist->next = t;
                }         
                (yyval.EXPR) = make_call((yyvsp[-2].EXPR),(yyvsp[0].for_call)->elist);
                callFlag =0;}
#line 2354 "parser.c"
    break;

  case 63:
#line 580 "parser.y"
                                                     {callFlag =1;libcheck = 0;}
#line 2360 "parser.c"
    break;

  case 64:
#line 580 "parser.y"
                                                                                                                          {
                expr* func = newexpr(pfunc_);
                func->sym = (yyvsp[-5].item);
                (yyval.EXPR) = make_call(func,(yyvsp[-1].EXPR));
                callFlag =0;}
#line 2370 "parser.c"
    break;

  case 65:
#line 589 "parser.y"
                       {
                callFlag =1; 
                (yyval.for_call) = (yyvsp[0].for_call);
        }
#line 2379 "parser.c"
    break;

  case 66:
#line 593 "parser.y"
                         {
                callFlag =1;
                (yyval.for_call) = (yyvsp[0].for_call);
        }
#line 2388 "parser.c"
    break;

  case 67:
#line 599 "parser.y"
                             {callFlag =1;}
#line 2394 "parser.c"
    break;

  case 68:
#line 599 "parser.y"
                                                                    {
        (yyval.for_call) = insert_call((yyvsp[-1].EXPR),0,NULL);
        }
#line 2402 "parser.c"
    break;

  case 69:
#line 606 "parser.y"
                        {callFlag =1;}
#line 2408 "parser.c"
    break;

  case 70:
#line 606 "parser.y"
                                                                                   {
                (yyval.for_call) = insert_call((yyvsp[-1].EXPR),1,(yyvsp[-3].strVal));
        }
#line 2416 "parser.c"
    break;

  case 71:
#line 613 "parser.y"
                             {
                (yyvsp[-1].EXPR)->next = (yyvsp[0].EXPR);
                (yyval.EXPR) = (yyvsp[-1].EXPR);  
        }
#line 2425 "parser.c"
    break;

  case 72:
#line 617 "parser.y"
          {(yyval.EXPR) = NULL;}
#line 2431 "parser.c"
    break;

  case 73:
#line 620 "parser.y"
                                      {
                 (yyvsp[-1].EXPR)->next = (yyvsp[0].EXPR);
                 (yyval.EXPR) = (yyvsp[-1].EXPR);
        }
#line 2440 "parser.c"
    break;

  case 74:
#line 624 "parser.y"
          {(yyval.EXPR) = NULL;}
#line 2446 "parser.c"
    break;

  case 75:
#line 627 "parser.y"
                        {scopeCounter--;objectHide =0;}
#line 2452 "parser.c"
    break;

  case 76:
#line 627 "parser.y"
                                                                            {
        scopeCounter++;
        objectHide=1;
        expr *t = newexpr(newtable_);
        t->sym = tmp_item();
        emit(TABLECREATE,t,NULL,NULL,-1);
        int i = 0;
        while((yyvsp[-1].EXPR)){
                emit(TABLESETELEM, newexpr_constnum(i++),(yyvsp[-1].EXPR), t,-1);
                (yyvsp[-1].EXPR) = (yyvsp[-1].EXPR)->next;
        }
        (yyval.EXPR) = t;
        }
#line 2470 "parser.c"
    break;

  case 77:
#line 640 "parser.y"
                       {scopeCounter--;objectHide =0;}
#line 2476 "parser.c"
    break;

  case 78:
#line 640 "parser.y"
                                                                             {
                scopeCounter++;
                objectHide=1;
                expr *t = newexpr(newtable_);
                t->sym = tmp_item();
                emit(TABLECREATE,t,NULL,NULL,-1);
                while((yyvsp[-1].indexstr)){
                        emit(TABLESETELEM, (yyvsp[-1].indexstr)->ena,(yyvsp[-1].indexstr)->dio,t,-1);
                        (yyvsp[-1].indexstr) = (yyvsp[-1].indexstr)->next;
                }     
                (yyval.EXPR) = t;  
        }
#line 2493 "parser.c"
    break;

  case 79:
#line 655 "parser.y"
                                  {
                 (yyvsp[-1].indexstr)->next=(yyvsp[0].indexstr);
                 (yyval.indexstr) = (yyvsp[-1].indexstr);
        }
#line 2502 "parser.c"
    break;

  case 80:
#line 661 "parser.y"
                                            {
                // if($3 == NULL){
                //         cyn();
                //         $1 = malloc(sizeof(indexstr));
                //         $1 = $3;
                // }else{
                //      red();
                //      $1->next = $3;  
                // }
                
                (yyvsp[-1].indexstr)->next = (yyvsp[0].indexstr);
                (yyval.indexstr) = (yyvsp[-1].indexstr);}
#line 2519 "parser.c"
    break;

  case 81:
#line 673 "parser.y"
          {(yyval.indexstr)= NULL;}
#line 2525 "parser.c"
    break;

  case 82:
#line 676 "parser.y"
                                   {scopeCounter++;
                if(scopeCounter > maxScope) maxScope = scopeCounter;}
#line 2532 "parser.c"
    break;

  case 83:
#line 678 "parser.y"
                                                                {       
                        if(objectHide)hide(scopeCounter);
                        scopeCounter--;
                        (yyval.indexstr) = malloc(sizeof(indexstr));
                        (yyval.indexstr)->ena = (yyvsp[-3].EXPR);
                        (yyval.indexstr)->dio = (yyvsp[-1].EXPR);
                        (yyval.indexstr)->next = NULL;
                 }
#line 2545 "parser.c"
    break;

  case 84:
#line 689 "parser.y"
                          {scopeCounter++;
        if(scopeCounter > maxScope) maxScope = scopeCounter;}
#line 2552 "parser.c"
    break;

  case 85:
#line 691 "parser.y"
                                  {
                if(objectHide)hide(scopeCounter);
                scopeCounter--;
                (yyval.EXPR) = (yyvsp[-1].EXPR);
                }
#line 2562 "parser.c"
    break;

  case 86:
#line 699 "parser.y"
                                                                   {

        backpatch((yyvsp[-1].EXPR)->returnlist, nextquad()+1);
        expr*temp = newexpr(pfunc_);
        temp->sym = (yyvsp[-4].item);
        emit(FUNCEND,temp,NULL,NULL,-1);
        patchlabel((yyvsp[-4].item)->jump,nextquad()+1);
        (yyval.item) = (yyvsp[-4].item);
        }
#line 2576 "parser.c"
    break;

  case 87:
#line 710 "parser.y"
                             {
        item* new = newItem((yyvsp[0].strVal),"User Function", scopeCounter , yylineno );
        new_check(new);
        expr*temp = newexpr(pfunc_);
        temp->sym = new;
        emit(JUMP,NULL,NULL,NULL,-1);
        emit(FUNCSTART,temp,NULL,NULL,-1);
        functionName = strdup((yyvsp[0].strVal));
        offset =0;
        new->jump = nextquad()-2;
        (yyval.item) = new;
}
#line 2593 "parser.c"
    break;

  case 88:
#line 724 "parser.y"
             {
                (yyval.strVal) = (yyvsp[0].strVal);
        }
#line 2601 "parser.c"
    break;

  case 89:
#line 727 "parser.y"
          {
                char noname[20];
                sprintf(noname,"function$%d",functionCounter);
                functionCounter++;
                (yyval.strVal) = noname;
        }
#line 2612 "parser.c"
    break;

  case 90:
#line 735 "parser.y"
                           {scopeCounter++;}
#line 2618 "parser.c"
    break;

  case 91:
#line 735 "parser.y"
                                                                       {offset = 0;scopeCounter--;functionFlag++; }
#line 2624 "parser.c"
    break;

  case 92:
#line 738 "parser.y"
                {
        (yyval.EXPR)=(yyvsp[0].EXPR);
        functionFlag --;getoffset();
        }
#line 2633 "parser.c"
    break;

  case 93:
#line 744 "parser.y"
                {push1(loopcounterstack, loopFlag); loopFlag = 0;}
#line 2639 "parser.c"
    break;

  case 94:
#line 747 "parser.y"
              {
        loopFlag = pop1(loopcounterstack);}
#line 2646 "parser.c"
    break;

  case 95:
#line 751 "parser.y"
                {(yyval.EXPR) = newexpr_constint((yyvsp[0].intVal));
        }
#line 2653 "parser.c"
    break;

  case 96:
#line 753 "parser.y"
               {(yyval.EXPR) = newexpr_constnum((yyvsp[0].doubleVal));}
#line 2659 "parser.c"
    break;

  case 97:
#line 754 "parser.y"
                 {(yyval.EXPR) = newexpr_constring((yyvsp[0].strVal));}
#line 2665 "parser.c"
    break;

  case 98:
#line 755 "parser.y"
              {(yyval.EXPR) = newexpr(nill_);}
#line 2671 "parser.c"
    break;

  case 99:
#line 756 "parser.y"
               {(yyval.EXPR) = newexpr_constbool(1);}
#line 2677 "parser.c"
    break;

  case 100:
#line 757 "parser.y"
                {(yyval.EXPR) = newexpr_constbool(0);}
#line 2683 "parser.c"
    break;

  case 101:
#line 762 "parser.y"
                    {
        
                item* new = newItem((yyvsp[-1].strVal),"formal argument", scopeCounter , yylineno );
                    formal_flag = 1;
                    new_check(new);
                    insert_formal_arg(functionName , (yyvsp[-1].strVal));
                    formal_flag = 0;
                    
        }
#line 2697 "parser.c"
    break;

  case 102:
#line 771 "parser.y"
          {;}
#line 2703 "parser.c"
    break;

  case 103:
#line 774 "parser.y"
                            {
        
                  item* new = newItem((yyvsp[0].strVal),"formal argument", scopeCounter , yylineno );
                  new_check(new);
                  insert_formal_arg(functionName , (yyvsp[0].strVal));
        }
#line 2714 "parser.c"
    break;

  case 104:
#line 780 "parser.y"
          {;}
#line 2720 "parser.c"
    break;

  case 105:
#line 786 "parser.y"
                   {
               
                patchlabel((yyvsp[-1].label_jumps)-1 , nextquad()+1);
                (yyval.EXPR) = (yyvsp[0].EXPR);
        }
#line 2730 "parser.c"
    break;

  case 106:
#line 791 "parser.y"
                                  {
                patchlabel((yyvsp[-3].label_jumps) -1 , (yyvsp[-1].label_jumps)+2);
                patchlabel((yyvsp[-1].label_jumps) , nextquad()+1);
                (yyval.EXPR) = (yyvsp[-2].EXPR);
        }
#line 2740 "parser.c"
    break;

  case 107:
#line 798 "parser.y"
                                                       {
                if((yyvsp[-1].EXPR)->type== boolexpr_){
                        emit(ASSIGN,newexpr_constbool(1),NULL,(yyvsp[-1].EXPR),-1);
                        emit(JUMP,NULL,NULL,NULL,nextquad() +3);
                        emit(ASSIGN,newexpr_constbool(0),NULL,(yyvsp[-1].EXPR),-1);
                        assign_flag =0 ;
                        backpatch((yyvsp[-1].EXPR)->truelist, nextquad()-2);
                        backpatch((yyvsp[-1].EXPR)->falselist, nextquad());
                }else{
                        backpatch((yyvsp[-1].EXPR)->truelist, nextquad()+1);
                        backpatch((yyvsp[-1].EXPR)->falselist, nextquad()+3);    
                } 
                emit(IF_EQ , (yyvsp[-1].EXPR) , new_expr_constbool(1) ,NULL, nextquad() +3);
                emit(JUMP , NULL , NULL , NULL , -1);
              
                (yyval.label_jumps) = nextquad();
}
#line 2762 "parser.c"
    break;

  case 108:
#line 816 "parser.y"
              {
        (yyval.label_jumps) = nextquad();                                        /* STAF */
        emit(JUMP , NULL , NULL ,NULL, -1);
}
#line 2771 "parser.c"
    break;

  case 109:
#line 822 "parser.y"
                  {
        (yyval.label_jumps) = nextquad();
}
#line 2779 "parser.c"
    break;

  case 110:
#line 827 "parser.y"
                                                         {
        if((yyvsp[-1].EXPR)->type== boolexpr_){ 
        if(assign_flag != 2){       
        emit(ASSIGN,newexpr_constbool(1),NULL,(yyvsp[-1].EXPR),-1);
        emit(JUMP,NULL,NULL,NULL,nextquad()+3);
        emit(ASSIGN,newexpr_constbool(0),NULL,(yyvsp[-1].EXPR),-1);
        backpatch((yyvsp[-1].EXPR)->truelist, nextquad()-2);
        backpatch((yyvsp[-1].EXPR)->falselist, nextquad());
        assign_flag = 0;
        }
        }
        emit(IF_EQ , (yyvsp[-1].EXPR) , new_expr_constbool(1) , NULL , nextquad()+3);
        emit(JUMP , NULL , NULL , NULL , -1);
        (yyval.label_jumps) = nextquad();
}
#line 2799 "parser.c"
    break;

  case 111:
#line 844 "parser.y"
                                {loopFlag ++;}
#line 2805 "parser.c"
    break;

  case 112:
#line 844 "parser.y"
                                                    {
                loopFlag--;
                (yyval.EXPR)=(yyvsp[0].EXPR);

                emit(JUMP , NULL , NULL , NULL,(yyvsp[-3].label_jumps)+1);         
                patchlabel((yyvsp[-2].label_jumps) -1, nextquad()+1);

                backpatch((yyvsp[0].EXPR)->breaklist, nextquad()+1); 
                backpatch((yyvsp[0].EXPR)->contlist,(yyvsp[-3].label_jumps)+ 1);
                
                (yyval.EXPR)->breaklist = NULL;
                (yyval.EXPR)->contlist = NULL;
        }
#line 2823 "parser.c"
    break;

  case 113:
#line 859 "parser.y"
                                          {loopFlag ++;}
#line 2829 "parser.c"
    break;

  case 114:
#line 859 "parser.y"
                                                                  {
        loopFlag --;
        
        patchlabel((yyvsp[-7].for_init)->enter,(yyvsp[-2].label_jumps)+2);
        patchlabel((yyvsp[-6].label_jumps),nextquad()+1);
        patchlabel((yyvsp[-2].label_jumps),(yyvsp[-7].for_init)->test+1);
        patchlabel((yyvsp[0].label_jumps),(yyvsp[-6].label_jumps)+2);
        
        backpatch((yyvsp[-1].EXPR)->breaklist,nextquad()+1);
        backpatch((yyvsp[-1].EXPR)->contlist,(yyvsp[-6].label_jumps)+2);
        
        (yyval.EXPR) = (yyvsp[-1].EXPR);
        (yyval.EXPR)->breaklist = NULL;
        (yyval.EXPR)->contlist = NULL;
}
#line 2849 "parser.c"
    break;

  case 115:
#line 876 "parser.y"
                                                                    {
        backpatch((yyvsp[-1].EXPR)->truelist, nextquad()+1);
        backpatch((yyvsp[-1].EXPR)->falselist, nextquad()+3);
        if((yyvsp[-1].EXPR)->type == boolexpr_){  
                emit(ASSIGN,newexpr_constbool(1),NULL,(yyvsp[-1].EXPR),-1);
                emit(JUMP,NULL,NULL,NULL,nextquad()+3);
                emit(ASSIGN,newexpr_constbool(0),NULL,(yyvsp[-1].EXPR),-1);
                assign_flag = 0;
        }
        (yyval.for_init) = malloc(sizeof(for_init));
        (yyval.for_init)->test = (yyvsp[-2].label_jumps);
        (yyval.for_init)->enter = nextquad();
        emit(IF_EQ,(yyvsp[-1].EXPR),newexpr_constbool(1),NULL,-1);
}
#line 2868 "parser.c"
    break;

  case 116:
#line 892 "parser.y"
  {
        (yyval.label_jumps) = nextquad();
}
#line 2876 "parser.c"
    break;

  case 117:
#line 896 "parser.y"
  {
        (yyval.label_jumps) = nextquad();
         emit(JUMP,NULL,NULL,NULL,-1);
}
#line 2885 "parser.c"
    break;

  case 118:
#line 901 "parser.y"
                             {libcheck =0;
         (yyval.EXPR) = malloc(sizeof(expr));
         emit(RETURN, NULL, NULL, NULL, -1);
         emit(JUMP,NULL,NULL,NULL,-1);
         (yyval.EXPR)->returnlist = new_list(nextquad()-1);
        }
#line 2896 "parser.c"
    break;

  case 119:
#line 907 "parser.y"
                 {returnFlag = 1; 
        }
#line 2903 "parser.c"
    break;

  case 120:
#line 908 "parser.y"
                               {libcheck =0;
        returnFlag =0; 
        (yyval.EXPR)= (yyvsp[-1].EXPR);
        emit(RETURN, (yyvsp[-1].EXPR), NULL, NULL, -1);
        emit(JUMP,NULL,NULL,NULL,-1);
        (yyval.EXPR)->returnlist = new_list(nextquad()-1);
        }
#line 2915 "parser.c"
    break;


#line 2919 "parser.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

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
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
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
                  yystos[+*yyssp], yyvsp);
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
  return yyresult;
}
#line 919 "parser.y"





int yyerror (char * YaccProvidedMessage){
        red();
        fprintf(stderr,"%s in :%d\n",YaccProvidedMessage , yylineno);
        wht();
        exit(1);
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
    loopcounterstack = arxikopoisi();
    yyparse();
    //printSymTable();
    //printHash();
    //printScopeList();
    
    print_quads();
   
}
