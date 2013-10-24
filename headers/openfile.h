#ifndef OPENFILE_H
#define OPENFILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_EXTENSION ".IN"
#define OUTPUT_EXTENSION ".c"

typedef struct {
    char ** tokens;
    unsigned short int index;
} tokened_string;


typedef struct {
    FILE * input;
    FILE * output;
    FILE * listing_file;
    FILE * temp1;
    FILE * temp2;
	FILE * outc;
} openfile_data;

openfile_data of_d;

char * prompt_user(const char *);
openfile_data handle_no_params(void);
openfile_data handle_one_params(char*);
openfile_data handle_two_params(char*,char*);

char * check_or_add_extension(char *, char *);
char * find_extension(char *);
void generate_filename(char *, char *, char *);
int file_exists(char *);
void backup(FILE *);
void close_if_open(FILE *);

#endif
