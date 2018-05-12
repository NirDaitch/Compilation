%{

/* Declarations section */
#include <stdio.h>
void showToken(char *);
void showError();
%}

%option yylineno
%option noyywrap


digit   		([0-9])
letter  		([a-zA-Z])
whitespace		([\t\n \x0D\x0A])
endofline       (\x0D|\x0D\x0A|\x0A)


%%


void 									showToken("VOID");
int 									showToken("INT");
byte 									showToken("BYTE");
b 										showToken("B");
bool 									showToken("BOOL");
and 									showToken("AND");
or 										showToken("OR");
not 									showToken("NOT");
true 									showToken("TRUE");
false 									showToken("FALSE");
return 									showToken("RETURN");
if 										showToken("IF");
else 									showToken("ELSE");
while 									showToken("WHILE");
break 									showToken("BREAK");
\; 										showToken("SC");
\, 										showToken("COMMA");
\( 										showToken("LPAREN");
\) 										showToken("RPAREN");
\{ 										showToken("LBRACE");
\} 										showToken("RBRACE");
\[ 										showToken("LBRACK");
\] 										showToken("RBRACK");
\= 										showToken("ASSIGN");
			
(==|!=|<|>|<=|>=) 						showToken("RELOP");
			
(\+|-|\*|\/) 							showToken("BINOP");
([a-zA-Z][a-zA-Z0-9]*) 					showToken("ID");
			
(0|[1-9][0-9]*) 						showToken("NUM");
\"([^\n\r\"\\]|\\[rnt"\\])+\" 			showToken("STRING");

{whitespace}                     ;

(\/\/[^\r\n]*[\r|\n|\r\n]?)			;



.		showError();exit(0);

%%

void showToken(char * name)
{
	
        /* printf("Lex found a %s, the lexeme is %s and its length is %d\n", name, yytext, yyleng); */
		printf("%d %s %s\n", yylineno, name, yytext);
}

void showError() {
	printf("Error %s\n", yytext);
}