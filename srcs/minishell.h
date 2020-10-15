/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 15:24:32 by badam             #+#    #+#             */
/*   Updated: 2020/10/16 00:03:52 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <stdio.h>
# include <sys/stat.h>
# include <limits.h>
# include "libft.h"

typedef enum		e_error
{
	ERR = -1,
	OK = 0,
	ERR_MALLOC,
	ERR_SYNTAX,
	ERR_READ,
	ERR_UNIMPLENTED,
	ERR_PRINTF,
	ERR_QUOTE,
	ERR_EMPTY_COMMAND,
	ERR_TOOMUCH_ARGS,
	ERR_ROOTPARENT,
	ERR_ERRNO
}					t_error;

typedef struct		s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef enum		e_builtin
{
	BI_NONE = -1,
	BI_ECHO,
	BI_CD,
	BI_PWD,
	BI_EXPORT,
	BI_UNSET,
	BI_ENV,
	BI_EXIT,
	BUILTINS_COUNT
}					t_builtin;

bool				env_isvalid_equality(const char *equality);
char				*env_parse_key(const char *equality);
char				*env_parse_value(const char *equality);
t_env				**env_dictionary(void);
void				env_init(char **environ);
void				env_shutdown(void);
t_env				*env_create(char *equality);
t_env				*env_set(const char *key, const char *value);
void				env_unset(const char *key);
t_env				*env_get(const char *key);
char				*env_get_value(const char *key);

char				*path_pwd(void);
t_error				path_dir_exists(const char *path, bool follow_links,
							bool *ret);
t_error				path_canonize(char **str);
t_error				path_relativize(char **path, char *pwd);
char				*path_join(char *begin, char *end);

t_builtin			get_builtin(char *command);
t_error				builtins(t_builtin builtin, size_t argc, char **argv);
t_error				builtin_export(size_t argc, char **argv);
t_error				builtin_unset(size_t argc, char **argv);
t_error				builtin_env(size_t argc, char **argv);
t_error				builtin_pwd(size_t argc, char **argv);
t_error				builtin_cd(size_t argc, char **argv);
t_error				builtin_echo(size_t argc, char **argv);
t_error				builtin_exit(size_t argc, char **argv);

char				*whereis(const char *filepath);
void				panic(t_error err_code);
void				print_warning(t_error err_code);

#endif
