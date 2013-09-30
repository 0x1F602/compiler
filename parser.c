#include "headers/scanner.h"

token * c;

int advance() {
    int sentinel = 0;
    if (c->next != NULL) {
        sentinel = 1;
        c = (token *)c->next;
    }
    return sentinel;
}

int parser(token * cu)
{
    c = cu;
	if(program(c))
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
		valid=statement_list(c);
		if (valid==1)
		{
			if(c->token_number == END)
			{
				//valid program grammar
				return 1;
			}
			else
			{
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
	while(statement(c)==1)
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
			if(expression(c))
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
			if(id_list(c)==1)
			{
                advance();
				if (c->token_number == RPAREN)
				{
                    advance();
					if (c->token_number == SEMICOLON)
					{
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
                    printf("Missing right parentheses");
					return 0;
				}
			}
			else
			{
                printf("Expected identifier");
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
			if(expr_list(c)==1)
			{
                advance();
				if (c->token_number == RPAREN)
				{
                    advance();
					if (c->token_number == SEMICOLON)
						{
							//valid statement
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
	token * prev;
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
                printf("Expected identifier");
				return 0;
			}
		}
		c=prev;
	}
	else
	{
        printf("Expected identifier");
		return 0;
	}
}

int expr_list()
{
    int sentinel = 1;
    if (expression(c)
    {
		advance();
		while (c->token_number==COMMA)
		{
			advance();
			if expression(c)
			{
				advance();
			}
			else
			{
				sentinel=0;
				printf("Expected expression");
				break;
			}
		}
    }
	else
	{
		sentinel=0;
	}
}

int expression() {
    int sentinel = 0; // fail by default
    if (primary(c)) {
        advance();
        if (c->token_number == PLUSOP || c->token_number == MINUSOP) {
            advance();
            if (primary(c)) {
                advance();
                sentinel = 1;
            }
        }
        else {
            sentinel = 1;
        }
    }
    return sentinel;
}

int primary() {
    int sentinel = 0;
    if (c->token_number == INTLITERAL || c->token_number == ID) {
        sentinel = 1;
    }
    else if (c->token_number == LPAREN) {
        advance();
        if (expression(c)) {
            //advance();
            if (c->token_number == RPAREN) {
                sentinel = 1;
            }
        }
    }
    return sentinel;
}
