/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdescam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 17:14:45 by frdescam          #+#    #+#             */
/*   Updated: 2021/01/12 03:01:29 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

void	free_cmds(t_list *cmds)
{
	t_list		*cmds_elem;
	t_list		*pipe_cmd_elem;
	t_pipe_cmd	*pipe_cmd;
	t_list		*tmp_next;

	cmds_elem = cmds;
	while (cmds_elem)
	{
		pipe_cmd_elem = ((t_cmd *)cmds_elem->content)->pipe_cmds;
		while (pipe_cmd_elem)
		{
			pipe_cmd = (t_pipe_cmd *)pipe_cmd_elem->content;
			ft_string_destroy(pipe_cmd->pipe_cmd);
			while (pipe_cmd->argc)
				free(*(pipe_cmd->argv + --pipe_cmd->argc));
			free(pipe_cmd->argv);
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
		ft_string_destroy(data->line);
	if (data->cmds)
		free_cmds(data->cmds);
	ft_bzero(data, sizeof(t_data));
}

int	*should_prompt_be_printed(void)
{
	static int	i = 0;

	return (&i);
}
