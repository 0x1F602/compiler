#include <stdio.h>
#include "scanner.h"

int parser()
{
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
	
	if(strcmp(current->token_type,"BEGIN")==0)
	{
		current=(token *)current->next;
		valid=statement_list(t);
		
		
		
		if (valid==1)
		{
			if(strcmp(current->token_type,"END")==0)
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

int statement_list()
{
	int count=0;
	while(statement()==1)
	{
		count++;
		current=(token *)current->next;
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

int statement()
{
	//ID:=<expression>;
	if(strcmp(current_token->type,"ID")==0)
	{
		current=(token*)current->next;
		if(strcmp(current_token->type,"ASSIGNOP")==0)
		{
			if(expression()==1)
			{
				current=(token*)current->next;
				if(strcmp(current_token->type,"SEMICOLON")==0)
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
	else if (strcmp(current_token->type,"READ")==0)
	{
		current=(token *)current->next;
		if (strcmp(current_token->type,"LPAREN")==0)
		{
			if(id_list()==1)
			{
				current=(token *)current->next;
				if (strcmp(current_token->type,"RPAREN")==0)
				{
					current=(token *)current->next;
					if (strcmp(current_token->type,"SEMICOLON")==0)
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
	else if (strcmp(current_token->type,"WRITE")==0)
	{
		current=(token *)current->next;
		if (strcmp(current_token->type,"LPAREN")==0)
		{
			if(expr_list()==1)
			{
				current=(token *)current->next;
				if (strcmp(current_token->type,"RPAREN")==0)
				{
					current=(token *)current->next;
					if (strcmp(current_token->type,"SEMICOLON")==0)
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

int id_list()
{
	token * prev;
	current=(token *)current->next;
	if (strcmp(current_token->type,"ID")==0)
	{
		prev=current;
		current=(token *)current->next;
		while(strcmp(current_token->type,"COMMA")==1)
		{
			current=(token *)current->next;
			if (strcmp(current_token->type,"ID")==0)
			{
				prev=current;
			}
			else
			{
				return 0;
			}
		}
		current=prev;
	}
	else
	{
		return 0;
	}
}

int expr_list()
{
	
}