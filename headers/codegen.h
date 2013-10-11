#ifndef CODEGEN_H_
#define CODEGEN_H_


#include "parser.h"

typedef struct 
{
	char name[128];
	int value;
	
} var_list;

var_list list[100];

void codegen(token *);
token* next(token *);
int id_search(token *);
void code_begin(void);

#endif /*PARSER_H_*/

