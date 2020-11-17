/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 16:14:06 by badam             #+#    #+#             */
/*   Updated: 2020/11/17 14:29:34 by badam            ###   ########.fr       */
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

char	*env_toequality(t_env *env)
{
	size_t	keyl;
	size_t	vall;
	char	*eqlt;

	keyl = ft_strlen(env->key);
	vall = ft_strlen(env->value);
	if (!(eqlt = malloc(sizeof(char) * (keyl + vall + 2))))
		panic(ERR_MALLOC);
	ft_memcpy(eqlt, env->key, keyl);
	*(eqlt + keyl) = '=';
	ft_memcpy(eqlt + keyl + 1, env->value, vall + 1);
	return (eqlt);
}
