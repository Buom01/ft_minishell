/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 21:03:19 by badam             #+#    #+#             */
/*   Updated: 2021/01/12 04:31:43 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

static t_error	step_five_test_cdpath(char **cdpath_array, t_cd_opts *options, char **curpath)
{
	char	*cdpath;
	t_error	err;

	err = OK;
	while (*cdpath_array)
	{
		if (**cdpath_array)
			cdpath = path_join(*cdpath_array, options->path);
		else
			cdpath = ft_strjoin("./", options->path);
		if (!cdpath)
		{
			err = ERR_MALLOC;
			break ;
		}
		if (dir_exists(cdpath, true))
		{
			*curpath = cdpath;
			break ;
		}
		free(cdpath);
		cdpath_array++;
	}
	if (err != OK)
		free(cdpath);
	return (err);
}

static t_error	step_five(t_cd_opts *options, char **curpath)
{
	char	*env_cdpath;
	char	**cdpath_array;
	t_error	err;

	env_cdpath = env_get_value("CDPATH");
	if (env_cdpath)
	{
		cdpath_array = ft_split(env_cdpath, ":");
		if (!cdpath_array)
			return (ERR_MALLOC);
		err = step_five_test_cdpath(cdpath_array, options, curpath);
		while (*cdpath_array)
			free(*(cdpath_array++));
		free(cdpath_array);
		if (err != OK)
			return (err);
		if (*curpath)
			return (OK);
	}
	*curpath = ft_strdup(options->path);
	if (!*curpath)
		return (ERR_MALLOC);
	return (OK);
}

static t_error	step_seven(char **curpath, char *pwd)
{
	char	*curpath_cpy;

	if (**curpath != '/')
	{
		curpath_cpy = *curpath;
		*curpath = path_join(pwd, *curpath);
		free(curpath_cpy);
		if (!(*curpath))
			return (ERR_MALLOC);
	}
	return (OK);
}

static t_error	exec(t_cd_opts *options, char **curpath, char *pwd)
{
	t_error	err;

	if (ft_strcmp(options->path, "-") == 0)
	{
		options->path = *(path_oldpath());
		if (!options->path)
			options->path = options->home;
	}
	if (!options->relative || options->dot)
	{
		*curpath = ft_strdup(options->path);
		if (!*curpath)
			return (ERR_MALLOC);
	}
	else
	{
		err = step_five(options, curpath);
		if (err != OK)
			return (err);
	}
	err = step_seven(curpath, pwd);
	if (err != OK)
		return (err);
	err = path_canonize(curpath);
	if (err != OK)
		return (err);
	err = path_relativize(curpath, pwd);
	if (err != OK)
		return (err);
	return (OK);
}

t_error	builtin_cd(size_t argc, char **argv)
{
	t_cd_opts	options;
	char		*curpath;
	char		*pwd;
	t_error		err;

	if (argc > 1)
		return (ERR_TOOMUCH_ARGS);
	options.home = env_get_value("HOME");
	if (!options.home && !argc)
		return (OK);
	if (argc)
		options.path = *argv;
	else
		options.path = options.home;
	options.relative = (*options.path != '/');
	options.dot = (*options.path == '.');
	curpath = NULL;
	err = path_pwd(&pwd);
	if (err == OK)
		err = path_pwd(&pwd);
	if (err == OK)
		err = exec(&options, &curpath, pwd);
	if (err == OK)
		err = path_chdir(curpath, pwd);
	if (pwd)
		free(pwd);
	if (curpath)
		free(curpath);
	if (err == ERR)
		return (ERR_ERRNO);
	else
		return (err);
}
