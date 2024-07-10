#include "minishell.h"

void double_quote(t_token *tokens, char **env)
{
	t_token *res;

	res = tokens;
	while (res != NULL)
	{
		if(res->type == DOUBLE_QUOTE)
		{
			while(res != tokens)
			{
				if(res->type == DOLLAR)
					get_env(env,res->text);
				res->type = WORD;
				res = res->prev;
			}
		}
		res = res->next;
	}
}
void sıngle_quote(t_token *tokens)
{
	t_token *res;

	res = tokens;
	while (res != NULL)
	{
		if(res->type == QUOTE)
		{
			while(res != tokens)
			{
				res->type = WORD;
				res = res->prev;
			}
		}
		res = res->next;
	}
}
void check_quotes(t_token *token_list,char **env)
{
	t_token	*temp;

	temp = token_list;
	while(temp != NULL)
	{
		if (temp->type == DOUBLE_QUOTE)
			double_quote(temp,env);
		if (temp->type == QUOTE)
			sıngle_quote(temp);
		temp = temp->next;
	}
}
