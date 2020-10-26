/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdescam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 16:51:12 by frdescam          #+#    #+#             */
/*   Updated: 2020/10/24 14:07:40 by frdescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parsing.h"
#include <unistd.h>

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

t_string	*get_next_redir(t_string *cmd, int *error)
{
	t_string		*next_redir;
	int				inside_quote;
	int				inside_dquote;
	unsigned int	i;

	inside_dquote = 0;
	inside_quote = 0;
	i = 0;
	while (i < cmd->len)
	{
		if (cmd->str[i] == '"' && !inside_quote)
			inside_dquote = !inside_dquote;
		else if (cmd->str[i] == '\'' && !inside_dquote)
			inside_quote = !inside_quote;
		else if ((cmd->str[i] == '<' || cmd->str[i] == '>') &&
				!inside_quote && !inside_dquote)
			break ;
		i++;
	}
	if (i == cmd->len)
		return (NULL);
	if (!(next_redir = extract_redir(cmd, i)))
		*error = 1;
	return (next_redir);
}

void		handle_redir(t_string *redir, int *fd_in, int *fd_out)
{
	ft_printf("redir : %s\n", redir->str);
	(void)fd_in;
	(void)fd_out;
}

void		exec_redir(t_string *cmd, int fd_in, int fd_out)
{
	t_string	*next_redir;
	int			error;

	error = 0;
	while ((next_redir = get_next_redir(cmd, &error)))
	{
		if (error)
			return ;
		handle_redir(next_redir, &fd_in, &fd_out);
	}
	exec_action(cmd, fd_in, fd_out);
}
