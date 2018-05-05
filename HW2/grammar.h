#ifndef __GRAMMAR__
#define __GRAMMAR__

#include "tokens.h"
#include <vector>
#include <set>

enum nonterminal {
	S, // 0
	Structure, // 1
	SItems, // 2
	Collection, // 3
	List, // 4
	LItems, // 5
	Map, // 6
	MItems, // 7
	Key, // 8
	Item, // 9
	NONTERMINAL_ENUM_SIZE // 10
};

//             		STARTSTRUCT	|	LLIST	|	LDICT
// S         	|		0		|	1		|	1
// Structure	|		2		|	

//
//enum tokens {
//	STARTSTRUCT = 11,
//	ENDSTRUCT,	// 12
//	LLIST, // 13
//	RLIST, // 14
//	LDICT, // 15
//	RDICT, // 16
//	KEY, // 17
//	COMPLEXKEY, // 18
//	ITEM, // 19
//	COMMA, // 20
//	TYPE, // 21
//	TRUE, // 22
//	FALSE, // 23
//	INTEGER, // 24
//	REAL, // 25
//	STRING, // 26
//	VAL, // 27
//	DECLARATION, // 28
//	DEREFERENCE, // 29
//	EF // 30
//};

struct grammar_rule {
	nonterminal lhs;
	std::vector<int> rhs; //nonterminal and token
	grammar_rule(nonterminal _lhs, std::vector<int> _rhs) :lhs(_lhs), rhs(_rhs) {}
};

extern std::vector<grammar_rule> grammar;

/**
 * @param vec vector of booleans, i-th element is true if i-th nonterminal (see nonterminal enum) is nullable, i.e. can produce empty word
 */
void print_nullable(const std::vector<bool>& nullables);
/**
 * @param vec vector of ordered sets of tokens (see tokens enum in tokens.h), i-th element corresponds to i-th nonterminal (see nonterminal enum)
 */
void print_first(const std::vector<std::set<tokens> >& vec);
/**
 * @param vec vector of ordered sets of tokens (see tokens enum in tokens.h), i-th element corresponds to i-th nonterminal (see nonterminal enum)
 */
void print_follow(const std::vector<std::set<tokens> >& vec);
/**
 * @param vec vector of ordered sets of tokens (see tokens enum in tokens.h), i-th element corresponds to i-th grammar rule (see grammar global variable)
 */
void print_select(const std::vector<std::set<tokens> >& vec);

#endif //__GRAMMAR__
