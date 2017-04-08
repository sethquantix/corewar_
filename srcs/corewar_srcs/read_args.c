/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/08 17:48:43 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/08 17:48:44 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	option_g(t_expr **e, t_arena *a)
{
	a->opts |= G_OPT;
	(void)e;
}

static void	option_v(t_expr **e, t_arena *a)
{
	*e = (*e)->next;
	a->opts |= V_OPT;
	a->verbose_lvl = ft_atoi((*e)->expr);
}

static void	option_d(t_expr **e, t_arena *a)
{
	int		fd;

	*e = (*e)->next;
	a->opts |= D_OPT;
	if ((fd = open((*e)->expr)) == -1)
		err("Can't open %s for writing\n", (*e)->expr);
	else
		a->debug_fd = fd;
}

static void player(t_expr **e, t_arena *a)
{
	t_champ	c;
	int		n;
	int		set;

	*e = (*e)->next;
	n = 0;
	if (ft_strcmp((*e)->rule, "NUMBER") == 0)
	{
		n = ft_atoi((*e)->expr);
		set = 1;
		if (check_set(a->champs, a->champ_count, n))
			die("Can't set same player id twice\n", EXIT_FAILURE);
	}
	c = (t_champ){(*e)->expr, NULL, 0, a->champ_count, n, set};
	ft_pushback((void **)&a->champs, sizeof(t_champ), a->champ_count++, &c);
}

void	read_args(t_expr *expr, t_arena *a)
{
	const char	*rules[] = {"OPTION_G, OPTION_V, OPTION_D, PLAYER", NULL};
	const void	(*handlers[])(t_expr **, t_arena *) =
		{option_g, option_v, option_d, player, NULL};
	int			i;
	
	while (expr)
	{
		i = 0;
		while (rules[i])
			if (!ft_strncmp(rules[i], expr->rule, ft_strlen(rules[i])))
			{
				handlers[i](&expr, arena);
				break ;
			}
			else
				i++;
		if (!rules[i])
			die("Error : Bad options\n", EXIT_FAILURE);
		expr = expr->next;
	}
}
