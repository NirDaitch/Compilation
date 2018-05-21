%{

/* Declarations section */


#include <stdlib.h>
#include <stdio.h>
#include <string>
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


void 									{yylval.type = Type_VOID;		return VOID;};
int 									{yylval.type = Type_INT;		return INT;};
byte 									{yylval.type = Type_BYTE;		return BYTE;};
b 										{								return B;};
bool 									{yylval.type = Type_BOOL;		return BOOL;};
and 									{								return AND;};
or 										{								return OR;};
not 									{								return NOT;};
true 									{yylval.type = Type_BOOL;		return TRUE;};
false 									{yylval.type = Type_BOOL;		return FALSE;};
return 									{								return RETURN;};								
if 										{								return IF;};
else 									{								return ELSE;};
while 									{								return WHILE;};
break 									{								return BREAK;};
\; 										{								return SC;};
\, 										{								return COMMA;};
\( 										{								return LPAREN;};
\) 										{								return RPAREN;};
\{ 										{								return LBRACE;};
\} 										{								return RBRACE;};
\[ 										{								return LBRACK;};
\] 										{								return RBRACK;};
\= 										{								return ASSIGN;};
																
(==|!=) 								{					 			return RELOP_2;};
(<|>|<=|>=) 							{					 			return RELOP_1;};
																		
(\*|\/) 								{					 			return BINOP_1;};
(\+|-) 									{					 			return BINOP_2;};
([a-zA-Z][a-zA-Z0-9]*) 					{yylval.name = string(yytext); 	return ID;};
										
(0|[1-9][0-9]*) 						{yylval.value=atoi(yytext); yylval.type = Type_INT; return NUM;};
\"([^\n\r\"\\]|\\[rnt"\\])+\" 			{yylval.type = Type_STRING; 	return STRING;};

{whitespace}                     ;

(\/\/[^\r\n]*[\r|\n|\r\n]?)			;



.		showError();exit(0);

%%

void showError() {
	printf("Error %s\n", yytext);
}