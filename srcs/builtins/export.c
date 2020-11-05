/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 15:22:15 by badam             #+#    #+#             */
/*   Updated: 2020/11/05 22:40:52 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_error	builtin_export(size_t argc, char **argv)
{
	while (argc)
	{
		ft_printf("Exec: %s\n", *argv);
		if (env_isvalid_equality(*argv))
			env_create(*argv);
		else
			ft_printf("Synthax: %s\n", *argv);
		argv++;
		argc--;
	}
	return (OK);
}
