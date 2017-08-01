/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_circular_find.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/20 12:41:09 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/11 16:53:13 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_generics.h"

int			ft_circ_equal(void *node, void *data)
{
	return (node == data);
}

t_circular	*ft_circular_find(t_circular *head, void *data,
	int (*f)(void *, void *))
{
	t_circular	*node;

	node = head;
	if (!node)
		return (NULL);
	while (node->next != head)
		if (f(node->content, data))
			return (node);
		else
			node = node->next;
	return (f(node->content, data) ? node : NULL);
}

int			ft_circ_find_ind(t_circular *head, void *data,
	int (*f)(void *, void *))
{
	t_circular	*node;
	int			i;

	i = 0;
	node = head;
	if (!node)
		return (-1);
	while (node->next != head)
		if (f(node->content, data))
			return (i);
		else
		{
			i++;
			node = node->next;
		}
	return (f(node->content, data) ? i : -1);
}

void		*run_circular(t_circular *head, void *data, void *(*f)(void *,
	void *, size_t))
{
	t_circular	*node;
	void		*p;

	node = head;
	while (node != head->prev)
	{
		if ((p = f(node->content, data, node->size)) != NULL)
			return (p);
		node = node->next;
	}
	return (f(node->content, data, node->size));
}
