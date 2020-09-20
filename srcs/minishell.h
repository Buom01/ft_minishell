/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 15:24:32 by badam             #+#    #+#             */
/*   Updated: 2020/09/20 13:34:22 by frdescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <stdio.h>
# include <sys/stat.h>
# include "libft.h"

# define ERR -1
# define OK 0
# define ERR_MALLOC 1
# define ERR_SYNTAX 2
# define ERR_READ 3

typedef struct		s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

void				env_init(t_env **entries, char **environ);
void				env_shutdown(t_env **entries);
t_env				*env_get(const t_env *entries, const char *key);
char				*env_get_value(const t_env *entries, const char *key);

char				*whereis(const char *filepath, t_env *entries);
void				panic(int err_code);

#endif
