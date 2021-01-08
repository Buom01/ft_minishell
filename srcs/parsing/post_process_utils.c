/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_process_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 03:27:13 by badam             #+#    #+#             */
/*   Updated: 2021/01/08 01:41:26 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"
# include "parsing.h"

void	pp_realloc(t_pprocess_state *st, t_string *str, size_t capacity)
{
	char	*old_str;

	old_str = str->str;
	if (!(str->str = malloc(sizeof(char) * capacity)))
		panic(ERR_MALLOC);
	ft_memcpy(str->str, old_str, str->len + 1);
	str->capacity = capacity;
	st->cursor += str->str - old_str;
	st->anchor += str->str - old_str;
	free(old_str);
}

void	pp_replace(t_pprocess_state *st, ssize_t old_len, char *new_word,
				t_string *str)
{
	ssize_t	new_len;
	size_t	total_len;
	char	*at;

	new_len = ft_strlen(new_word);
	total_len = str->len - old_len + new_len + 1;
	if (str->capacity < total_len)
		pp_realloc(st, str, total_len);
	at = st->cursor;
	ft_memmove(at + new_len, at + old_len,
			str->len - old_len - (at - str->str) + 1);
	ft_memcpy(at, new_word, new_len);
	str->len -= old_len - new_len;
	st->cursor += new_len - 1;
}

void	pp_strip(t_pprocess_state *st, ssize_t strip_len, t_string *str)
{
	char	*at;

	if (!strip_len)
		return;
	at = st->cursor;
	ft_memmove(at, at + strip_len, str->len - strip_len - (at - str->str) + 1);
	str->len -= strip_len;
	st->cursor--;
}
