/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 18:39:37 by badam             #+#    #+#             */
/*   Updated: 2021/01/13 23:44:41 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdbool.h>

typedef enum e_env_equality
{
	ENV_EQ_MISFORMAT = -1,
	ENV_EQ_NONE = 0,
	ENV_EQ_UNIFIED = 1
}					t_env_equality;

typedef struct s_echo_opts
{
	bool			nonewline;
}					t_echo_opts;

typedef struct s_cd_opts
{
	char	*home;
	char	*path;
	bool	relative;
	bool	back;
	char	*pwd;
	char	*finalpath;
	bool	print;
}			t_cd_opts;

#endif
