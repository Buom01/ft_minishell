/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdescam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 14:34:05 by frdescam          #+#    #+#             */
/*   Updated: 2020/10/28 11:31:12 by frdescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

void	exec_line(t_string *line);
void	exec_pipes(t_string *cmd);
void	exec_redir(t_string *cmd, int fd_in, int fd_out);
void	exec_action(t_string *cmd, int fd_in, int fd_out);
void	ft_string_destroy_wrapper(void *content);

#endif
