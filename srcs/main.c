/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdescam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 11:18:54 by frdescam          #+#    #+#             */
/*   Updated: 2020/09/27 14:43:17 by frdescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <minishell.h>
#include "parsing/parsing.h"

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

int	main(void)
{
	int			read_ret;
	t_string	*line;

	if (!(line = ft_string_new()))
		panic(ERR_MALLOC);
	ft_printf("This is a prompt please enter your cmd $ ");
	while ((read_ret = read_full_line(line)) >= 0)
	{
		if (read_ret == 0)
			break ;
		printf("executing %s\n", line->str);
		exec_line(line);
		ft_string_destroy(line);
		if (!(line = ft_string_new()))
			panic(ERR_MALLOC);
		ft_printf("This is a prompt please enter your cmd $ ");
	}
	ft_string_destroy(line);
	if (read_ret == -1)
		panic(ERR_READ);
	write(1, "exit\n", 5);
}
