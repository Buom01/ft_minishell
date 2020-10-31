/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdescam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 13:47:33 by frdescam          #+#    #+#             */
/*   Updated: 2020/10/31 19:57:22 by frdescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	panic(t_error err_code)
{
	if (err_code == ERR_MALLOC)
		ft_printf("Error : out of memory ... exiting\n");
	else if (err_code == ERR_READ)
		ft_printf("Error : cannot read stdin ... exiting\n");
	else if (err_code == ERR_UNIMPLENTED)
		ft_printf("Error : unimplented function ... exiting\n");
	else if (err_code == ERR_PRINTF)
		ft_printf("Error : ft_printf returned negative value ... exiting\n");
	else
		ft_printf("Unknown Error ... exiting\n");
	exit(ERR);
}

void	print_warning(t_error err_code)
{
	if (err_code == ERR_QUOTE)
		ft_printf("Syntax error : The command is not complete\n");
	else if (err_code == ERR_EMPTY_COMMAND)
		ft_printf("Syntax error : Empty command\n");
	else if (err_code == ERR_SYNTAX)
		ft_printf("Syntax error\n");
	else if (err_code == ERR_ERRNO)
		ft_printf("\n"); // Print errno
	else if (err_code == ERR_UNKNOWN_CMD)
		ft_printf("Error : Unknown command\n");
	else if (err_code == ERR_OPEN)
		ft_printf("Error : Cannot open file\n");
	else
		ft_printf("Unknown error\n");
}
