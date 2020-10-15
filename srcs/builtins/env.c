/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 17:47:06 by badam             #+#    #+#             */
/*   Updated: 2020/10/09 21:13:04 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_error	builtin_env(size_t argc, char **argv)
{
	t_env	*entry;

	(void)argv;
	if (argc > 0)
		return (ERR_TOOMUCH_ARGS);
	entry = *(env_dictionary());
	while (entry)
	{
		if (ft_printf("%s=%s\n", entry->key, entry->value) < 0)
			return (ERR_PRINTF);
		entry = entry->next;
	}
	return (OK);
}
