/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_opts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnagy <lnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:47:34 by lnagy             #+#    #+#             */
/*   Updated: 2017/03/08 14:47:36 by lnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	read_debug(t_env *e, t_expr **expr)
{
	int	fd;

	*expr = (*expr)->next;
	if ((fd = open((*expr)->expr, O_WRONLY)) == -1)
		die("error : couldn't open %s for writing\n", EXIT_FAILURE,
			(*expr)->expr);
	if (e->debug)
		close(e->debug);
	e->debug = fd;
}

static void	set_opt(t_env *e, t_expr **expr)
{
	e->opts |= ft_strcmp((*expr)->rule, "OPTION_A") == 0 ? OPT_A : OPT_X;
	if ((e->opts & OPT_A) && (e->opts & OPT_X))
		die("error : unsupported combination of options\n", EXIT_FAILURE);
}

static void read_path(t_env *e, t_expr **expr)
{
	char	*file;

	file = ft_strdup((*expr)->expr);
	ft_pushback((void **)&e->files, sizeof(char *), e->n_file++, &file);
}

void	read_opts(t_env *e, t_expr *expr)
{
	const char	*s[] = {"PATH", "OPTION_A", "OPTION_X", "OPTION_D", 0};
	static void	(*f[])(t_env *, t_expr **) = {read_path, set_opt,
		set_opt, read_debug, 0};

	while (expr)
	{
		if (expr->rule)
			find_rule(e, &expr, s, (t_f_rule *)f);
		expr = expr->next;
	}
}
