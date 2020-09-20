/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_from.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdescam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 14:31:20 by frdescam          #+#    #+#             */
/*   Updated: 2020/09/20 15:22:44 by frdescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_string	*ft_string_from(char *str)
{
	t_string	*new_string;
	size_t		str_len;

	str_len = ft_strlen(str);
	if (!(new_string = malloc(sizeof(t_string))))
		return (NULL);
	if (!(new_string->str = malloc(sizeof(char) * (str_len + 1))))
		return (NULL);
	ft_strlcpy(new_string->str, str, str_len + 1);
	new_string->len = str_len;
	new_string->capacity = str_len + 1;
	return (new_string);
}
/*
**#include <stdio.h>
**
**int			main(void)
**{
**	t_string *cmd = ft_string_from("hello");
**	printf("cmd->str = %s, cmd->len = %ld, cmd->capacity = %ld\n",
**     cmd->str, cmd->len, cmd->capacity);
**}
*/
