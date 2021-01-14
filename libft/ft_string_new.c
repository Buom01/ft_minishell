/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_new.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdescam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 14:14:48 by frdescam          #+#    #+#             */
/*   Updated: 2021/01/14 19:21:31 by frdescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_string	*ft_string_new(void)
{
	t_string	*new_string;

	new_string = malloc(sizeof(t_string));
	if (!new_string)
		return (NULL);
	new_string->str = NULL;
	new_string->len = 0;
	new_string->capacity = 0;
	return (new_string);
}
/*
**#include <stdio.h>
**
**int			main(void)
**{
**	t_string *cmd = ft_string_new();
**	printf("cmd->str = %s, cmd->len = %ld, cmd->capacity = %ld\n",
**      cmd->str, cmd->len, cmd->capacity);
**}
*/
