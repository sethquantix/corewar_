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

void	print_stack(t_list *stack)
{
	t_tok	*tok;

	while (stack)
	{
		tok = stack->content;
		ft_dprintf(2, "%s [%s]\n", tok->rule->name, parser_getl(tok->pos));
		stack = stack->next;
	}
}

static char	*get_err(t_parser *p, char *ret, int *c)
{
	t_expr	*expr;
	t_list	*stack;
	char	*t;
	char	*e;

	stack = p->stack;
	print_stack(stack);
	p->stack = NULL;
	if (((t_tok *)stack->content)->pos == ret)
	{
		*c += ((t_tok *)ft_lstend(stack)->content)->pos - ret;
		ft_lstdel(&stack, ft_del);
		return (err(ERR_INV_ARG));
	}
	ft_lstdel(&stack, ft_del);
	t = parser_getl(ret);
	if ((e = run_parser(p, t, "EXPR", &expr)) == NULL)
	{
		e = err(ERR_BAD_TOK, expr->rule, expr->expr);
		parser_clear_expr(&expr);
		free(t);
		return (e);
	}
	free(t);
	return (err(ERR_BAD_SYM, ret));
}

static void	*compile_error(t_parser *p, char *file, char *source, char *ret)
{
	int		l;
	int		c;
	char	*s;
	char	*err;

	parser_get_pos(ret, source, &l, &c);
	s = parser_getl(ret - c + 1);
	err = get_err(p, ret, &c);
	ft_dprintf(2, "%s:%d:%d: %serror:%s %s\n", file, l,
		c, COLOR_RED, COLOR_END, err);
	err = s;
	while (ft_iswhite(*err))
	{
		c--;
		err++;
	}
	ft_dprintf(2, "\t%s\n", err);
	ft_dprintf(2, "\t%s%.*s%s\n", COLOR_GREEN, c, "^", COLOR_END);
	free(s);
	return (NULL);
}

static void	*print_err(t_expr **expr, char *file, int err)
{
	if (err)
	{
		parser_clear_expr(expr);
		ft_printf("compiling %s : %sFAILURE !%s\n", file, COLOR_RED, COLOR_END);
		err >= 20 ? ft_printf("Too many errors ! (stopped at 20)\n\n") :
			ft_printf("%d errors\n\n", err);
	}
	return (NULL);
}

t_expr		*parse_asm(t_parser *p, char *file, char **source)
{
	t_expr		*expr;
	char		*s;
	char		*ret;
	int			err;

	if ((*source = getfile(file)) == NULL || *source == (void *)-1)
	{
		if (*source)
			ft_dprintf(2, "%sError : file %s exceeds max size of %d%s\n",
				acol(4, 0, 0), file, MAX_SIZE, COLOR_END);
		else
			ft_dprintf(2, "%sError : Can't read file %s%s\n",
				acol(4, 0, 0), file, COLOR_END);
		return ((t_expr *)(*source = NULL));
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
