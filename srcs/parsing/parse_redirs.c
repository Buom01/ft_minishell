/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdescam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 17:11:41 by frdescam          #+#    #+#             */
/*   Updated: 2020/11/09 20:20:37 by frdescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft.h"
#include "minishell.h"
#include "parsing.h"

void		go_to_redir_end(t_string *pipe_cmd, unsigned int *i)
{
	int			inside_quote;
	int			inside_dquote;

	inside_dquote = 0;
	inside_quote = 0;
	while (*i < pipe_cmd->len)
	{
		if (pipe_cmd->str[*i] == '"' && !inside_quote)
			inside_dquote = !inside_dquote;
		else if (pipe_cmd->str[*i] == '\'' && !inside_dquote)
			inside_quote = !inside_quote;
		else if (ft_strchr("\f\t \n\r\v<>", pipe_cmd->str[*i]) &&
				!inside_quote && !inside_dquote)
			break ;
		(*i)++;
	}
}

t_string	*extract_redir(t_string *pipe_cmd, unsigned int i)
{
	t_string	*redir;
	int			start;

	start = i;
	i++;
	if (pipe_cmd->str[i] == '>')
		i++;
	while (ft_strchr("\f\t \n\r\v", pipe_cmd->str[i]))
		i++;
	go_to_redir_end(pipe_cmd, &i);
	if (!(redir = ft_string_remove(pipe_cmd, start, i)))
		panic(ERR_MALLOC);
	return (redir);
}

t_string	*get_next_redir(t_pipe_cmd *pipe_cmd)
{
	t_string		*next_redir;
	int				inside_quote;
	int				inside_dquote;
	unsigned int	i;

	inside_dquote = 0;
	inside_quote = 0;
	i = 0;
	while (i < pipe_cmd->pipe_cmd->len)
	{
		if (pipe_cmd->pipe_cmd->str[i] == '"' && !inside_quote)
			inside_dquote = !inside_dquote;
		else if (pipe_cmd->pipe_cmd->str[i] == '\'' && !inside_dquote)
			inside_quote = !inside_quote;
		else if ((pipe_cmd->pipe_cmd->str[i] == '<' ||
				pipe_cmd->pipe_cmd->str[i] == '>') &&
				!inside_quote && !inside_dquote)
			break ;
		i++;
	}
	if (i == pipe_cmd->pipe_cmd->len)
		return (NULL);
	if (!(next_redir = extract_redir(pipe_cmd->pipe_cmd, i)))
		(void)next_redir;// TODO handle this case
	return (next_redir);
}

void		handle_redir(t_pipe_cmd *pipe_cmd, t_string *redir)
{
	if (!ft_strncmp(">>", redir->str, 2))
	{
		if (pipe_cmd->fd_out > 2)
			close(pipe_cmd->fd_out);
		pipe_cmd->fd_out = open(&redir->str[2],
				O_RDWR | O_APPEND | O_CREAT, 00644);
	}
	else if (!ft_strncmp(">", redir->str, 1))
	{
		if (pipe_cmd->fd_out > 2)
			close(pipe_cmd->fd_out);
		pipe_cmd->fd_out = open(&redir->str[1], O_RDWR | O_CREAT, 00644);
	}
	else if (!ft_strncmp("<", redir->str, 1))
	{
		if (pipe_cmd->fd_in > 2)
			close(pipe_cmd->fd_in);
		if ((pipe_cmd->fd_in = open(&redir->str[1], 0)) == -1)
			print_warning(ERR_OPEN);
	}
}

void		parse_redirs(t_data *data)
{
	t_list		*cmd_elem;
	t_list		*pipe_cmd_elem;
	t_string	*next_redir;

	cmd_elem = data->cmds;
	while (cmd_elem)
	{
		pipe_cmd_elem = ((t_cmd *)cmd_elem->content)->pipe_cmds;
		while (pipe_cmd_elem)
		{
			while ((next_redir = get_next_redir(pipe_cmd_elem->content)))
				handle_redir(pipe_cmd_elem->content, next_redir);
			pipe_cmd_elem = pipe_cmd_elem->next;
		}
		cmd_elem = cmd_elem->next;
	}
}
