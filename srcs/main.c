/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdescam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 11:18:54 by frdescam          #+#    #+#             */
/*   Updated: 2021/01/15 22:38:28 by frdescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "minishell.h"
#include "parsing/parsing.h"
#include "libft.h"

int	is_line_empty(t_string *line)
{
	char	**splitted;
	int		ret;

	splitted = ft_split(line->str, "\f\t \n\r\v");
	if (!splitted)
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

	data->line = ft_string_new();
	if (!data->line)
		panic(ERR_MALLOC);
	ft_putstr_fd(MSG_PROMPT, 1);
	*should_prompt_be_printed() = 1;
	read_ret = read_full_line(data->line);
	while (read_ret >= 0)
	{
		if (read_ret == 0)
			handle_ctrl_d(data);
		if (read_ret == -1)
			panic(ERR_READ);
		if (!is_line_empty(data->line))
		{
			*should_prompt_be_printed() = 0;
			return ;
		}
		ft_putstr_fd(MSG_PROMPT, 1);
		read_ret = read_full_line(data->line);
	}
}

void	handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		if (*should_prompt_be_printed())
		{
			ft_string_destroy(get_data()->line);
			get_data()->line = ft_string_new();
			ft_putstr_fd(MSG_PROMPT, 1);
		}
		get_data()->sigint_received = 1;
		env_set("?", "130");
	}
	else if (sig == SIGQUIT)
	{
		printf("Quit\n");
		get_data()->sigquit_received = 1;
		env_set("?", "131");
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data		*data;

	(void)argc;
	(void)argv;
	data = get_data();
	ft_bzero(data, sizeof(t_data));
	env_init(env);
	signal(SIGINT, &handle_sig);
	signal(SIGQUIT, &handle_sig);
	while (1)
	{
		wait_for_input(data);
		parse_line(data);
		parse_cmds(data);
		if (parse_redirs(data) == ERR)
		{
			free_data(data);
			continue ;
		}
		post_process(data);
		exec_line(data);
		free_data(data);
	}
}
