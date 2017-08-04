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

static char	*getfile(char *file)
{
	int			fd;
	int			len;
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
		source = ft_strjoinfree(source, ft_strjoinfree(line, "\n", 1), 3);
	}
	free(line);
	return (source);
}

static char	*get_err(t_parser *p, char *ret, int *c)
{
	t_expr	*expr;
	t_list	*stack;
	char	*t;
	char	*e;

	stack = p->err;
	p->err = NULL;
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

static void	print_err(t_expr **expr, char *file, int err)
{
	if (err)
	{
		parser_clear_expr(expr);
		ft_printf("compiling %s : %sFAILURE !%s\n", file, COLOR_RED, COLOR_END);
		err >= 20 ? ft_printf("Too many errors ! (stopped at 20)\n\n") :
			ft_printf("%d errors\n\n", err);
	}
}

t_expr		*parse_asm(t_parser *p, char *file, char **source)
{
	t_expr		*expr;
	char		*s;
	char		*ret;
	int			err;

	if ((*source = getfile(file)) == NULL || *source == (void *)-1)
	{
		ft_dprintf(2, *source ? "File %s is too heavy for a corewar champion\n"
			: "Can't read file %s\n", file);
		(*source) ? *source = 0 : 0;
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
	print_err(&expr, file, err);
	return (err ? NULL : expr);
}
