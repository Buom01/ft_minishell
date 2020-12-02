/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 17:34:37 by badam             #+#    #+#             */
/*   Updated: 2020/12/02 17:36:57 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_error	path_chdir(const char *newpath, const char *oldpath)
{
	t_error err;

	if ((err = chdir(newpath)) == OK)
	{
		env_set("OLDPWD", oldpath);
		env_set("PWD", newpath);
	}
	else
		err = ERR_ERRNO;
	return (err);
}
