/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 03:50:47 by badam             #+#    #+#             */
/*   Updated: 2020/11/21 12:38:46 by badam            ###   ########.fr       */
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

bool	env_verify_name(const char *str)
{
	char	*lim;

	if (!(lim = (char*)ft_strchr(str, '=')))
		lim = (char*)(str + ft_strlen(str));
	if (!ft_isalpha(*str) && *str != '_')
		return (false);
	++str;
	while (str < lim)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (false);
		++str;
	}
	return (true);
}
