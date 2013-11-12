#ifndef SCANNER_H
#define SCANNER_H

#include <stdio.h>
#include <stdbool.h>
#include "openfile.h"

typedef enum{
    START,
	FINISH,
	SCANEOF,
    INT,
    REAL,
    STRING,
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
	IF,
	THEN,
	WHILE,
	ENDWHILE,
	ELSE,
	ENDIF,
	COMMA,
	QUOTE,
	PLUSOP,
	MINUSOP,
	MULTOP,
	DIVOP,
	EXPOP,
	NOT,
	AND,
	OR,
	LTSIGN,
	LTESIGN,
	GTSIGN,
	GTESIGN,
	EQUIVSIGN,
	NOTEQSIGN,
    ERROR
} token_number;


typedef struct{
	int number;
	char type[20];
	char actual[32];
}token;

char linebuff[250];
int linenum;

token getToken(fileStruct *);
token process_alpha(char,fileStruct *);
token process_num(char,fileStruct *);
token process_symbol(char,fileStruct *);

char fpeek(FILE * f);

#endif
