/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdescam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 13:47:33 by frdescam          #+#    #+#             */
/*   Updated: 2021/01/11 22:19:59 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	else if (err_code == ERR_UNINIT_ENV_DICO)
		ft_printf("Error : environ dico must be initialized ... exiting\n");
	else if (err_code == ERR_DOUBLE_INIT_ENV_DICO)
		ft_printf("Error : environ dico is already initialized ... exiting\n");
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
	else if (err_code == ERR_UNKNOWN_CMD)
		ft_printf("Error : Unknown command\n");
	else if (err_code == ERR_OPEN)
		ft_printf("Error : Cannot open file\n");
	else if (err_code == ERR_ERRNO)
		ft_printf("%s\n", strerror(errno));
	else if (err_code == ERR_PRINTF)
		ft_printf("ft_printf returned negative value\n");
	else if (err_code == ERR_TOOMUCH_ARGS)
		ft_printf("Too much arguments provided\n");
	else if (err_code == ERR_ROOTPARENT)
		ft_printf("Cannot get parent of the root directory\n");
	else
		ft_printf("Unknown error\n");
}
