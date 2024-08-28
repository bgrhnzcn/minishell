/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: buozcan <buozcan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 20:20:27 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/08/27 15:00:10 by buozcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include "structs.h"

void		*ft_bzero(void *s, size_t n);
char		*ft_strdup(const char *s);
t_bool		ft_isalnum(int c);
t_bool		ft_isalpha(int c);
t_bool		ft_isascii(int c);
t_bool		ft_isdigit(int c);
t_bool		ft_isprint(int c);
/**
 * @brief 
 * Move the memeory specified with parameters.
 * Usefull when moving large areas for a small amount.
 * @param dst Destination adress.
 * @param src Source adress.
 * @param len Size of moving area as byte.
 * @return Returns a pointer to dest.
 */
void		*ft_memmove(void *dst, const void *src, size_t len);
/**
 * @brief 
 * Scans the n bytes of the area pointed by s to find c.
 * Checks only single byte.
 * @param s Start point for check.
 * @param c Scanned byte.
 * @param n Size of the scan area as byte.
 * @return Returns the adress of found c or NULL if can't find.
 */
void		*ft_memchr(const void *s, int c, size_t n);
/**
 * @brief 
 * 
 * @param s1 
 * @param s2 
 * @param n 
 * @return int 
 */
int			ft_memcmp(const void *s1, const void *s2, size_t n);
/**
 * @brief 
 * Copies n bytes of data from src to dst.
 * @param dst Destination adress.
 * @param src Source adress.
 * @param n Size of copying area as byte.
 * @return Returns dst.
 */
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memset(void *b, int c, size_t len);
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int nb, int fd);
void		ft_putstr_fd(char *s, int fd);
char		*ft_strchr(const char *s, int c);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlen(const char *s);
t_bool		ft_strequ(const char *s1, const char *s2);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strrchr(const char *s, int c);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_tolower(int c);
int			ft_toupper(int c);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
int			ft_atoi(const char *str);
char		*ft_itoa(int n);
char		**ft_split(char const *s, char c);

//----------------------Memory-----------------------

void		*ft_calloc(size_t nmemb, size_t size);

//-----------------------Lists------------------------

/*Initializes new list struct in heap and set content to provided one.
If you provide heap-allocated content,
make sure all other contents are heap-allocated too.*/
t_list		*ft_lstnew(void *content);
/*Returns the last element of the list.
If list is empty, returns NULL.*/
t_list		*ft_lstlast(t_list *lst);
/*Returns size of the list.*/
size_t		ft_lstsize(t_list *lst);
/*Adds provided element to end of the list.*/
void		ft_lstadd_back(t_list **lst, t_list *new);
/*Adds provided element to start of the list.*/
void		ft_lstadd_front(t_list **lst, t_list *new);
/*Swaps the given element's of the list if both of the elements exist.
This function swaps only contents.*/
void		ft_lstdelone(t_list *lst, void (*del)(void *));
/*Applies the (del) function to every content in the list and free the lists.
If you have stack-allocated contents, use NULL, otherwise use free
to prevent memory leaks, or your own specific implementation.*/
void		ft_lstclear(t_list **lst, void (*del)(void *));
/*Iterates through the list and
applies the (f) function to every element's content.*/
void		ft_lstiter(t_list *lst, void (*f)(void *));
/*Iterates through copy of the list and
applies the (f) function to the every element's content.*/
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
/*Sorts the list with Bubble-Sort. Define a (comp) function before use.
The (comp) function is the condition for swap and
must be defined uniquely for the type of content in the list.
If you use condition con1 > con2, it will sort to increasing order.*/

/*Gets numbers of strings inside of string arrays.
String arrays must be null-ended.*/
size_t		ft_strarrlen(char **arr);
//Free all the arrays inside float array.
void		ft_free_str_arr(char **str_arr);
/*Hexadecimal version of atoi().
It works both of uppercase and lowercase versions.*/

#endif