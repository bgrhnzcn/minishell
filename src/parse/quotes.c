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
				{
					printf("%s\n", get_env(env, res->text + 1));
					remove_token(tokens, res);
				}
				else
					res->type = WORD;
				res = res->prev;
			}
		}
		res = res->next;
	}
	ft_putstr_fd("Unclosed Quotes.", STDERR_FILENO);
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
	ft_putstr_fd("Unclosed Quotes.", STDERR_FILENO);
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
