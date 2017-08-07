/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_opts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnagy <lnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:47:34 by lnagy             #+#    #+#             */
/*   Updated: 2017/08/07 06:08:13 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	set_opt(t_env *e, t_expr **expr)
{
	const char	options[] = "axc";
	char		*s;
	char		*p;

	s = (*expr)->expr;
	while (*s)
	{
		if ((p = ft_strchr(options, *s)))
			e->opts |= 1 << (int)(p - options);
		else
			die(EXIT_FAILURE, "error : bad option\n");
		s++;
	}
	if ((e->opts & OPT_A) && (e->opts & OPT_X))
		die(EXIT_FAILURE, "error : unsupported combination of options\n");
}

static void	read_path(t_env *e, t_expr **expr)
{
	char	*file;

	file = ft_strdup((*expr)->expr);
	ft_pushback((void **)&e->files, sizeof(char *), e->n_file++, &file);
}

void		read_opts(t_env *e, t_expr *expr)
{
	const char	*s[] = {"PATH", "OPTION_VAL", 0};
	static void	(*f[])(t_env *, t_expr **) = {read_path, set_opt, 0};

	while (expr)
	{
		if (expr->rule)
			find_rule(e, &expr, s, (t_f_rule *)f);
		expr = expr->next;
	}
}
