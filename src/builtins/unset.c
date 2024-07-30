/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:14:08 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/07/28 13:29:17 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_unset(t_shell *shell, char **argv)
{
    int i = 0;
    int j = 0;
    int env_size = 0;
    int found = 0;

    if (!shell || !argv || !argv[1])
        return;
	
    while (shell->env[env_size])
        env_size++;
	
    char **new_env = malloc(sizeof(char *) * env_size);
    if (!new_env)
        return;

    //envyi yeni yere kopyala
    while (i < env_size)
    {
        if (strcmp(shell->env[i], argv[1]) == 0)
        {
            free(shell->env[i]); //silineni freeleyelim
            found = 1; // Kaldırılacak değişkeni bulunca foundı 1 ledik 
        }
        else
        {
            new_env[j] = shell->env[i];
            j++;
        }
        i++;
    }
    
    new_env[j] = NULL; 

    // istediğimi bulursam eski env listesini freeledim
    if (found)
        free(shell->env);

    shell->env = new_env;

    // Yeni envyi yazdım
    i = 0;
    while (shell->env[i])
    {
        printf("envler: %s\n", shell->env[i]);
        i++;
    }
}