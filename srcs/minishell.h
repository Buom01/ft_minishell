/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 15:24:32 by badam             #+#    #+#             */
/*   Updated: 2020/11/21 12:33:36 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <stdio.h>
# include <sys/stat.h>
# include <limits.h>
# include <string.h>
# include <errno.h>
# include "libft.h"
# include "builtins/builtins.h"

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
	ERR_PIPE,
	ERR_EMPTY_COMMAND,
	ERR_TOOMUCH_ARGS,
	ERR_ROOTPARENT,
	ERR_ERRNO,
	ERR_OPEN,
	ERR_UNKNOWN_CMD,
	ERR_UNINIT_ENV_DICO,
	ERR_DOUBLE_INIT_ENV_DICO
}					t_error;

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

/*
**  Data structure :
**
**              ┌───────────────────  data
**      main()  ┤                     ├─ env
**              ├───────────────────  ├─ line
** parse_line() ┤                     └─ cmds            -> list
**              ├───────────────────     ├─ cmd
**              │            ┌──────     └─ pipe_cmds    -> list
**              │  parse_    │              ├─ pipe_cmd
** parse_cmds() ┤  redirs()  ┤              ├─ fd_in
**              │            └──────        ├─ fd_out
**              └───────────────────        └─ pid
*/

typedef struct		s_data
{
	char			**env;
	t_string		*line;
	t_list			*cmds;
}					t_data;

typedef struct		s_cmd
{
	t_string		*cmd;
	t_list			*pipe_cmds;
}					t_cmd;

typedef struct		s_pipe_cmd
{
	t_string		*pipe_cmd;
	pid_t			pid;
	int				fd_in;
	int				fd_out;
}					t_pipe_cmd;

typedef struct		s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

void				exec_line(t_data *data);
void				init_data(t_data *data);
void				free_data(t_data *data);
int					*should_prompt_be_printed(void);

bool				env_verify_name(const char *str);
t_env_equality		env_isvalid_equality(const char *str, bool sanitizename);
bool				env_isinternal(const char *key);
char				*env_toequality(t_env *env);
size_t				env_listlen(t_env *list);
char				*env_parse_key(const char *eqlt);
char				*env_parse_value(const char *eqlt);
t_env				**env_dictionary(void);
void				env_init(char **environ);
void				env_shutdown(void);
t_env				*env_create(char *equality);
t_env				*env_set(const char *key, const char *value);
void				env_unset(const char *key);
t_env				*env_get(const char *key);
char				*env_get_value(const char *key);
char				**env_get_array();
void				env_clear_array(char **envs);

t_error				path_pwd(char **str);
t_error				path_trailslash(char **str);
t_error				path_dir_exists(const char *path, bool follow_links,
							bool *ret);
t_error				path_canonize(char **str);
t_error				path_relativize(char **path, char *pwd);
char				*path_join(char *begin, char *end);

t_builtin			get_builtin(char *command);
t_error				builtins(t_builtin builtin, size_t argc, char **argv);
t_error				exec_builtin(size_t argc, char **argv);
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
