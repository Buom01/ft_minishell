/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frdescam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 14:51:53 by frdescam          #+#    #+#             */
/*   Updated: 2021/01/14 19:31:28 by frdescam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstnew(const char *name, void *content)
{
	t_list	*new_elem;

	new_elem = malloc(sizeof(t_list));
	if (!new_elem)
		return (NULL);
	new_elem->name = ft_strdup(name);
	new_elem->content = content;
	new_elem->next = NULL;
	return (new_elem);
}
/*
**#include <stdio.h>
**
**int		main(void)
**{
**	char	str[] = "lorem ipsum dolor sit";
**	char	name[] = "this is my name";
**
**	t_list	*elem;
**
**	elem = ft_lstnew(name, (void *)str);
**	printf("\nname : %s\ncontent : %s\n", elem->name, (char *)elem->content);
**}
*/
