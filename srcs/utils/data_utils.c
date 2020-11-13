/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdescam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 10:26:11 by frdescam          #+#    #+#             */
/*   Updated: 2020/11/10 11:13:08 by frdescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

void	init_data(t_data *data)
{
	data->env = NULL;
	data->line = NULL;
	data->cmds = NULL;
}

void	free_cmds(t_list *cmds)
{
	t_list	*cmds_elem;
	t_list	*pipe_cmd_elem;
	t_list	*tmp_next;

	cmds_elem = cmds;
	while (cmds_elem)
	{
		pipe_cmd_elem = ((t_cmd *)cmds_elem->content)->pipe_cmds;
		while (pipe_cmd_elem)
		{
			ft_string_destroy(((t_pipe_cmd *)pipe_cmd_elem->content)->pipe_cmd);
			free(pipe_cmd_elem->content);
			free((char *)pipe_cmd_elem->name);
			tmp_next = pipe_cmd_elem->next;
			free(pipe_cmd_elem);
			pipe_cmd_elem = tmp_next;
		}
		ft_string_destroy(((t_cmd *)cmds_elem->content)->cmd);
		free(cmds_elem->content);
		free((char *)cmds_elem->name);
		tmp_next = cmds_elem->next;
		free(cmds_elem);
		cmds_elem = tmp_next;
	}
}

void	free_data(t_data *data)
{
	if (data->line)
	{
		ft_string_destroy(data->line);
		data->line = NULL;
	}
	if (data->cmds)
	{
		free_cmds(data->cmds);
		data->cmds = NULL;
	}
}
