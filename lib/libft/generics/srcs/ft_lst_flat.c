/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_flat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 03:36:51 by cchaumar          #+#    #+#             */
/*   Updated: 2017/01/27 03:36:52 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_generics.h"

void	*ft_lst_flat(t_list *root, void *(*f)(int i, void *p), size_t elem_size)
{
	int		n;
	int		i;
	void	*out;
	void	*p;

	if (!root)
		return (NULL);
	n = ft_lstsize(root);
	out = ft_memalloc(elem_size * (n + 1));
	i = 0;
	while (root)
	{
		p = f(i, root->content);
		ft_memcpy(&out[i], p, elem_size);
		i++;
		root = root->next;
	}
	return (out);
}
