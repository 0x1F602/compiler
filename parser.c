#include "headers/scanner.h"
#include <string.h>
#include <stdio.h>

token * c;
token * prev;

int advance() {
    int sentinel = 0;
	prev=c;		//sets the prev token to the current one before advancing
    if (c->next != NULL) {
        sentinel = 1;
        c = (token *)c->next;
    }
    return sentinel;
}

//this will allow us to go back to the prev token if we need to
int previous()
{
	c=prev;
}

int parser(token * cu)
{
    c = cu;
	if(program())
	{
		return 1;	//program syntax valid
	}
	else
	{
		return 0;	//program syntax invalid
	}

}

int program()
{
	int valid;

	if(c->token_number == BEGIN)
	{
		fprintf(of_d.temp1, "Token number %d\tToken type %s\t\tActual %s\n", c->token_number, c->token_type, c->buffer);
                fprintf(of_d.temp1,"\nPROGRAM LINE: BEGIN\n\n\n");
                fprintf(of_d.listing_file, "1:\t%s\n", c->buffer);
        	advance();
		valid=statement_list();
		if (valid > 0)
		{
			if(c->token_number == END)
			{
				//valid program grammar
				fprintf(of_d.temp1, "Token number %d\tToken type %s\t\tActual %s\n", c->token_number, c->token_type, c->buffer);
                		fprintf(of_d.temp1,"\nPROGRAM LINE: END\n\n\n");
                fprintf(of_d.listing_file, "%d:\t%s\n", valid, c->buffer);
				return 1;
			}
			else
			{
                		printf("Missing END\n");
				return 0;
			}
		}
		else
		{
            		printf("Invalid grammar detected\n");
			return 0;
		}
	}
	else
	{
        	printf("Missing BEGIN\n");
		return 0;
	}
}

int statement_list()
{
	int count=0;
	while(statement(count + 2)==1) // + 1, for count = 0. + 2, to account for begin
	{
		count++;
	}
	if(count<=0)
	{
        	printf("Must have at least 1 statement\n");
	}
	return count;

}

int statement(int count)
{
char buffer[200];
token * begin;
begin=c;
memset(buffer, 0, sizeof buffer);

	//ID:=<expression>;
	if(c->token_number == ID)
	{
        	advance();
		if(c->token_number == ASSIGNOP)
		{
            		advance();
			if(expression())
			{
                		//advance();
				if(c->token_number == SEMICOLON)
				{
					advance();
                                        while(c!=begin)
                                        {
                                            fprintf(of_d.temp1, "Token number %d\tToken type %s\t\tActual %s\n", begin->token_number, begin->token_type, begin->buffer);
                                            sprintf(buffer+strlen(buffer),"%s",begin->buffer);
                                            begin=(token *) begin->next;
                                        }
                                        fprintf(of_d.temp1,"\nPROGRAM LINE: %s\n\n\n",buffer);
                                        fprintf(of_d.listing_file, "%d:\t%s\n", count, buffer);
                                        //valid statement
                                        return 1;
				}
				else
				{
                        printf("Missing semicolon\n");
					return 0;
				}
			}
			else
			{
				//keep increment pointer until after ;?
				printf("Invalid expression\n");
				return 0;
			}
		}
		else
		{
			//keep increment pointer until after ;?
			printf("Missing assignment operator\n");
			return 0;
		}
	}
	//READ(<id_list>);
	else if (c->token_number == READ)
	{
        	advance();
		if (c->token_number == LPAREN)
		{
			if(id_list()==1)
			{
                		advance();
				if (c->token_number == RPAREN)
				{
                    			advance();
					if (c->token_number == SEMICOLON)
					{
					    advance();
                                            while(c!=begin)
                                            {
                                                fprintf(of_d.temp1, "Token number %d\tToken type %s\t\tActual %s\n", begin->token_number, begin->token_type, begin->buffer);
                                                sprintf(buffer+strlen(buffer),"%s",begin->buffer);
                                                begin=(token *) begin->next;
                                            }
                                            fprintf(of_d.temp1,"\nPROGRAM LINE: %s\n\n\n",buffer);
                                            //valid statement
                                            return 1;
					}
					else
					{
                        		    printf("Missing semicolon\n");
				            return 0;
					}
				}
				else
				{
                    			printf("Missing right parentheses\n");
					return 0;
				}
			}
			else
			{
               			 printf("Expected at least one identifier\n");
				return 0;
			}
		}
		else
		{
            		printf("Expected left parentheses\n");
			return 0;
		}
	}
	//WRITE(<expr_list>);
	else if (c->token_number == WRITE)
	{
		advance();
		if (c->token_number == LPAREN)
		{
            		advance();
			if(expr_list()==1)
			{
				if (c->token_number == RPAREN)
				{
                    	   		advance();
					if (c->token_number == SEMICOLON)
					 {
				             advance();
                                             while(c!=begin)
                                       	     {
                                                 fprintf(of_d.temp1, "Token number %d\tToken type %s\t\tActual %s\n", begin->token_number, begin->token_type, begin->buffer);
                                                 sprintf(buffer+strlen(buffer),"%s",begin->buffer);
                                                 begin=(token *) begin->next;
                                             }
                                        fprintf(of_d.temp1,"\nPROGRAM LINE: %s\n\n\n",buffer);
                                        //valid statement
                                        return 1;
					}
					else
					{
                            		    printf("Missing semicolon\n");
					    return 0;
					}
				}
			}
			else
			{
                		printf("Invalid expression in list\n");
				return 0;
			}
		}
		else
		{
           		 printf("Expected left parentheses\n");
			return 0;
		}

	}
	//else not a statement
	else
	{
		//printf("Not a statement\n");
		return 0;
	}
}

int id_list()
{
    advance();
	if (c->token_number == ID)
	{
		prev=c;
        	advance();
		while(c->token_number == COMMA)
		{
            		advance();
			if (c->token_number == ID)
			{
				prev=c;
			}
			else
			{
                		printf("Expected another identifier\n");
				return 0;
			}
            	advance();
		}
	    c=prev;
	    return 1;
	}
	else
	{
        	printf("Expected at least one identifier\n");
		return 0;
	}
}

int expr_list()
{
    int sentinel = 1;
    if (expression())
    {
        //token * pr;
	    	while (c->token_number==COMMA)
		{
			advance();
			if (expression())
			{
				//advance();
			}
			else
			{
				sentinel=0;
				printf("Expected expression after comma\n");
				break;
			}
			//advance();
		}
		//previous();
    }
	else
	{
		sentinel=0;
	    printf("Expected expression or expression list\n");
	}
    return sentinel;
}

int expression() {
    int sentinel = 0; // fail by default
    if (primary()) {
	sentinel = 1;
        while (addop()) {
            if (primary()) {
                sentinel = 1;
            }
            else {
		printf("Expected Primary\n");
                sentinel = 0;
            }
        }
    }
    else
    {
	printf("Expecting primary\n");
    }
    return sentinel;
}

int primary() {
    int sentinel = 0;
    if (c->token_number == INTLITERAL) {
        sentinel = 1;
    }
    else if (c->token_number == LPAREN) {
        advance();
        if (expression()) {
            if (c->token_number == RPAREN) {
                sentinel = 1;
            }
        }
    }
	else if (c->token_number== ID)
	{
		sentinel=1;
	}
	else
	{
		printf("Expecting primary\n");
	}
    advance();
    return sentinel;
}

int addop()
{
	int sentinel = 0;
	if(c->token_number==PLUSOP)
	{
	    sentinel=1;
	    advance();
	}
	else if (c->token_number==MINUSOP)
	{
	    sentinel=1;
	    advance();
	}
	else
	{
//		printf("Expecting ADDOP");
	}
	return sentinel;
}

