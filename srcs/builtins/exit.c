/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 18:19:56 by badam             #+#    #+#             */
/*   Updated: 2020/11/03 21:24:37 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_error	builtin_exit(size_t argc, char **argv)
{
	if (argc > 1)
		return (ERR_TOOMUCH_ARGS);
	env_shutdown();
	exit(argc == 1 ? ft_atoi(*argv) : 0);
	return (OK);
}
