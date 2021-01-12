/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_process_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 03:27:13 by badam             #+#    #+#             */
/*   Updated: 2021/01/11 23:45:59 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

void	pp_realloc(t_pp_state *st, t_string *str, size_t capacity)
{
	char	*old_str;

	old_str = str->str;
	str->str = malloc(sizeof(char) * capacity);
	if (!str->str)
		panic(ERR_MALLOC);
	ft_memcpy(str->str, old_str, str->len + 1);
	str->capacity = capacity;
	st->cursor += str->str - old_str;
	st->anchor += str->str - old_str;
	free(old_str);
}

void	pp_replace(t_pp_state *st, ssize_t oldlen, char *newword, t_string *str)
{
	ssize_t	newlen;
	size_t	totallen;
	char	*at;

	newlen = ft_strlen(newword);
	totallen = str->len - oldlen + newlen + 1;
	if (str->capacity < totallen)
		pp_realloc(st, str, totallen);
	at = st->cursor;
	ft_memmove(at + newlen, at + oldlen,
		str->len - oldlen - (at - str->str) + 1);
	ft_memcpy(at, newword, newlen);
	str->len -= oldlen - newlen;
	st->cursor += newlen - 1;
}

void	pp_strip(t_pp_state *st, ssize_t striplen, t_string *str)
{
	char	*at;

	if (!striplen)
		return ;
	at = st->cursor;
	ft_memmove(at, at + striplen, str->len - striplen - (at - str->str) + 1);
	str->len -= striplen;
	st->cursor--;
}
