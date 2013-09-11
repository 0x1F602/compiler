#ifndef OPENFILE_H
#define OPENFILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_EXTENSION ".IN"
#define OUTPUT_EXTENSION ".OUT"

typedef struct {
    char ** tokens;
    unsigned short int index;
} tokened_string;

typedef struct {
    FILE * input;
    FILE * output;
    FILE * listing_file;
    FILE * temp1;
} openfile_data;

char * prompt_user(const char *);
void handle_no_params(void);
void handle_one_params(char*);
void handle_two_params(char*,char*);

char * check_or_add_extension(char *, char *);
char * find_extension(char *);
char * generate_filename(char *);
int file_exists(char *);
void backup(FILE *);
void close_if_open(FILE *);

#endif
