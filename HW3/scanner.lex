%{

/* Declarations section */


#include <stdlib.h>
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


void 									{yylval.name = string("void"); return VOID;};
int 									{yylval.name = string("int"); return INT;};
byte 									{yylval.name = string("byte"); return BYTE;};
b 										{yylval.name = string("b"); return B;};
bool 									{yylval.name = string("bool"); return BOOL;};
and 									{yylval.name = string("and"); return AND;};
or 										{yylval.name = string("or"); return OR;};
not 									{yylval.name = string("not"); return NOT;};
true 									{yylval.name = string("true"); return TRUE;};
false 									{yylval.name = string("false"); return FALSE;};
return 									{yylval.name = string("return"); return RETURN;};								
if 										{yylval.name = string("if"); return IF;};
else 									{yylval.name = string("else"); return ELSE;};
while 									{yylval.name = string("while"); return WHILE;};
break 									{yylval.name = string("break"); return BREAK;};
\; 										{yylval.name = string("sc"); return SC;};
\, 										{yylval.name = string("comma"); return COMMA;};
\( 										{yylval.name = string("lparen"); return LPAREN;};
\) 										{yylval.name = string("rparen"); return RPAREN;};
\{ 										{yylval.name = string("lbrace"); return LBRACE;};
\} 										{yylval.name = string("rbrace"); return RBRACE;};
\[ 										{yylval.name = string("lbrack"); return LBRACK;};
\] 										{yylval.name = string("rbrack"); return RBRACK;};
\= 										{yylval.name = string("assign"); return ASSIGN;};
										
(==|!=) 								{yylval.name = string("relop_2"); return RELOP_2;};
(<|>|<=|>=) 							{yylval.name = string("relop_1"); return RELOP_1;};
										
(\*|\/) 								{yylval.name = string("binop_1"); return BINOP_1;};
(\+|-) 									{yylval.name = string("binop_2"); return BINOP_2;};
([a-zA-Z][a-zA-Z0-9]*) 					{yylval.name = string("id"); return ID;};
										
(0|[1-9][0-9]*) 						{yylval.name = string("num"); return NUM;};
\"([^\n\r\"\\]|\\[rnt"\\])+\" 			{yylval.name = string("string"); return STRING;};

{whitespace}                     ;

(\/\/[^\r\n]*[\r|\n|\r\n]?)			;



.		showError();exit(0);

%%

void showError() {
	printf("Error %s\n", yytext);
}