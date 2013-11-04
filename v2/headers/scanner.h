#ifndef SCANNER_H
#define SCANNER_H

#include <stdio.h>
#include <stdbool.h>
#include "openfile.h"

typedef enum{START,
	FINISH,
	SCANEOF,
	INTLIT,
	REALLIT,
	STRINGLIT,
	SEMICOLON,
	INPUT,
	OUTPUT,
	LPAREN,
	RPAREN,
	ID,
	ASSIGN,
	IFSTMT,
	THEN,
	WHILESTMT,
	ENDWHILE,
	ELSESTMT,
	ENDIF,
	COMMA,
	QUOTE,
	PLUSOP,
	MINUSOP,
	MULTOP,
	DIVOP,
	EXPOP,
	NOTOP,
	ANDOP,
	OROP,
	LTSIGN,
	LTESIGN,
	GTSIGN,
	GTESIGN,
	EQUIVSIGN,
	NOTEQSIGN
} token_number;

typedef struct{
	int number;
	char type[20];
	char actual[30];
}token;

char linebuff[250];
int linenum;

token getToken(fileStruct *);
token process_alpha(char,fileStruct *);
token process_num(char,fileStruct *);
token process_symbol(char,fileStruct *);



#endif
