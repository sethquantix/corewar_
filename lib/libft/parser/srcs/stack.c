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
	
	// ft_printf("push %s [%s]\n", st.rule->name, parser_getl(st.pos));
	node = ft_lstnew(&st, sizeof(t_tok));
	end = ft_lstend(p->stack);
	if (ps)
		*ps = end;
	if (end)
		end->next = node;
	else
		p->stack = node;
}

void	err_stack_pop(t_parser *p, t_list *ps, int r, t_list **s)
{
	if (*s)
	{
		if (!r || ft_lstsize(*s) < ft_lstsize(p->stack))
		{
			ft_lstdel(s, ft_del);
			stock_stack(s, p->stack);
		}
		ft_lstdel(ps ? &ps->next : &p->stack, ft_del);
	}
	else
	{
		stock_stack(s, p->stack);
		ft_lstdel(ps ? &ps->next : &p->stack, ft_del);
	}
}

// static void		stack_handle(t_parser *p, t_tok *st, t_list **ps, int err)
// {
// 	t_list		*t;
// 
// 	else
// 	{
// 		if (err && ft_lstsize(p->stack) > ft_lstsize(p->err))
// 			stock_stack(p);
// 		t = p->stack;
// 		if (t == *ps)
// 			ft_lstdel(&p->stack, ft_del);
// 		else
// 		{
// 			while (t->next != *ps)
// 				t = t->next;
// 			ft_lstdel(ps, ft_del);
// 			t->next = NULL;
// 		}
// 	}
// }

void		print_stak(t_list *stack)
{
	t_tok	*t;

	ft_printf("************************************************\n");
	while (stack)
	{
		t = stack->content;
		ft_printf("%s [%s]\n", t->rule->name, parser_getl(t->pos));
		stack = stack->next;
	}
}
