/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 18:27:41 by badam             #+#    #+#             */
/*   Updated: 2020/10/28 23:06:22 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

t_error	builtin_echo(size_t argc, char **argv)
{
	t_echo_opts	options;

	ft_bzero(&options, sizeof(options));
	while (argc)
	{
		if (!ft_strcmp(*argv, "-n"))
			options.nonewline = true;
		else
			break ;
		argv++;
		argc--;
	}
	while (argc)
	{
		if (ft_printf(*argv) < 0)
			return (ERR_PRINTF);
		argv++;
		argc--;
	}
	if (!options.nonewline)
		if (ft_printf("\n") < 0)
			return (ERR_PRINTF);
	return (OK);
}
