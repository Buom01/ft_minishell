/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 15:53:18 by badam             #+#    #+#             */
/*   Updated: 2020/11/26 21:38:28 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env		*env_get(const char *key)
{
	t_env	*entry;

	if (!(entry = *(env_dictionary())))
		panic(ERR_UNINIT_ENV_DICO);
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

char		**env_get_array(void)
{
	size_t	listlen;
	t_env	*entry;
	char	**envs;
	char	**envs_cpy;

	entry = *(env_dictionary());
	listlen = env_listlen(entry);
	if (!(envs = malloc(sizeof(char*) * (listlen + 1))))
		panic(ERR_MALLOC);
	envs_cpy = envs;
	while (entry)
	{
		if (!env_isinternal(entry->key))
			*(envs_cpy++) = env_toequality(entry);
		entry = entry->next;
	}
	*envs_cpy = NULL;
	return (envs);
}

void		env_clear_array(char **envs)
{
	if (envs)
		while (*envs)
			free(*(envs++));
}
