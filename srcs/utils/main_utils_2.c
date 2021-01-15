/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdescam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:49:14 by frdescam          #+#    #+#             */
/*   Updated: 2021/01/15 22:20:23 by frdescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>

void	handle_ctrl_d(t_data *data)
{
	free_data(data);
	env_shutdown();
	write(1, "exit\n", 5);
	exit(0);
}

void	handle_error_code(t_data *data, int status)
{
	char		*status_str;

	status_str = ft_itoa(status >> 8);
	if (data->sigint_received)
	{
		data->sigint_received = 0;
		env_set("?", "130");
	}
	else if (data->sigquit_received)
	{
		data->sigquit_received = 0;
		env_set("?", "131");
	}
	else
		env_set("?", status_str);
	free(status_str);
}
