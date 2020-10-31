/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdescam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 14:34:05 by frdescam          #+#    #+#             */
/*   Updated: 2020/10/31 14:55:23 by frdescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

//typedef struct	s_process
//{
//	t_pid	pid;
//	int		fd_in;
//	int		fd_out;
//}				t_process
void	exec_line(t_string *line, char **env);
void	exec_pipes(t_string *cmd, char **env);
void	exec_redir(t_string *cmd, int fd_in, int fd_out, char **env);
void	exec_action(t_string *cmd, int fd_in, int fd_out, char **env);
void	ft_string_destroy_wrapper(void *content);

#endif
