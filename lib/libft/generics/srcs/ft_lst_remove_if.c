/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_remove_if.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 02:29:44 by cchaumar          #+#    #+#             */
/*   Updated: 2017/02/01 02:29:44 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_generics.h"

void	ft_lst_remove_if(t_list **list, void *reference,
	int (*f)(void *reference, void *content), void (*del)(void *content,
	size_t size))
{
	t_list		*o;
	t_list		*node;

	if (!list || !*list)
		return ;
	while (*list && f(reference, (*list)->content))
	{
		o = (*list)->next;
		ft_lstdelone(list, del);
		*list = o;
	}
	if (!(o = *list) || !o->next)
		return ;
	while (o && o->next)
	{
		if (f(reference, o->next->content))
		{
			node = o->next->next;
			ft_lstdelone(&o->next, del);
			o->next = node;
		}
		o = o->next;
	}
}
