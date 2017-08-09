/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_asm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnagy <lnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 16:51:13 by lnagy             #+#    #+#             */
/*   Updated: 2017/08/08 04:54:28 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	err_pos(char *start, char *e, int c)
{
	while (ft_iswhite(*start))
	{
		if (*start == '\t')
			*start = ' ';
		c--;
		start++;
	}
	while (start != e)
	{
		if (*start == '\t')
			*start = ' ';
		start++;
	}
	return (c);
}

static char	*get_err(t_parser *p, char *ret, char *error, t_list *stack)
{
	char	*r;
	t_tok	*e;
	t_expr	*expr;
	t_list	*l;

	e = tok(ft_lstend(stack));
	if (stack && e->pos != tok(stack)->pos && e->pos != ret)
	{
		r = getword(e->pos);
		l = get_rule(stack);
		ret = err(ERR_INV_ARG, r, l ? tok(l)->rule->name : "unknown");
		free(r);
		return (ret);
	}
	r = run_parser(p, error, "ERR", &expr);
	if (expr)
	{
		r = !ft_strcmp(expr->rule, "NAME") ? expr->next->expr : NULL;
		r = err(r ? ERR_BAD_INS : ERR_BAD_TOK, r ? r : expr->rule, expr->expr);
		parser_clear_expr(&expr);
		return (r);
	}
	return (err(ERR_BAD_SYM, ret));
}

static void	*compile_error(t_parser *p, char *file, char *source, char *ret)
{
	t_list	*stack;
	int		l;
	int		c;
	char	*err;
	char	*pos;

	err = parser_getl(ret);
	stack = p->stack;
	p->stack = NULL;
	parser_get_pos(tok(ft_lstend(stack))->pos, source, &l, &c);
	ft_dprintf(2, "%s:%d:%d: %serror:%s %s\n", file, l, c,
		COLOR_RED, COLOR_END, get_err(p, ret, err, stack));
	free(err);
	c = err_pos(tok(stack)->pos, tok(ft_lstend(stack))->pos, c);
	err = parser_getl(tok(stack)->pos);
	pos = ft_strtrim(err);
	free(err);
	ft_dprintf(2, "\t%s\n", (err = pos));
	ft_dprintf(2, "\t%s%.*s%s\n", acol(1, 4, 1), c, "^", COLOR_END);
	free(err);
	return (NULL);
}

static void	*print_err(t_expr **expr, char *file, int err)
{
	ft_printf("%016p\n%016p\n%016p\n", expr, file, *expr);
	if (err)
	{
		parser_clear_expr(expr);
		ft_printf("compiling %s : %sFAILURE !%s\n", file, COLOR_RED, COLOR_END);
		err >= 20 ? ft_printf("Too many errors ! (stopped at 20)\n\n") :
			ft_printf("%d errors\n\n", err);
	}
	return ((void *)-1);
}

t_expr		*parse_asm(t_parser *p, char *file, char **source, t_expr *expr)
{
	char		*s;
	char		*ret;
	int			err;

	if ((*source = getfile(file)) == NULL || *source == (void *)-1)
	{
		if (*source)
			ft_dprintf(2, "%sError : file %s may not compile or is %s%s",
				acol(4, 0, 0), file, "invalid for some reasons.\n", COLOR_END);
		else
			ft_dprintf(2, "%sError : Can't read file %s%s\n",
				acol(4, 0, 0), file, COLOR_END);
		*source = NULL;
		return ((void *)-1);
	}
	err = 0;
	s = *source;
	while (err < 20 && s && (ret = run_parser(p, s, "EXPR", &expr)) != NULL)
	{
		err++;
		compile_error(p, file, *source, ret);
		parser_clear_expr(&expr);
		s = ft_strchr(ret, '\n');
	}
	return (err ? print_err(&expr, file, err) : expr);
}
