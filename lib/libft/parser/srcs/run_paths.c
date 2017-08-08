/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 17:06:43 by cchaumar          #+#    #+#             */
/*   Updated: 2017/08/08 05:20:46 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "parser_marching.h"

static int		build_expr_rule(t_rule *rule, char **s, t_parser *parser,
	t_expr **ret)
{
	int		r;
	char	*p;
	t_expr	*e;

	err_stack_push(parser, (t_tok){rule, *s}, NULL);
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
	return (r);
}

static	int		build_expr_opts(t_rule **rules, char **s, t_parser *p,
	t_expr **ret)
{
	int		r;
	char	*t;
	t_list	*ps;
	t_list	*temp;

	temp = p->stack;
	p->stack = NULL;
	ps = NULL;
	r = 1;
	t = *s;
	while (r && *rules)
	{
		ft_dprintf(2, "option => %s\n", (*rules)->name);
		if ((r = build_expr_rule(*rules, s, p, ret)))
			*s = t;
		ft_dprintf(2, "%d %p option %s got %d\n", r, ps, (*rules)->name,
			ft_lstsize(p->stack));
		if (!r || !ps || ft_lstsize(ps) < ft_lstsize(p->stack))
		{
			ft_dprintf(2, "replacing %s with %s\n",
				!ps ? "-" :
				((t_tok *)ps->content)->rule->name,
				((t_tok *)p->stack->content)->rule->name);
			ft_lstdel(&ps, ft_del);
			ps = p->stack;
			p->stack = NULL;
		}
		else
			ft_lstdel(&p->stack, ft_del);
		rules++;
	}
	if (temp)
	{
		ft_lstend(temp)->next = ps;
		p->stack = temp;
	}
	// else
	// 	p->stack = ps;
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
