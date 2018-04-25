%{

/* Declarations section */
#include "tokens.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void showToken(int);
void showTokenInt(char *);
void showError();
void handleString1(char *);
void initHandleString();
void handleString2(char *);
void determineEscapeOrEOF();
void pushToString(char*);
void initStr666(char *,int);
char cCurrentString[1050];


%}

%option yylineno
%option noyywrap

%x STRING
%x COMMENT



digit   		([0-9])
letter  		([a-zA-Z])
whitespace		([\t\n \x0D\x0A])

plusorminus 	([+-])
integer 		({plusorminus}?{digit}+)
hexaNum			(0x[0-9a-fA-F]+)
octalNum		(0o[0-7]+)

decimal1		({integer}\.?{digit}*)
decimal2		({plusorminus}?\.{digit}+)
decimal         ({decimal1}|{decimal2})
exp				(e{integer})


validEscape 	(\\\\|\\"|\\[abefnrtv0]|\\x[a-fA-F][a-fA-F])


validEscape2 	(\\\\|\\"|\\[abefnrtv0]|\\x[a-fA-F][a-fA-F])



%%


(---)			showToken(STARTSTRUCT);
(\.\.\.)		showToken(ENDSTRUCT);

(\[)			showToken(LLIST);
(\])			showToken(RLIST);

(\{)			showToken(LDICT);
(\})			showToken(RDICT);

(:)			showToken(KEY);
(\?)			showToken(COMPLEXKEY);

(-)			showToken(ITEM);

(,)			showToken(COMMA);

(!!{letter}+)			showToken(TYPE);



\#                                          BEGIN(COMMENT); initHandleString(); pushToString(yytext);
<COMMENT>[^\x0D\x0A]              pushToString(yytext);
<COMMENT>^(\x0D\x0A)              pushToString(yytext);
<COMMENT>[\x0D\x0A]               BEGIN(INITIAL);
<COMMENT>\x0D\x0A              BEGIN(INITIAL);
<COMMENT><<EOF>>                        BEGIN(INITIAL);




(true)			showToken(TRUE);
(false)			showToken(FALSE);



{integer}   			showTokenInt("INTEGER");		
{hexaNum}				showTokenInt("INTEGER");
{octalNum}				showTokenInt("oct");

({decimal}|{decimal}e[+-]{integer}|\.inf|\.NaN)		showToken(REAL);


\'([\x20-\x26\x28-\x7E\x0D\x0A\x09]|\x0D\x0A)*\'	  handleString1("STRING");


\"\"                                printf("%d\n", STRING);

"\""								      BEGIN(STRING); initHandleString();
<STRING>[^\\\"]                  		  pushToString(yytext);
<STRING>(\\\")                   		  pushToString(yytext);
<STRING>(\\\\)	                 	      pushToString(yytext);
<STRING>(\\[^\"\\])                 	  pushToString(yytext);
<STRING><<EOF>>                           determineEscapeOrEOF();
<STRING>"\""                              handleString2("STRING"); BEGIN(INITIAL);


{letter}({letter}|{digit})*                       showToken(VAL);

\&({letter})+                       showToken(DECLARATION);

\*({letter})+                       showToken(DEREFERENCE);

\'[^\']*					printf("Error unclosed string\n");exit(0);


<<EOF>>                     showToken(EOF);exit(0);

{whitespace}                ;

.		showError();exit(0);

%%

void determineEscapeOrEOF()
{
	int i=0;
	int length=strlen(cCurrentString);
	char val, val2, val3, val4;
	
	for(;i<length-1;i++) {//check valid escapes without \xDD
		val=cCurrentString[i];
		val2=cCurrentString[i+1];
		
		if(val=='\\') {
			if( !(val2=='\\' || val2== '\"' || val2=='a' || val2=='b' || val2=='e' || val2=='f' ||val2=='n' || val2=='r' || val2=='t' || val2=='v' || val2=='0' || val2=='x') ) {
				printf("Error undefined escape sequence %c\n",val2);
				exit(0);
			}
			else {
				i++;
			}
		}
	}
	i=0;
	for(;i<length-3;i++) {//checking if there is \x in valid format - \xDD
		val=cCurrentString[i];
		val2=cCurrentString[i+1];
		val3=cCurrentString[i+2];
		val4=cCurrentString[i+3];
		if(val=='\\' && val2=='x') {
			if ( ( (val3>='0' && val3<='9') || (val3>='a' && val3<='f') || (val3>='A' && val3<='F') ) &&
			 ( (val4>='0' && val4<='9') || (val4>='a' && val4<='f') || (val4>='A' && val4<='F') ) )  
			{
				//printf("hurray! %c%c%c%c\n",val,val2,val3,val4);
			} 
			else {
				printf("Error undefined escape sequence %c\n",val2);
				exit(0);
			}
		}	
	}
	printf("Error unclosed string\n");
	exit(0);
}

void showToken(int name)
{
	
	if (name == COMMENT)
	{
		//printf("%d %s %s", yylineno, name, yytext);	
		return;
	} 
	
	printf("%d\n", name);	
}

void showTokenInt(char *name) {
	char *end;
	long ans=strtol(yytext,&end,0);
	char *tmp=name;
	if(strcmp(name,"oct")==0) {
		name="INTEGER";
		if(yyleng>1) {
			char str[yyleng+1];
			strcpy(str,yytext);
			str[1]='0';
			ans=strtol(&(str[1]),&end,0);
		}
	}
	printf("%d\n", INTEGER);
	
}

void handleString1(char *name) {
	char str[yyleng+1]; 
	//trimming starting and trailing apostrophe
	yytext++;
	strcpy(str,yytext);
	str[yyleng-2]='\0';
	printf("%d\n", STRING);
}

void initHandleString()
{
	
	int i = 0;
    while(cCurrentString[i] != '\0') {
        cCurrentString[i] = '\0';
        i++;
    }
}

void pushToString(char* sText)
{
	strcat(cCurrentString, sText);
}

void handleString2(char *name) 
{
	char val;
	char val2;
	char val3;
	char val4;
	int i=0;
	int length=strlen(cCurrentString);
	for(;i<length;i++) {//check valid chars
		val=cCurrentString[i];
		if( (val>='\x20' && val<='\x7E' ) || (val=='\x09') || (val=='\x0A') || (val=='\x0D')){
			//ok
		}
		else {
			showError();exit(0);
		}

	}
	i=0;
	for(;i<length-1;i++) {//check valid escapes without \xDD
		val=cCurrentString[i];
		val2=cCurrentString[i+1];
		
		if(val=='\\') {
			if( !(val2=='\\' || val2== '\"' || val2=='a' || val2=='b' || val2=='e' || val2=='f' ||val2=='n' || val2=='r' || val2=='t' || val2=='v' || val2=='0' || val2=='x') ) {
				printf("Error undefined escape sequence %c\n",val2);
				exit(0);
			}
			else {
				i++;
			}
		}
	}
	i=0;
	for(;i<length-3;i++) {//checking if there is \x in valid format - \xDD
		val=cCurrentString[i];
		val2=cCurrentString[i+1];
		val3=cCurrentString[i+2];
		val4=cCurrentString[i+3];
		if(val=='\\' && val2=='x') {
			if ( ( (val3>='0' && val3<='9') || (val3>='a' && val3<='f') || (val3>='A' && val3<='F') ) &&
			 ( (val4>='0' && val4<='9') || (val4>='a' && val4<='f') || (val4>='A' && val4<='F') ) )  
			{
				//printf("hurray! %c%c%c%c\n",val,val2,val3,val4);
			} 
			else {
				printf("Error undefined escape sequence %c\n",val2);
				exit(0);
			}
		}	
	}
	//here the string is valid, now we need to replace the characters	
	char str[1060];
	initStr666(str,1060);
	int j=0;
	char *tmp=cCurrentString;
	if(*(tmp+1)=='\0') {//string is of size 1, replace cr,lf, with space and finish (no other replacements possible)
		if(*tmp=='\x0D' || *tmp=='\x0A') {
			str[0]=' ';
		}
	}
	while(*tmp!='\0') {//string is at least of size 2
		if(*tmp=='\x0D' || *tmp=='\x0A') {//handle CR,LF,CRLF
			//printf("found CR or LF);
			str[j]=' ';
			if(*tmp=='\x0D' && *(tmp+1)=='\x0A') {
				//CRLF
				
				tmp++;
			}
			tmp++;
			j++;
			continue;
		}
		if(*tmp!='\\') {
			str[j]=*tmp;
			j++;
			tmp++;
			continue;
		}
		else {
			tmp++;
			if(*tmp=='\\') {str[j]='\\';j++;tmp++;}
			else if (*tmp== '\"'){ str[j]='\"';j++;tmp++;}
			else if (*tmp== 'a') { str[j]='\a';j++;tmp++;}
			else if (*tmp== 'b') { str[j]='\b';j++;tmp++;}
			else if (*tmp== 'e') { str[j]='\e';j++;tmp++;}
			else if (*tmp== 'f') { str[j]='\f';j++;tmp++;}
			else if (*tmp== 'n') { str[j]='\n';j++;tmp++;}
			else if (*tmp== 'r') { str[j]='\r';j++;tmp++;}
			else if (*tmp== 't') { str[j]='\t';j++;tmp++;}
			else if (*tmp== 'v') { str[j]='\v';j++;tmp++;}
			else if (*tmp== '0') { str[j]='\0';j++;tmp++; break;}
			else if (*tmp== 'x') {
				val3=*(tmp+1);
				val4=*(tmp+2);
				//at this point, we encountered \xDD where DD are valid characters. 
				//we need to write \xDD into str[j]
				//str[j]='\xval3val4'; TODO:figure how we can swap val3val4 for their characters and insert it into str -----> '\xval3val4'

				//FUCK ME

				char tmpSTR[5];
				initStr666(tmpSTR, 5);
				char sZeroX[] = "0x";
				strcat(tmpSTR, sZeroX);
				tmpSTR[2]=val3;
				tmpSTR[3]=val4;
				
				//printf("tmpSTR is: %s\n", tmpSTR);
				

				char *end;
				long ans=strtol(tmpSTR ,&end, 0);
				///printf("ans is: %ld \n", ans);
				char cCharFromHexa = (char) ans;
				///printf("cCharFromHexa is: %c \n", cCharFromHexa);
				str[j] = cCharFromHexa;
				
				j++;
				tmp++;
				tmp++;
				tmp++;
				
				//and last TODO from faq-unrelated to this section- if string has invalid escape and also string didn't close (got EOF), print invalid escape instead of unclosed string.
				//meaning we have to make a new function and call it instead of instantly writing error unclosed string. this func will duplicate the code checking for valid escape.
				//if not valid, print invalid escape. else print unclosed string.
			}

			

		}
	}	
	printf("%d\n", STRING);

}

void showError() {
	printf("Error %s\n", yytext);
}
void initStr666(char *str,int len) {
	int i=0;
	for(;i<len;i++) {
		str[i]='\0';
	}	
}