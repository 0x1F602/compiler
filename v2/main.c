//Group 4 Compiler
//Ian Wlodarczyk
//Patrik Natali
//Mike Hetzel


#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "headers/openfile.h"
#include "headers/scanner.h"
#include "headers/parser.h"

int main(int argc, char * argv[])
{
	int parseError=0;
	fileStruct file_struct;
	linenum=1;
	memset(linebuff,0,sizeof(linebuff));
	file_struct = openfile(argc, argv[1]);
	parseError=program(&file_struct);

    return 0;
}
