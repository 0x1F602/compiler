#include <stdio.h>
#include "headers/scanner.h"
#include <string.h>

int program(fileStruct *files)
{
	int retval1=0,retval2=0;
	token intoken;
	intoken=getToken(files);
	if(strcmp(intoken.type,"START")==0)
	{
	}
	else
	{
		fprintf(files->lis_file, "Expected START TOKEN. %s found instead.\n",intoken.actual);
		retval1++;
	}
	
	retval2=declarelist(*files);

	intoken=getToken(files);
	if(strcmp(intoken.type,"FINISH")==0)
    {
    }
    else
    {
		fprintf(files->lis_file, "Expected FINISH TOKEN. %s found instead.\n",intoken.actual);
        retval1++;
    }

	intoken=getToken(files);
	if(strcmp(intoken.type,"SCANEOF")==0)
    {
	
    }
    else
    {
        //no eof token
		fprintf(files->lis_file, "Expected EOF TOKEN. %s found instead.\n",intoken.actual);
		fprintf(files->lis_file, "Reached expected end of program. Printing remaining code. It will not be parsed\n");
		while(!feof(files->input))
		{
			intoken=getToken(files);
		}
        retval1++;
    }
	
	retval1=retval1+retval2;

	//0 is finished with no problems
	//if < 0, number indicates number of parsing errors.
	return retval1;
}

int declarelist(fileStruct *files)
{

}



