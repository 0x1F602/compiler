#ifndef OPENFILE_H
#define OPENFILE_H

#include <stdio.h>
#include <stdlib.h>

#define INPUT_EXTENSION ".IN"
#define OUTPUT_EXTENSION ".OUT"

typedef enum { READY, ERROR } status_t;

const char * src_prompt = "Source filename: ";
const char * tar_prompt = "Target filename: ";

char * prompt_user(const char *);
void handle_no_params(void);
void handle_one_params(char*);
void handle_two_params(char*,char*);

char * check_or_add_extension(char *, char *);
int file_exists(char *);
void backup(FILE *);
void close_if_open(FILE *);

#endif
