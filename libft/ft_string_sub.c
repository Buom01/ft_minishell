/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_sub.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdescam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 14:54:19 by frdescam          #+#    #+#             */
/*   Updated: 2021/01/14 19:25:32 by frdescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_string	*ft_string_sub(t_string *string, size_t start, size_t len)
{
	t_string	*out;

	out = ft_string_new();
	if (!out)
		return (NULL);
	out->str = malloc(sizeof(char) * (len + 1));
	if (!out->str)
		return (NULL);
	ft_strlcpy(out->str, string->str + start, len + 1);
	out->len = len;
	out->capacity = len + 1;
	return (out);
}
/*
**#include <stdio.h>
**
**int			main(void)
**{
**	t_string *cmd = ft_string_from("hello world!");
**	printf("cmd->str = %s, cmd->len = %ld, cmd->capacity = %ld\n",
**      cmd->str, cmd->len, cmd->capacity);
**	t_string *sub = ft_string_sub(cmd, 6, 5);
**	printf("sub->str = %s, sub->len = %ld, sub->capacity = %ld\n",
**      sub->str, sub->len, sub->capacity);
**}
*/
