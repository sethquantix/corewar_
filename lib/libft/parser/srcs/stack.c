/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 07:00:24 by cchaumar          #+#    #+#             */
/*   Updated: 2017/08/08 07:00:45 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "parser_marching.h"

void		stock_stack(t_list **st, t_list *o)
{
	t_list	*s;
	t_list	*n;

	s = NULL;
	while (o)
	{
		n = ft_lstnew(o->content, o->content_size);
		ft_lstadd_end(&s, n);
		o = o->next;
	}
	*st = s;
}

void		err_stack_push(t_parser *p, t_tok st, t_list **ps)
{
	t_list	*node;
	t_list	*end;

	node = ft_lstnew(&st, sizeof(t_tok));
	end = ft_lstend(p->stack);
	if (ps)
		*ps = end;
	if (end)
		end->next = node;
	else
		p->stack = node;
}
