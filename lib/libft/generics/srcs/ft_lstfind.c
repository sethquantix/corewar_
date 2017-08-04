/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfind.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 10:36:32 by cchaumar          #+#    #+#             */
/*   Updated: 2017/01/24 10:39:54 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_generics.h"

t_list	*ft_lstfind(t_list *root, void *data, int (*f)(void *content,
	void *data))
{
	if (!root)
		return (NULL);
	if (f(root->content, data))
		return (root);
	return (ft_lstfind(root->next, data, f));
}
