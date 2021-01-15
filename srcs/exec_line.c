/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdescam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 17:38:57 by frdescam          #+#    #+#             */
/*   Updated: 2021/01/15 22:21:36 by frdescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing/parsing.h"
#include "libft.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

size_t	get_argc(char **argv)
{
	size_t	argc;

	argc = 0;
	while (argv[argc])
		argc++;
	return (argc);
}

void	close_fds(t_data *data, t_cmd *cmd, t_pipe_cmd *pipe_cmd)
{
	t_list	*cmds_elem;
	t_list	*pipe_cmd_elem;

	cmds_elem = data->cmds;
	while (cmds_elem)
	{
		pipe_cmd_elem = ((t_cmd *)cmds_elem->content)->pipe_cmds;
		while (pipe_cmd_elem && cmds_elem->content == cmd)
		{
			if (pipe_cmd_elem->content != pipe_cmd
				&& ((t_cmd *)cmds_elem->content)->should_fork)
			{
				if (((t_pipe_cmd *)pipe_cmd_elem->content)->fd_in > 2)
					close(((t_pipe_cmd *)pipe_cmd_elem->content)->fd_in);
				if (((t_pipe_cmd *)pipe_cmd_elem->content)->fd_out > 2)
					close(((t_pipe_cmd *)pipe_cmd_elem->content)->fd_out);
			}
			pipe_cmd_elem = pipe_cmd_elem->next;
		}
		cmds_elem = cmds_elem->next;
	}
}

void	wait_for_all_process_to_finish(t_data *data, t_cmd *cmd)
{
	t_list		*pipe_cmd_elem;
	int			status;
	t_pipe_cmd	*pipe_cmd;

	(void)data;
	status = 0;
	pipe_cmd_elem = cmd->pipe_cmds;
	while (pipe_cmd_elem)
	{
		pipe_cmd = pipe_cmd_elem->content;
		if (pipe_cmd->forked)
		{
			waitpid(pipe_cmd->pid, &status, 0);
			handle_error_code(data, status);
		}
		pipe_cmd_elem = pipe_cmd_elem->next;
	}
}

void	exec_cmd(t_data *data, t_cmd *cmd)
{
	t_list	*pipe_cmd_elem;

	data->env = env_get_array();
	pipe_cmd_elem = cmd->pipe_cmds;
	cmd->should_fork = !(pipe_cmd_elem && !(pipe_cmd_elem->next));
	while (pipe_cmd_elem)
	{
		if (((t_pipe_cmd *)pipe_cmd_elem->content)->cmd)
			ex_pipe_cmd(data, cmd, pipe_cmd_elem->content);
		pipe_cmd_elem = pipe_cmd_elem->next;
	}
	close_fds(data, cmd, NULL);
	wait_for_all_process_to_finish(data, cmd);
	env_clear_array(data->env);
}

void	exec_line(t_data *data)
{
	t_list	*cmds_elem;

	cmds_elem = data->cmds;
	while (cmds_elem)
	{
		exec_cmd(data, cmds_elem->content);
		cmds_elem = cmds_elem->next;
	}
}
