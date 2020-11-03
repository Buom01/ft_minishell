/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdescam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 18:46:12 by frdescam          #+#    #+#             */
/*   Updated: 2020/10/31 18:54:05 by frdescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parsing.h"

void		t_cmd_destroyer(void *cmd)
{
	ft_string_destroy(((t_cmd *)cmd)->string);
	free(cmd);
}

void		copy_arr_val(int arr1[2], int arr2[2])
{
	arr1[0] = arr2[0];
	arr1[1] = arr2[1];
}
