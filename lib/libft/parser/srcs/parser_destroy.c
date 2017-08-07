/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_destroy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 15:01:27 by cchaumar          #+#    #+#             */
/*   Updated: 2017/08/07 10:36:14 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parser_destroy_path(t_path *path)
{
	if (!path)
		return ;
	parser_destroy_path(path->next);
	ft_memdel((void **)&path->options);
	ft_memdel((void **)&path);
}

void	parser_clear_expr(t_expr **expr)
{
	t_expr	*node;
	t_expr	*next;

	node = *expr;
	while (node)
	{
		next = node->next;
		ft_memdel((void **)&node->rule);
		ft_memdel((void **)&node->expr);
		ft_memdel((void **)&node);
		node = next;
	}
	*expr = NULL;
}
