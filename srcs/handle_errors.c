/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdescam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 13:47:33 by frdescam          #+#    #+#             */
/*   Updated: 2020/09/20 13:47:35 by frdescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	panic(int err_code)
{
	if (err_code == ERR)
		ft_printf("Unknown Error ... exiting\n");
	else if (err_code == ERR_MALLOC)
		ft_printf("Error : out of memory ... exiting\n");
	else if (err_code == ERR_READ)
		ft_printf("Error : cannot read stdin ... exiting\n");
	exit(ERR);
}
