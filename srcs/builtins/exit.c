/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 18:19:56 by badam             #+#    #+#             */
/*   Updated: 2020/10/08 18:26:10 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_error	builtin_exit(size_t argc, char **argv)
{
	if (argc > 1)
		return (ERR_TOOMUCH_ARGS);
	exit(ft_atoi(*argv));
	return (OK);
}
