/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:16:19 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/04/30 02:01:31 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define ALLOCATED

int	main(int argc, char **argv)
{
	(void)argv;
	(void)argc;
	//char	*cmd;
	//char	*path;
	//char	*temp;
	//char	*prompt;
	//char	*splitted;
	//HISTORY_STATE state;

	int	holder;
	int* vector_int = ft_vector_new(sizeof(int));
	for (int i = 0; i < 100; i++)
	{
		ft_vector_append(&vector_int, &i);
		t_vector *head = ft_vector_head(vector_int);
		printf("----\nres: %d\n-----\n", vector_int[i]);
		printf("type: %ld\n", head->type_size);
		printf("buff_size: %ld\n", head->buffer_size);
		printf("lenght: %ld\n", head->lenght);
		printf("buffer: %p\n", head->buffer);
	}
	int	ins = -5461;
	ft_vector_insert(&vector_int, &ins, 53);
	for (int i = ft_vector_len(vector_int); i > 0; i--)
	{
		ft_vector_pop(vector_int, &holder);
		printf("Index(%d): %d\n", i, holder);
	}
	ft_vector_free(vector_int);
	//cmd = malloc(0);
	//if (cmd == NULL)
	//	exit(EXIT_FAILURE);
	////state.length = 0;
	//rl_clear_history();
	//path = NULL;
	//while (ft_strncmp(cmd, "exit", 5))
	//{
	//	free(cmd);
	//	path = getcwd(NULL, 0);
	//	temp = ft_strjoin("root@localhost:~", path);
	//	prompt = ft_strjoin(temp, "$");
	//	cmd = readline(prompt);
	//	add_history(cmd);
	//	printf("%s\n", cmd);
	//	splitted = strtok(cmd, " 	");
	//	printf("%s\n", splitted);
	//	printf("%s\n", cmd);
	//	free(path);
	//	free(temp);
	//	free(prompt);
	//}
	//free(cmd);
	//exit(EXIT_SUCCESS);
}
