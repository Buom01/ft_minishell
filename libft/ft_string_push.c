/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_push.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdescam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 14:55:47 by frdescam          #+#    #+#             */
/*   Updated: 2021/01/14 19:23:09 by frdescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_string	*ft_string_push(t_string *string, char *to_append)
{
	size_t	to_append_len;
	char	*tmp;

	to_append_len = ft_strlen(to_append);
	if (string->capacity < string->len + to_append_len + 1)
	{
		tmp = malloc(sizeof(char) * (string->len + to_append_len + 1));
		if (!tmp)
			return (NULL);
		string->capacity = string->len + to_append_len + 1;
		ft_strlcpy(tmp, string->str, string->len + to_append_len + 1);
		ft_strlcpy(tmp + string->len, to_append, to_append_len + 1);
		free(string->str);
		string->str = tmp;
	}
	else
	{
		ft_strlcpy(string->str + string->len, to_append,
				string->capacity - string->len);
	}
	string->len += to_append_len;
	return (string);
}

/*
**#include <stdio.h>
**
**int			main(void)
**{
**	t_string *cmd = ft_string_from("hello ");
**	printf("cmd->str = %s, cmd->len = %ld, cmd->capacity = %ld\n",
**      cmd->str, cmd->len, cmd->capacity);
**	ft_string_push(cmd, "world!");
**	printf("cmd->str = %s, cmd->len = %ld, cmd->capacity = %ld\n",
**      cmd->str, cmd->len, cmd->capacity);
**}
*/

t_string	*ft_string_push_char(t_string *string, char to_append)
{
	char	*tmp;

	if (string->capacity < string->len + 2)
	{
		tmp = malloc(sizeof(char) * (string->len + 2));
		if (!tmp)
			return (NULL);
		string->capacity = string->len + 2;
		ft_strlcpy(tmp, string->str, string->len + 2);
		tmp[string->len] = to_append;
		tmp[string->len + 1] = '\0';
		free(string->str);
		string->str = tmp;
	}
	else
	{
		string->str[string->len] = to_append;
		string->str[string->len + 1] = '\0';
	}
	string->len += 1;
	return (string);
}
/*
**#include <stdio.h>
**
**int			main(void)
**{
**	t_string *cmd = ft_string_with_capacity(14);
**	printf("cmd->str = %s, cmd->len = %ld, cmd->capacity = %ld\n",
**      cmd->str, cmd->len, cmd->capacity);
**	ft_string_push_char(cmd, 'w');
**	printf("cmd->str = %s, cmd->len = %ld, cmd->capacity = %ld\n",
**      cmd->str, cmd->len, cmd->capacity);
**	ft_string_push_char(cmd, 'c');
**	printf("cmd->str = %s, cmd->len = %ld, cmd->capacity = %ld\n",
**      cmd->str, cmd->len, cmd->capacity);
**}
*/
