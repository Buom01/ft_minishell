/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdescam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 17:11:41 by frdescam          #+#    #+#             */
/*   Updated: 2020/11/11 17:33:20 by frdescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft.h"
#include "minishell.h"
#include "parsing.h"

void		skip_start(t_string *redir, int *i)
{
	if (redir->str[*i] == '>')
		(*i)++;
	while (ft_strchr("\f\t \n\r\v", redir->str[*i]))
		(*i)++;
}

t_string	*extract_filename(t_string *redir)
{
	t_string	*filename;
	int			i;
	int			inside_quote;
	int			inside_dquote;

	inside_dquote = 0;
	inside_quote = 0;
	filename = ft_string_new();
	i = 1;
	skip_start(redir, &i);
	while (redir->str[i])
	{
		if (redir->str[i] == '"' && !inside_quote)
			inside_dquote = !inside_dquote;
		else if (redir->str[i] == '\'' && !inside_dquote)
			inside_quote = !inside_quote;
		else if ((redir->str[i] == '<' || redir->str[i] == '>') &&
				!inside_quote && !inside_dquote)
			break ;
		else
			ft_string_push_char(filename, redir->str[i]);
		i++;
	}
	return (filename);
}

void		handle_redir(t_pipe_cmd *pipe_cmd, t_string *redir)
{
	t_string	*filename;

	filename = extract_filename(redir);
	if (!ft_strncmp(">>", redir->str, 2))
	{
		if (pipe_cmd->fd_out > 2)
			close(pipe_cmd->fd_out);
		pipe_cmd->fd_out =
			open(filename->str, O_RDWR | O_APPEND | O_CREAT, 00644);
	}
	else if (!ft_strncmp(">", redir->str, 1))
	{
		if (pipe_cmd->fd_out > 2)
			close(pipe_cmd->fd_out);
		pipe_cmd->fd_out = open(filename->str, O_RDWR | O_CREAT, 00644);
	}
	else if (!ft_strncmp("<", redir->str, 1))
	{
		if (pipe_cmd->fd_in > 2)
			close(pipe_cmd->fd_in);
		if ((pipe_cmd->fd_in = open(filename->str, 0)) == -1)
			print_warning(ERR_OPEN);
	}
	ft_string_destroy(filename);
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
