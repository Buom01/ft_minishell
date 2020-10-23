/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_remove.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdescam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 22:02:43 by frdescam          #+#    #+#             */
/*   Updated: 2020/10/23 12:09:05 by frdescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_string	*ft_string_remove(t_string *string, int start, int end)
{
	t_string	*out;

	if (!(out = ft_string_with_capacity(end - start + 2)))
		return (NULL);
	ft_strlcpy(out->str, &string->str[start], end - start + 2);
	out->len = end - start + 1;
	ft_strlcpy(&string->str[start], &string->str[end + 1], string->capacity);
	string->len -= out->len;
	return (out);
}
/*
**#include <stdio.h>
**
**int			main(void)
**{
**	t_string *string = ft_string_from("ls > out");
**
**	printf("string->str = %s, string->len = %ld, string->capacity = %ld\n",
**     string->str, string->len, string->capacity);
**	t_string *removed = ft_string_remove(string, 3, 8);
**	printf("removed->str = %s, removed->len = %ld, removed->capacity = %ld\n",
**     removed->str, removed->len, removed->capacity);
**	printf("string->str = %s, string->len = %ld, string->capacity = %ld\n",
**     string->str, string->len, string->capacity);
**}
*/
