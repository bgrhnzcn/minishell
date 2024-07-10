#include "minishell.h"

void double_quote(t_token *tokens, char **env)
{
	t_token *temp;

	temp = tokens;
	while (temp != NULL)
	{
		if(temp->type == DOUBLE_QUOTE)
		{
			while(temp != tokens)
			{
				if(temp->type == DOLLAR)
				{
					printf("%s\n", get_env(env, temp->text + 1));
					remove_token(tokens, temp);
				}
				else
					temp->type = WORD;
				temp = temp->prev;
			}
		}
		temp = temp->next;
	}
	ft_putstr_fd("Unclosed Quotes.", STDERR_FILENO);
}

void sıngle_quote(t_token *tokens)
{
	t_token *temp;

	temp = tokens;
	while (temp != NULL)
	{
		if(temp->type == QUOTE)
		{
			while(temp != tokens)
			{
				temp->type = WORD;
				temp = temp->prev;
			}
		}
		temp = temp->next;
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
		else if (temp->type == QUOTE)
			sıngle_quote(temp);
		temp = temp->next;
	}
}
