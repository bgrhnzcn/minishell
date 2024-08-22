/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olyetisk <olyetisk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:14:08 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/08/22 16:07:26 by olyetisk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t counter_argv(char *str)
{
	int i;
	i =0;
	while(str[i])
	{
		if (str[i] == '=')
			break;
		i++;
	}return(i);
}

void mini_unset(t_shell *shell, char **argv)
{
    int i;

    if (!shell || !argv)
        return;

    i = 1; // argv[0] genellikle komut adı olur, bu yüzden 1'den başlıyoruz
    while (argv[i])
    {
        if (!valid_identifier(argv[i]))
        {
            ft_putstr_fd("minishell: unset: '", STDERR_FILENO);
            ft_putstr_fd(argv[i], STDERR_FILENO);
            ft_putstr_fd("': not a valid identifier \n", STDERR_FILENO);
        }
        else
        {
            remove_env(shell, argv[i]);
        }
        i++;
    }
}
