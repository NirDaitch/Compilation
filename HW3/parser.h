#ifndef H_PARSER
#define H_PARSER

#include <list>
#include <string>
#include <stdlib.h>

#define YYSTYPE EXPATTRIBUTE

using namespace std;

typedef enum {
    T_INT,
    T_BOOL
} Type;

typedef struct {
	int id;
    Type type;
    
} EXPATTRIBUTE;





#endif