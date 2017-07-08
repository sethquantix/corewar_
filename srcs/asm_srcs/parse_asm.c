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
	int			fd;
	int 		len;
	char		*line;
	char		*source;
	struct stat	stat_;

	len = 0;
	stat(file, &stat_);
	if (stat_.st_size < 4 || (fd = open(file, O_RDONLY)) == -1)
		return (NULL);
	source = NULL;
	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		len += ft_strlen(line);
		ft_printf("read %d (%s)\n", len, line);
		source = ft_strjoinfree(source, ft_strjoinfree(line, "\n", 1), 3);
	}
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
		ft_lstdel(&stack, ft_del);
		return (err("Invalid argument"));
	}
	ft_lstdel(&stack, ft_del);
	t = parser_getl(ret);
	if ((e = run_parser(p, t, "EXPR", &expr)) == NULL)
	{
		e = err("Unexpected token %s : \"%s\"", expr->rule, expr->expr);
		parser_clear_expr(&expr);
		free(t);
		return (e);
	}
	free(t);
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

	if ((*source = getfile(file)) == NULL || *source == (void *)-1)
	{
		ft_dprintf(2, *source ? "File %s is too heavy for a corewar champion\n" :
			"Can't read file %s\n", file);
		if (*source)
			*source = 0;
		return (NULL);
	}
	err = 0;
	expr = NULL;
	s = *source;
	while (err < 20 && s && (ret = run_parser(p, s, "EXPR", &expr)) != NULL)
	{
		err++;
		compile_error(p, file, *source, ret);
		parser_clear_expr(&expr);
		expr = NULL;
		s = ft_strchr(ret, '\n');
	}
	if (err)
	{
		parser_clear_expr(&expr);
		ft_printf("compiling %s : %sFAILURE !%s\n", file, COLOR_RED, COLOR_END);
		err >= 20 ? ft_printf("Too many errors ! (stopped at 20)\n\n") :
			ft_printf("%d errors\n\n", err);
	}
	return (err ? NULL : expr);
}
