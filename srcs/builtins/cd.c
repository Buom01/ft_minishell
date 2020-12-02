/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 21:03:19 by badam             #+#    #+#             */
/*   Updated: 2020/12/02 20:58:06 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins.h"

static t_error	step_five_test_cdpath(char **cdpath_array,
		t_cd_opts *options, char **curpath)
{
	char	*cdpath;
	bool	exists;
	t_error	err;

	err = OK;
	while (*cdpath_array)
	{
		if (**cdpath_array)
			cdpath = path_join(*cdpath_array, options->path);
		else
			cdpath = ft_strjoin("./", options->path);
		if (!cdpath && (err = ERR_MALLOC))
			break ;
		if ((err = path_dir_exists(cdpath, true, &exists)) != OK)
			break ;
		if (exists && (*curpath = cdpath))
			break ;
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
	char	**cdpath_array_cpy;
	t_error	err;

	if ((env_cdpath = env_get_value("CDPATH")))
	{
		if (!(cdpath_array = ft_split(env_cdpath, ":")))
			return (ERR_MALLOC);
		cdpath_array_cpy = cdpath_array;
		err = step_five_test_cdpath(cdpath_array, options, curpath);
		while (*cdpath_array)
			free(*(cdpath_array++));
		free(cdpath_array_cpy);
		if (err != OK)
			return (err);
		if (*curpath)
			return (OK);
	}
	if (!(*curpath = ft_strdup(options->path)))
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
		if (!(options->path = *(path_oldpath())))
			options->path = options->home;
	if (!options->relative || options->dot)
	{
		if (!(*curpath = ft_strdup(options->path)))
			return (ERR_MALLOC);
	}
	else if ((err = step_five(options, curpath)) != OK)
		return (err);
	if ((err = step_seven(curpath, pwd)) != OK
			|| (err = path_canonize(curpath)) != OK
			|| (err = path_relativize(curpath, pwd)) != OK)
		return (err);
	return (OK);
}

t_error			builtin_cd(size_t argc, char **argv)
{
	t_cd_opts	options;
	char		*curpath;
	char		*pwd;
	t_error		err;

	if (argc > 1)
		return (ERR_TOOMUCH_ARGS);
	if (!argc && !(options.home = env_get_value("HOME")))
		return (OK);
	options.path = !argc ? options.home : *argv;
	options.relative = (*options.path != '/');
	options.dot = (*options.path == '.');
	curpath = NULL;
	if ((err = path_pwd(&pwd)) == OK
			&& (err = exec(&options, &curpath, pwd)) == OK)
		err = path_chdir(curpath, pwd);
	if (pwd)
		free(pwd);
	if (curpath)
		free(curpath);
	return (err == ERR ? ERR_ERRNO : err);
}
