%{

/* Declarations section */


#include <stdlib.h>
#include "definitions.h"
#include "parser.tab.hpp"
#include "output.hpp"
using namespace output;

void showError();
%}

%option yylineno
%option noyywrap


digit   		([0-9])
letter  		([a-zA-Z])
whitespace		([\t\n \x0D\x0A])


%%


void 									return VOID;
int 									return INT;
byte 									return BYTE;
b 										return B;
bool 									return BOOL;
and 									return AND;
or 										return OR;
not 									return NOT;
true 									return TRUE;
false 									return FALSE;
return 									{yylval.id = 666; return RETURN;}	;								
if 										return IF;
else 									return ELSE;
while 									return WHILE;
break 									return BREAK;
\; 										return SC;
\, 										return COMMA;
\( 										return LPAREN;
\) 										return RPAREN;
\{ 										return LBRACE;
\} 										return RBRACE;
\[ 										return LBRACK;
\] 										return RBRACK;
\= 										return ASSIGN;
			
(==|!=) 								return RELOP_2;
(<|>|<=|>=) 							return RELOP_1;
			
(\*|\/) 								return BINOP_1;
(\+|-) 									return BINOP_2;
([a-zA-Z][a-zA-Z0-9]*) 					return ID;
			
(0|[1-9][0-9]*) 						return NUM;
\"([^\n\r\"\\]|\\[rnt"\\])+\" 			return STRING;

{whitespace}                     ;

(\/\/[^\r\n]*[\r|\n|\r\n]?)			;



.		showError();exit(0);

%%

void showError() {
	printf("Error %s\n", yytext);
}