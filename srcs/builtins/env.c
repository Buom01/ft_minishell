/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 17:47:06 by badam             #+#    #+#             */
/*   Updated: 2020/10/08 18:18:25 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_error	builtin_env(void)
{
	t_env	*entry;

	entry = *(env_dictionary());
	while (entry)
	{
		if (ft_printf("%s=%s\n", entry->key, entry->value) < 0)
			return (ERR_PRINTF);
		entry = entry->next;
	}
	return (OK);
}
