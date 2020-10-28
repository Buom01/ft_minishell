/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 16:14:06 by badam             #+#    #+#             */
/*   Updated: 2020/10/28 23:18:00 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	env_isvalid_equality(const char *equality)
{
	return (ft_strchr(equality, '=') != NULL);
}

char	*env_parse_key(const char *equality)
{
	char	*delimiter;

	delimiter = ft_strchr(equality, '=');
	return (ft_substr(equality, 0, delimiter - equality));
}

char	*env_parse_value(const char *equality)
{
	char	*delimiter;

	delimiter = ft_strchr(equality, '=');
	return (ft_strdup(delimiter + 1));
}

bool	env_isinternal(const char *key)
{
	return (!ft_strcmp(key, "?"));
}
