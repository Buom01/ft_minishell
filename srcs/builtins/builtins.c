/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 14:30:32 by badam             #+#    #+#             */
/*   Updated: 2020/09/22 15:20:10 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_builtin	get_builtin(char *command)
{
	if (ft_strcmp(command, "echo") == 0)
		return (BI_ECHO);
	else if (ft_strcmp(command, "cd") == 0)
		return (BI_CD);
	else if (ft_strcmp(command, "pwd") == 0)
		return (BI_PWD);
	else if (ft_strcmp(command, "export") == 0)
		return (BI_EXPORT);
	else if (ft_strcmp(command, "unset") == 0)
		return (BI_UNSET);
	else if (ft_strcmp(command, "env") == 0)
		return (BI_ENV);
	else if (ft_strcmp(command, "exit") == 0)
		return (BI_EXIT);
	else
		return (BI_NONE);
}

t_error		builtins(t_builtin builtin, size_t argc, char **argv)
{
	if (builtin == BI_EXPORT)
		return (builtin_export(argc, argv));
	else if (builtin == BI_UNSET)
		return (builtin_unset(argc, argv));
	else if (builtin == BI_ENV)
		return (builtin_env(argc, argv));
	else
		return (ERR_UNIMPLENTED);
}
