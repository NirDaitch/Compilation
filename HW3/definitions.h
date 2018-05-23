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
    Type_BOOL,
	__Type_INVALID
} Type;

class EXP_ATTRIBUTE {
	public:
	std::string name;
    Type type;
    int num_value;
	
	
	EXP_ATTRIBUTE() 
	{
		this->name = "";		
		this->num_value=-1;
	};
	~EXP_ATTRIBUTE(){};
};

class T_Symbol {
	public:
	std::string name;
    Type type;
	int offset;
	int Type_ARRAY_SIZE;
	
	T_Symbol() 
	{
		this->name = "";
	};
	
	T_Symbol (const T_Symbol& s)
	{
		this->name = s.name;
		this->type = s.type;
		this->offset = s.offset;
		this->Type_ARRAY_SIZE = -1;
	};
	
	~T_Symbol(){};
};


class SymbolTable {
	public:
	std::list<T_Symbol> lstSymbols;

	void addSymbol(const T_Symbol& symbol)
	{
		cout << "name: " << symbol.name << endl;
		cout << "type: " << symbol.type << endl;
		
		lstSymbols.push_back(symbol);
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