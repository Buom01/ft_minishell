/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 18:19:56 by badam             #+#    #+#             */
/*   Updated: 2021/01/14 00:35:55 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_error	builtin_exit(size_t argc, char **argv)
{
	if (argc > 1)
		return (ERR_TOOMUCH_ARGS);
	env_shutdown();
	if (argc == 1)
		exit((unsigned char)ft_atoi(*argv));
	else
		exit(0);
	return (OK);
}
