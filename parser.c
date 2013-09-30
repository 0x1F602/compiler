#include "headers/scanner.h"

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
        advance();
		valid=statement_list();
		if (valid==1)
		{
			if(c->token_number == END)
			{
				//valid program grammar
				return 1;
			}
			else
			{
                printf("Received: %s", c->buffer);
                printf("Missing END");
				return 0;
			}
		}
		else
		{
            printf("Invalid grammar detected");
			return 0;
		}
	}
	else
	{
        printf("Missing BEGIN");
		return 0;
	}
}

int statement_list()
{
	int count=0;
	while(statement()==1)
	{
		count++;
	}
	if(count>0)
	{
		return 1;
	}
	else
	{
        printf("Must have at least 1 statement");
		return 0;
	}

}

int statement()
{
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
					//valid statement
					return 1;
				}
				else
				{
                    printf("Missing semicolon");
					return 0;
				}
			}
			else
			{
				//keep increment pointer until after ;?
				printf("Invalid expression");
				return 0;
			}
		}
		else
		{
			//keep increment pointer until after ;?
			printf("Missing assignment operator");
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
						//valid statement
                        advance();
						return 1;
					}
					else
					{
                        printf("Missing semicolon");
						return 0;
					}
				}
				else
				{
                    printf("Missing right parentheses");
					return 0;
				}
			}
			else
			{
                printf("Expected at least one identifier");
				return 0;
			}
		}
		else
		{
            printf("Expected left parentheses");
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
							//valid statement
							advance();
							return 1;
						}
						else
						{
                            printf("Missing semicolon");
							return 0;
						}
				}
			}
			else
			{
                printf("Invalid expression in list");
				return 0;
			}
		}
		else
		{
            printf("Expected left parentheses");
			return 0;
		}

	}
	//else not a statement
	else
	{
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
                printf("Expected another identifier");
				return 0;
			}
            advance();
		}
	    c=prev;
		return 1;
	}
	else
	{
        printf("Expected at least one identifier");
		return 0;
	}
}

int expr_list()
{
    int sentinel = 1;
    if (expression())
    {
        token * pr;
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
				printf("Expected expression after comma");
				break;
			}
		}
		previous();
    }
	else
	{
		sentinel=0;
	    printf("Expected expression or expression list");
	}
    return sentinel;
}

int expression() {
    int sentinel = 0; // fail by default
    if (primary()) {
        while (addop()) {
            if (primary()) {
                sentinel = 1;
            }
            else {
                sentinel = 0;
            }
        }
        sentinel = 1;
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
		printf("Expecting primary");
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
//		printf("Expecting ADDOP);
	}
	return sentinel;
}

