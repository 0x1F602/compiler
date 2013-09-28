#include <stdio.h>
#include "scanner.h"

int parser(*token head)
{
	if(program(*head))
	{
		return 1;	//program syntax valid
	}
	else
	{
		return 0;	//program syntax invalid
	}
	
}

int program(*token current)
{
	int valid;
	
	if(strcmp(current->token_type,"BEGIN")==0)
	{
		valid=statement_list((token*)current->next);
		
		
		
		//not sure if current is changed in other functions whether it will change here too...
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

int statement_list(*token current)
{
	int count=0;
	while(statement(*current)==1)
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

int statement(*token current)
{
	
}
