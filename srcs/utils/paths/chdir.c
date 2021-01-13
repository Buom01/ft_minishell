/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 17:34:37 by badam             #+#    #+#             */
/*   Updated: 2021/01/12 23:20:44 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**path_oldpath(void)
{
	static char	*oldpath = NULL;

	return (&oldpath);
}

t_error	path_chdir(const char *newpath, const char *oldpath)
{
	t_error	err;
	char	**intern_oldpath;

	err = chdir(newpath);
	if (err == OK)
	{
		intern_oldpath = path_oldpath();
		if (*intern_oldpath)
			free(*intern_oldpath);
		*intern_oldpath = ft_strdup(oldpath);
		if (!*intern_oldpath)
			return (ERR_MALLOC);
		env_set("OLDPWD", oldpath);
		env_set("PWD", newpath);
	}
	else
		err = ERR_ERRNO;
	return (err);
}
