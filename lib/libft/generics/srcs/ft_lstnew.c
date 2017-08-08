/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <cchaumar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/23 18:49:59 by cchaumar          #+#    #+#             */
/*   Updated: 2016/01/23 19:21:20 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_generics.h"

t_list	*ft_lstnew(void	const *content, size_t content_size)
{
	t_list	*node;
	void	*p;

	node = try(sizeof(t_list));
	if (content)
		p = try(content_size);
	node->content = (content == NULL) ? NULL :
		ft_memcpy(p, content, content_size);
	node->content_size = (content == NULL) ? 0 : content_size;
	return (node);
}
