%{

/* Declarations section */
#include <stdio.h>
void showToken(char *);

%}

%option yylineno
%option noyywrap


digit   		([0-9])
letter  		([a-zA-Z])
whitespace		([\t\n ])
endofline       (\x0D|\x0D\x0A|\x0A)


%%


(---)		showToken("STARTSTRUCT");
(\.\.\.)		showToken("ENDSTRUCT");

(\[)			showToken("LLIST");
(\])			showToken("RLIST");

(\{)			showToken("LDICT");
(\})			showToken("RDICT");

(:)			showToken("KEY");
(\?)			showToken("COMPLEXKEY");

(-)			showToken("ITEM");

(,)			showToken("COMMA");

(!!{letter}+)			showToken("TYPE");

(#.*{endofline})			showToken("COMMENT");

(true)			showToken("TRUE");
(false)			showToken("FALSE");


{digit}+          			showToken("number");
{letter}+					showToken("word");
{letter}+@{letter}+\.com		showToken("email address");
{whitespace}                     ;
.		printf("Lex doesn't know what that is!\n");

%%

void showToken(char * name)
{
	
        /* printf("Lex found a %s, the lexeme is %s and its length is %d\n", name, yytext, yyleng); */
		printf("%d %s %s\n", yylineno, name, yytext);
}