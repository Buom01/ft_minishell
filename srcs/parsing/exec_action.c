/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_action.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdescam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 17:43:49 by frdescam          #+#    #+#             */
/*   Updated: 2020/10/28 11:21:06 by frdescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

size_t		get_argc(char **argv)
{
	size_t	argc;

	argc = 0;
	while (argv[argc])
		argc++;
	return (argc);
}

void		exec_action(t_string *cmd, int fd_in, int fd_out)
{
//	pid_t		pid;
	char		**argv;
	t_builtin	bi;
//	int			status;

	(void)fd_in;
	(void)fd_out;
	if (!(argv = ft_split(cmd->str, "\f\t \n\r\v")))
		panic(ERR_MALLOC);
	bi = get_builtin(argv[0]);
	builtins(bi, get_argc(argv), argv);
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
	ft_clear_splitted(argv);
}
