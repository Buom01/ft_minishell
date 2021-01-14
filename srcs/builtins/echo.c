/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 18:27:41 by badam             #+#    #+#             */
/*   Updated: 2021/01/14 21:16:30 by badam            ###   ########.fr       */
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
		ft_putstr_fd(*argv, 1);
		if (argc > 1)
			ft_putstr_fd(" ", 1);
		argv++;
		argc--;
	}
	if (!options.nonewline)
		ft_putstr_fd("\n", 1);
	return (OK);
}
