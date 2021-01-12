/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 15:22:15 by badam             #+#    #+#             */
/*   Updated: 2021/01/12 02:51:56 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_error	builtin_export_printall(void)
{
	t_env			*entry;

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

t_error	builtin_export(size_t argc, char **argv)
{
	t_env_equality	eqlt;

	if (!argc)
		return (builtin_export_printall());
	while (argc)
	{
		eqlt = env_isvalid_equality(*argv, true);
		if (eqlt == ENV_EQ_MISFORMAT)
			return (ERR_SYNTAX);
		else if (eqlt == ENV_EQ_UNIFIED)
			env_create(*argv);
		++argv;
		--argc;
	}
	return (OK);
}
