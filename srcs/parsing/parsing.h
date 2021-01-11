/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdescam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 14:34:05 by frdescam          #+#    #+#             */
/*   Updated: 2021/01/11 21:21:07 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <sys/types.h>
# include "libft.h"
# include "minishell.h"

typedef	struct		s_pprocess_state
{
	t_pipe_cmd		*cmd;
	char			*cursor;
	char			*anchor;
	bool			in_quote;
	bool			in_dquote;
}					t_pprocess_state;

t_error				parse_line(t_data *data);
void				parse_cmds(t_data *data);
t_error				parse_redirs(t_data *data);
void				pp_replace(t_pprocess_state *st, ssize_t old_len,
							char *new_word,	t_string *str);
void				pp_strip(t_pprocess_state *st, ssize_t strip_len,
							t_string *str);
void				process_env(t_string *cmd, t_pprocess_state *st,
							char *cursor);
void				process_escape(t_string *cmd, t_pprocess_state *st,
							char *cursor);
bool				process_space(t_string *cmd, t_pprocess_state *st,
							char *cursor);
void				post_process(t_data *data);
void				ft_string_destroy_wrapper(void *content);
t_string			*get_next_redir(t_pipe_cmd *pipe_cmd);

#endif
