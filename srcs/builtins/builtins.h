/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 18:39:37 by badam             #+#    #+#             */
/*   Updated: 2020/10/09 21:37:32 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdbool.h>

typedef struct		s_echo_opts
{
	bool			nonewline;
}					t_echo_opts;

typedef struct		s_cd_opts
{
	char			*home;
	char			*path;
	bool			relative;
	bool			dot;
}					t_cd_opts;

#endif
