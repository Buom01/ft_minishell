/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 15:29:31 by badam             #+#    #+#             */
/*   Updated: 2021/01/12 03:11:48 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	**env_dictionary(void)
{
	static t_env	*entries;

	return (&entries);
}

void	env_init(char **environ)
{
	char	**environ_p;
	t_env	*entry;
	t_env	**prev_next;

	prev_next = env_dictionary();
	if (*prev_next)
		panic(ERR_DOUBLE_INIT_ENV_DICO);
	environ_p = environ;
	while (*environ_p)
	{
		if (env_isvalid_equality(*environ_p, false))
		{
			entry = malloc(sizeof(t_env));
			if (!entry)
				panic(ERR_MALLOC);
			*prev_next = entry;
			entry->key = env_parse_key(*environ_p);
			if (!entry->key)
				panic(ERR_MALLOC);
			entry->value = env_parse_value(*environ_p);
			if (!entry->value)
				panic(ERR_MALLOC);
			prev_next = &(entry->next);
		}
		environ_p++;
	}
	entry->next = NULL;
}

void	env_shutdown(void)
{
	t_env	**entries;
	t_env	*entry;
	t_env	*next;

	entries = env_dictionary();
	entry = *entries;
	*entries = NULL;
	while (entry)
	{
		next = entry->next;
		free(entry->key);
		free(entry->value);
		free(entry);
		entry = next;
	}
}
