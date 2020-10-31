/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_action.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdescam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 17:43:49 by frdescam          #+#    #+#             */
/*   Updated: 2020/10/31 15:11:08 by frdescam         ###   ########.fr       */
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

void		exec_external_program(char **argv, char **env)
{
	pid_t		pid;
	int			status;
	char		*filepath;

	env_init(env);
	pid = fork();
	if (pid == 0)
	{
		if (!(filepath = whereis(argv[0])))
			print_warning(ERR_UNKNOWN_CMD);
		else
			execve(filepath, argv, env);
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}

void		exec_action(t_string *cmd, int fd_in, int fd_out, char **env)
{
	size_t		argc;
	char		**argv;

	(void)fd_in;
	(void)fd_out;
	if (!(argv = ft_split(cmd->str, "\f\t \n\r\v")))
		panic(ERR_MALLOC);
	argc = get_argc(argv);
	if (exec_builtin(argc, argv) != OK)
		exec_external_program(argv, env);
	ft_clear_splitted(argv);
}
