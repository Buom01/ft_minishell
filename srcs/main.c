/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdescam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 11:18:54 by frdescam          #+#    #+#             */
/*   Updated: 2020/09/20 16:42:20 by frdescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <minishell.h>

int	read_full_cmd(t_string *cmd)
{
	char	buf[11];
	int		read_ret;
	int		full_cmd;

	full_cmd = 0;
	while (!full_cmd)
	{
		read_ret = read(0, buf, 10);
		if (read_ret == -1)
			return (-1);
		if (read_ret == 0 && cmd->len == 0)
			return (read_ret);
		buf[read_ret] = '\0';
		if (!(ft_string_push(cmd, buf)))
			panic(ERR_MALLOC);
		if (cmd->str[cmd->len - 1] == '\n')
			full_cmd = 1;
	}
	return (read_ret);
}

int	main(void)
{
	int			read_ret;
	t_string	*cmd;

	if (!(cmd = ft_string_new()))
		panic(ERR_MALLOC);
	ft_printf("This is a prompt please enter your cmd $ ");
	while ((read_ret = read_full_cmd(cmd)) >= 0)
	{
		if (read_ret == 0)
			break ;
		printf("executing %s\n", cmd->str);
		//TODO : implement parsing and call it here
		ft_string_destroy(cmd);
		if (!(cmd = ft_string_new()))
			panic(ERR_MALLOC);
		ft_printf("This is a prompt please enter your cmd $ ");
	}
	ft_string_destroy(cmd);
	if (read_ret == -1)
		panic(ERR_READ);
	write(1, "exit\n", 5);
}
