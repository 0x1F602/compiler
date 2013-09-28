#include "headers/scanner.h"

int parser(token * c)
{
	if(program(c))
	{
		return 1;	//program syntax valid
	}
	else
	{
		return 0;	//program syntax invalid
	}
	
}

int program(token * c)
{
	int valid;
	
	if(c->token_number == BEGIN)
	{
		c=(token *)c->next;
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
				return 0;
			}
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}

int statement_list(token * c)
{
	int count=0;
	while(statement(c)==1)
	{
		count++;
		c=(token *)c->next;
	}
	if(count>0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
	
}

int statement(token * c)
{
	//ID:=<expression>;
	if(c->token_number == ID)
	{
		c=(token*)c->next;
		if(c->token_number == ASSIGNOP)
		{
			if(expression(c)==1)
			{
				c=(token*)c->next;
				if(c->token_number == SEMICOLON)
				{
					//valid statement
					return 1;
				}
				else
				{
					return 0;
				}
			}
			else
			{
				//keep increment pointer until after ;?
				return 0;
			}
		}
		else
		{
			//keep increment pointer until after ;?
			return 0;
		}
	}
	//READ(<id_list>);
	else if (c->token_number == READ)
	{
		c=(token *)c->next;
		if (c->token_number == LPAREN)
		{
			if(id_list(c)==1)
			{
				c=(token *)c->next;
				if (c->token_number == RPAREN)
				{
					c=(token *)c->next;
					if (c->token_number == SEMICOLON)
					{
						//valid statement
						return 1;
					}
					else
					{
						return 0;
					}
				}
				else
				{
					return 0;
				}
			}
			else
			{
				return 0;
			}
		}
		else
		{
			return 0;
		}
	}
	//WRITE(<expr_list>);
	else if (c->token_number == WRITE)
	{
		c=(token *)c->next;
		if (c->token_number == LPAREN)
		{
			if(expr_list(c)==1)
			{
				c=(token *)c->next;
				if (c->token_number == RPAREN)
				{
					c=(token *)c->next;
					if (c->token_number == SEMICOLON)
						{
							//valid statement
							return 1;
						}
						else
						{
							return 0;
						}
				}
			}
			else
			{
				return 0;
			}
		}
		else
		{
			return 0;
		}
		
	}
	//else not a statement
	else
	{
		return 0;
	}
}

int id_list(token * c)
{
	token * prev;
	c=(token *)c->next;
	if (c->token_number == ID)
	{
		prev=c;
		c=(token *)c->next;
		while(c->token_number == COMMA)
		{
			c=(token *)c->next;
			if (c->token_number == ID)
			{
				prev=c;
			}
			else
			{
				return 0;
			}
		}
		c=prev;
	}
	else
	{
		return 0;
	}
}

int expr_list(token * c)
{
	
}

int expression(token * c) {

}
