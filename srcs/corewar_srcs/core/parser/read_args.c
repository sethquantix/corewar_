/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/08 17:48:43 by cchaumar          #+#    #+#             */
/*   Updated: 2017/08/01 08:37:24 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void 	player(t_expr **e, t_arena *a)
{
	static int 	id = 0;
	t_champ		c;
	int			n;
	int			set;
	int			fd;

	*e = (*e)->next;
	n = 0;
	set = 0;
	if (ft_strcmp((*e)->rule, "NUMBER") == 0)
	{
		*e = (*e)->next;
		n = ft_atoi((*e)->expr);
		if ((set = 1) && check_set(a->champs, a->champ_count, n))
			die(EXIT_FAILURE, "Can't set same player id %d twice\n", n);
	}
	if ((fd = open((*e)->expr, O_RDONLY) == -1))
	{
		ft_printf("%s[%s]: Can't open file%s\n",
			acol(5, 0, 0), (*e)->expr, COLOR_END);
		return ;
	}
	else
		close(fd);
	c = (t_champ){(*e)->expr, NULL, empty_head(), --id, n, set};
	ft_pushback((void **)&a->champs, sizeof(t_champ), a->champ_count++, &c);
}

void	read_args(t_expr *expr, t_arena *a)
{
	const char	*rules[] = {"OPTION_G", "OPTION_V", "OPTION_D", "OPTION_O",
		"OPTION_A", "OPTION_S", "PLAYER", NULL};
	static void	(*handlers[])(t_expr **, t_arena *) =
		{option_g, option_v, option_d, option_o, option_a, option_s,
		 player, NULL};
	int			i;

	while (expr)
	{
		i = 0;
		while (rules[i])
			if (!ft_strncmp(rules[i], expr->rule, ft_strlen(rules[i])))
			{
				handlers[i](&expr, a);
				break ;
			}
			else
				i++;
		if (!rules[i])
			die(EXIT_FAILURE, "Error : Bad options\n");
		expr = expr->next;
	}
}
