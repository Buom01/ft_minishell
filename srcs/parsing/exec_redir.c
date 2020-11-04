/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdescam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 16:51:12 by frdescam          #+#    #+#             */
/*   Updated: 2020/11/02 22:04:44 by frdescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft.h"
#include "minishell.h"
#include "parsing.h"

void		go_to_redir_end(t_string *cmd, unsigned int *i)
{
	int			inside_quote;
	int			inside_dquote;

	inside_dquote = 0;
	inside_quote = 0;
	while (*i < cmd->len)
	{
		if (cmd->str[*i] == '"' && !inside_quote)
			inside_dquote = !inside_dquote;
		else if (cmd->str[*i] == '\'' && !inside_dquote)
			inside_quote = !inside_quote;
		else if (ft_strchr("\f\t \n\r\v<>", cmd->str[*i]) &&
				!inside_quote && !inside_dquote)
			break ;
		(*i)++;
	}
}

t_string	*extract_redir(t_string *cmd, unsigned int i)
{
	t_string	*redir;
	int			start;

	start = i;
	i++;
	if (cmd->str[i] == '>')
		i++;
	while (ft_strchr("\f\t \n\r\v", cmd->str[i]))
		i++;
	go_to_redir_end(cmd, &i);
	if (!(redir = ft_string_remove(cmd, start, i)))
		panic(ERR_MALLOC);
	return (redir);
}

t_string	*get_next_redir(t_cmd *cmd, int *error)
{
	t_string		*next_redir;
	int				inside_quote;
	int				inside_dquote;
	unsigned int	i;

	inside_dquote = 0;
	inside_quote = 0;
	i = 0;
	while (i < cmd->string->len)
	{
		if (cmd->string->str[i] == '"' && !inside_quote)
			inside_dquote = !inside_dquote;
		else if (cmd->string->str[i] == '\'' && !inside_dquote)
			inside_quote = !inside_quote;
		else if ((cmd->string->str[i] == '<' || cmd->string->str[i] == '>') &&
				!inside_quote && !inside_dquote)
			break ;
		i++;
	}
	if (i == cmd->string->len)
		return (NULL);
	if (!(next_redir = extract_redir(cmd->string, i)))
		*error = 1;
	return (next_redir);
}

void		handle_redir(t_cmd *cmd, t_string *redir)
{
	if (!ft_strncmp(">>", redir->str, 2))
	{
		if (cmd->fd_out > 2)
			close(cmd->fd_out);
		cmd->fd_out = open(&redir->str[2], O_RDWR | O_APPEND | O_CREAT, 00644);
	}
	else if (!ft_strncmp(">", redir->str, 1))
	{
		if (cmd->fd_out > 2)
			close(cmd->fd_out);
		cmd->fd_out = open(&redir->str[1], O_RDWR | O_CREAT, 00644);
	}
	else if (!ft_strncmp("<", redir->str, 1))
	{
		if (cmd->fd_in > 2)
			close(cmd->fd_in);
		if ((cmd->fd_in = open(&redir->str[1], 0)) == -1)
			print_warning(ERR_OPEN);
	}
}

void		exec_redir(t_cmd *cmd, char **env)
{
	t_string	*next_redir;
	int			error;

	error = 0;
	while ((next_redir = get_next_redir(cmd, &error)))
	{
		if (error)
			return ;
		handle_redir(cmd, next_redir);
	}
	exec_action(cmd, env);
}
