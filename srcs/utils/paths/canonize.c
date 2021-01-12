/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canonize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 17:42:29 by badam             #+#    #+#             */
/*   Updated: 2021/01/12 03:09:06 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	rm_doubleslash(char *buff)
{
	size_t	len;

	while (*buff && *(buff + 1))
	{
		if (*buff == '/' && *(buff + 1) == '/')
		{
			len = ft_strlen(buff + 1);
			ft_memcpy(buff, buff + 1, len + 1);
		}
		else
			buff++;
	}
}

static t_error	rm_dotdotslash(char *buff)
{
	char	*buff_cpy;
	size_t	len;
	size_t	offset;

	++buff;
	buff_cpy = buff;
	while (*buff && *(buff + 1) && *(buff + 2))
	{
		if (*buff == '.' && *(buff + 1) == '.' && *(buff + 2) == '/')
		{
			offset = 1;
			if (buff == buff_cpy)
				return (ERR_ROOTPARENT);
			while (offset++ && *(--buff) != '/' && buff_cpy < buff)
				;
			len = ft_strlen(buff + 3 + offset);
			ft_memcpy(buff, buff + 3 + offset, len + 1);
		}
		else
			buff++;
	}
	return (OK);
}

static t_error	rm_dotslash(char *buff)
{
	size_t	len;

	while (*buff && *(buff + 1))
	{
		if (*buff == '.' && *(buff + 1) == '/')
		{
			len = ft_strlen(buff + 2);
			ft_memcpy(buff, buff + 2, len + 1);
		}
		else
			buff++;
	}
	return (OK);
}

static t_error	rm_trailing(char *buff)
{
	size_t	len;

	len = ft_strlen(buff);
	if (len > 1 && buff[len - 1] == '/')
		buff[len - 1] = '\0';
	return (OK);
}

t_error	path_canonize(char **str)
{
	char	*buff;
	t_error	err;

	buff = ft_strdup(*str);
	rm_doubleslash(buff);
	err = rm_dotdotslash(buff);
	if (err != OK)
	{
		free(buff);
		return (err);
	}
	rm_dotslash(buff);
	rm_trailing(buff);
	free(*str);
	*str = ft_strdup(buff);
	free(buff);
	return (OK);
}
