/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrhnzcn <bgrhnzcn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 20:20:27 by bgrhnzcn          #+#    #+#             */
/*   Updated: 2024/05/11 16:30:21 by bgrhnzcn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# ifdef USE_MATH
#  include <math.h>
# endif
# include "structs.h"

# define PI		3.14159265358979323846

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
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strrchr(const char *s, int c);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_tolower(int c);
int			ft_toupper(int c);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
t_bool		ft_strcheck(char *str, t_bool (*cond)(int));
int			ft_atoi(const char *str);
int			ft_atoi_hex(const char *str);
char		*ft_itoa(int n);
char		**ft_split(char const *s, char c);

//----------------------Memory-----------------------

void		*ft_malloc(size_t nmemb, size_t size);
void		*ft_calloc(size_t nmemb, size_t size);

//-----------------------Vectors----------------------

typedef int*			t_int_vec;
typedef char*			t_char_vec;
typedef long*			t_long_vec;
typedef unsigned char*	t_uchar_vec;
typedef unsigned int*	t_uint_vec;
typedef unsigned long*	t_ulong_vec;

/**
 * @brief
 * Returns dynamic array implemantation.
 * You can access elements like standart array.
 * @param type_size_b Size of stored type in bytes.
 * @return Pointer to buffer.
 */
void		*ft_vector_new(size_t type_size_b);
/**
 * @brief 
 * Free allocated memory for vector.
 * @param vector Pointer to buffer.
 */
void		ft_vector_free(void *vector);
/**
 * @brief 
 * Increases the capacity of the vector with given amount.
 * Don't use if it's not important.
 * @param vector_adrr Adress of pointer to buffer.
 * @param head Head of vector.
 * @param size Growing size as a byte.
 * @return Returns newly allocated version of vector head.
 */
t_vector	*ft_vector_grow(void *vector_adrr, t_vector *head, size_t size);
/**
 * @brief 
 * Decrease the capacity of the vector with given amount.
 * Don't use if it's not important.
 * @param vector_adrr Adress of pointer to buffer.
 * @param head Head of vector.
 * @param size Shrinking size as a byte.
 * @return Returns newly allocated version of vector head.
 */
t_vector	*ft_vector_shrink(void *vector_adrr, t_vector *head, size_t size);
/**
 * @brief 
 * Gets head of a vector.
 * @param vector Vector buffer.
 * @return Returns pointer to head of vector.
 */
t_vector	*ft_vector_head(void *vector);
/**
 * @brief 
 * Gets current lenght of a vector.
 * @param vector Vector buffer.
 * @return Returns lenght of a vector as an existing element count.
 */
size_t		ft_vector_len(void *vector);
/**
 * @brief 
 * Add new element to end of the vector.
 * If necessery growe the vector.
 * @param vector_adrr Adress of pointer to buffer.
 * @param val The value at the address is copied to the vector.
 * @return Returns the new lenght of vector after new element.
 */
size_t		ft_vector_append(void *vector_adrr, void *val);
/**
 * @brief 
 * Add new element to given index of the vector.
 * It moves the elements after the index by one.
 * If necessery growe the vector.
 * @param vector_adrr Adress of pointer to buffer.
 * @param val The value at the address is copied to the vector.
 * @param index Index to operate.
 * @return Returns the new size of the vector after new element.
 */
size_t		ft_vector_insert(void *vector_adrr, void *val, const size_t index);
/**
 * @brief 
 * Removes last element of the vector.
 * If necessery shrinks the vector.
 * @param vector_adrr Adress of pointer to buffer.
 * @param out The adress of output value. If not need then pass NULL.
 * @return Returns the new size of the vector after element removed.
 */
size_t		ft_vector_pop(void *vector_adrr, void *out);
/**
 * @brief 
 * Removes the element of given index.
 * It moves the elements after the index by one.
 * If necessery shrinks the vector.
 * @param vector_adrr Adress of pointer to buffer.
 * @param out The adress of output value. If not need then pass NULL.
 * @param index Index to operate.
 * @return Returns the new size of the vector after element removed.
 */
size_t		ft_vector_remove(void *vector_adrr, void *out, const size_t index);
/**
 * @brief 
 * Removes all the element in the vector.
 * Doesn't free vectors itself.
 * @param vector_adrr Adress of pointer to buffer.
 */
void		ft_vector_iter(void *vector, void (*f)());
void		ft_vector_clear(void *vector_adrr);

//-----------------------Hash-------------------------

size_t			ft_hash(void *data, size_t size);

t_hash_table	*ft_table_new(size_t table_size, t_types key_type,
				t_types value_type, size_t (hash)(void *data, size_t size));

void			ft_table_insert(t_hash_table *table, void *key, void *value);

void			ft_table_print(t_hash_table *table);

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
void		ft_lstswap(t_list *first, t_list *second);
/*Applies the (del) function to given element's content and free the element.
If you have stack-allocated contents, use NULL, otherwise use free
to prevent memory leaks, or your own specific implementation.*/
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
void		ft_lstsort(t_list **list, t_bool (*comp)(void *con1, void *con2));
/*Returns true if lst is sorted. Define a (comp) function before use.
The (comp) function is the condition for sorting and must be defined
uniquely for the type of data of content in the list.
If you use condition con1 > con2, it will check for increasing order.*/
t_bool		ft_lstissorted(t_list *lst, t_bool (*comp)(void *con1, void *con2));

//------------------------Stacks----------------------------

/*Initializes new stack struct in heap.
Starting value of count is 0 and values list are NULL.
Don't try to access before some contents are pushed.*/
t_stack		*ft_stacknew(void);
/*Pushes the provided content to stack.
If you push heap-allocated content,
make sure all other contents are heap-allocated too.*/
void		ft_stackpush(t_stack *stack, void *content);
/*Return the content address from the top of the stack and removes it.
If stack is empty, returns NULL and write error message to STDERR.*/
void		*ft_stackpop(t_stack *stack);
/*Applies the (del) function to every member of stack and free stacks itself.
If you have stack-allocated contents, use NULL, otherwise use free
to prevent memory leaks, or your own specific implementation.*/
void		ft_stackclear(t_stack *stack, void (*del)(void *));

/*Gets numbers of strings inside of string arrays.
String arrays must be null-ended.*/
size_t		ft_strarrlen(char **arr);
//Free all the arrays inside double array.
void		ft_free_str_arr(char **str_arr);
/*Hexadecimal version of atoi().
It works both of uppercase and lowercase versions.*/
int			ft_atoi_hex(const char *str);
//Degree to Radian conversions.
double		ft_deg_to_rad(double deg);
//Radian to Degree conversions.
double		ft_rad_to_deg(double rad);

//----------------------------- Mapping ----------------------------------

//Initializes map from given values to use inside map function.
t_map		ft_map_init(double min_i, double max_i, double min_o, double max_o);
/*Gives normalized value (0 to 1 range value)
of given value inside specified range.*/
double		ft_normalize(double val, double min, double max);
/*Gets normalized value (0 to 1 range value)
and gives the value corresponding on specified range.*/
double		ft_lerp(double val, double min, double max);
//This function uses t_map to convert value from one range to another.
double		ft_map(double val, t_map map);

t_vec2		ft_vec2_set(double x, double y);
t_vec2		ft_vec2_sub(t_vec2	vec1, t_vec2 vec2);
t_vec2		ft_vec2_add(t_vec2 vec1, t_vec2 vec2);
t_vec2		ft_vec2_mul(t_vec2 vec, double mul);
t_vec2		ft_vec2_div(t_vec2 vec, double div);

t_vec3		ft_vec3_set(double x, double y, double z);
t_vec3		ft_vec3_sub(t_vec3	vec1, t_vec3 vec2);
t_vec3		ft_vec3_add(t_vec3 vec1, t_vec3 vec2);
t_vec3		ft_vec3_mul(t_vec3 vec, double mul);
t_vec3		ft_vec3_div(t_vec3 vec, double div);

t_vec4		ft_vec4_set(double x, double y, double z, double w);
t_vec4		ft_vec4_add(t_vec4 vec1, t_vec4 vec2);
t_vec4		ft_vec4_sub(t_vec4 vec1, t_vec4 vec2);
t_vec4		ft_vec4_mul(t_vec4 vec, double mul);
t_vec4		ft_vec4_div(t_vec4 vec, double div);

t_vec2		ft_vec2_norm(t_vec2 vec);

double		ft_vec2_dot(t_vec2 vec1, t_vec2 vec2);
double		ft_get_dist2(t_vec2 point1, t_vec2 point);
double		ft_vec2_mag(t_vec2 vec);

t_vec3		ft_vec3_norm(t_vec3 vec);
t_vec3		ft_vec3_cross(t_vec3 vec1, t_vec3 vec2);

double		ft_vec3_dot(t_vec3 vec1, t_vec3 vec2);
double		ft_get_dist3(t_vec3 point1, t_vec3 point);
double		ft_vec3_mag(t_vec3 vec);

t_vec4		ft_vec4_norm(t_vec4 vec);

double		ft_vec4_dot(t_vec4 vec1, t_vec4 vec2);
double		ft_vec4_mag(t_vec4 vec);

//------------------------------ Basic Matrix Functions ---------------------

//3D matrix row setter.
void		ft_set_row3(t_mtx3 *mtx, int row_val, t_vec3 row);
//Get values in row of 3D matrix.
t_vec3		ft_get_row3(t_mtx3 mtx, int row_val);
//3D matrix 3D vector multiplication.
t_vec3		ft_mtx_vec_mul3(t_mtx3 mtx, t_vec3 vec);
//3D matrix 3D matrix multiplication.
t_mtx3		ft_mtx_mtx_mul3(t_mtx3 mtx1, t_mtx3 mtx2);

//4D matrix row setter.
void		ft_set_row4(t_mtx4 *mtx, int row_val, t_vec4 row);
//Get values in row of 4D matrix.
t_vec4		ft_get_row4(t_mtx4 mtx, int row_val);
//4D matrix 4D vector multiplication.
t_vec4		ft_mtx_vec_mul4(t_mtx4 mtx, t_vec4 vec);
//4D matrix 4D matrix multiplication.
t_mtx4		ft_mtx_mtx_mul4(t_mtx4 mtx1, t_mtx4 mtx2);

//3D vector to 4D vector conversion.
t_vec4		ft_vec3_to_vec4(t_vec3 vec3, double w);
//4D vector to 3D vector conversion.
t_vec3		ft_vec4_to_vec3(t_vec4 vec4);

//------------------------- Color Functions ---------------------------

/*4 channel int value color setter.
a = Alpha, r = Red, g = Green, b = Blue*/
t_color		ft_set_color(__uint8_t a, __uint8_t r, __uint8_t g, __uint8_t b);
//Returns gradient value from given normalized value.
t_color		ft_get_gradient_val(t_color from, t_color to, double value);
//Gradient initializer.
t_gradient	ft_set_gradient(t_color from, t_color to);
//Gradient inverter.
t_gradient	ft_inv_gradient(t_gradient in);

void		ft_put_pixel(t_img *img, int x, int y, t_color color);
void		ft_draw_line(t_data *dt, t_vec3 pt1, t_vec3 pt2, t_color color);
void		ft_draw_tri(t_data *data, t_tri *tris, int j, t_color color);
void		ft_fill_img(t_data *data, t_color color);

#endif