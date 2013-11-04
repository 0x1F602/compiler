#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "headers/scanner.h"
#include "headers/openfile.h"

/* from stack overflow http://stackoverflow.com/a/16151299 */
void toUpper(char *text, char *nText){
    int i;
    for(i=0; i<=strlen(text); i++){
        if( (text[i] > 96 ) && (text[i] < 123) ) // is the char lower case
            nText[i] = text[i] - 'a' + 'A';   //make upper
        else
            nText[i] = text[i]; //do nothing
    }   
}

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
    wipeout(&outToken);
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

    if (c == -1) {
        outToken.actual[0] = ':'; 
        outToken.actual[1] = 'D';
        strcpy(outToken.type, "SCANEOF");
        outToken.number = SCANEOF;
    }
    else if(isalpha(c))
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
    else {
        outToken.actual[0] = c;
        strcpy(outToken.type, "ERROR");
        outToken.number = ERROR;
    }
    
    return outToken;
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
	strcat(linebuff,outToken.actual);

    //assume it's an ID and prove it wrong
    strcpy(outToken.type, "ID");
    outToken.number = ID;
    // initializing our big ol table of reserved keywords
    // it's a little sparse right now
    char * uppercase_actual = malloc(sizeof(outToken.actual));
    toUpper(outToken.actual, uppercase_actual);
    char reserved_keywords[37][16];
    memset(reserved_keywords, '\0', sizeof(reserved_keywords));
    strcpy(reserved_keywords[START], "START");
    strcpy(reserved_keywords[FINISH], "FINISH");
    strcpy(reserved_keywords[INTEGER], "INTEGER");
    strcpy(reserved_keywords[REAL], "REAL");
    strcpy(reserved_keywords[STRING], "STRING");
    strcpy(reserved_keywords[INPUT], "INPUT");
    strcpy(reserved_keywords[OUTPUT], "OUTPUT");
    strcpy(reserved_keywords[ENDIF], "ENDIF");
    strcpy(reserved_keywords[ENDWHILE], "ENDWHILE");
    strcpy(reserved_keywords[ELSE], "ELSE");
    strcpy(reserved_keywords[THEN], "THEN");
    strcpy(reserved_keywords[NOT], "NOT");
    strcpy(reserved_keywords[AND], "AND");
    strcpy(reserved_keywords[OR], "OR");
    strcpy(reserved_keywords[IF], "IF");
    strcpy(reserved_keywords[WHILE], "WHILE");
    int i = 0;
    for (i = 0; i < 37; i++) {
       if (reserved_keywords[i][0] != '\0') {
           if (strcmp(reserved_keywords[i],uppercase_actual) == 0) {
            // we have a match
                strcpy(outToken.type,reserved_keywords[i]);
                outToken.number = i;
                break;
           } 
       } 
    }
    free(uppercase_actual);
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
    token out;
    wipeout(&out);
    ungetc(c, files->input); // woops
    if (fpeek(files->input) == '<') {
        out.actual[0] = fgetc(files->input);
        strcpy(out.type, "LTSIGN");
        out.number = LTSIGN;
        if (fpeek(files->input) == '=') {
            out.actual[1] = fgetc(files->input);
            strcpy(out.type, "LTESIGN");
            out.number = LTESIGN;
        }
        else if (fpeek(files->input) == '>') {
            out.actual[1] = fgetc(files->input);
            strcpy(out.type, "NOTEQSIGN");
            out.number = NOTEQSIGN;
        }
    } 
    else if (fpeek(files->input) == '>') {
        out.actual[0] = fgetc(files->input);
        strcpy(out.type, "GTSIGN");
        out.number = GTSIGN;
        if (fpeek(files->input) == '=') {
            out.actual[1] = fgetc(files->input);
            strcpy(out.type, "GTESIGN");
            out.number = GTESIGN;
        }
    } 
    else if (fpeek(files->input) == ';') {
        out.actual[0] = fgetc(files->input);
        strcpy(out.type, "SEMICOLON");
        out.number = SEMICOLON;

    } 
    else if (fpeek(files->input) == '=') {
        out.actual[0] = fgetc(files->input);
        strcpy(out.type, "ASSIGN");
        out.number = ASSIGN;
        if (fpeek(files->input) == '=') {
            out.actual[1] = fgetc(files->input);
            strcpy(out.type, "EQUIVSIGN");
            out.number = EQUIVSIGN;
        }
    } 
    else if (fpeek(files->input) == ',') {
        out.actual[0] = fgetc(files->input);
        strcpy(out.type, "COMMA");
        out.number = COMMA;
    } 
    else if (fpeek(files->input) == '*') {
        out.actual[0] = fgetc(files->input);
        strcpy(out.type, "MULTOP");
        out.number = MULTOP;
    }
    else if (fpeek(files->input) == '/') {
        out.actual[0] = fgetc(files->input);
        strcpy(out.type, "DIVOP");
        out.number = DIVOP;
    }
    else if (fpeek(files->input) == '-') {
        out.actual[0] = fgetc(files->input);
        strcpy(out.type, "MINUSOP");
        out.number = MINUSOP;
    }
    else if (fpeek(files->input) == '+') {
        out.actual[0] = fgetc(files->input);
        strcpy(out.type, "PLUSOP");
        out.number = PLUSOP;
    }
    else if (fpeek(files->input) == '^') {
        out.actual[0] = fgetc(files->input);
        strcpy(out.type, "EXPOP");
        out.number = EXPOP;
    }
    else if (fpeek(files->input) == '"') {
        out.actual[0] = fgetc(files->input);
        strcpy(out.type, "QUOTE");
        out.number = QUOTE;
    }
    else {
        // error
        out.actual[1] = fgetc(files->input);
        strcpy(out.type, "ERROR");
        out.number = ERROR;
    }
	strcat(linebuff,out.actual);
    return out;
}
