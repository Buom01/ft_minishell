/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdescam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 14:44:47 by frdescam          #+#    #+#             */
/*   Updated: 2020/10/31 19:04:41 by frdescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "minishell.h"
#include "parsing.h"

t_cmd		*get_next_pipe_cmd(t_string *cmd, unsigned int *i)
{
	int			start;
	int			inside_quote;
	int			inside_dquote;
	t_cmd		*next_pipe_cmd;

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
	if (!(next_pipe_cmd = malloc(sizeof(t_cmd))) ||
		!(next_pipe_cmd->string = ft_string_sub(cmd, start, *i - start - 1)))
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
		((t_cmd *)new_elem->content)->fd_in = 0;
		((t_cmd *)new_elem->content)->fd_out = 1;
		ft_lstadd_back(&pipes_cmds, new_elem);
	}
	return (pipes_cmds);
}

void		handle_middle_cmd(int pipefd[2], int last_pipefd[2],
								t_list *pipe_cmd)
{
	copy_arr_val(last_pipefd, pipefd);
	if (pipe(pipefd) == -1)
		panic(ERR_PIPE);
	((t_cmd *)pipe_cmd->content)->fd_in = last_pipefd[0];
	((t_cmd *)pipe_cmd->content)->fd_out = pipefd[1];
}

void		exec_pipes(t_string *cmd, char **env)
{
	t_list	*pipes_cmds;
	t_list	*pipe_cmd;
	int		pipefd[2];
	int		last_pipefd[2];

	pipes_cmds = get_pipes_cmds(cmd);
	pipe_cmd = pipes_cmds;
	if (pipe(pipefd) == -1)
		panic(ERR_PIPE);
	while (pipe_cmd)
	{
		if (pipe_cmd == pipes_cmds && pipe_cmd->next)
			((t_cmd *)pipe_cmd->content)->fd_out = pipefd[1];
		else if (!pipe_cmd->next && pipe_cmd != pipes_cmds)
			((t_cmd *)pipe_cmd->content)->fd_in = pipefd[0];
		else if (pipe_cmd->next && pipe_cmd != pipes_cmds)
			handle_middle_cmd(pipefd, last_pipefd, pipe_cmd);
		exec_redir(((t_cmd *)pipe_cmd->content), env);
		pipe_cmd = pipe_cmd->next;
	}
	ft_lstclear(&pipes_cmds, &t_cmd_destroyer);
}
