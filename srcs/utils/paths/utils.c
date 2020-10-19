/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 23:58:26 by badam             #+#    #+#             */
/*   Updated: 2020/10/19 23:18:50 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_error	path_trailslash(char **str)
{
	char	*str2;
	size_t	str_len;

	str_len = ft_strlen(*str);
	if ((*str)[str_len - 1] == '/')
		return (OK);
	if (!(str2 = malloc((str_len + 2) * sizeof(char))))
		return (ERR_MALLOC);
	ft_memcpy(str2, *str, str_len);
	str2[str_len] = '/';
	str2[str_len + 1] = '\0';
	*str = str2;
	free(str);
	return (OK);
}

t_error	path_pwd(char **str)
{
	char	buff[PATH_MAX];
	t_error	err;

	if (!(*str = ft_strdup(getcwd(buff, PATH_MAX))))
		return (ERR_MALLOC);
	if ((err = path_trailslash(str)) != OK)
		return (err);
	return (OK);
}
