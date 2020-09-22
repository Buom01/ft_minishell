/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 16:08:13 by badam             #+#    #+#             */
/*   Updated: 2020/09/22 17:43:10 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_create(char *equality)
{
	char	*key;
	char	*value;

	if (!(key = env_parse_key(equality)))
		panic(ERR_MALLOC);
	if (!(value = env_parse_value(equality)))
		panic(ERR_MALLOC);
	return (env_set(key, value));
	free(key);
	free(value);
}

t_env	*env_set(const char *key, const char *value)
{
	t_env	*entry;
	t_env	**prev_next;

	if ((entry = env_get(key)))
	{
		free(entry->value);
		if (!(entry->value = ft_strdup(value)))
			panic(ERR_MALLOC);
		return (entry);
	}
	else
	{
		prev_next = env_dictionary();
		while (*prev_next)
			prev_next = &((*prev_next)->next);
		if (!(entry = malloc(sizeof(t_env))))
			panic(ERR_MALLOC);
		if (!(entry->key = ft_strdup(key))
				|| !(entry->value = ft_strdup(value)))
			panic(ERR_MALLOC);
		*prev_next = entry;
		return (entry);
	}
}

void	env_unset(const char *key)
{
	t_env	**prev_next;
	t_env	*entry;

	prev_next = env_dictionary();
	entry = *prev_next;
	while (entry && ft_strcmp(entry->key, key) != 0)
	{
		prev_next = &(entry->next);
		entry = entry->next;
	}
	if (entry)
	{
		*prev_next = entry->next;
		free(entry->key);
		free(entry->value);
		free(entry);
	}
}
