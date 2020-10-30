/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_action.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdescam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 17:43:49 by frdescam          #+#    #+#             */
/*   Updated: 2020/10/30 13:55:42 by frdescam         ###   ########.fr       */
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

void		exec_external_program(char **argv)
{
	pid_t		pid;
	int			status;

	pid = fork();
	if (pid == 0)
	{
		execve(argv[0], argv, argv);
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}

void		exec_action(t_string *cmd, int fd_in, int fd_out)
{
	size_t		argc;
	char		**argv;

	(void)fd_in;
	(void)fd_out;
	if (!(argv = ft_split(cmd->str, "\f\t \n\r\v")))
		panic(ERR_MALLOC);
	argc = get_argc(argv);
	if (exec_builtin(argc, argv) != OK)
		exec_external_program(argv);
	ft_clear_splitted(argv);
}
