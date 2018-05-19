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





#endif