/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exists.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 23:14:27 by badam             #+#    #+#             */
/*   Updated: 2020/10/15 23:56:45 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_error	path_dir_exists(const char *path, bool follow_links, bool *ret)
{
	struct stat	stat_buff;

	if (follow_links)
	{
		if (stat(path, &stat_buff) == -1)
			return (ERR_ERRNO);
	}
	else
		if (lstat(path, &stat_buff) == -1)
			return (ERR_ERRNO);
	*ret = S_ISDIR(stat_buff.st_mode)
			|| (follow_links && S_ISLNK(stat_buff.st_mode));
	return (OK);
}
