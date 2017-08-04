/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 17:06:43 by cchaumar          #+#    #+#             */
/*   Updated: 2017/06/27 03:01:04 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "parser_marching.h"

static void		stock_stack(t_parser *p)
{
	t_list	*s;
	t_list	*n;

	ft_lstdel(&p->err, ft_del);
	s = p->stack;
	while (s)
	{
		n = ft_lstnew(s->content, s->content_size);
		ft_lstadd_end(&p->err, n);
		s = s->next;
	}
}

static void		stack_handle(t_parser *p, t_tok *st, t_list **ps, int err)
{
	t_list		*t;

	if (st)
	{
		ft_lstadd_end(&p->stack, ft_lstnew(st, sizeof(t_tok)));
		*ps = ft_lstend(p->stack);
	}
	else
	{
		if (err && ft_lstsize(p->stack) > ft_lstsize(p->err))
			stock_stack(p);
		t = p->stack;
		if (t == *ps)
			ft_lstdel(&p->stack, ft_del);
		else
		{
			while (t->next != *ps)
				t = t->next;
			ft_lstdel(ps, ft_del);
			t->next = NULL;
		}
	}
}

static int		build_expr_rule(t_rule *rule, char **s, t_parser *parser,
	t_expr **ret)
{
	int		r;
	char	*p;
	t_tok	st;
	t_list	*ps;
	t_expr	*e;

	st = (t_tok){rule, *s};
	stack_handle(parser, &st, &ps, 0);
	p = NULL;
	if (parser_tab_find(parser->list, rule->name) == 0)
		p = *s;
	r = rule->tok ? parser_check_tok(rule->tok, s) : march_path(rule->path,
		s, ret, parser);
	if (r == 0 && p)
	{
		e = try(sizeof(t_expr));
		*e = (t_expr){p, ft_strdup(rule->name), p, *ret, NULL};
		p = ft_strsub(p, 0, *s - p);
		e->expr = ft_trim(&p);
		*ret = e;
	}
	stack_handle(parser, NULL, &ps, r);
	return (r);
}

static	int		build_expr_opts(t_rule **rules, char **s, t_parser *p,
	t_expr **ret)
{
	int		r;
	char	*t;

	r = 1;
	t = *s;
	while (r && *rules)
	{
		if ((r = build_expr_rule(*rules, s, p, ret)))
		{
			*s = t;
			rules++;
		}
	}
	return (r);
}

int				march_path(t_path *path, char **s, t_expr **expr,
	t_parser *parser)
{
	t_expr		**t;
	t_expr		*r;
	t_expr		*e;
	int			ret;

	r = NULL;
	e = NULL;
	while (path)
	{
		ret = !path->options ? build_expr_rule(path->rule, s, parser, &e) :
			build_expr_opts(path->options, s, parser, &e);
		if (!r)
			r = e;
		else
			end_expr(r)->next = e;
		if (!(e = NULL) && ret)
		{
			parser_clear_expr(&r);
			return (-1);
		}
		path = path->next;
	}
	t = *expr ? &end_expr(*expr)->next : expr;
	*t = r;
	return (0);
}
