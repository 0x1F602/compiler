#include <stdio.h>
#include <string.h>
#include "headers/codegen.h"


int var_next;

void codegen(token * current)
{
	int var_next=0;
	char read_buffer[128];
	memset(read_buffer, 0, sizeof read_buffer);
	current=(token *)next(current);		//first token is begin
	code_begin();
	while(current->token_number!=END)
	{
		if(current->token_number==ID)
		{
			search_id(current);
			current=(token *)next(current);
			while(current->token_number!=SEMICOLON)
			{
				current=(token *)next(current);
			}
			fprintf(of_d.temp2,";\n");
		}
		else if(current->token_number==READ)
		{
			current=(token *)next(current);	//read
			current=(token *)next(current);	//(
			fprintf(of_d.temp2,"scanf(\"");
			while(current->token_number!=RPAREN)
            {
				search_id(current);
				strcat(read_buffer,current->buffer);
				fprintf(of_d.temp2,"%%s");
                current=(token *)next(current);
				if(current->token_number==COMMA)
				{
					strcat(read_buffer,",");
					fprintf(of_d.temp2," ");
					current=(token *)next(current);
				}
            }
			current=(token *)next(current);//
			fprintf(of_d.temp2,"\",%s);\n",read_buffer);
			memset(read_buffer, 0, sizeof read_buffer);
		}
		else if(current->token_number==WRITE)
		{
			current=(token *)next(current);	//write
			current=(token *)next(current);	//(
			while(current->token_number!=SEMICOLON)
            {
                current=(token *)next(current);
            }
			fprintf(of_d.temp2,";\n");
		}
		else
		{
			//error
		}
		current=(token *)next(current);
	}	//end-while
	fprintf(of_d.temp2,"}");
}


token* next(token * current)
{
    if (current->next != NULL) 
	{
        current = (token *)current->next;
    }
	return current;
}

int search_id(token * current)
{
	int i;
	for(i=0;i<var_next;i++)
	{
		if(strcmp(current->buffer,list[i].name)==0)
		{
			//variable already in list
			return i;
		}
	}
	strcpy((char*)list[var_next].name,current->buffer);
	list[var_next].value=0;
	fprintf(of_d.temp1,"int %s;\n",current->buffer);
	//fprintf(of_d.temp2,"%s=0\n",current->buffer);
	var_next++;
	return (var_next-1);	
}

void code_begin(void)
{
	fprintf(of_d.temp1,"#include <stdio.h>\n");
	fprintf(of_d.temp1,"int main()\n");
	fprintf(of_d.temp1,"{\n");
}



