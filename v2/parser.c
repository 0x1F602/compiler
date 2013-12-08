//Parser evaluates expressions in prefix notation
//! or -- are both comments according to this parser!


#include <stdio.h>
#include <string.h>
#include "headers/scanner.h"
#include "headers/parser.h"

int lex_errors = 0;

int program(fileStruct *files)
{
	symbind=0;
	fprintf(files->tmp1,"#include <stdio.h>\n main()\n{\n");
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
		fprintf(files->tmp2,"}:");
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
    if (retval1 > 0) {
        if (retval1 > 1) {
            fprintf(files->lis_file, "\n%d parser errors found\n", retval1);
        }
        else {
            fprintf(files->lis_file, "\n%d parser error found\n", retval1);
        }
    }
    if (lex_errors > 0) {
        if (lex_errors > 1) {
            fprintf(files->lis_file, "\n%d lexical errors found\n", retval1);
        }
        else {
            fprintf(files->lis_file, "\n%d lexical error found\n", retval1);
        }
    }

	return retval1;
}

token declarelist(fileStruct *files)
{
	int errorflag=0;
	token intoken;
	intoken=getToken(files);
	
	if(strcmp(intoken.type,"INT")==0)
    {
		fprintf(files->tmp1,"int ");
		intoken=idlist(files,0,intoken);
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
		fprintf(files->tmp1,"float ");
		intoken=idlist(files,0,intoken);
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
		fprintf(files->tmp1,"char ");
		intoken=idlist(files,2,intoken);
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
			fprintf(files->tmp1,"int ");
    	    intoken=idlist(files,0,intoken);
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
			fprintf(files->tmp1,"float ");
        	intoken=idlist(files,0,intoken);
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
			fprintf(files->tmp1,"char ");
        	intoken=idlist(files,2,intoken);
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


//flag=0 for declare list
//flag=1 for input stmt
//flag=2 for char declare
token idlist(fileStruct *files, int flag,token intoken)
{
	int errorflag=0;
	int type=-1;
	char tmpbuff[200];
	char outbuffer[200];

	memset(tmpbuff, '\0', sizeof(tmpbuff) );	
	memset(tmpbuff, '\0', sizeof(outbuffer) );
	if(strcmp(intoken.type,"INT")==0)
	{
		type=0;
	}
	else if(strcmp(intoken.type,"REAL")==0)
    {
        type=1;
    }
	else if(strcmp(intoken.type,"STRING")==0)
    {
        type=2;
    }
	intoken=getToken(files);
	
	if(strcmp(intoken.type,"ID")==0)
	{
		if (flag==0)
			fprintf(files->tmp1, "%s=0",intoken.actual);
		if (flag==2)
			fprintf(files->tmp1, "%s[100]",intoken.actual);
		if(flag==0||flag==2)
		{
			strcpy(symboltable[symbind].name,intoken.actual);
			symboltable[symbind].type=type;
			symbind++;	
		}
		if (flag==1)
		{
			type=getType(intoken.actual);
			if (type==0)
			{
				memset(tmpbuff, '\0', sizeof(tmpbuff) );
				fprintf(files->tmp2,"\"%%d ");
				sprintf(tmpbuff,", %s",intoken.actual);
				strcpy(outbuffer,tmpbuff);
			}
			else if (type==1)
			{
				memset(tmpbuff, '\0', sizeof(tmpbuff) );
				fprintf(files->tmp2,"\"%%f ");
				sprintf(tmpbuff,", %s",intoken.actual);
                strcpy(outbuffer,tmpbuff);
			}
			else if (type==2)
			{
				memset(tmpbuff, '\0', sizeof(tmpbuff) );
				fprintf(files->tmp2,"\"%%s ");
				sprintf(tmpbuff,", %s",intoken.actual);
                strcpy(outbuffer,tmpbuff);
			}
		}
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
			if (flag==0)
				fprintf(files->tmp1,",%s=0",intoken.actual);
			if(flag==2)
				fprintf(files->tmp1,",%s[100]",intoken.actual);
			if(flag==0||flag==2)
 	        {
    	        strcpy(symboltable[symbind].name,intoken.actual);
        	    symboltable[symbind].type=type;
            	symbind++;
        	}
			if (flag==1)
       		{	
            	type=getType(intoken.actual);
	            if (type==0)
    	        {
        	        fprintf(files->tmp2,"%%d ");
            	    sprintf(tmpbuff,", %s",intoken.actual);
               		strcat(outbuffer,tmpbuff);
	                memset(tmpbuff, '\0', sizeof(tmpbuff) );
    	        }
        	    else if (type==1)
           		{
                	fprintf(files->tmp2,"%%f ");
	                sprintf(tmpbuff,", %s",intoken.actual);
    	            strcat(outbuffer,tmpbuff);
        	        memset(tmpbuff, '\0', sizeof(tmpbuff) );
            	}
	            else if (type==2)
    	        {
        	        fprintf(files->tmp2,"%%s ");
            	    sprintf(tmpbuff,", %s",intoken.actual);
                	strcat(outbuffer,tmpbuff);
	                memset(tmpbuff, '\0', sizeof(tmpbuff) );
    	        }
        	}
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
	if (flag==1)
	{
		fprintf(files->tmp2,"\"%s",outbuffer);
	}
	if (flag==0||flag==2)
	{
		fprintf(files->tmp1,";\n");	
	}
	return intoken;
}



token statementlist(fileStruct *files, token oldtoken)
{
	token intoken;

	intoken=oldtoken;
	while(strcmp(intoken.type,"FINISH")!=0) // || (strcmp(intoken.type, "SCANEOF")) != 0)
	{
		if(strcmp(intoken.type,"INPUT")==0)
		{
			intoken=getToken(files);
			if(strcmp(intoken.type,"LPAREN")==0)
			{
			}
			else
			{
				fprintf(files->lis_file, "Expected a (. %s found instead.\n",intoken.type);
				retval1++;
			}
			fprintf(files->tmp2,"scanf(");
			intoken=idlist(files,1,intoken);
			if(strcmp(intoken.type,"RPAREN")==0)
			{
			}
			else
			{
				fprintf(files->lis_file, "Expected a ). %s found instead.\n",intoken.type);
				retval1++;
			}
			intoken=getToken(files);
			if(strcmp(intoken.type,"SEMICOLON")==0)
			{
			}
			else
			{
				fprintf(files->lis_file, "Expected a ;. %s found instead.\n",intoken.type);
				retval1++;
			}
			fprintf(files->tmp2,");\n");
			intoken=getToken(files);
			}
		else if(strcmp(intoken.type,"OUTPUT")==0)
		{
			intoken=getToken(files);
			if(strcmp(intoken.type,"LPAREN")==0)
			{
			}
			else
			{
				fprintf(files->lis_file, "Expected a (. %s found instead.\n",intoken.type);
				retval1++;
			}
			intoken=outputlist(files);
			if(strcmp(intoken.type,"RPAREN")==0)
			{
			}
			else
			{
				fprintf(files->lis_file, "Expected a ). %s found instead.\n",intoken.type);
				retval1++;
			}
			intoken=getToken(files);
			if(strcmp(intoken.type,"SEMICOLON")==0)
			{
			}
			else
			{
				fprintf(files->lis_file, "Expected a ;. %s found instead.\n",intoken.type);
				retval1++;
			}
			intoken=getToken(files);
		}
		else if(strcmp(intoken.type,"ID")==0)
		{
			intoken=getToken(files);
			if (strcmp(intoken.type,"ASSIGN")==0)
			{
			}
			else
			{
				fprintf(files->lis_file, "Expected a =. %s found instead.\n",intoken.type);
                retval1++;
			}
			intoken=getToken(files);
			if (strcmp(intoken.type,"STRINGLIT")==0)
			{
			}
			else
			{
				intoken=expression2(files,intoken);
			}
			intoken=getToken(files);
			if (strcmp(intoken.type,"SEMICOLON")==0)
            {
            }
            else
            {
                fprintf(files->lis_file, "Expected a ;. %s found instead.\n",intoken.type);
                retval1++;
            }
			intoken=getToken(files);
		}
		else if(strcmp(intoken.type,"IF")==0)
		{
			intoken=getToken(files);
			if(strcmp(intoken.type,"LPAREN")==0)
            {
            }
            else
            {
                fprintf(files->lis_file, "Expected a (. %s found instead.\n",intoken.type);
                retval1++;
            }
			intoken=condition(files);
			intoken=getToken(files);
			if(strcmp(intoken.type,"RPAREN")==0)
            {
            }
            else
            {
                fprintf(files->lis_file, "Expected a ). %s found instead.\n",intoken.type);
                retval1++;
            }
			intoken=getToken(files);
			if(strcmp(intoken.type,"THEN")==0)
			{	
			}
			else
            {
                fprintf(files->lis_file, "Expected a THEN. %s found instead.\n",intoken.type);
                retval1++;
            }
			intoken=getToken(files);
			intoken=statementlist2(files,intoken);
			if(strcmp(intoken.type,"ELSE")==0)
			{
			}
			else
            {
                fprintf(files->lis_file, "Expected an ELSE. %s found instead.\n",intoken.type);
                retval1++;
            }
			intoken=getToken(files);
			intoken=statementlist3(files,intoken);
			intoken=getToken(files);
		}
		else if(strcmp(intoken.type,"WHILE")==0)
		{
			intoken=getToken(files);
			if(strcmp(intoken.type,"LPAREN")==0)
            {
            }
            else
            {
                fprintf(files->lis_file, "Expected a (. %s found instead.\n",intoken.type);
                retval1++;
            }
			intoken=condition(files);
			intoken=getToken(files);
			if(strcmp(intoken.type,"RPAREN")==0)
            {
            }
            else
            {
                fprintf(files->lis_file, "Expected a ). %s found instead.\n",intoken.type);
                retval1++;
            }
			intoken=getToken(files);
			intoken=statementlist4(files,intoken);
			intoken=getToken(files);
		}
		else
		{
			//will keep pushing untiil it can at least get to a finish token
			if (intoken.number == ERROR) {
			    fprintf(files->lis_file, "Lexical error found: %s\n", intoken.actual);
                lex_errors += 1;
            }
			intoken=getToken(files);
		}
	}
	return intoken;	
}

token statementlist2(fileStruct *files, token oldtoken)
{
	token intoken;

	intoken=oldtoken;
	while(strcmp(intoken.type,"ELSE")!=0) //|| (strcmp(intoken.type, "SCANEOF")) != 0)
	{
		if(strcmp(intoken.type,"INPUT")==0)
		{
			intoken=getToken(files);
			if(strcmp(intoken.type,"LPAREN")==0)
			{
			}
			else
			{
				fprintf(files->lis_file, "Expected a (. %s found instead.\n",intoken.type);
				retval1++;
			}
			fprintf(files->tmp2,"scanf(");
			intoken=idlist(files,1,intoken);
			if(strcmp(intoken.type,"RPAREN")==0)
			{
			}
			else
			{
				fprintf(files->lis_file, "Expected a ). %s found instead.\n",intoken.type);
				retval1++;
			}
			intoken=getToken(files);
			if(strcmp(intoken.type,"SEMICOLON")==0)
			{
			}
			else
			{
				fprintf(files->lis_file, "Expected a ;. %s found instead.\n",intoken.type);
				retval1++;
			}
			fprintf(files->tmp2,");\n");
			intoken=getToken(files);
			}
		else if(strcmp(intoken.type,"OUTPUT")==0)
		{
			intoken=getToken(files);
			if(strcmp(intoken.type,"LPAREN")==0)
			{
			}
			else
			{
				fprintf(files->lis_file, "Expected a (. %s found instead.\n",intoken.type);
				retval1++;
			}
			intoken=outputlist(files);
			if(strcmp(intoken.type,"RPAREN")==0)
			{
			}
			else
			{
				fprintf(files->lis_file, "Expected a ). %s found instead.\n",intoken.type);
				retval1++;
			}
			intoken=getToken(files);
			if(strcmp(intoken.type,"SEMICOLON")==0)
			{
			}
			else
			{
				fprintf(files->lis_file, "Expected a ;. %s found instead.\n",intoken.type);
				retval1++;
			}
			intoken=getToken(files);
		}
		else if(strcmp(intoken.type,"ID")==0)
		{
			intoken=getToken(files);
			if (strcmp(intoken.type,"ASSIGN")==0)
			{
			}
			else
			{
				fprintf(files->lis_file, "Expected a =. %s found instead.\n",intoken.type);
                retval1++;
			}
			intoken=getToken(files);
			if (strcmp(intoken.type,"STRINGLIT")==0)
			{
			}
			else
			{
				intoken=expression2(files,intoken);
			}
			intoken=getToken(files);
			if (strcmp(intoken.type,"SEMICOLON")==0)
            {
            }
            else
            {
                fprintf(files->lis_file, "Expected a ;. %s found instead.\n",intoken.type);
                retval1++;
            }
			intoken=getToken(files);
		}
		else if(strcmp(intoken.type,"IF")==0)
		{
			intoken=getToken(files);
			if(strcmp(intoken.type,"LPAREN")==0)
            {
            }
            else
            {
                fprintf(files->lis_file, "Expected a (. %s found instead.\n",intoken.type);
                retval1++;
            }
			intoken=condition(files);
			if(strcmp(intoken.type,"RPAREN")==0)
            {
            }
            else
            {
                fprintf(files->lis_file, "Expected a ). %s found instead.\n",intoken.type);
                retval1++;
            }
			intoken=getToken(files);
			intoken=getToken(files);
			if(strcmp(intoken.type,"THEN")==0)
			{	
			}
			else
            {
                fprintf(files->lis_file, "Expected a THEN. %s found instead.\n",intoken.type);
                retval1++;
            }
			intoken=getToken(files);
			intoken=statementlist2(files,intoken);
			if(strcmp(intoken.type,"ELSE")==0)
			{
			}
			else
            {
                fprintf(files->lis_file, "Expected an ELSE. %s found instead.\n",intoken.type);
                retval1++;
            }
			intoken=getToken(files);
			intoken=statementlist3(files,intoken);
		}
		else if(strcmp(intoken.type,"WHILE")==0)
		{
			intoken=getToken(files);
			if(strcmp(intoken.type,"LPAREN")==0)
            {
            }
            else
            {
                fprintf(files->lis_file, "Expected a (. %s found instead.\n",intoken.type);
                retval1++;
            }
			intoken=condition(files);
			intoken=getToken(files);
			if(strcmp(intoken.type,"RPAREN")==0)
            {
            }
            else
            {
                fprintf(files->lis_file, "Expected a ). %s found instead.\n",intoken.type);
                retval1++;
            }
			intoken=getToken(files);
			intoken=statementlist4(files,intoken);
		}
		else
		{
			//will keep pushing untiil it can at least get to a else token
			intoken=getToken(files);
		}
	}
	return intoken;	
}

token statementlist3(fileStruct *files, token oldtoken)
{
	token intoken;

	intoken=oldtoken;
	while(strcmp(intoken.type,"ENDIF")!=0 )// || (strcmp(intoken.type, "SCANEOF")) != 0)
	{
		if(strcmp(intoken.type,"INPUT")==0)
		{
			intoken=getToken(files);
			if(strcmp(intoken.type,"LPAREN")==0)
			{
			}
			else
			{
				fprintf(files->lis_file, "Expected a (. %s found instead.\n",intoken.type);
				retval1++;
			}
			fprintf(files->tmp2,"scanf(");
			intoken=idlist(files,1,intoken);
			if(strcmp(intoken.type,"RPAREN")==0)
			{
			}
			else
			{
				fprintf(files->lis_file, "Expected a ). %s found instead.\n",intoken.type);
				retval1++;
			}
			intoken=getToken(files);
			if(strcmp(intoken.type,"SEMICOLON")==0)
			{
			}
			else
			{
				fprintf(files->lis_file, "Expected a ;. %s found instead.\n",intoken.type);
				retval1++;
			}
			fprintf(files->tmp2,");\n");
			intoken=getToken(files);
			}
		else if(strcmp(intoken.type,"OUTPUT")==0)
		{
			intoken=getToken(files);
			if(strcmp(intoken.type,"LPAREN")==0)
			{
			}
			else
			{
				fprintf(files->lis_file, "Expected a (. %s found instead.\n",intoken.type);
				retval1++;
			}
			intoken=outputlist(files);
			if(strcmp(intoken.type,"RPAREN")==0)
			{
			}
			else
			{
				fprintf(files->lis_file, "Expected a ). %s found instead.\n",intoken.type);
				retval1++;
			}
			intoken=getToken(files);
			if(strcmp(intoken.type,"SEMICOLON")==0)
			{
			}
			else
			{
				fprintf(files->lis_file, "Expected a ;. %s found instead.\n",intoken.type);
				retval1++;
			}
			intoken=getToken(files);
		}
		else if(strcmp(intoken.type,"ID")==0)
		{
			intoken=getToken(files);
			if (strcmp(intoken.type,"ASSIGN")==0)
			{
			}
			else
			{
				fprintf(files->lis_file, "Expected a =. %s found instead.\n",intoken.type);
                retval1++;
			}
			intoken=getToken(files);
			if (strcmp(intoken.type,"STRINGLIT")==0)
			{
			}
			else
			{
				intoken=expression2(files,intoken);
			}
			intoken=getToken(files);
			if (strcmp(intoken.type,"SEMICOLON")==0)
            {
            }
            else
            {
                fprintf(files->lis_file, "Expected a ;. %s found instead.\n",intoken.type);
                retval1++;
            }
			intoken=getToken(files);
		}
		else if(strcmp(intoken.type,"IF")==0)
		{
			intoken=getToken(files);
			if(strcmp(intoken.type,"LPAREN")==0)
            {
            }
            else
            {
                fprintf(files->lis_file, "Expected a (. %s found instead.\n",intoken.type);
                retval1++;
            }
			intoken=condition(files);
			intoken=getToken(files);
			if(strcmp(intoken.type,"RPAREN")==0)
            {
            }
            else
            {
                fprintf(files->lis_file, "Expected a ). %s found instead.\n",intoken.type);
                retval1++;
            }
			intoken=getToken(files);
			if(strcmp(intoken.type,"THEN")==0)
			{	
			}
			else
            {
                fprintf(files->lis_file, "Expected a THEN. %s found instead.\n",intoken.type);
                retval1++;
            }
			intoken=getToken(files);
			intoken=statementlist2(files,intoken);
			if(strcmp(intoken.type,"ELSE")==0)
			{
			}
			else
            {
                fprintf(files->lis_file, "Expected an ELSE. %s found instead.\n",intoken.type);
                retval1++;
            }
			intoken=getToken(files);
			intoken=statementlist3(files,intoken);
		}
		else if(strcmp(intoken.type,"WHILE")==0)
		{
			intoken=getToken(files);
			if(strcmp(intoken.type,"LPAREN")==0)
            {
            }
            else
            {
                fprintf(files->lis_file, "Expected a (. %s found instead.\n",intoken.type);
                retval1++;
            }
			intoken=condition(files);
			intoken=getToken(files);
			if(strcmp(intoken.type,"RPAREN")==0)
            {
            }
            else
            {
                fprintf(files->lis_file, "Expected a ). %s found instead.\n",intoken.type);
                retval1++;
            }
			intoken=getToken(files);
			intoken=statementlist4(files,intoken);
		}
		else
		{
			//will keep pushing untiil it can at least get to an endif token
			intoken=getToken(files);
		}
	}
	return intoken;	
}

token statementlist4(fileStruct *files, token oldtoken)
{
	token intoken;

	intoken=oldtoken;
	while(strcmp(intoken.type,"ENDWHILE")!=0)// || intoken.number != SCANEOF)
	{
		if(strcmp(intoken.type,"INPUT")==0)
		{
			intoken=getToken(files);
			if(strcmp(intoken.type,"LPAREN")==0)
			{
			}
			else
			{
				fprintf(files->lis_file, "Expected a (. %s found instead.\n",intoken.type);
				retval1++;
			}
			fprintf(files->tmp2,"scanf(");
			intoken=idlist(files,1,intoken);
			if(strcmp(intoken.type,"RPAREN")==0)
			{
			}
			else
			{
				fprintf(files->lis_file, "Expected a ). %s found instead.\n",intoken.type);
				retval1++;
			}
			intoken=getToken(files);
			if(strcmp(intoken.type,"SEMICOLON")==0)
			{
			}
			else
			{
				fprintf(files->lis_file, "Expected a ;. %s found instead.\n",intoken.type);
				retval1++;
			}
			fprintf(files->tmp2,");\n");
			intoken=getToken(files);
			}
		else if(strcmp(intoken.type,"OUTPUT")==0)
		{
			intoken=getToken(files);
			if(strcmp(intoken.type,"LPAREN")==0)
			{
			}
			else
			{
				fprintf(files->lis_file, "Expected a (. %s found instead.\n",intoken.type);
				retval1++;
			}
			intoken=outputlist(files);
			if(strcmp(intoken.type,"RPAREN")==0)
			{
			}
			else
			{
				fprintf(files->lis_file, "Expected a ). %s found instead.\n",intoken.type);
				retval1++;
			}
			intoken=getToken(files);
			if(strcmp(intoken.type,"SEMICOLON")==0)
			{
			}
			else
			{
				fprintf(files->lis_file, "Expected a ;. %s found instead.\n",intoken.type);
				retval1++;
			}
			intoken=getToken(files);
		}
		else if(strcmp(intoken.type,"ID")==0)
		{
			intoken=getToken(files);
			if (strcmp(intoken.type,"ASSIGN")==0)
			{
			}
			else
			{
				fprintf(files->lis_file, "Expected a =. %s found instead.\n",intoken.type);
                retval1++;
			}
			intoken=getToken(files);
			if (strcmp(intoken.type,"STRINGLIT")==0)
			{
			}
			else
			{
				intoken=expression2(files,intoken);
			}
			intoken=getToken(files);
			if (strcmp(intoken.type,"SEMICOLON")==0)
            {
            }
            else
            {
                fprintf(files->lis_file, "Expected a ;. %s found instead.\n",intoken.type);
                retval1++;
            }
			
		}
		else if(strcmp(intoken.type,"IF")==0)
		{
			intoken=getToken(files);
			if(strcmp(intoken.type,"LPAREN")==0)
            {
            }
            else
            {
                fprintf(files->lis_file, "Expected a (. %s found instead.\n",intoken.type);
                retval1++;
            }
			intoken=condition(files);
			intoken=getToken(files);
			if(strcmp(intoken.type,"RPAREN")==0)
            {
            }
            else
            {
                fprintf(files->lis_file, "Expected a ). %s found instead.\n",intoken.type);
                retval1++;
            }
			intoken=getToken(files);
			if(strcmp(intoken.type,"THEN")==0)
			{	
			}
			else
            {
                fprintf(files->lis_file, "Expected a THEN. %s found instead.\n",intoken.type);
                retval1++;
            }
			intoken=getToken(files);
			intoken=statementlist2(files,intoken);
			if(strcmp(intoken.type,"ELSE")==0)
			{
			}
			else
            {
                fprintf(files->lis_file, "Expected an ELSE. %s found instead.\n",intoken.type);
                retval1++;
            }
			intoken=getToken(files);
			intoken=statementlist3(files,intoken);
		}
		else if(strcmp(intoken.type,"WHILE")==0)
		{
			intoken=getToken(files);
			if(strcmp(intoken.type,"LPAREN")==0)
            {
            }
            else
            {
                fprintf(files->lis_file, "Expected a (. %s found instead.\n",intoken.type);
                retval1++;
            }
			intoken=condition(files);
			intoken=getToken(files);
			if(strcmp(intoken.type,"RPAREN")==0)
            {
            }
            else
            {
                fprintf(files->lis_file, "Expected a ). %s found instead.\n",intoken.type);
                retval1++;
            }
			intoken=getToken(files);
			intoken=statementlist4(files,intoken);
		}
		else
		{
			//will keep pushing untiil it can at least get to an endwhile token
			intoken=getToken(files);
		}
	}
	return intoken;	
}

token outputlist(fileStruct *files)
{
	token intoken;

	intoken=expression(files);
	intoken=getToken(files);
	while(strcmp(intoken.type,"COMMA")==0)
    {
		intoken=expression(files);
    }

	return intoken;
}

token expression(fileStruct *files)
{
	token intoken;

	intoken=getToken(files);

	if(strcmp(intoken.type,"NEGATION")==0)
	{
		intoken=getToken(files);
	}
	if(strcmp(intoken.type,"PLUSOP")==0||strcmp(intoken.type,"MINUSOP")==0||strcmp(intoken.type,"MULTOP")==0||strcmp(intoken.type,"DIVOP")==0||strcmp(intoken.type,"EXPOP")==0)
	{
		intoken=expression(files);
		intoken=expression(files);
	}	
	else if(strcmp(intoken.type,"INTLIT")==0)
	{
	}
	else if(strcmp(intoken.type,"REALLIT")==0)
    {
    }
	else if(strcmp(intoken.type,"ID")==0)
    {
    }
	else
	{
		fprintf(files->lis_file, "Expected a MATHOP, INTLIT, REALLIT, or ID. %s found instead.\n",intoken.type);
        retval1++;
	}

	return intoken;



}

token expression2(fileStruct *files, token oldtoken)
{
    token intoken;

    intoken=oldtoken;
    if(strcmp(intoken.type,"NEGATION")==0)
    {
        intoken=getToken(files);
    }
    if(strcmp(intoken.type,"PLUSOP")==0||strcmp(intoken.type,"MINUSOP")==0||strcmp(intoken.type,"MULTOP")==0||strcmp(intoken.type,"DIVOP")==0||strcmp(intoken.type,"EXPOP")==0)
    {
        intoken=expression(files);
        intoken=expression(files);
    }
    else if(strcmp(intoken.type,"INTLIT")==0)
    {
    }
    else if(strcmp(intoken.type,"REALLIT")==0)
    {
    }
    else if(strcmp(intoken.type,"ID")==0)
    {
    }
    else
    {
        fprintf(files->lis_file, "Expected a MATHOP, INTLIT, REALLIT, or ID. %s found instead.\n",intoken.type);
        retval1++;
    }

    return intoken;



}

token condition(fileStruct *files)
{
	token intoken;

	intoken=getToken(files);

	if(strcmp(intoken.type,"NOT")==0)
	{
		intoken=getToken(files);
	}
	
	if(strcmp(intoken.type,"AND")==0)
	{
		intoken=condition(files);
		intoken=condition(files);
		intoken=getToken(files);
	}
	else if(strcmp(intoken.type,"OR")==0)
	{
		intoken=condition(files);
		intoken=condition(files);
		intoken=getToken(files);
	}
	else if(strcmp(intoken.type,"LTSIGN")==0||strcmp(intoken.type,"LTESIGN")==0||strcmp(intoken.type,"GTSIGN")==0||strcmp(intoken.type,"GTESIGN")==0||strcmp(intoken.type,"EQUIVSIGN")==0||strcmp(intoken.type,"NOTEQSIGN")==0)
	{
		intoken=expression(files);
		intoken=expression(files);
	}
	else
	{
		fprintf(files->lis_file, "Expected a Logical Op or Relational Op. %s found instead.\n",intoken.type);
        retval1++;
	}

	return intoken;
}

int getType(char *name)
{
	int endflag=0;
	int scanindex=0;
	int returnval=-1;

	while(scanindex<symbind && endflag==0)
	{
		if(strcmp(name,symboltable[scanindex].name)==0)
		{
			endflag=1;
			returnval=symboltable[scanindex].type;
		}
		else
		{
			scanindex++;
		}
	}
	return returnval;
}

