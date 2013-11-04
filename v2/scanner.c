#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "headers/scanner.h"
#include "headers/openfile.h"

void wipeout(token * t) {
    memset(t->actual,0,sizeof(t->actual)); // clear it
    memset(t->type,0,sizeof(t->type)); // clear it
}

char fpeek(FILE * f) {
    char x = '\0'; // to be extracted
    x = fgetc(f);
    ungetc(x, f);
    return x;
}

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
	//printf("%s\n",outToken.actual);
	strcat(linebuff,outToken.actual);
	//printf("%s\n",linebuff);

    return outToken;
}

token process_num(char c, fileStruct *files)
{
    // shiny new token
    token out;
    wipeout(&out);
    // assume it's integer 
    strcpy(out.type, "INTLIT");
    out.number = INTLIT;
    int index = 0; //index for out.actual assignment
    out.actual[0] = c; // assign the first one
    index++; // accounting for above line
    while (isdigit(fpeek(files->input))) {
        c = fgetc(files->input);
        out.actual[index] = c;
        index++;
    }
    // if we encounter a period, it's a real
    if (fpeek(files->input) == '.') {
        strcpy(out.type, "REALLIT");
        out.number = REALLIT;
        out.actual[index++] = fgetc(files->input);
        while (isdigit(fpeek(files->input))) {
            out.actual[index++] = fgetc(files->input);
        }
    }

	strcat(linebuff,out.actual);
    return out;
}

token process_symbol(char c, fileStruct *files)
{
}
