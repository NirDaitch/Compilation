#ifndef H_DEFINITIONS
#define H_DEFINITIONS

#include <stdlib.h>
#include <string>
#include <list>

#define YYSTYPE EXP_ATTRIBUTE

using namespace std;

typedef enum {
    T_INT,
    T_BOOL
} Type;

typedef struct {
	int id;
    Type type;
    
} EXP_ATTRIBUTE;





#endif