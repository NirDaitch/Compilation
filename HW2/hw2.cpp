#include "hw2.h"
#include <vector>
#include <iostream>
#include <algorithm>

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


bool isTerminal(int var)
{
	return var >= 11;
}

void printVector(vector<int> vec)
{
	cout << "start printVector" << endl;
	for (vector<int>::const_iterator XX = vec.begin(); XX != vec.end(); ++XX) 
	{
		cout << *XX << endl; 
	}
	cout << "end printVector" << endl;
}


//returns a vector containing a vector of all rules derived from nt
vector< vector<int> > getRules(nonterminal nt) {
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

bool contains(vector<int> vec, int var)
{
	return find(vec.begin(), vec.end(), var) != vec.end();
}	

set<tokens> getFirst(vector<int> vecVaribales, vector<int> used)
{
	set<tokens> finalSet;
	for (vector<int>::const_iterator it = vecVaribales.begin(); it != vecVaribales.end(); ++it) 
	{		
		int iCurrentVar = *it;
		
		if (isTerminal(iCurrentVar)) 
		{
			//cout << "terminal found: " << iCurrentVar << endl;
			finalSet.insert((tokens)iCurrentVar);			
			break;
		}

		if (contains(used, iCurrentVar))  
		{
			continue;
		}
		vector< vector<int> > vecRules = getRules((nonterminal)iCurrentVar);
				
		//cout << "nonterminal found: " << iCurrentVar << endl;
		

		for (vector< vector<int> >::const_iterator it2 = vecRules.begin(); it2 != vecRules.end(); ++it2)
		{
		
			//cout << "recursive call" << endl;
			//printVector(*it2);
			
			set<tokens> tmpSet = getFirst(*it2, used);
			
			
			finalSet.insert(tmpSet.begin(), tmpSet.end());
			used.push_back(iCurrentVar);
			//if ((*it2)[0] != LItems || (*it2)[0] != SItems || (*it2)[0] != MItems)
			//{
			//	cout << "found non-epsilon character: " << (*it2)[0];
			//	break;
			//}
		}
		break;
	}

	return finalSet;
}


/**
 * computes first for all nonterminal (see nonterminal enum in grammar.h)
 * calls print_first when finished
 */
void compute_first()
{
	vector< set<tokens> > vec4Print;
	
	for (int i = 0; i < NONTERMINAL_ENUM_SIZE; ++i) {
		vector<int> vecTmp;
		vecTmp.push_back(i);
		vector<int> used;
		//cout << " i is " << i << endl;
		set<tokens> setTmp = getFirst(vecTmp, used);
		
		vec4Print.push_back(setTmp);
	}
    
    print_first(vec4Print);
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

