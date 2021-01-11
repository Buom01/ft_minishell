/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 17:59:37 by badam             #+#    #+#             */
/*   Updated: 2021/01/11 21:25:42 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"
# include "parsing.h"

static bool	process_char(t_string *cmd, t_pprocess_state *st, char *cursor)
{
	size_t	strip;

	strip = 0;
	if (st->in_quote)
	{
		if (*cursor == '\\' && *(cursor + 1) == '\'')
		{
			pp_strip(st, 1, cmd);
			++(st->cursor);
		}
		else if (*cursor == '\'' && ++strip)
			st->in_quote = false;
	}
	else if (ft_strchr("\f\t  \n\r\v", *cursor))
		return (process_space(cmd, st, cursor));
	else if (*cursor == '\\')
		process_escape(cmd, st, cursor);
	else if (*cursor == '$')
		process_env(cmd, st, cursor);
	else if (*cursor == '"' && ++strip)
		st->in_dquote = !st->in_dquote;
	else if (*cursor == '\'' && ++strip)
		st->in_quote = true;
	pp_strip(st, strip, cmd);
	return (*(st->cursor + 1) == '\0');
}

static void	push_arg(t_pipe_cmd *cmd, char **old_argv, t_pprocess_state *st)
{
	if (!(cmd->argv = malloc((2 + cmd->argc) * sizeof(char*))))
		panic(ERR_MALLOC);
	if (!cmd->cmd)
	{
		cmd->cmd = ft_substr(st->anchor, 0, st->cursor - st->anchor);
		*(cmd->argv) = cmd->cmd;
	}
	else
	{
		ft_memcpy(cmd->argv, old_argv, cmd->argc * sizeof(char*));
		*(cmd->argv + cmd->argc) =
				ft_substr(st->anchor, 0, st->cursor - st->anchor);
		free(old_argv);
	}
	if (!*(cmd->argv + cmd->argc))
		panic(ERR_MALLOC);
	*(cmd->argv + ++cmd->argc) = NULL;
	st->anchor = st->cursor + 1;
}

static void	init_state(t_pprocess_state *st, t_list *pipe_cmds)
{
	ft_bzero(st, sizeof(t_pprocess_state));
	st->cmd = (t_pipe_cmd *)(pipe_cmds->content);
	st->cursor = st->cmd->pipe_cmd->str;
	while (*(st->cursor) && ft_strchr("\f\t  \n\r\v", *(st->cursor)))
		st->cursor++;
	st->anchor = st->cursor;
}

void		post_process(t_data *data)
{
	t_list				*cmds;
	t_list				*pipe_cmds;
	t_pprocess_state	st;

	cmds = data->cmds;
	while (cmds)
	{
		pipe_cmds = (t_list *)(((t_cmd *)(cmds->content))->pipe_cmds);
		while (pipe_cmds)
		{
			init_state(&st, pipe_cmds);
			while (*st.cursor)
			{
				if (process_char(st.cmd->pipe_cmd, &st, st.cursor))
					push_arg(st.cmd, st.cmd->argv, &st);
				st.cursor++;
			}
			pipe_cmds = pipe_cmds->next;
		}
		cmds = cmds->next;
	}
}
