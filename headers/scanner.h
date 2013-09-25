#ifndef SCANNER_H
#define SCANNER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 128

typedef struct {
    short int token_number;
    char token_type [16];
    char buffer [128];
} token;

/* Adding a linked list type */
typedef struct {
    token t;
    struct token_node * next;
} token_node;

typedef struct {
    int line_index;
    char line_buffer [MAX_SIZE];
    token t[MAX_SIZE];
    int t_index;
} scanner_data;

typedef enum {
    BEGIN,
    END,
    READ,
    WRITE,
    ID,
    INTLITERAL,
    LPAREN,
    RPAREN,
    SEMICOLON,
    COMMA,
    ASSIGNOP,
    PLUSOP,
    MINUSOP,
    SCANEOF,
    ERROR
} tokens;

void scanner(openfile_data *);

/* this is called once all the files are open and we get a line buffer in */
void match_code_to_token(scanner_data *);

/* int is the position in line_buffer to start at */

token match_alpha(scanner_data *);
token match_numeric(scanner_data *);
token match_error(scanner_data *);
token match_symbol(scanner_data *);

#endif
