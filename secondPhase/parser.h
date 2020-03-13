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




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 23 "parser.y"
{
    int intVal;
    char* strVal;
    double doubleVal;
}
/* Line 1529 of yacc.c.  */
#line 153 "parser.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

