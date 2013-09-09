#ifndef SCANNER_H
#define SCANNER_H

#define MAX_SIZE 128

typedef struct {
    short int token_number;
    char token_type [16];
    char buffer [128];
} token;

typedef struct {
    char line_buffer [MAX_SIZE];
    char token_buffer [MAX_SIZE];
    token t;
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

#endif
