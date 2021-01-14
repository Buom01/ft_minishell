/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdescam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 18:40:52 by frdescam          #+#    #+#             */
/*   Updated: 2021/01/14 21:50:03 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_fork(t_data *data, t_cmd *cmd, t_pipe_cmd *pipe_cmd, t_builtin bi)
{
	char		*filepath;

	pipe_cmd->pid = fork();
	if (pipe_cmd->pid == 0)
	{
		close_fds(data, cmd, pipe_cmd);
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
		if (bi == BI_NONE && !filepath)
			exit(127);
		else
			exit(0);
	}
}

void	ex_pipe_cmd(t_data *data, t_cmd *cmd, t_pipe_cmd *pipe_cmd)
{
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
		exec_fork(data, cmd, pipe_cmd, bi);
}
