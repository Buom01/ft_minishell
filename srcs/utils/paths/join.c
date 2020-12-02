/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 18:30:08 by badam             #+#    #+#             */
/*   Updated: 2020/12/02 16:22:32 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*path_join(char *begin, char *end)
{
	size_t	beginlen;
	size_t	endlen;
	char	*joined;
	char	*joined_cpy;

	if (!begin || !end)
		return (NULL);
	beginlen = ft_strlen(begin);
	endlen = ft_strlen(end);
	if ((begin)[beginlen - 1] == '/')
		return (ft_strjoin(begin, end));
	else
	{
		if (!(joined = malloc((beginlen + endlen + 2) * sizeof(char))))
			return (NULL);
		joined_cpy = joined;
		ft_memcpy(joined_cpy, begin, beginlen);
		joined_cpy += beginlen;
		*(joined_cpy++) = '/';
		ft_memcpy(joined_cpy, end, endlen);
		joined_cpy += endlen;
		*joined_cpy = '\0';
		return (joined);
	}
}
