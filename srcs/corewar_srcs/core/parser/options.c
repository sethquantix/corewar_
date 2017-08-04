/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/09 01:57:07 by cchaumar          #+#    #+#             */
/*   Updated: 2017/08/01 03:56:10 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	option_d(t_expr **e, t_arena *a)
{
	a->opts |= D_OPT;
	*e = (*e)->next;
	a->dump_cycles = ft_atoi((*e)->expr);
}

void	option_s(t_expr **e, t_arena *a)
{
	a->opts |= S_OPT;
	*e = (*e)->next;
	a->dump_cycles = ft_atoi((*e)->expr);
}

void	option_g(t_expr **e, t_arena *a)
{
	a->opts |= G_OPT;
	(void)e;
}

void	option_v(t_expr **e, t_arena *a)
{
	*e = (*e)->next;
	a->opts |= V_OPT;
	a->verbose_lvl = ft_atoi((*e)->expr);
}

void	option_o(t_expr **e, t_arena *a)
{
	int		fd;

	*e = (*e)->next;
	a->opts |= O_OPT;
	if ((fd = open((*e)->expr, O_RDONLY)) == -1)
		err(ERR, "Can't open %s for writing\n", (*e)->expr);
	else
		a->debug_fd = fd;
}
