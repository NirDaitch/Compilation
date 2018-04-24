#ifndef __GRAMMAR__
#define __GRAMMAR__

#include "tokens.h"
#include <vector>
#include <set>

enum nonterminal {
	S,
	Structure,
	SItems,
	Collection,
	List,
	LItems,
	Map,
	MItems,
	Key,
	Item,
	NONTERMINAL_ENUM_SIZE
};

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
