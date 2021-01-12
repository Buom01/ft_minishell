/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exists.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 23:14:27 by badam             #+#    #+#             */
/*   Updated: 2021/01/12 03:02:33 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_error	path_dir_exists(const char *path, bool follow, bool *ret)
{
	struct stat	stat_buff;

	if (follow)
	{
		if (stat(path, &stat_buff) == -1)
		{
			*ret = false;
			return (OK);
		}
	}
	else
	{
		if (lstat(path, &stat_buff) == -1)
		{
			*ret = false;
			return (OK);
		}
	}
	*ret = S_ISDIR(stat_buff.st_mode)
		|| (follow && S_ISLNK(stat_buff.st_mode));
	return (OK);
}
