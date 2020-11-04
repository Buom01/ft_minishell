/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 15:29:31 by badam             #+#    #+#             */
/*   Updated: 2020/11/04 02:26:26 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env		**env_dictionary(void)
{
	static t_env	*entries;

	return (&entries);
}

void		env_init(char **environ)
{
	char	**environ_p;
	t_env	*entry;
	t_env	**prev_next;

	prev_next = env_dictionary();
	environ_p = environ;
	while (*environ_p)
	{
		if (env_isvalid_equality(*environ_p))
		{
			if (!(entry = malloc(sizeof(t_env))))
				panic(ERR_MALLOC);
			*prev_next = entry;
			if (!(entry->key = env_parse_key(*environ_p)))
				panic(ERR_MALLOC);
			if (!(entry->value = env_parse_value(*environ_p)))
				panic(ERR_MALLOC);
			prev_next = &(entry->next);
		}
		environ_p++;
	}
	entry->next = NULL;
}

void		env_shutdown(void)
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
