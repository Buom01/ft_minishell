/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdescam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 11:18:54 by frdescam          #+#    #+#             */
/*   Updated: 2020/12/29 17:18:12 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "minishell.h"
#include "parsing/parsing.h"
#include "libft.h"

int		is_line_empty(t_string *line)
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

int		read_full_line(t_string *line)
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
	ft_printf(MSG_PROMPT);
	*should_prompt_be_printed() = 1;
	while ((read_ret = read_full_line(data->line)) >= 0)
	{
		if (read_ret == 0)
		{
			free_data(data);
			env_shutdown();
			write(1, "exit\n", 5);
			exit(0);
		}
		if (read_ret == -1)
			panic(ERR_READ);
		if (!is_line_empty(data->line))
		{
			*should_prompt_be_printed() = 0;
			return ;
		}
		ft_printf(MSG_PROMPT);
	}
}

void	handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n");
		if (*should_prompt_be_printed())
			ft_printf(MSG_PROMPT);
	}
	else if (sig == SIGQUIT)
		ft_printf("Quit\n");
}

int		main(int argc, char **argv, char **env)
{
	t_data		data;

	(void)argc;
	(void)argv;
	init_data(&data);
	env_init(env);
	signal(SIGINT, &handle_sig);
	signal(SIGQUIT, &handle_sig);
	while (1)
	{
		wait_for_input(&data);
		parse_line(&data);
		parse_cmds(&data);
		parse_redirs(&data);
		exec_line(&data);
		free_data(&data);
	}
}
