/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdescam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:49:14 by frdescam          #+#    #+#             */
/*   Updated: 2021/01/14 17:59:28 by frdescam         ###   ########.fr       */
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
