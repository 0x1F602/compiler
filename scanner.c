#include "headers/scanner.h"
#include <stdio.h>
#include <string.h>
#include "headers/openfile.h"
#include <ctype.h>
token match_symbol(scanner_data * scanner_data , int a)
{
	token t;
	if (strcmp(scanner_data->token_buffer,"(")==1)
	{
		t.token_number=6;
		strcpy(t.token_type,"LPAREN");
		strcpy(t.buffer,"(");
		
	}
	else if (strcmp(scanner_data->token_buffer,")")==1)
	{
		t.token_number=7;
		strcpy(t.token_type,"RPAREN");
		strcpy(t.buffer,")");
	}	
	else if (strcmp(scanner_data->token_buffer,";")==1)
	{
		t.token_number=8;
		strcpy(t.token_type,"SEMICOLON");
		strcpy(t.buffer,";");
	}
	else if (strcmp(scanner_data->token_buffer,",")==1)
	{
		t.token_number=9;
		strcpy(t.token_type,"COMMA");
		strcpy(t.buffer,",");
	}
	else if (strcmp(scanner_data->token_buffer,":")==1)
	{
		//get next character from line buffer
		/*if(next_char=="=")
		{
			t.token_number=10;
			strcpy(t.token_type,"ASSIGNOP");
			strcpy(t.buffer,":=");
		}
		else
		{
			//place latest character back in buffer
			//lexical error
		}	
		*/
	}
	else if (strcmp(scanner_data->token_buffer,"+")==1)
	{
		t.token_number=11;
		strcpy(t.token_type,"PLUSOP");
		strcpy(t.buffer,"+");
	}
	else if (strcmp(scanner_data->token_buffer,"-")==1)
	{
		//get next character from line buffer
		/*if(next_char=="-")
		{
			//place rest of line into listing file
		}
		*/
		else
		{	
			//putchar back
			t.token_number=12;
			strcpy(t.token_type,"MINUSOP");
			strcpy(t.buffer,"-");
		}
	}
	else
	{
		//lexical error or potentially whitespace
	}
	return t;
}

void scanner(openfile_data * of_d_ptr) {
    openfile_data of_d = *of_d_ptr;
    FILE * in = of_d.input;
    FILE * listing_file = of_d.listing_file;
    token t;
    scanner_data s;
    scanner_data * s_p = &s;
    // priming the loop
    s.line_buffer[0] = '\0';
    s.token_buffer[0] = '\0';
    while (fgets(s.line_buffer, MAX_SIZE, in) != NULL) {
        t = match_code_to_token(s_p);
        //format from token and print to temp file
        //watch out for accidentally setting feof on this in there
        if (feof(in)) {
            break;
        }
    }
    return;
}

token match_code_to_token(scanner_data * s_p) {
    token t;
    
    
    // while we still have characters..
        // if starts with alpha..
        // if starts with int..
        // if starts with symbol, go there..
    		//all characters non-alpha numeric should get sent
    		//allows to catch invalid characters in symbol match too
    return t;
}
