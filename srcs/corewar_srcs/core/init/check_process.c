/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 17:36:39 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/07 17:36:42 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	check(t_proc *p)
{
	int		die;

	die = p->arena->cycles - p->last_live > p->arena->ctd ? 1 : 0;
	if (die && (p->arena->verbose_lvl & V_LVL_DEATH))
		ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
			p->id, p->arena->cycles - p->last_live, p->arena->ctd);
	if (die)
	{
		p->arena->alive--;
		UNSET_PLAYER(p->arena->mem[p->pc], p->player);
	}
	return (die);
}

void		check_process(t_arena *a)
{
	int		i;

	i = 0;
	while (i < a->proc_count)
	{
		if (!a->procs[i]->dead)
			a->procs[i]->dead = check(a->procs[i]);
		i++;
	}
	a->last_check = a->cycles;
	if (++a->check_cycles >= MAX_CHECKS || a->nbr_lives >= NBR_LIVE)
	{
		a->ctd -= CYCLE_DELTA;
		if (a->verbose_lvl & V_LVL_CYCLES)
			ft_printf("Cycle to die is now %d\n", a->ctd);
		a->check_cycles = 0;
	}
	a->nbr_lives = 0;
}

int 		cmp_id(int *ref, t_champ *data)
{
	return (*ref == data->id);
}
