/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_asm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnagy <lnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 16:51:13 by lnagy             #+#    #+#             */
/*   Updated: 2017/03/10 16:51:14 by lnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*getfile(char *file)
{
	int		fd;
	char	*line;
	char	*source;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (NULL);
	source = NULL;
	line = NULL;
	while (get_next_line(fd, &line) > 0)
		source = ft_strjoinfree(source, ft_strjoinfree(line, "\n", 1), 3);
	free(line);
	return (source);
}

void	print_stack2(t_list *s)
{
	t_tok	*t;

	while (s)
	{
		t = s->content;
		ft_dprintf(2, "%s - %s\n", t->rule->name, parser_getl(t->pos));
		s = s->next;
	}
}

char 	*err(char *format, ...)
{
	va_list va;
	char 	*e;

	va_start(va, format);
	e = NULL;
	ft_vasprintf(&e, format, va);
	va_end(va);
	return (e);
}

char 	*get_err(t_parser *p, char *ret, int *c)
{
	t_expr	*expr;
	t_list	*stack;
	t_tok	*tok;
	char 	*t;
	char 	*e;

	stack = p->err;
	tok = stack->content;
	p->err = NULL;
	if (tok->pos == ret)
	{
		*c += ((t_tok *)ft_lstend(stack)->content)->pos - ret;
		return (err("Invalid argument"));
	}
	t = parser_getl(ret);
	if ((e = run_parser(p, t, "EXPR", &expr)) == NULL)
	{
		free(t);
		return (err("Unexpected expression %s", expr->rule));
	}
	return (err("Unexpected symbol \"%.1s\"", ret));
}

void	*compile_error(t_parser *p, char *file, char *source, char *ret)
{
	int 	l;
	int 	c;
	char 	*s;
	char 	*err;

	parser_get_pos(ret, source, &l, &c);
	s = parser_getl(ret - c + 1);
	err = get_err(p, ret, &c);
	ft_dprintf(2, "%s:%d:%d: %serror:%s %s\n", file, l, c, COLOR_RED, COLOR_END, err);
	ft_dprintf(2, "\t%s\n", s);
	ft_dprintf(2, "\t%s%.*s%s\n", COLOR_GREEN, c, "^", COLOR_END);
	free(err);
	free(s);
	return (NULL);
}

t_expr	*parse_asm(t_parser *p, char *file, char **source)
{
	t_expr		*expr;
	char 		*s;
	char		*ret;
	int			err;

	if ((*source = getfile(file)) == NULL)
	{
		ft_printf("Can't read file %s\n", file);
		return (NULL);
	}
	err = 0;
	expr = NULL;
	s = *source;
	while (s && (ret = run_parser(p, s, "EXPR", &expr)) != NULL)
	{
		err++;
		compile_error(p, file, *source, ret);
		parser_clear_expr(&expr);
		expr = NULL;
		s = ft_strchr(ret, '\n');
	}
	if (err)
		ft_printf("Failed to compile %s : %d errors\n", file, err);
	return (err ? NULL : expr);
}
