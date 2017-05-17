/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ins_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/29 04:44:35 by cchaumar          #+#    #+#             */
/*   Updated: 2017/01/29 04:44:36 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	i_live(t_proc *proc, uint8_t mem[])
{
	static t_ft_arr	c = {0, 0, 0};
	t_champ			*v;

	if (c.t == 0)
		c = ft_array(proc->arena->champs, sizeof(t_champ),
			proc->arena->champ_count);
	proc->last_live = proc->arena->cycles;
	if ((proc->arena->verbose_lvl & V_LVL_LIVES) && (v = ft_arr_find(c,
		proc->params, (int (*)(void *, void *))cmp_id)) != NULL)
	{
		ft_printf("process %d says that %d is alive\n", proc->id, v->num);
		v->nbr_live++;
		v->last_live = proc->arena->cycles;
	}
	(void)mem;
}
void	i_ld(t_proc *proc, uint8_t mem[])
{
	int 	v;

	(void)proc;
	(void)mem;
}
void	i_st(t_proc *proc, uint8_t mem[])
{
	(void)proc;
	(void)mem;
}
void	i_aff(t_proc *proc, uint8_t mem[])
{
	(void)proc;
	(void)mem;
}

void	i_zjmp(t_proc *proc, uint8_t mem[])
{
	(void)proc;
	(void)mem;
}
