/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 15:22:15 by badam             #+#    #+#             */
/*   Updated: 2020/11/21 12:34:53 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_error	builtin_export(size_t argc, char **argv)
{
	t_env			*entry;
	t_env_equality	eqlt;

	if (!argc)
	{
		entry = *(env_dictionary());
		while (entry)
		{
			if (!env_isinternal(entry->key))
				if (ft_printf("declare -x %s=\"%s\"\n",
						entry->key, entry->value) < 0)
					return (ERR_PRINTF);
			entry = entry->next;
		}
		return (OK);
	}
	while (argc)
	{
		eqlt = env_isvalid_equality(*argv, true);
		if (eqlt == ENV_EQ_MISFORMAT)
			return (ERR_SYNTAX);
		else if (eqlt == ENV_EQ_UNIFIED)
			env_create(*argv);
		argv++;
		argc--;
	}
	return (OK);
}
