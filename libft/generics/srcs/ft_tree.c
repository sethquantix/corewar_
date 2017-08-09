/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/19 08:43:00 by cchaumar          #+#    #+#             */
/*   Updated: 2017/07/19 11:26:31 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_generics.h"

t_tree	*ft_tree_new(void *content, size_t size)
{
	t_tree	*node;

	node = try(sizeof(t_tree));
	if (!size)
		return (node);
	if (content)
	{
		node->content = try(size);
		ft_memcpy(node->content, content, size);
	}
	node->size = size;
	return (node);
}

t_tree	*ft_tree_insert(t_tree **root, t_tree *node, int (*f)(void *, void *))
{
	if (!*root)
		return ((*root = node));
	if (f((*root)->content, node->content) < 0)
	{
		if ((*root)->left)
			return (ft_tree_insert(&((*root)->left), node, f));
		else
			return ((*root)->left = node);
	}
	else
	{
		if ((*root)->left)
			return (ft_tree_insert(&((*root)->left), node, f));
		else
			return ((*root)->left = node);
	}
	return (NULL);
}

void	ft_tree_del(t_tree **root, void (*del)(void *content, size_t size))
{
	if (!*root)
		return ;
	ft_tree_del(&(*root)->left, del);
	ft_tree_del(&(*root)->right, del);
	del((*root)->content, (*root)->size);
	ft_memdel((void **)root);
}

t_tree	*ft_tree_find(t_tree *root, void *base, int (*cmp)(void *, void *))
{
	t_tree	*ret;

	if (!root)
		return (NULL);
	if (!cmp(base, root->content))
		return (root);
	ret = root->left ? ft_tree_find(root->left, base, cmp) : NULL;
	if (ret)
		return (ret);
	return (ft_tree_find(root->right, base, cmp));
}
