/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdescam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 09:42:53 by frdescam          #+#    #+#             */
/*   Updated: 2021/01/14 21:05:10 by frdescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_list
{
	const char		*name;
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_string
{
	char	*str;
	size_t	len;
	size_t	capacity;
}					t_string;

int			ft_atoi(const char *str);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
char		*ft_itoa(int n);
void		ft_lstadd_back(t_list **alst, t_list *new);
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstnew(const char *name, void *content);
void		*ft_memchr(const void *s, int c, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
char		**ft_split(char const *s, const char *delimiters);
char		**ft_clear_splitted(char **tab);
char		*ft_strchr(const char *s, int c);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strdup(const char *s1);
t_string	*ft_string_new(void);
t_string	*ft_string_from(char *str);
t_string	*ft_string_with_capacity(size_t capacity);
t_string	*ft_string_push(t_string *string, char *to_append);
t_string	*ft_string_push_char(t_string *string, char to_append);
t_string	*ft_string_sub(t_string *string, size_t start, size_t len);
t_string	*ft_string_remove(t_string *string, int start, int end);
void		ft_string_destroy(t_string *string);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlen(const char *s);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		ft_putstr_fd(char *s, int fd);
void		ft_putchar_fd(char c, int fd);

#endif
