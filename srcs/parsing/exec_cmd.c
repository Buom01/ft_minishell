/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdescam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 00:08:00 by frdescam          #+#    #+#             */
/*   Updated: 2020/10/01 11:45:33 by frdescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static void	ft_string_destroy_wrapper(void *content)
{
	ft_string_destroy(content);
}

t_string	*get_next_word(size_t *i, t_string *cmd)
{
	t_string	*next_word;

	if (!(next_word = ft_string_new()))
		panic(ERR_MALLOC);
	while (cmd->str[*i] && ft_strchr("\f\t \n\r\v", cmd->str[*i]))
		(*i)++;
	if (cmd->str[*i] == '|')
	{
		ft_string_push_char(next_word, '|');
		(*i)++;
		return (next_word);
	}
	while (cmd->str[*i] && !ft_strchr("\f\t \n\r\v|", cmd->str[*i]))
	{
		ft_string_push_char(next_word, cmd->str[*i]);
		(*i)++;
	}
	if (!next_word->str)
	{
		ft_string_destroy(next_word);
		return (NULL);
	}
	return (next_word);
}

void		exec_cmd(t_string *cmd)
{
	size_t		i;
	t_list		*words;
	t_list		*word;
	t_string	*next_word;

	i = 0;
	words = NULL;
	while (i < cmd->len)
	{
		if ((next_word = get_next_word(&i, cmd)))
		{
			if (!(word = ft_lstnew("", next_word)))
				panic(ERR_MALLOC);
			ft_lstadd_back(&words, word);
		}
	}
	word = words;
	while (word)
	{
		ft_printf("executing %s\n", ((t_string *)word->content)->str);
		word = word->next;
	}
	ft_lstclear(&words, &ft_string_destroy_wrapper);
}
