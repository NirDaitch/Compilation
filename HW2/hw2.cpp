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

bool isNullable(nonterminal nt)
{
	if (nt == SItems || nt == LItems || nt == MItems)
	{
		return true;
	}
	return false;
}


bool isTerminal(int var)
{
	return var >= 11;
}

bool contains(vector<int> vec, int var)
{
	return find(vec.begin(), vec.end(), var) != vec.end();
}
bool contains2(vector<int> vec, nonterminal var)
{
    return find(vec.begin(), vec.end(), var) != vec.end();
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

vector< grammar_rule > getContainingRules(nonterminal nt) {
    vector< grammar_rule > rules;
    for (int i = 0; i < grammar.size() ; ++i) {
        grammar_rule tmp=grammar[i];
        if (contains2(tmp.rhs,nt))
        {
            rules.push_back(tmp);

        }
    }



    return rules;
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


set<tokens> getFollow_init(nonterminal vecVaribale)
{
	set<tokens> finalSet;

	if (vecVaribale == S)
	{
		finalSet.insert((tokens)EF);
	}
	 return finalSet;
}

int indexOf(vector<int> vec, int var)
{
	int i = 0;
	for (vector<int>::const_iterator it = vec.begin(); it != vec.end(); ++it)
	{
		if (*it == var)
		{
			return i;
		}
		i++;
	}
	return -1;
}

set<tokens> getFollow(nonterminal nt,vector<int> used)
{
	set<tokens> finalSet;
	vector< grammar_rule >  vecRules = getContainingRules(nt);
	//cout<<"current nt = " << nt<<endl;
	for (vector< grammar_rule >::const_iterator it = vecRules.begin(); it != vecRules.end(); ++it)
	{
		grammar_rule currentRule = *it;
		vector<int> vecRHSCurrentRule = currentRule.rhs;
		int index = indexOf(vecRHSCurrentRule, nt);
		if (index == -1)
		{
			// TODO: delete tyhis before submitting-
			cout << "getContainingRules has brought inccorect containing rule";
			continue;
		}
		if (index +1 >= vecRHSCurrentRule.size())
		{
			/// if nt is the last nonterminal in the rule
            nonterminal Y2 = currentRule.lhs;
            //cout << "Y is " << (int)Y << endl;
            if(contains2(used,Y2) )
            {
                continue;
            }
            used.push_back(Y2);
            set<tokens> setTmp3 = getFollow(Y2,used);
            finalSet.insert(setTmp3.begin(), setTmp3.end());
			continue;
		}




		int beta = vecRHSCurrentRule[index + 1];
		//cout << "beta is " << beta << endl;
		vector<int> vecTmp;
		vecTmp.push_back(beta);
		vector<int> used2;
		set<tokens> setTmp = getFirst(vecTmp, used2);
		finalSet.insert(setTmp.begin(), setTmp.end());

		if (isNullable((nonterminal)beta))
		{
			nonterminal Y = currentRule.lhs;
			//cout << "Y is " << (int)Y << endl;
            if(contains2(used,Y) )
            {
                continue;
            }
            used.push_back(Y);
			set<tokens> setTmp2 = getFollow(Y,used);
			finalSet.insert(setTmp2.begin(), setTmp2.end());
		}

	}
	return finalSet;
}
 /**
 * computes follow for all nonterminal (see nonterminal enum in grammar.h)
 * calls print_follow when finished
 */
void compute_follow()
{
	cout << "compute_follow()" << endl;
	//vector< grammar_rule >  vecVaribales = getContainingRules(Collection);
	//
	//for (vector< grammar_rule >::const_iterator it = vecVaribales.begin(); it != vecVaribales.end(); ++it)
	//{
	//	printVector((*it).rhs);
	//}

	//set<tokens> setTmp = getFollow(Collection);
	//for (set<tokens>::const_iterator it = setTmp.begin(); it != setTmp.end(); ++it)
	//{
	//	cout << "token: " << *it << endl;
	//}

	vector< set<tokens> > vec4Print;
	for (int i = 0; i < NONTERMINAL_ENUM_SIZE; ++i) {
        vector<int> used;
		set<tokens> setTmp = getFollow_init((nonterminal)i);
		set<tokens> setTmp2 = getFollow((nonterminal)i,used);
		setTmp.insert(setTmp2.begin(), setTmp2.end());
		vec4Print.push_back(setTmp);
	}








     //vector<int> used;
//     set<tokens> setTmp = getFollow_init(List);
//     set<tokens> setTmp2 = getFollow( (nonterminal)List,used);
//     setTmp.insert(setTmp2.begin(), setTmp2.end());
//    // vec4Print.push_back(setTmp);
//
//     cout << "start set" << endl;
//     for (set<tokens>::const_iterator XX = setTmp2.begin(); XX != setTmp2.end(); ++XX)
//     {
//         cout << *XX << endl;
//     }
//     cout << setTmp2.size();
//     cout << "end set" << endl;

    print_follow(vec4Print);

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

