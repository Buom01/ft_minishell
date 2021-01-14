/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 18:27:41 by badam             #+#    #+#             */
/*   Updated: 2021/01/14 17:50:36 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

t_error	builtin_echo(size_t argc, char **argv)
{
	t_echo_opts	options;

	ft_bzero(&options, sizeof(t_echo_opts));
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
		if (printf("%s", *argv) < 0
			|| (argc > 1 && printf(" ") < 0))
			return (ERR_PRINTF);
		argv++;
		argc--;
	}
	if (!options.nonewline)
		if (printf("\n") < 0)
			return (ERR_PRINTF);
	return (OK);
}
