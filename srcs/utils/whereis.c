/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whereis.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 16:51:09 by badam             #+#    #+#             */
/*   Updated: 2021/01/12 02:59:48 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	get_path_len(const char *path)
{
	char	*delimiter;

	delimiter = ft_strchr(path, ':');
	if (delimiter)
		return (delimiter - path);
	else
		return (ft_strlen(path));
}

static void	set_next_path(char **path, const size_t len)
{
	if (*(*path + len) == '\0' || *(*path + len + 1) == '\0')
		*path = NULL;
	else
		*path += len + 1;
}

char	*whereis(const char *filepath)
{
	size_t		filepath_len;
	char		*path_cur;
	char		*pathname;
	size_t		pathname_len;
	struct stat	stat_buff;

	path_cur = env_get_value("PATH");
	if (*filepath == '/' || *filepath == '.')
		return (ft_strdup(filepath));
	else if (path_cur)
	{
		filepath_len = ft_strlen(filepath);
		while (path_cur)
		{
			pathname_len = get_path_len(path_cur);
			pathname = malloc(sizeof(char) * (pathname_len + filepath_len + 2));
			ft_strlcpy(pathname, path_cur, pathname_len + 1);
			ft_strlcpy(pathname + pathname_len, "/", 2);
			ft_strlcpy(pathname + pathname_len + 1, filepath, filepath_len + 1);
			if (stat(pathname, &stat_buff) == 0 && S_ISREG(stat_buff.st_mode))
				return (pathname);
			free(pathname);
			set_next_path(&path_cur, pathname_len);
		}
	}
	return (NULL);
}
