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

/* this is called once all the files are open and we get a line buffer in */
token match_code_to_token(scanner_data *);

/* int is the position in line_buffer to start at */

token match_alpha(scanner_data *, int);
token match_end(scanner_data *, int);
token match_begin(scanner_data *, int);

token match_numeric(token *, int);
token match_error(token *, int);

token match_symbol(token *, int);
token match_comment(token *, int);
token match_terminal_symbol(token *, int);

#endif
