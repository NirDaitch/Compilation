#include "tokens.h"
#include "grammar.h"
#include "hw2.h"
#include <iostream>

void print_token(tokens tok) {
    switch (tok) {
        case STARTSTRUCT: std::cout << "STARTSTRUCT"; break;
        case ENDSTRUCT: std::cout << "ENDSTRUCT"; break;
        case LLIST: std::cout << "LLIST"; break;
        case RLIST: std::cout << "RLIST"; break;
        case LDICT: std::cout << "LDICT"; break;
        case RDICT: std::cout << "RDICT"; break;
        case KEY: std::cout << "KEY"; break;
        case COMPLEXKEY: std::cout << "COMPLEXKEY"; break;
        case ITEM: std::cout << "ITEM"; break;
        case COMMA: std::cout << "COMMA"; break;
        case TYPE: std::cout << "TYPE"; break;
        case TRUE: std::cout << "TRUE"; break;
        case FALSE: std::cout << "FALSE"; break;
        case INTEGER: std::cout << "INTEGER"; break;
        case REAL: std::cout << "REAL"; break;
        case STRING: std::cout << "STRING"; break;
        case VAL: std::cout << "VAL"; break;
        case DECLARATION: std::cout << "DECLARATION"; break;
        case DEREFERENCE: std::cout << "DEREFERENCE"; break;
        case EF: std::cout << "EOF"; break;
    };
}

void print_nonterminal(nonterminal var) {
    switch (var) {
        case S: std::cout << "S"; break;
        case Structure: std::cout << "Structure"; break;
        case SItems: std::cout << "SItems"; break;
        case Collection: std::cout << "Collection"; break;
        case List: std::cout << "List"; break;
        case LItems: std::cout << "LItems"; break;
        case Map: std::cout << "Map"; break;
        case MItems: std::cout << "MItems"; break;
        case Key: std::cout << "Key"; break;
        case Item: std::cout << "Item"; break;
    };
}

void print_nullable(const std::vector<bool>& vec) {
    std::cout << "Nullable:" << std::endl;
    for (int i = 0; i < NONTERMINAL_ENUM_SIZE; ++i) {
        print_nonterminal((nonterminal) (i));
        std::cout << " = ";
        if (vec[i]) std::cout << "true"; else std::cout << "false";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void print_first(const std::vector< std::set<tokens> >& vec) {
    std::cout << "First:" << std::endl;
    for (int i = 0; i < NONTERMINAL_ENUM_SIZE; ++i) {
        print_nonterminal((nonterminal) (i));
        std::cout << " = { ";
        for (std::set<tokens>::const_iterator it = vec[i].begin(); it != vec[i].end(); ++it) {
            if (it != vec[i].begin()) std::cout << " , ";
            print_token(*it);
        }
        std::cout << " }";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void print_follow(const std::vector< std::set<tokens> >& vec) {
    std::cout << "Follow:" << std::endl;
    for (int i = 0; i < NONTERMINAL_ENUM_SIZE; ++i) {
        print_nonterminal((nonterminal) (i));
        std::cout << " = { ";
        for (std::set<tokens>::const_iterator it = vec[i].begin(); it != vec[i].end(); ++it) {
            if (it != vec[i].begin()) std::cout << " , ";
            print_token(*it);
        }
        std::cout << " }";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void print_select(const std::vector< std::set<tokens> >& vec) {
    std::cout << "Select:" << std::endl;
    for (int i = 0; i < grammar.size(); ++i) {
        grammar_rule gr = grammar[i];
        std::cout << "( ";
        print_nonterminal((nonterminal) gr.lhs);
        std::cout << " -> ";
        for (int j = 0; j < gr.rhs.size(); ++j) {
            if (j > 0) std::cout << " ";
            if (gr.rhs[j] >= NONTERMINAL_ENUM_SIZE)
                print_token((tokens) gr.rhs[j]);
            else
                print_nonterminal((nonterminal) gr.rhs[j]);
        }
        std::cout << " ) = { ";
        for (std::set<tokens>::const_iterator it = vec[i].begin(); it != vec[i].end(); ++it) {
            if (it != vec[i].begin()) std::cout << " , ";
            print_token(*it);
        }
        std::cout << " }";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


std::vector <grammar_rule> make_grammar() {
    std::vector <grammar_rule> res;

    res.push_back(grammar_rule(S, std::vector<int>(1, Structure)));
    res.push_back(grammar_rule(S, std::vector<int>(1, Collection)));

    int rule3[] = {STARTSTRUCT, SItems, ENDSTRUCT};
    res.push_back(grammar_rule(Structure, std::vector<int>(rule3, rule3 + 3)));

    int rule4[] = {Collection, SItems};
    res.push_back(grammar_rule(SItems, std::vector<int>(rule4, rule4 + 2)));
    res.push_back(grammar_rule(SItems, std::vector<int>()));

    res.push_back(grammar_rule(Collection, std::vector<int>(1, List)));
    res.push_back(grammar_rule(Collection, std::vector<int>(1, Map)));

    int rule8[] = {LLIST, LItems, RLIST};
    res.push_back(grammar_rule(List, std::vector<int>(rule8, rule8 + 3)));

    int rule9[] = {Item, COMMA, LItems};
    res.push_back(grammar_rule(LItems, std::vector<int>(rule9, rule9 + 3)));
    res.push_back(grammar_rule(LItems, std::vector<int>()));

    int rule11[] = {LDICT, MItems, RDICT};
    res.push_back(grammar_rule(Map, std::vector<int>(rule11, rule11 + 3)));

    int rule12[] = {Key, KEY, Item, COMMA, MItems};
    res.push_back(grammar_rule(MItems, std::vector<int>(rule12, rule12 + 5)));
    res.push_back(grammar_rule(MItems, std::vector<int>()));

    res.push_back(grammar_rule(Key, std::vector<int>(1, VAL)));
    int rule15[] = {COMPLEXKEY, Collection};
    res.push_back(grammar_rule(Key, std::vector<int>(rule15, rule15 + 2)));

    res.push_back(grammar_rule(Item, std::vector<int>(1, STRING)));
    res.push_back(grammar_rule(Item, std::vector<int>(1, INTEGER)));
    res.push_back(grammar_rule(Item, std::vector<int>(1, REAL)));
    res.push_back(grammar_rule(Item, std::vector<int>(1, Collection)));
    res.push_back(grammar_rule(Item, std::vector<int>(1, TRUE)));
    res.push_back(grammar_rule(Item, std::vector<int>(1, FALSE)));
    res.push_back(grammar_rule(Item, std::vector<int>(1, VAL)));

    return res;
}

std::vector <grammar_rule> grammar = make_grammar();
