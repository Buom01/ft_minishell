/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdescam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 00:09:21 by frdescam          #+#    #+#             */
/*   Updated: 2020/10/01 11:48:01 by frdescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "parsing.h"

static void	ft_string_destroy_wrapper(void *content)
{
	ft_string_destroy(content);
}

t_string	*check_next_cmd_errors(t_string *next_cmd, int inside_quote,
		int inside_dquote)
{
	if (inside_dquote || inside_quote)
	{
		print_warning(ERR_QUOTE);
		ft_string_destroy(next_cmd);
		return (NULL);
	}
	if (!next_cmd->str)
	{
		print_warning(ERR_EMPTY_COMMAND);
		ft_string_destroy(next_cmd);
		return (NULL);
	}
	return (next_cmd);
}

t_string	*get_next_cmd(t_string *line, size_t *i)
{
	t_string	*next_cmd;
	int			inside_quote;
	int			inside_dquote;

	if (!(next_cmd = ft_string_new()))
		panic(ERR_MALLOC);
	inside_dquote = 0;
	inside_quote = 0;
	while (*i < line->len)
	{
		if (line->str[*i] == '"' && !inside_quote)
			inside_dquote = !inside_dquote;
		else if (line->str[*i] == '\'' && !inside_dquote)
			inside_quote = !inside_quote;
		else if (line->str[*i] == ';' && !inside_quote && !inside_dquote)
		{
			(*i)++;
			break ;
		}
		ft_string_push_char(next_cmd, line->str[*i]);
		(*i)++;
	}
	return (check_next_cmd_errors(next_cmd, inside_quote, inside_dquote));
}

void		exec_line(t_string *line)
{
	size_t		i;
	t_list		*cmds;
	t_list		*cmd;
	t_string	*next_cmd;

	cmds = NULL;
	i = 0;
	while (i < line->len)
	{
		if (!(next_cmd = get_next_cmd(line, &i)))
		{
			ft_lstclear(&cmds, &ft_string_destroy_wrapper);
			return ;
		}
		if (!(cmd = ft_lstnew("", next_cmd)))
			panic(ERR_MALLOC);
		ft_lstadd_back(&cmds, cmd);
	}
	cmd = cmds;
	while (cmd)
	{
		exec_cmd(((t_string *)cmd->content));
		cmd = cmd->next;
	}
	ft_lstclear(&cmds, &ft_string_destroy_wrapper);
}
