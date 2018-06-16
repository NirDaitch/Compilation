#ifndef H_DEFINITIONS
#define H_DEFINITIONS

#include <stdlib.h>
#include <iostream>
#include <string>
#include <list>
#include <vector>

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
	int resultReg;
    bool is_array;
	
	std::vector<int> trueList;
	std::vector<int> falseList;
	std::vector<int> nextList;
	
	
	EXP_ATTRIBUTE() 
	{
		this->name = "";		
		this->num_value=-1;
		this->resultReg=-1;
		this->is_array = false;
		this->trueList = std::vector<int>();
		this->falseList = std::vector<int>();
		this->nextList = std::vector<int>();
	};
	~EXP_ATTRIBUTE(){};
};


class T_Symbol {
	public:
	std::string name;
    Type type;
	int offset;
	int Type_ARRAY_SIZE;
	
	//// THIS LANGUAGE SUCKS!! ////
	//// you can't use dynamic casting if it's not a pointer,////
	//// and i really don't feal like changing the whole program ////
	bool isFunction;
	std::list<T_Symbol> lstArgs;
	
	T_Symbol() 
	{
		this->name = "";
		this->Type_ARRAY_SIZE = -1;
		this->isFunction = false;
		this->type = (Type) -1;
	};
	
	T_Symbol (const T_Symbol& s)
	{
		this->name = s.name;
		this->type = s.type;
		this->offset = s.offset;
		this->Type_ARRAY_SIZE = s.Type_ARRAY_SIZE;
		this->isFunction = s.isFunction;
		this->lstArgs = s.lstArgs;
	};
	
	~T_Symbol(){};
};

//class Function
//{
//	public:
//	std::string name;
//	std::list<T_Symbol> lstArgs;
//	Type returnType;
//	
//	Function (const Function& f)
//	{
//		this->name = f.name;
//		this->returnType = f.returnType;
//		this->lstArgs = f.lstArgs;
//	};
//	
//	~Function(){};
//};

class SymbolTable {
	public:
	std::list<T_Symbol> lstSymbols;

	void addSymbol(const T_Symbol& symbol)
	{
		//cout << "name: " << symbol.name << endl;
		//cout << "type: " << symbol.type << endl;
		
		
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
//typedef map< std::string, Function > FunctionTable;


#endif