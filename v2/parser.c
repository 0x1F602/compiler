#include <stdio.h>
#include "headers/scanner.h"
#include "headers/parser.h"
#include <string.h>

int program(fileStruct *files)
{
	token intoken;
	retval1=0;
	intoken=getToken(files);
	if(strcmp(intoken.type,"START")==0)
	{
	}
	else
	{
		fprintf(files->lis_file, "Expected START TOKEN. %s found instead.\n",intoken.type);
		retval1++;
	}
	
	intoken=declarelist(files);
	intoken=statementlist(files,intoken);	

	if(strcmp(intoken.type,"FINISH")==0)
    {
    }
    else
    {
		fprintf(files->lis_file, "Expected FINISH TOKEN. %s found instead.\n",intoken.type);
        retval1++;
    }

	intoken=getToken(files);
	if(strcmp(intoken.type,"SCANEOF")==0)
    {
	
    }
    else
    {
        //no eof token
		fprintf(files->lis_file, "Expected EOF TOKEN. %s found instead.\n",intoken.type);
		fprintf(files->lis_file, "Reached expected end of program. Printing remaining code. It will not be parsed\n");
		while(!feof(files->input))
		{
			intoken=getToken(files);
		}
        retval1++;
    }
	//0 is finished with no problems
	//>0 if parsing errors
	return retval1;
}

token declarelist(fileStruct *files)
{
	int errorflag=0;
	token intoken;
	intoken=getToken(files);
	
	if(strcmp(intoken.type,"INT")==0)
    {
		intoken=idlist(files);
		if(strcmp(intoken.type,"SEMICOLON")==0)
		{
		}
		else
		{
		fprintf(files->lis_file, "Expected a semicolon. %s found instead.\n",intoken.type);
        retval1++;
		}
    }
	else if(strcmp(intoken.type,"REAL")==0)
	{
		intoken=idlist(files);
		if(strcmp(intoken.type,"SEMICOLON")==0)
        {
        }
        else
        {
        fprintf(files->lis_file, "Expected a semicolon. %s found instead.\n",intoken.type);
        retval1++;
        }
	}
	else if(strcmp(intoken.type,"STRING")==0)
	{
		intoken=idlist(files);
		if(strcmp(intoken.type,"SEMICOLON")==0)
        {
        }
        else
        {
        fprintf(files->lis_file, "Expected a semicolon. %s found instead.\n",intoken.type);
        retval1++;
        }
	}
    else
    {
		errorflag=1;
        fprintf(files->lis_file, "Expected at least one declaration. %s found instead.\n",intoken.type);
        retval1++;
    }
	if(errorflag==0)
	{
		intoken=getToken(files);
	}
	while((strcmp(intoken.type,"INT")==0)||(strcmp(intoken.type,"REAL")==0)||(strcmp(intoken.type,"STRING")==0))
	{
		if(strcmp(intoken.type,"INT")==0)
	    {
    	    intoken=idlist(files);
			if(strcmp(intoken.type,"SEMICOLON")==0)
			{
			}
			else
			{
				fprintf(files->lis_file, "Expected at least one declaration. %s found instead.\n",intoken.type);
		        retval1++;
			}
  	  	}
    	else if(strcmp(intoken.type,"REAL")==0)
    	{
        	intoken=idlist(files);
            if(strcmp(intoken.type,"SEMICOLON")==0)
            {
            }
            else
            {
                fprintf(files->lis_file, "Expected at least one declaration. %s found instead.\n",intoken.type);
                retval1++;
            }
    	}
    	else if(strcmp(intoken.type,"STRING")==0)
    	{
        	intoken=idlist(files);
            if(strcmp(intoken.type,"SEMICOLON")==0)
            {
            }
            else
            {
                fprintf(files->lis_file, "Expected at least one declaration. %s found instead.\n",intoken.type);
                retval1++;
            }
   		}
		intoken=getToken(files);
	}
	
	return intoken;
}

token idlist(fileStruct *files)
{
	int errorflag=0;
	token intoken;
	
	intoken=getToken(files);
	
	if(strcmp(intoken.type,"ID")==0)
	{
	}
	else
	{
		fprintf(files->lis_file, "Expected at least one ID. %s found instead.\n",intoken.type);
		retval1++;
		errorflag=1;
	}
	if (errorflag==0)
	{
		intoken=getToken(files);
	}
	while(strcmp(intoken.type,"COMMA")==0)
	{
		errorflag=0;
		intoken=getToken(files);
		if(strcmp(intoken.type,"ID")==0)
		{
		}
		else
		{
			fprintf(files->lis_file, "Expected an ID. %s found instead.\n",intoken.type);
        	retval1++;
			errorflag=1;
		}
		if(errorflag==0)
		{
		intoken=getToken(files);
		}
		
	}
	
	return intoken;
}

token statementlist(fileStruct *files, token oldtoken)
{
	token intoken;
	
	intoken=getToken(files);
	return intoken;	
}
