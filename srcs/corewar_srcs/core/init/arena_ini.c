/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_ini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 13:21:53 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/06 13:21:54 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_proc	*add_proc(t_arena *a, t_champ *c, int pc)
{
	t_proc	*proc;

	proc = try(sizeof(t_proc));
	proc->pc = pc;
	proc->id = ++a->proc_id;
	proc->get_inst = proc_read_inst;
	proc->get_params = proc_read_params;
	proc->reg[1] = (uint32_t)c->id;
	proc->arena = a;
	proc->op = NULL;
	proc->player = -c->id - 1;
	ft_pushback((void **)&a->procs, sizeof(t_proc *), a->proc_count++, &proc);
	a->alive++;
	return (proc);
}

t_proc	*fork_proc(t_arena *a, t_proc *p, int pc)
{
	t_proc	*proc;

	proc = try(sizeof(t_proc));
	proc->pc = pc;
	proc->id = ++a->proc_id;
	proc->oct = 0;
	proc->get_inst = proc_read_inst;
	proc->get_params = proc_read_params;
	ft_memcpy(proc->reg, p->reg, sizeof(p->reg));
	proc->arena = a;
	proc->op = NULL;
	proc->cycles_left = 0;
	proc->last_live = p->last_live;
	proc->carry = p->carry;
	proc->player = p->player;
	ft_pushback((void **)&a->procs, sizeof(t_proc *), a->proc_count++, &proc);
	a->alive++;
	return (proc);
}

void	load_code(t_arena *a, t_champ *c)
{
	int		pc;
	t_proc	*p;

	pc = (-c->id - 1) * (MEM_SIZE / a->champ_count);
	p = add_proc(a, c, pc);
	ft_memcpy(a->arena + p->pc, c->source, c->head.prog_size);
	set_mem(a->mem, p->pc, c->head.prog_size, p->player);
	proc_set(p, SET_PLAYER);
}

void	init(t_arena *arena)
{
	int			num;
	int			i;

	arena->check = check_process;
	arena->add_proc = (t_f_add)add_proc;
	arena->ctd = CYCLE_TO_DIE;
	i = 0;
	num = 1;
	while (i < arena->champ_count)
	{
		if (!arena->champs[i].set)
		{
			while (check_set(arena->champs, arena->champ_count, num))
				num++;
			arena->champs[i].num = num++;
		}
		load_code(arena, arena->champs + i);
		i++;
	}
	arena->add_proc = (t_f_add)fork_proc;
	ft_printf("\n\n%s********** BEGIN ! *************%s\n\n",
		acol(1, 1, 4), COLOR_END);
}
