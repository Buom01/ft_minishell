/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 18:32:12 by badam             #+#    #+#             */
/*   Updated: 2020/10/09 21:13:11 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_error	builtin_pwd(size_t argc, char **argv)
{
	char	*cwd;

	(void)argv;
	if (argc > 0)
		return (ERR_TOOMUCH_ARGS);
	if (!(cwd = getcwd(NULL, 0)))
		return (ERR_MALLOC);
	if (ft_printf("%s\n", cwd) < 0)
		return (ERR_PRINTF);
	free(cwd);
	return (OK);
}
