/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdescam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 16:51:12 by frdescam          #+#    #+#             */
/*   Updated: 2020/10/20 17:02:33 by frdescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	exec_redir(t_string *cmd, int fd_in, int fd_out)
{
	ft_printf("cmd : %s, fd_in : %d, fd_out : %d\n", cmd->str, fd_in, fd_out);
}
