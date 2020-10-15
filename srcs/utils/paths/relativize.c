/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   relativize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 22:14:26 by badam             #+#    #+#             */
/*   Updated: 2020/10/15 22:34:55 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_error	path_relativize(char **path, char *pwd)
{
	bool	trail;
	char	*rel;

	trail = ((pwd)[ft_strlen(pwd) - 1] == '/');
	if (ft_strnstr(*path, pwd, ft_strlen(*path)) == *path)
	{
		if (!(rel = ft_strdup(*path + ft_strlen(pwd) + !trail)))
			return (ERR_MALLOC);
		free(*path);
		*path = rel;
	}
	return (OK);
}
