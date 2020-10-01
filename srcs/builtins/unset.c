/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 17:37:09 by badam             #+#    #+#             */
/*   Updated: 2020/09/22 17:38:12 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_error	builtin_unset(size_t argc, char **argv)
{
	while (argc)
	{
		env_unset(*argv);
		argv++;
		argc--;
	}
	return (OK);
}