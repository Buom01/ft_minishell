/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdescam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 11:18:54 by frdescam          #+#    #+#             */
/*   Updated: 2020/11/08 18:40:55 by frdescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <minishell.h>
#include "parsing/parsing.h"
#include "libft.h"

int	is_line_empty(t_string *line)
{
	char	**splitted;
	int		ret;

	if (!(splitted = ft_split(line->str, "\f\t \n\r\v")))
		panic(ERR_MALLOC);
	if (!*splitted)
		ret = 1;
	else
		ret = 0;
	ft_clear_splitted(splitted);
	return (ret);
}

int	read_full_line(t_string *line)
{
	char	buf[11];
	int		read_ret;
	int		full_line;

	full_line = 0;
	while (!full_line)
	{
		read_ret = read(0, buf, 10);
		if (read_ret == -1)
			return (-1);
		if (read_ret == 0 && line->len == 0)
			return (read_ret);
		buf[read_ret] = '\0';
		if (!(ft_string_push(line, buf)))
			panic(ERR_MALLOC);
		if (line->str[line->len - 1] == '\n')
			full_line = 1;
	}
	return (read_ret);
}

void	wait_for_input(t_data *data)
{
	int			read_ret;

	if (!(data->line = ft_string_new()))
		panic(ERR_MALLOC);
	ft_printf("This is a prompt please enter your cmd $ ");
	while ((read_ret = read_full_line(data->line)) >= 0)
	{
		if (read_ret == 0)
		{
			write(1, "exit\n", 5);
			exit(0);
		}
		if (read_ret == -1)
			panic(ERR_READ);
		if (!is_line_empty(data->line))
			return ;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data		data;

	(void)argc;
	(void)argv;
	data.env = env;
	env_init(data.env);
	while (1)
	{
		wait_for_input(&data);
		parse_line(&data);
		parse_cmds(&data);
		parse_redirs(&data);
		exec_line(&data);
	}
	env_shutdown();
}
