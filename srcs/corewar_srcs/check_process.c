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
	p->die = p->arena->cycles - p->last_live > p->arena->ctd ? 1 : 0;
	if (p->die && (p->arena->verbose_lvl & V_LVL_DEATH))
		ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
			p->id, p->arena->cycles - p->last_live, p->arena->ctd);
	if (p->die)
	{
		p->arena->alive--;
		UNSET_PLAYER(p->arena->mem[p->pc], p->player);
	}
	return (p->die);
}

static void ctd_update(t_arena *a)
{
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

void		check_process(t_arena *a)
{
	t_list	*p;
	t_list	*living;
	t_list	*n;

	living = NULL;
	p = a->procs;
	while (p)
	{
		if (check(p->content) == 0)
		{
			n = ft_lstnew(NULL, 0);
			n->content_size = p->content_size;
			n->content = p->content;
			ft_lstadd_end(&living, n);
		}
		p = p->next;
	}
	ft_lstdel(&a->procs, ft_dummy);
	a->procs = living;
	ctd_update(a);
}

int 		cmp_id(uint32_t	*ref, t_champ *data)
{
	return (*ref == data->id);
}
