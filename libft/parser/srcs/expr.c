/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 13:45:20 by cchaumar          #+#    #+#             */
/*   Updated: 2017/06/27 02:45:16 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_expr	*end_expr(t_expr *e)
{
	while (e && e->next)
		e = e->next;
	return (e);
}

int		parser_tab_find(char **list, char *str)
{
	int		i;

	i = 0;
	while (list[i])
		if (ft_strcmp(list[i], str) == 0)
			return (0);
		else
			i++;
	return (-1);
}

void	parser_add_expr(t_expr **expr, char *pos)
{
	(*expr)->rule = NULL;
	(*expr)->expr = NULL;
	(*expr)->pos = pos;
	(*expr)->next = try(sizeof(t_expr));
	(*expr)->next->prev = *expr;
	(*expr) = (*expr)->next;
}
