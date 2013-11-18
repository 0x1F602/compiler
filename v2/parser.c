#include <stdio.h>
#include <string.h>
#include "headers/scanner.h"
#include "headers/parser.h"

int lex_errors = 0;

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
			intoken=idlist(files);
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
			intoken=idlist(files);
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
			intoken=idlist(files);
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
			intoken=idlist(files);
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



