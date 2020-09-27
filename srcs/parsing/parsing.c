/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdescam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 14:31:04 by frdescam          #+#    #+#             */
/*   Updated: 2020/09/27 15:48:58 by frdescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	exec_line(t_string *line)
{
	size_t		i;
	int			start;
	t_list		*cmds;
	t_string	*sub;
	t_list		*cmd;

	cmds = NULL;
	start = 0;
	i = 0;
	while (i < line->len)
	{
		while (i < line->len && line->str[i] != ';')
			i++;
		if (!(sub = ft_string_sub(line, start, i - start)))
			panic(ERR_MALLOC);
		if (!(cmd = ft_lstnew("", sub)))
			panic(ERR_MALLOC);
		ft_lstadd_back(&cmds, cmd);
		i++;
		start = i;
	}
}
