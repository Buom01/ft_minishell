/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 15:29:31 by badam             #+#    #+#             */
/*   Updated: 2020/09/16 16:33:43 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		env_init(t_env **entries, char **environ)
{
	char	**environ_p;
	char	*delimiter;
	t_env	*entry;
	t_env	**prev_next;

	prev_next = entries;
	environ_p = environ;
	while (*environ_p)
	{
		if (!(entry = malloc(sizeof(t_env))))
			return ;
		*prev_next = entry;
		delimiter = ft_strchr(*environ_p, '=');
		entry->key = ft_substr(*environ_p, 0, delimiter - *environ_p);
		entry->value = ft_strdup(delimiter + 1);
		prev_next = &(entry->next);
		environ_p++;
	}
	entry->next = NULL;
}

void		env_shutdown(t_env **entries)
{
	t_env	*entry;
	t_env	*next;

	entry = *entries;
	while (entry)
	{
		next = entry->next;
		free(entry->key);
		free(entry->value);
		free(entry);
		entry = next;
	}
}

t_env		*env_get(const t_env *entries, const char *key)
{
	t_env	*entry;

	entry = (t_env *)entries;
	while (entry && ft_strcmp(entry->key, key) != 0)
		entry = entry->next;
	return (entry);
}

char		*env_get_value(const t_env *entries, const char *key)
{
	t_env	*entry;

	if ((entry = env_get(entries, key)))
		return (entry->value);
	return (NULL);
}
