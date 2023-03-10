/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirs_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdescam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 17:22:41 by frdescam          #+#    #+#             */
/*   Updated: 2021/01/15 23:53:02 by frdescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	go_to_redir_end(t_string *pipe_cmd, unsigned int *i)
{
	int	inside_quote;
	int	inside_dquote;

	inside_dquote = 0;
	inside_quote = 0;
	while (*i < pipe_cmd->len)
	{
		if (pipe_cmd->str[*i] == '"' && !inside_quote)
			inside_dquote = !inside_dquote;
		else if (pipe_cmd->str[*i] == '\'' && !inside_dquote)
			inside_quote = !inside_quote;
		else if (ft_strchr("\f\t \n\r\v<>", pipe_cmd->str[*i])
			&& !inside_quote && !inside_dquote)
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
	redir = ft_string_remove(pipe_cmd, start, i);
	if (!redir)
		panic(ERR_MALLOC);
	return (redir);
}

int	in_quote(t_pipe_cmd *pipe_cmd, int i, int inside_quote)
{
	if (pipe_cmd->pipe_cmd->str[i] == '"' && !inside_quote && i > 0
		&& pipe_cmd->pipe_cmd->str[i - 1] != '\\')
		return (1);
	return (0);
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
		if (in_quote(pipe_cmd, i, inside_quote))
			inside_dquote = !inside_dquote;
		else if (pipe_cmd->pipe_cmd->str[i] == '\'' && !inside_dquote && i > 0
			&& pipe_cmd->pipe_cmd->str[i - 1] != '\\')
			inside_quote = !inside_quote;
		else if ((pipe_cmd->pipe_cmd->str[i] == '<'
				|| pipe_cmd->pipe_cmd->str[i] == '>')
			&& !inside_quote && !inside_dquote)
			break ;
		i++;
	}
	if (i == pipe_cmd->pipe_cmd->len)
		return (NULL);
	next_redir = extract_redir(pipe_cmd->pipe_cmd, i);
	return (next_redir);
}
