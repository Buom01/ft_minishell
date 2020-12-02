/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 17:34:37 by badam             #+#    #+#             */
/*   Updated: 2020/12/02 20:48:39 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**path_oldpath(void)
{
	static char	*oldpath;

	return (&oldpath);
}

t_error	path_chdir(const char *newpath, const char *oldpath)
{
	t_error err;
	char	**intern_oldpath;

	if ((err = chdir(newpath)) == OK)
	{
		intern_oldpath = path_oldpath();
		if (*intern_oldpath)
			free(*intern_oldpath);
		if (!(*intern_oldpath = ft_strdup(oldpath)))
			return (ERR_MALLOC);
		env_set("OLDPWD", oldpath);
		env_set("PWD", newpath);
	}
	else
		err = ERR_ERRNO;
	return (err);
}
