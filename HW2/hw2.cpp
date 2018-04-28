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
		
		if (isTerminal(iCurrentVar) ) 
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
		
		////////////
		//for (vector< vector<int> >::const_iterator IT_1 = vecRules.begin(); IT_1 != vecRules.end(); ++IT_1)
		//{
		//	cout << "rule is: " << endl;
		//	printVector(*IT_1);
		//	cout << endl;
		//}
		//
		//////////
		

		
		for (vector< vector<int> >::const_iterator it2 = vecRules.begin(); it2 != vecRules.end(); ++it2)
		{
		
			//cout << "recursive call" << endl;
			//printVector(*it2);
			
			set<tokens> tmpSet = getFirst(*it2, used);
			
			/////////////
			//
			//for (std::set<tokens>::const_iterator IT_2 = tmpSet.begin(); IT_2 != tmpSet.end(); ++IT_2) {
			//	cout << "token is: " << *IT_2 << endl;
			//	
			//}
			//
			/////////////
			
			finalSet.insert(tmpSet.begin(), tmpSet.end());
			used.push_back(iCurrentVar);
			//if ((*it2)[0] != LItems || (*it2)[0] != SItems || (*it2)[0] != MItems)
			//{
			//	cout << "found non-epsilon character: " << (*it2)[0];
			//	break;
			//}
		}
	}

	return finalSet;
}


/**
 * computes first for all nonterminal (see nonterminal enum in grammar.h)
 * calls print_first when finished
 */
void compute_first()
{
	vector<int> vecTmp;
	vector<int> used;
	vecTmp.push_back((int)S);
    set<tokens> mySet = getFirst(vecTmp, used);
	for (std::set<tokens>::const_iterator IT_2 = mySet.begin(); IT_2 != mySet.end(); ++IT_2) {
		cout << "token is: " << *IT_2 << endl;
		
	}
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

