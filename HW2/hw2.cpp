#include "hw2.h"
#include <vector>
#include <iostream>
using namespace std;
/**
 * determines which variables are nullable, i.e. can produce an empty word
 * calls print_nullable when finished
 */
void compute_nullable()
{
    vector<bool> answer(NONTERMINAL_ENUM_SIZE,false);
    answer[SItems]=true;
    answer[LItems]=true;
    answer[MItems]=true;
    print_nullable(answer);
}

//returns a vector containing a vector of all rules derived from nt
vector< vector<int> > computer_first_helper(nonterminal nt) {
    vector< vector<int> > rules;
    for (int i = 0; i < grammar.size() ; ++i) {
        grammar_rule tmp=grammar[i];
        if (tmp.lhs == nt)
        {
            rules.push_back(tmp.rhs);
        }
    }
    return rules;
}

/**
 * computes first for all nonterminal (see nonterminal enum in grammar.h)
 * calls print_first when finished
 */
void compute_first()
{
    computer_first_helper(Collection);
    //print_first();
}

/**
 * computes follow for all nonterminal (see nonterminal enum in grammar.h)
 * calls print_follow when finished
 */
void compute_follow()
{
}

/**
 * computes select for all grammar rules (see grammar global variable in grammar.h)
 * calls print_select when finished
 */
void compute_select()
{
}

/**
 * implements an LL(1) parser for the grammar using yylex()
 */
void parser()
{
}

