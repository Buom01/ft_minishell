/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 22:35:11 by badam             #+#    #+#             */
/*   Updated: 2021/01/14 17:53:00 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

static void	exec_cd_cdpath_free(char **cdpath)
{
	char	**cdpath_cpy;

	cdpath_cpy = cdpath;
	while (*cdpath_cpy)
		free(*(cdpath_cpy++));
	free(cdpath);
}

static t_error	exec_cd_cdpath_exec(t_cd_opts *options, char **cdpath)
{
	char	*testpath;

	while (*cdpath)
	{
		testpath = path_join(*(cdpath++), options->path);
		if (!testpath)
			return (ERR_MALLOC);
		if (dir_exists(testpath, true))
		{
			options->finalpath = testpath;
			options->print = true;
			break ;
		}
		else
			free(testpath);
	}
	return (OK);
}

static t_error	exec_cd_cdpath(t_cd_opts *options, char *cdpath_env)
{
	t_error	err;
	char	**cdpath;

	err = OK;
	cdpath = ft_split(cdpath_env, ":");
	if (!cdpath)
		return (ERR_MALLOC);
	err = exec_cd_cdpath_exec(options, cdpath);
	if (err == OK && !options->finalpath)
		options->finalpath = ft_strdup(options->path);
	exec_cd_cdpath_free(cdpath);
	return (err);
}

static t_error	exec_cd(t_cd_opts *options)
{
	t_error	err;
	char	*cdpath_env;

	err = OK;
	cdpath_env = env_get_value("CDPATH");
	if (options->back)
		options->finalpath = ft_strdup(*(path_oldpath()));
	else if (options->relative && cdpath_env)
		err = exec_cd_cdpath(options, cdpath_env);
	else
		options->finalpath = ft_strdup(options->path);
	if (err == OK && !options->finalpath)
		return (ERR_MALLOC);
	if (err == OK)
		err = path_chdir(options->finalpath, options->pwd);
	if (err == OK && (options->back || options->print))
		printf("%s\n", options->finalpath);
	if (err == OK)
		free(options->finalpath);
	return (err);
}

t_error	builtin_cd(size_t argc, char **argv)
{
	t_cd_opts	options;
	t_error		err;

	err = OK;
	ft_bzero(&options, sizeof(options));
	if (argc > 1)
		return (ERR_TOOMUCH_ARGS);
	options.home = env_get_value("HOME");
	if (argc)
		options.path = *argv;
	else
		options.path = options.home;
	if (!options.path)
		return (OK);
	options.relative = (*options.path != '/');
	options.back = ft_strcmp(options.path, "-") == 0;
	err = path_pwd(&(options.pwd));
	if (err == OK && options.path)
		err = exec_cd(&options);
	free(options.pwd);
	return (err);
}
