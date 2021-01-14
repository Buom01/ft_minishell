/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_with_capacity.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdescam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 14:44:58 by frdescam          #+#    #+#             */
/*   Updated: 2021/01/14 19:26:56 by frdescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_string	*ft_string_with_capacity(size_t capacity)
{
	t_string	*new_string;

	new_string = malloc(sizeof(t_string));
	if (!new_string)
		return (NULL);
	new_string->str = malloc(sizeof(char) * capacity);
	if (!new_string->str)
		return (NULL);
	new_string->len = 0;
	new_string->capacity = capacity;
	return (new_string);
}
/*
**#include <stdio.h>
**
**int			main(void)
**{
**	t_string *cmd = ft_string_with_capacity(10);
**	printf("cmd->str = %s, cmd->len = %ld, cmd->capacity = %ld\n",
**			cmd->str, cmd->len, cmd->capacity);
**}
*/
