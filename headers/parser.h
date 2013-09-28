#ifndef PARSER_H_
#define PARSER_H_

#include "scanner.h"

typedef struct token;

int parser(token * );
int program(token *);
int statement_list(token *);
int statement(token *);
int id_list(token *);

#endif /*PARSER_H_*/
