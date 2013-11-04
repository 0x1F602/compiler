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
    while (!feof(file_struct.input)) {
	    token o = getToken(&file_struct);
        fprintf(file_struct.tmp1, "TOKEN %s\nTYPE %s\nNUMBER %d\n\n", o.actual, o.type, o.number);
    }
}
