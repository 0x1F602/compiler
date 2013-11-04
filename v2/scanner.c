#include <stdio.h>
#include <ctype.h>
#include "headers/scanner.h"
#include "headers/openfile.h"





token getToken(fileStruct *files)
{
	token outToken;
	char c,array[2];

	c=fgetc(files->input);
	
	while(c==' '||c=='\t'||c=='\n')
	{
		array[0]=c;
		array[1]='\0';
		strcat(linebuff,array);
		if(c=='\n')
		{
			fprintf(files->lis_file,"%d %s",linenum,linebuff);
			linenum++;
			memset(linebuff,0,sizeof(linebuff));
		}
		c=fgetc(files->input);
	}
	if(isalpha(c))
	{
		outToken=process_alpha(c, files);
	}
	else if(isdigit(c))
	{
		outToken=process_num(c,files);
	}
	else if(ispunct(c))
	{
		outToken=process_symbol(c,files);
	}	

}

token process_alpha(char c, fileStruct *files)
{
	token outToken;
	int index=0;
	
	memset(outToken.actual,0,sizeof(outToken.actual));
	outToken.actual[index]=c;
	index++;
	c=fgetc(files->input);
	while(isalnum(c))
	{
		outToken.actual[index]=c;
    	index++;
		c=fgetc(files->input);
	}
	ungetc(c,files->input);
	printf("%s\n",outToken.actual);
	strcat(linebuff,outToken.actual);
	printf("%s\n",linebuff);

}

token process_num(char c, fileStruct *files)
{
}

token process_symbol(char c, fileStruct *files)
{
}
