/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdescam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 14:34:05 by frdescam          #+#    #+#             */
/*   Updated: 2020/11/11 17:28:56 by frdescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <sys/types.h>
# include "libft.h"
# include "minishell.h"

t_error			parse_line(t_data *data);
void			parse_cmds(t_data *data);
void			parse_redirs(t_data *data);
void			ft_string_destroy_wrapper(void *content);
t_string		*get_next_redir(t_pipe_cmd *pipe_cmd);

#endif
