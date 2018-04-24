#ifndef __HW2__
#define __HW2__

#include "tokens.h"
#include "grammar.h"

/**
 * determines which variables are nullable, i.e. can produce an empty word
 * calls print_nullable when finished
 */
void compute_nullable();

/**
 * computes first for all nonterminal (see nonterminal enum in grammar.h)
 * calls print_first when finished
 */
void compute_first();

/**
 * computes follow for all nonterminal (see nonterminal enum in grammar.h)
 * calls print_follow when finished
 */
void compute_follow();

/**
 * computes select for all grammar rules (see grammar global variable in grammar.h)
 * calls print_select when finished
 */
void compute_select();

/**
 * implements an LL(1) parser for the grammar using yylex()
 */
void parser();
/*
 * implemented in lex.yy.c (generated from lexer.lex)
 */
int yylex();

#endif //__HW2__
