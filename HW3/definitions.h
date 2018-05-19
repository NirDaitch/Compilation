#ifndef H_DEFINITIONS
#define H_DEFINITIONS

#include <stdlib.h>
#include <iostream>
#include <string>
#include <list>

#define YYSTYPE EXP_ATTRIBUTE

using namespace std;

typedef enum {
    Type_INT,
    Type_BYTE,
    Type_STRING,
    Type_VOID,
    Type_B,
    Type_BOOL
} Type;

class EXP_ATTRIBUTE {
	public:
	std::string name;
    Type type;
	
	int Type_ARRAY_SIZE;
	
	EXP_ATTRIBUTE() 
	{
		this->name = "";
		this->Type_ARRAY_SIZE = -1;
	};
	~EXP_ATTRIBUTE(){};
};

class T_Symbol {
	public:
	std::string name;
    Type type;
	int offset;
	
	T_Symbol() 
	{
		this->name = "";
	};
	
	T_Symbol (const T_Symbol& s)
	{
		this->name = s.name;
		this->type = s.type;
		this->offset = s.offset;
	};
	
	~T_Symbol(){};
};


class SymbolTable {
	public:
	std::list<T_Symbol> lstSymbolTable;

	void addSymbol(const T_Symbol& symbol)
	{
		//cout << "name: " << symbol.name << endl;
		//cout << "type: " << symbol.type << endl;
		
		lstSymbolTable.push_back(symbol);
	}
	
	SymbolTable() 
	{
		
	};
	~SymbolTable()
	{	
	};
};


typedef std::list<SymbolTable> ScopeStack;



#endif