/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_action.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdescam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 17:43:49 by frdescam          #+#    #+#             */
/*   Updated: 2020/10/26 12:13:47 by frdescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void		exec_action(t_string *cmd, int fd_in, int fd_out)
{
//	pid_t		pid;
	char		**splitted;
	t_builtin	bi;
//	int			status;

	ft_printf("cmd : %s, fd_in : %d, fd_out : %d\n", cmd->str, fd_in, fd_out);
	if (!(splitted = ft_split(cmd->str, "\f\t \n\r\v")))
		panic(ERR_MALLOC);
	bi = get_builtin(splitted[0]);
	builtins(bi, ft_strlen((char *)splitted), splitted);
//	pid = fork();
//	if (pid == 0)
//	{
//		bi = get_builtin(cmd->str);
//		builtins(bi, ft_strlen((char *)splitted), splitted);
//	}
//	else
//	{
//		waitpid(pid, &status, 0);
//	}
	ft_clear_splitted(splitted);
}
