#ifndef OPENFILE_H
#define OPENFILE_H

#include <stdio.h>
#include <stdlib.h>

#define INPUT_EXTENSION ".IN"
#define OUTPUT_EXTENSION ".OUT"

typedef enum { READY, QUIT, ERROR } status_t;
typedef struct {
    FILE * in;          // this is our input file
    FILE * out;         // this is our output file
    status_t status;   // this is our status of the transaction
} IOTransaction;
IOTransaction files;
char * prompt_user(char *);
void  handle_no_params(void);
void  handle_one_params(char*);
void  handle_two_params(char*,char*);
char * input_file_name (void);
char * output_file_name (void);
#endif
