/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdescam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 14:34:05 by frdescam          #+#    #+#             */
/*   Updated: 2020/10/31 18:47:33 by frdescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <sys/types.h>
# include "libft.h"

typedef struct	s_cmd
{
	pid_t		pid;
	int			fd_in;
	int			fd_out;
	t_string	*string;
}				t_cmd;
void			exec_line(t_string *line, char **env);
void			exec_pipes(t_string *cmd, char **env);
void			exec_redir(t_cmd *cmd, char **env);
void			exec_action(t_cmd *cmd, char **env);
void			ft_string_destroy_wrapper(void *content);
void			t_cmd_destroyer(void *cmd);
void			copy_arr_val(int arr1[2], int arr2[2]);

#endif
