/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 16:14:06 by badam             #+#    #+#             */
/*   Updated: 2021/01/12 03:25:36 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_equality	env_isvalid_equality(const char *str, bool sanitizename)
{
	char	*cur;

	if (!str)
		return (ENV_EQ_NONE);
	if (sanitizename)
	{
		if (!env_verify_name(str))
			return (ENV_EQ_MISFORMAT);
	}
	else if (!*str || *str == '=')
		return (ENV_EQ_MISFORMAT);
	cur = (char*)ft_strchr(str, '=');
	if (cur == NULL)
		return (ENV_EQ_NONE);
	return (ENV_EQ_UNIFIED);
}

char	*env_parse_key(const char *eqlt)
{
	char	*delimiter;

	delimiter = ft_strchr(eqlt, '=');
	return (ft_substr(eqlt, 0, delimiter - eqlt));
}

char	*env_parse_value(const char *eqlt)
{
	char	*delimiter;

	delimiter = ft_strchr(eqlt, '=');
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
	eqlt = malloc(sizeof(char) * (keyl + vall + 2));
	if (!eqlt)
		panic(ERR_MALLOC);
	ft_memcpy(eqlt, env->key, keyl);
	*(eqlt + keyl) = '=';
	ft_memcpy(eqlt + keyl + 1, env->value, vall + 1);
	return (eqlt);
}
