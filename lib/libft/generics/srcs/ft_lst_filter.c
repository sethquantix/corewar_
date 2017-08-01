/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_filter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 07:25:29 by cchaumar          #+#    #+#             */
/*   Updated: 2017/02/01 03:43:16 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_generics.h"

t_list	*ft_lst_filter(t_list *root, int (*f)(void *content))
{
	t_list	*list;
	int		ret;

	list = NULL;
	while (root)
	{
		if ((ret = f(root->content)))
			ft_lstadd_end(&list, ft_lstnew(root->content, root->content_size));
		root = root->next;
	}
	return (list);
}
