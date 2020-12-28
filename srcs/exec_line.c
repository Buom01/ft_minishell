/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdescam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 17:38:57 by frdescam          #+#    #+#             */
/*   Updated: 2020/12/28 18:16:02 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing/parsing.h"
#include "libft.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

size_t		get_argc(char **argv)
{
	size_t	argc;

	argc = 0;
	while (argv[argc])
		argc++;
	return (argc);
}

void		close_all_useless_fd(t_data *data, t_cmd *cmd, t_pipe_cmd *pipe_cmd)
{
	t_list	*cmds_elem;
	t_list	*pipe_cmd_elem;

	cmds_elem = data->cmds;
	while (cmds_elem)
	{
		pipe_cmd_elem = ((t_cmd *)cmds_elem->content)->pipe_cmds;
		while (pipe_cmd_elem && cmds_elem->content == cmd &&
				pipe_cmd_elem->content != pipe_cmd)
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

void		exec_pipe_cmd(t_data *data, t_cmd *cmd, t_pipe_cmd *pipe_cmd,
					bool should_fork)
{
	char	*filepath;
	int		argc;
	char	**argv;

	argv = ft_split(pipe_cmd->pipe_cmd->str, "\f\t \n\r\v");
	argc = get_argc(argv);
	pipe_cmd->forked = should_fork || get_builtin(*argv) == BI_NONE;
	if (!pipe_cmd->forked)
		exec_builtin(argc, argv);  // Handle error
	else if ((pipe_cmd->pid = fork()) == 0)
	{
		close_all_useless_fd(data, cmd, pipe_cmd);
		dup2(pipe_cmd->fd_in, STDIN_FILENO);
		dup2(pipe_cmd->fd_out, STDOUT_FILENO);
		if (exec_builtin(argc, argv) == ERR)  // Handle error
		{
			if (!(filepath = whereis(argv[0])))
				print_warning(ERR_UNKNOWN_CMD);
			else
				execve(filepath, argv, data->env);  // get env from env_get_array
		}
		close(pipe_cmd->fd_out);
		exit(0);
	}
	close_all_useless_fd(data, cmd, pipe_cmd);
}

void		wait_for_all_process_to_finish(t_data *data, t_cmd *cmd)
{
	t_list	*pipe_cmd_elem;
	int		status;
	t_pipe_cmd *pipe_cmd;

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

void		exec_cmd(t_data *data, t_cmd *cmd)
{
	t_list	*pipe_cmd_elem;
	bool	should_fork;

	data->env = env_get_array();
	pipe_cmd_elem = cmd->pipe_cmds;
	should_fork = !(pipe_cmd_elem && !(pipe_cmd_elem->next));
	while (pipe_cmd_elem)
	{
		exec_pipe_cmd(data, cmd, pipe_cmd_elem->content, should_fork);
		pipe_cmd_elem = pipe_cmd_elem->next;
	}
	wait_for_all_process_to_finish(data, cmd);
	env_clear_array(data->env);
}

void		exec_line(t_data *data)
{
	t_list	*cmds_elem;

	cmds_elem = data->cmds;
	while (cmds_elem)
	{
		exec_cmd(data, cmds_elem->content);
		cmds_elem = cmds_elem->next;
	}
}
