/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdescam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 13:47:33 by frdescam          #+#    #+#             */
/*   Updated: 2021/01/14 17:51:46 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	panic(t_error err_code)
{
	if (err_code == ERR_MALLOC)
		printf("Error : out of memory ... exiting\n");
	else if (err_code == ERR_READ)
		printf("Error : cannot read stdin ... exiting\n");
	else if (err_code == ERR_UNIMPLENTED)
		printf("Error : unimplented function ... exiting\n");
	else if (err_code == ERR_PRINTF)
		printf("Error : printf returned negative value ... exiting\n");
	else if (err_code == ERR_UNINIT_ENV_DICO)
		printf("Error : environ dico must be initialized ... exiting\n");
	else if (err_code == ERR_DOUBLE_INIT_ENV_DICO)
		printf("Error : environ dico is already initialized ... exiting\n");
	else
		printf("Unknown Error ... exiting\n");
	exit(ERR);
}

void	print_warning(t_error err_code)
{
	if (err_code == ERR_QUOTE)
		printf("Syntax error : The command is not complete\n");
	else if (err_code == ERR_EMPTY_COMMAND)
		printf("Syntax error : Empty command\n");
	else if (err_code == ERR_SYNTAX)
		printf("Syntax error\n");
	else if (err_code == ERR_UNKNOWN_CMD)
		printf("Error : Unknown command\n");
	else if (err_code == ERR_OPEN)
		printf("Error : Cannot open file\n");
	else if (err_code == ERR_ERRNO)
		printf("%s\n", strerror(errno));
	else if (err_code == ERR_PRINTF)
		printf("printf returned negative value\n");
	else if (err_code == ERR_TOOMUCH_ARGS)
		printf("Too much arguments provided\n");
	else if (err_code == ERR_ROOTPARENT)
		printf("Cannot get parent of the root directory\n");
	else
		printf("Unknown error\n");
}
