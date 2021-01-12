/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdescam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 17:38:57 by frdescam          #+#    #+#             */
/*   Updated: 2021/01/12 03:40:18 by badam            ###   ########.fr       */
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

void	close_all_useless_fd(t_data *data, t_cmd *cmd, t_pipe_cmd *pipe_cmd)
{
	t_list	*cmds_elem;
	t_list	*pipe_cmd_elem;

	cmds_elem = data->cmds;
	while (cmds_elem)
	{
		pipe_cmd_elem = ((t_cmd *)cmds_elem->content)->pipe_cmds;
		while (pipe_cmd_elem && cmds_elem->content == cmd
			&& pipe_cmd_elem->content != pipe_cmd)
		{
			if (((t_pipe_cmd *)pipe_cmd_elem->content)->fd_in > 2)
				close(((t_pipe_cmd *)pipe_cmd_elem->content)->fd_in);
			if (((t_pipe_cmd *)pipe_cmd_elem->content)->fd_out > 2)
				close(((t_pipe_cmd *)pipe_cmd_elem->content)->fd_out);
			pipe_cmd_elem = pipe_cmd_elem->next;
		}
		cmds_elem = cmds_elem->next;
	}
}

void	exec_pipe_cmd(t_data *data, t_cmd *cmd, t_pipe_cmd *pipe_cmd)
{
	char		*filepath;
	t_builtin	bi;
	int			tmp_fdin;
	int			tmp_fdout;

	bi = get_builtin(pipe_cmd->cmd);
	pipe_cmd->forked = cmd->should_fork || bi == BI_NONE;
	if (!pipe_cmd->forked)
	{
		tmp_fdin = dup(STDIN_FILENO);
		tmp_fdout = dup(STDOUT_FILENO);
		dup2(pipe_cmd->fd_in, STDIN_FILENO);
		dup2(pipe_cmd->fd_out, STDOUT_FILENO);
		exec_builtin(bi, pipe_cmd->argc, pipe_cmd->argv);
		dup2(tmp_fdin, STDIN_FILENO);
		dup2(tmp_fdout, STDOUT_FILENO);
	}
	else
	{
		pipe_cmd->pid = fork();
		if (pipe_cmd->pid == 0)
		{
			close_all_useless_fd(data, cmd, pipe_cmd);
			dup2(pipe_cmd->fd_in, STDIN_FILENO);
			dup2(pipe_cmd->fd_out, STDOUT_FILENO);
			if (bi != BI_NONE)
				exec_builtin(bi, pipe_cmd->argc, pipe_cmd->argv);
			else
			{
				filepath = whereis(pipe_cmd->cmd);
				if (!filepath)
					print_warning(ERR_UNKNOWN_CMD);
				else
					execve(filepath, pipe_cmd->argv, data->env);
			}
			close(pipe_cmd->fd_out);
			exit(0);
		}
	}
	close_all_useless_fd(data, cmd, pipe_cmd);
}

void	wait_for_all_process_to_finish(t_data *data, t_cmd *cmd)
{
	t_list		*pipe_cmd_elem;
	int			status;
	t_pipe_cmd	*pipe_cmd;

	(void)data;
	pipe_cmd_elem = cmd->pipe_cmds;
	while (pipe_cmd_elem)
	{
		pipe_cmd = pipe_cmd_elem->content;
		if (pipe_cmd->forked)
			waitpid(pipe_cmd->pid, &status, 0);
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
		exec_pipe_cmd(data, cmd, pipe_cmd_elem->content);
		pipe_cmd_elem = pipe_cmd_elem->next;
	}
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
