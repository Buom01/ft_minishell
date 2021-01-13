/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 16:08:13 by badam             #+#    #+#             */
/*   Updated: 2021/01/13 23:59:39 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_create(char *equality)
{
	char	*key;
	char	*value;

	key = env_parse_key(equality);
	if (!key)
		panic(ERR_MALLOC);
	value = env_parse_value(equality);
	if (!value)
		panic(ERR_MALLOC);
	return (env_set(key, value));
	free(key);
	free(value);
}

static t_env	*env_set_append(const char *key, const char *value)
{
	t_env	**prev_next;
	t_env	*entry;

	prev_next = env_dictionary();
	if (!(*prev_next))
		panic(ERR_UNINIT_ENV_DICO);
	while (*prev_next)
		prev_next = &((*prev_next)->next);
	entry = malloc(sizeof(t_env));
	if (!entry)
		panic(ERR_MALLOC);
	entry->key = ft_strdup(key);
	if (!entry->key)
		panic(ERR_MALLOC);
	entry->value = ft_strdup(value);
	if (!entry->value)
		panic(ERR_MALLOC);
	entry->next = NULL;
	*prev_next = entry;
	return (entry);
}

t_env	*env_set(const char *key, const char *value)
{
	t_env	*entry;

	entry = env_get(key);
	if (entry)
	{
		free(entry->value);
		entry->value = ft_strdup(value);
		if (!entry->value)
			panic(ERR_MALLOC);
		return (entry);
	}
	else
		return (env_set_append(key, value));
}

void	env_unset(const char *key)
{
	t_env	**prev_next;
	t_env	*entry;

	prev_next = env_dictionary();
	entry = *prev_next;
	if (!entry)
		panic(ERR_UNINIT_ENV_DICO);
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
