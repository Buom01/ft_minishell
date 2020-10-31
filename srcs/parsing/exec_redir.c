/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdescam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 16:51:12 by frdescam          #+#    #+#             */
/*   Updated: 2020/10/31 15:05:01 by frdescam         ###   ########.fr       */
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
	(void)fd_in;
	if (!ft_strncmp(">>", redir->str, 2))
	{
		*fd_out = open(&redir->str[3], O_APPEND | O_CREAT);
		ft_printf("double redir out\n");
	}
	else if (!ft_strncmp(">", redir->str, 1))
	{
		*fd_out = open(&redir->str[2], O_CREAT);
		ft_printf("simple redir out\n");
	}
	else if (!ft_strncmp("<", redir->str, 1))
		ft_printf("simple redir in\n");
}

void		exec_redir(t_string *cmd, int fd_in, int fd_out, char **env)
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
	exec_action(cmd, fd_in, fd_out, env);
}
