/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdescam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 16:50:36 by frdescam          #+#    #+#             */
/*   Updated: 2020/11/09 17:25:34 by frdescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include "libft.h"
#include "minishell.h"
#include "parsing.h"

void			fill_pipe_fds(t_list *pipe_cmds)
{
	t_list	*pipe_cmd_elem;
	int		pipefd[2];
	int		lastpipefd[2];

	pipe_cmd_elem = pipe_cmds;
	while (pipe_cmd_elem)
	{
		if (pipe_cmd_elem == pipe_cmds && pipe_cmd_elem->next)
		{
			pipe(pipefd);
			((t_pipe_cmd *)pipe_cmd_elem->content)->fd_in = STDIN_FILENO;
			((t_pipe_cmd *)pipe_cmd_elem->content)->fd_out = pipefd[1];
		}
		else if (pipe_cmd_elem != pipe_cmds && pipe_cmd_elem->next)
		{
			lastpipefd[0] = pipefd[0];
			pipe(pipefd);
			((t_pipe_cmd *)pipe_cmd_elem->content)->fd_in = lastpipefd[0];
			((t_pipe_cmd *)pipe_cmd_elem->content)->fd_out = pipefd[1];
		}
		else if (pipe_cmd_elem != pipe_cmds && !pipe_cmd_elem->next)
			((t_pipe_cmd *)pipe_cmd_elem->content)->fd_in = pipefd[0];
		pipe_cmd_elem = pipe_cmd_elem->next;
	}
}

t_pipe_cmd		*get_next_pipe_cmd(t_string *cmd, unsigned int *i)
{
	int			start;
	int			inside_quote;
	int			inside_dquote;
	t_pipe_cmd		*next_pipe_cmd;

	inside_quote = 0;
	inside_dquote = 0;
	start = *i;
	while (*i < cmd->len)
	{
		if (cmd->str[*i] == '"' && !inside_quote)
			inside_dquote = !inside_dquote;
		else if (cmd->str[*i] == '\'' && !inside_dquote)
			inside_quote = !inside_quote;
		else if (cmd->str[*i] == '|' && !inside_quote && !inside_dquote)
		{
			(*i)++;
			break ;
		}
		(*i)++;
	}
	if (!(next_pipe_cmd = malloc(sizeof(t_pipe_cmd))) ||
		!(next_pipe_cmd->pipe_cmd = ft_string_sub(cmd, start, *i - start - 1)))
		panic(ERR_MALLOC);
	return (next_pipe_cmd);
}

t_list		*get_pipes_cmds(t_string *cmd)
{
	t_list			*pipes_cmds;
	t_list			*new_elem;
	unsigned int	i;

	pipes_cmds = NULL;
	i = 0;
	while (i < cmd->len)
	{
		if (!(new_elem = ft_lstnew("", get_next_pipe_cmd(cmd, &i))))
			panic(ERR_MALLOC);
		((t_pipe_cmd *)new_elem->content)->fd_in = STDIN_FILENO;
		((t_pipe_cmd *)new_elem->content)->fd_out = STDOUT_FILENO;
		ft_lstadd_back(&pipes_cmds, new_elem);
	}
	return (pipes_cmds);
}

void		parse_cmds(t_data *data)
{
	t_list		*cmd_elem;
	t_cmd		*cmd;

	cmd_elem = data->cmds;
	while (cmd_elem)
	{
		cmd = cmd_elem->content;
		cmd->pipe_cmds = get_pipes_cmds(cmd->cmd);
		fill_pipe_fds(cmd->pipe_cmds);
		cmd_elem = cmd_elem->next;
	}
}
