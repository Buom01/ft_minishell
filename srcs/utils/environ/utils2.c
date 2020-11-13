/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 03:50:47 by badam             #+#    #+#             */
/*   Updated: 2020/11/11 03:53:36 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	env_listlen(t_env *list)
{
	size_t	len;

	len = 0;
	while (list)
	{
		if (!env_isinternal(list->key))
			len++;
		list = list->next;
	}
	return (len);
}
