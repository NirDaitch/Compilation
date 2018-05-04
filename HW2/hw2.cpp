#include "hw2.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

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
	//cout << "start printVector" << endl;
	for (vector<int>::const_iterator XX = vec.begin(); XX != vec.end(); ++XX)
	{
		cout << *XX << " ";
	}
	//cout << "end printVector" << endl;
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
	set<tokens> finalSet = getFollow_init(nt);
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


set<tokens> getSelect(grammar_rule rule)
{
	vector<int> vRhs = rule.rhs;
	vector<int> usedFirst;
	set<tokens> setFirst;
	if (vRhs.size() != 0)
	{
		setFirst = getFirst(vRhs, usedFirst);
		if (vRhs.size() == 1 && !isTerminal(vRhs[0]) && isNullable((nonterminal)vRhs[0])) 		
		{
			vector<int> used;
			set<tokens> setFollow = getFollow((nonterminal)vRhs[0], used);
			setFirst.insert(setFollow.begin(), setFollow.end());
		}
	}
	else
	{
		vector<int> used;
		set<tokens> setFollow = getFollow(rule.lhs, used);
		setFirst.insert(setFollow.begin(), setFollow.end());
	}

	return setFirst;
}
 /**
 * computes follow for all nonterminal (see nonterminal enum in grammar.h)
 * calls print_follow when finished
 */
void compute_follow()
{

	vector< set<tokens> > vec4Print;
	for (int i = 0; i < NONTERMINAL_ENUM_SIZE; ++i) {
        vector<int> used;
		set<tokens> setTmp = getFollow((nonterminal)i,used);
		vec4Print.push_back(setTmp);
	}

    print_follow(vec4Print);

}

/**
 * computes select for all grammar rules (see grammar global variable in grammar.h)
 * calls print_select when finished
 */
void compute_select()
{
	vector< set<tokens> > vec4Print;
    for (int i = 0; i < grammar.size() ; ++i) {
		//cout << "running on rule" << i << endl;
        grammar_rule rule = grammar[i];
        set<tokens> setTmp = getSelect(rule);
		vec4Print.push_back(setTmp);
    }
	
	print_select(vec4Print);
}


//bool match(nonterminal X, tokens t, map< nonterminal, map<tokens, int> >& mpM)
//{
//	map<tokens, int> mpCurrentNonTerminal = mpM[X];
//	return mpCurrentNonTerminal.find(t) != mpCurrentNonTerminal.end();
//}

bool match(tokens a, tokens t, map< nonterminal, map<tokens, int> >& mpM)
{
	bool bMatch = false;
	for (int i = 0; i < NONTERMINAL_ENUM_SIZE; ++i)
	{
		map<tokens, int> mpCurrentNonTerminal = mpM[(nonterminal)i];
		if (mpCurrentNonTerminal.find(t) != mpCurrentNonTerminal.end())
		{
			bMatch = true;
		}
	}
	return bMatch;
}

void putInMap(int rule, set<tokens> selectSet, nonterminal nt, map< nonterminal, map<tokens, int> >& mpM)
{
	map<tokens, int>& mpCurrentNonTerminal = mpM[nt];
	for (set<tokens>::iterator it = selectSet.begin(); it != selectSet.end(); ++it) 
	{
		tokens currentToken = *it;
		mpCurrentNonTerminal[currentToken] = rule;
	}

}
 
 
void printMap(map< nonterminal, map<tokens, int> > mpM)
{
	cout << "printing map" << endl;
	for (map< nonterminal, map<tokens, int> >::iterator it = mpM.begin(); it != mpM.end(); it++)
	{
		cout << "nonterminal is " << it->first << " ";
		map< tokens, int > currMap = it->second;
		for (map< tokens, int >::iterator it2 = currMap.begin(); it2 != currMap.end(); it2++)
		{
			cout << ((int)it2->first) << " -> " << it2->second;
			cout << " , ";
		}
		cout << endl;
	}
}
 
/**
 * implements an LL(1) parser for the grammar using yylex()
 */
void parser()
{


	vector< set<tokens> > vec4Print;
    for (int i = 0; i < grammar.size() ; ++i) {
        grammar_rule rule = grammar[i];
        set<tokens> setTmp = getSelect(rule);
		vec4Print.push_back(setTmp);
    }
	
	map< nonterminal, map<tokens, int> > mpM;
	
	for (int i = 0; i < grammar.size() ; ++i) 
	{
		putInMap(i, vec4Print[i], grammar[i].lhs, mpM);
	}

	vector<int> Q;
	Q.push_back(S);

	tokens currToken = (tokens) yylex();

	do
	{
		if (Q.size() == 0)
		{
			if (currToken == EF)
			{
				cout << "Success\n";
				return;
			}
			cout << "Syntax error\n";
			return;
		}
		else {
		    if (currToken == EF)
            {
                cout << "Syntax error\n";
                return;
            }
		}
		
		const int X = Q.back();
		if (isTerminal(X))
		{
			bool bMatch = match((tokens) X, currToken, mpM);
			if (!bMatch)
			{
				cout << "Syntax error\n";
				return;
			}
			Q.pop_back();
		}
		else
		{
		    ///predict
			Q.pop_back();
			nonterminal ntX = (nonterminal)X;
			map< tokens, int > currNTMap = mpM[ntX];
			int iRuleNum = currNTMap[currToken];
			cout << iRuleNum << "\n";
			vector<int> vecRHS = (grammar[iRuleNum]).rhs;
			for (vector<int>::reverse_iterator  it = vecRHS.rbegin(); it != vecRHS.rend(); ++it)
			{
				Q.push_back(*it);
			}
		}
		
		
		currToken = (tokens) yylex();
		
	} while(currToken != EF);

    cout << "Syntax error\n";
    return;
	
	//cout << "match(Structure, STARTSTRUCT)" << match(Structure, STARTSTRUCT, mpM) << endl;
	//cout << "match(Key, COMPLEXKEY)" << match(Key, COMPLEXKEY, mpM) << endl;
	//cout << "match(Map, LLIST)" << match(Map, LLIST, mpM) << endl;
	
	//printMap(mpM);
	

}

