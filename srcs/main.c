/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:16:19 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/05/10 00:47:48 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define ALLOCATED

int	main(int argc, char **argv)
{
	(void)argc;
	//char	*cmd;
	//char	*path;
	//char	*temp;
	//char	*prompt;
	//char	*splitted;
	//HISTORY_STATE state;
	if (argc <= 1)
		exit(EXIT_FAILURE);
	char	**text = ft_split(argv[1], ' ');
	size_t	max = ft_strarrlen(text);
	t_hash_table *test_table = ft_table_new(10, type_str, type_int, ft_hash);
	if (test_table == NULL)
		exit(EXIT_FAILURE);
	for (size_t i = 0; i < max; i++)
	{
		ft_table_insert(test_table, text[i], &(int){i});
	}
	for (size_t i = 0; i < test_table->table_size; i++)
		printf("	%zu	--------	%s --- %d\n", i, (char *)test_table->table[i].key, *(int *)test_table->table[i].value);
	
	//printf("sizeof: %ld\n",sizeof(t_vector));
	//int	holder;
	//int* vector_int = ft_vector_new(sizeof(int));
	//for (int i = 0; i < 513; i++)
	//{
	//	ft_vector_append(&vector_int, &i);
	//	t_vector *head = ft_vector_head(vector_int);
	//	printf("----\nres: %d\n-----\n", vector_int[i]);
	//	printf("buff_size: %ld\n", head->buffer_size);
	//
	//ft_vector_insert(&vector_int, &(int){-54}, 53);
	//for (size_t i = 0; i < ft_vector_len(vector_int); i++)
	//	printf("Index(%ld): %d\n", i, vector_int[i]);
	//ft_vector_remove(&vector_int, NULL, 53);
	//for (size_t i = 0; i < ft_vector_len(vector_int); i++)
	//	printf("Index(%ld): %d\n", i, vector_int[i]);
	//for (int i = ft_vector_len(vector_int); i > 0; i--)
	//{
	//	ft_vector_pop(&vector_int, &holder);
	//	t_vector *head = ft_vector_head(vector_int);
	//	printf("----\nres: %d\n-----\n", holder);
	//	printf("buff_size: %ld\n", head->buffer_size);
	//}
	//ft_vector_free(vector_int);
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
