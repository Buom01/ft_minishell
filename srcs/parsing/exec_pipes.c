/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdescam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 14:44:47 by frdescam          #+#    #+#             */
/*   Updated: 2020/10/31 14:55:54 by frdescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "minishell.h"
#include "parsing.h"

void		copy_arr_val(int arr1[2], int arr2[2])
{
	arr1[0] = arr2[0];
	arr1[1] = arr2[1];
}

t_string	*get_next_pipe_cmd(t_string *cmd, unsigned int *i)
{
	int			start;
	int			inside_quote;
	int			inside_dquote;
	t_string	*next_pipe_cmd;

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
	if (!(next_pipe_cmd = ft_string_sub(cmd, start, *i - start - 1)))
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
		ft_lstadd_back(&pipes_cmds, new_elem);
	}
	return (pipes_cmds);
}

void		exec_pipe_cmd(t_list *pipe_cmd, t_list *pipes_cmds,
							int pipefd[2], int last_pipefd[2], char **env)
{
	if (pipe_cmd == pipes_cmds && !pipe_cmd->next)
		exec_redir(pipe_cmd->content, 0, 1, env);
	else if (pipe_cmd == pipes_cmds)
		exec_redir(pipe_cmd->content, 0, pipefd[1], env);
	else if (!pipe_cmd->next)
		exec_redir(pipe_cmd->content, pipefd[0], 1, env);
	else
	{
		copy_arr_val(last_pipefd, pipefd);
		if (pipe(pipefd) == -1)
			panic(ERR_PIPE);
		exec_redir(pipe_cmd->content, last_pipefd[0], pipefd[1], env);
	}
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
		exec_pipe_cmd(pipe_cmd, pipes_cmds, pipefd, last_pipefd, env);
		pipe_cmd = pipe_cmd->next;
	}
	ft_lstclear(&pipes_cmds, &ft_string_destroy_wrapper);
}
