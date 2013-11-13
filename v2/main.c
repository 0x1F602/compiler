#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "headers/openfile.h"
#include "headers/scanner.h"


main(int argc, char * argv[])
{
	fileStruct file_struct;
	linenum=1;
	memset(linebuff,0,sizeof(linebuff));
	file_struct = openfile(argc, argv[1]);
    unsigned int error_count = 0;
    while (!feof(file_struct.input)) {
	    token o = getToken(&file_struct);
        if (o.number >= 0) {
            fprintf(file_struct.tmp1, "token number:\t%d\ttoken type:\t%-15s\tactual token:\t%-15s\n", o.number, o.type, o.actual);
        }
        if (o.number == ERROR) {
            fprintf(file_struct.lis_file, "\nError. %s not recognized.\n", o.actual);
            error_count = error_count + 1;
        } 
    }
    if (error_count != 0) {
        fprintf(file_struct.lis_file, "\n\n%d\t\tLexical errors.\n", error_count);
    }
}
