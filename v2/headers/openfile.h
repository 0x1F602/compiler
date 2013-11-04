#ifndef OPENFILE_H
#define OPENFILE_H

#include <stdio.h>
#include <stdbool.h>
#define filenameSize 35

typedef struct {
    FILE * input;
    FILE * lis_file;
    FILE * tmp1;
    FILE * tmp2;
    FILE * outc;
} fileStruct;


fileStruct openfile(int, char *);
bool file_exists(char *);


#endif
