/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_action.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdescam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 17:43:49 by frdescam          #+#    #+#             */
/*   Updated: 2020/10/31 18:09:22 by frdescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
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

void		exec_external_program(char **argv, char **env, t_cmd *cmd)
{
	int			status;
	char		*filepath;

	env_init(env);
	cmd->pid = fork();
	if (cmd->pid == 0)
	{
		if (!(filepath = whereis(argv[0])))
			print_warning(ERR_UNKNOWN_CMD);
		else
			execve(filepath, argv, env);
		exit(0);
	}
	else
	{
		waitpid(cmd->pid, &status, 0);
	}
}

void		exec_action(t_cmd *cmd, char **env)
{
	size_t		argc;
	char		**argv;

	if (!(argv = ft_split(cmd->string->str, "\f\t \n\r\v")))
		panic(ERR_MALLOC);
	argc = get_argc(argv);
	if (exec_builtin(argc, argv) != OK)
		exec_external_program(argv, env, cmd);
	ft_clear_splitted(argv);
}
