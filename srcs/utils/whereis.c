/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whereis.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 16:51:09 by badam             #+#    #+#             */
/*   Updated: 2021/01/12 04:37:24 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*test_paths(char **paths, const char *filepath)
{
	char	*pathname;

	while (*paths)
	{
		pathname = path_join(*paths, filepath);
		if (!pathname)
			panic(ERR_MALLOC);
		if (file_exists(pathname))
			return (pathname);
		free(pathname);
		paths++;
	}
	return (NULL);
}

char	*whereis(const char *filepath)
{
	char	*env_path;
	char	**paths;
	char	**paths_cpy;
	char	*pathname;

	env_path = env_get_value("PATH");
	if (*filepath == '/' || *filepath == '.')
		return (ft_strdup(filepath));
	else if (env_path)
	{
		paths = ft_split(env_path, ":");
		if (!paths)
			panic(ERR_MALLOC);
		paths_cpy = paths;
		pathname = test_paths(paths, filepath);
		while (*paths_cpy)
			free(*(paths_cpy++));
		free(paths);
		return (pathname);
	}
	return (NULL);
}
