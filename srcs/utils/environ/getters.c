/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 15:53:18 by badam             #+#    #+#             */
/*   Updated: 2020/09/22 16:09:59 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env		*env_get(const char *key)
{
	t_env	*entry;

	entry = *(env_dictionary());
	while (entry && ft_strcmp(entry->key, key) != 0)
		entry = entry->next;
	return (entry);
}

char		*env_get_value(const char *key)
{
	t_env	*entry;

	if ((entry = env_get(key)))
		return (entry->value);
	return (NULL);
}
