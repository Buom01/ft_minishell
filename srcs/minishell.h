/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 15:24:32 by badam             #+#    #+#             */
/*   Updated: 2020/09/16 16:33:09 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <stdio.h>
# include <sys/stat.h>
# include "libft.h"

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

#endif
