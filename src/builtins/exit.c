/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:35:55 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/08/20 17:27:48 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	str_isdigit(char *str)
{
	int		i;
	char	*temp;

	temp = ft_strtrim(str, " \t");
	if ((temp[0] == '-' || temp[0] == '+') && ft_strlen(temp) > 1)
		i = 1;
	else
		i = 0;
	while (temp[i])
	{
		if (!ft_isdigit(temp[i]))
			return (free(temp), 1);
		i++;
	}
	return (free(temp), 0);
}

void	mini_exit(t_shell *shell, t_cmd *cmd)
{
	int	exit_status;

	exit_status = 0;
	if (shell->env)
		ft_free_str_arr(shell->env);
	if (shell->input)
		free(shell->input);
	if (cmd->argv[1])
	{
		if (cmd->argv[2] != NULL)
		{
			ft_putstr_fd("bash: exit: too many arguments\n", STDERR_FILENO);
			shell->status = 1;
			return ;
		}
		if (str_isdigit(cmd->argv[1]))
		{
			ft_putstr_fd("bash: exit: ", STDERR_FILENO);
			ft_putstr_fd(cmd->argv[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			exit(2);
		}
		exit_status = ft_atoi(cmd->argv[1]);
	}
	printf("exit\n");
	exit(exit_status);
}
