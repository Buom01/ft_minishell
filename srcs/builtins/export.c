/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 15:22:15 by badam             #+#    #+#             */
/*   Updated: 2020/11/17 14:07:37 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_error	builtin_export(size_t argc, char **argv)
{
	t_env	*entry;

	if (!argc)
	{
		entry = *(env_dictionary());
		while (entry)
		{
			if (!env_isinternal(entry->key))
				if (ft_printf("declare -x %s=\"%s\"\n", entry->key, entry->value) < 0)
					return (ERR_PRINTF);
			entry = entry->next;
		}
		return (OK);
	}
	while (argc)
	{
		if (env_isvalid_equality(*argv))
			env_create(*argv);
		argv++;
		argc--;
	}
	return (OK);
}
