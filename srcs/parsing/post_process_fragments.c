/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_process_fragments.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 21:08:03 by badam             #+#    #+#             */
/*   Updated: 2021/01/14 00:13:40 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

void	process_env(t_string *cmd, t_pp_state *st, char *cursor)
{
	size_t	len;
	char	*env_name;
	char	*env_value;

	len = env_get_name_len(cursor + 1);
	if (!len)
		pp_strip(st, 1, cmd);
	else
	{
		env_name = ft_substr(cursor, 1, len);
		if (!env_name)
			panic(ERR_MALLOC);
		env_value = env_get_value(env_name);
		if (!env_value)
			env_value = "";
		free(env_name);
		pp_replace(st, 1 + len, env_value, cmd);
	}
}

void	process_escape(t_string *cmd, t_pp_state *st, char *cursor)
{
	if (*(cursor + 1) == '\n')
		pp_strip(st, 2, cmd);
	else if (ft_strchr("$`\"\\", *(cursor + 1)) || !st->in_dquote)
		pp_strip(st, 1, cmd);
	++(st->cursor);
}

bool	process_space(t_string *cmd, t_pp_state *st, char *cursor)
{
	size_t	space_len;

	if (st->in_dquote)
		return (false);
	space_len = 0;
	while (*cursor && ft_strchr("\f\t  \n\r\v", *(cursor++)))
		++space_len;
	pp_replace(st, space_len, " ", cmd);
	return (true);
}
