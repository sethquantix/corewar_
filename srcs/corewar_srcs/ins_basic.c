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

void	i_live(t_proc *proc)
{
	static t_ft_arr	c = {0, 0, 0};
	t_champ			*v;

	if (c.t == 0)
		c = ft_array(proc->arena->champs, sizeof(t_champ),
			proc->arena->champ_count);
	if (proc->arena->verbose_lvl & V_LVL_OP)
		ft_printf("P %4d | live %d\n", proc->id, proc->params[0]);
	proc->last_live = proc->arena->cycles;
	proc->arena->nbr_lives++;
	if ((v = ft_arr_find(c, proc->params, (int (*)(void *, void *))cmp_id))
		!= NULL)
	{
		v->nbr_live++;
		v->last_live = proc->arena->cycles;
	}
	if ((proc->arena->verbose_lvl & V_LVL_LIVES) && v)
		ft_printf("Player %d (%s) is said to be alive\n", v->num,
				  v->head.prog_name);
}

void	i_ld(t_proc *proc)
{
	int		value;
	int 	reg;

	if (get_value(proc, &value, 0, V_VALUE))
		return ;
	if (get_value(proc, &reg, 1, V_REFERENCE))
		return ;
	if (proc->arena->verbose_lvl & V_LVL_OP)
		ft_printf("P %4d | ld %d r%d\n", proc->id, value, reg);
	proc->reg[reg] = value;
	proc->carry = value == 0;
}

void	i_st(t_proc *proc)
{
	int		reg;
	int		addr;

	if (get_value(proc, &reg, 0, V_REFERENCE))
		return ;
	if (get_value(proc, &addr, 1, V_REFERENCE))
		return ;
	if (proc->arena->verbose_lvl & V_LVL_OP)
		ft_printf("P %4d | st r%d %s%d\n", proc->id, reg,
			proc->p_types[1] == REG_CODE ? "r" : "", addr);
	if (proc->p_types[1] == REG_CODE)
		proc->reg[addr] = proc->reg[reg];
	else
	{
		addr = idx_mod(proc->pc, addr);
		write_mem(addr, val(&proc->reg[reg], sizeof(int)), proc->arena->arena);
		set_mem(proc->arena->mem, addr, 4, proc->player);
	}
}

void	i_aff(t_proc *proc)
{
	int 	v;
	char 	t[5];

	if (get_value(proc, &v, 0, V_VALUE))
		return ;
	t[4] = 0;
	ft_memcpy(t, &v, 4);
	if (proc->arena->opts & A_OPT)
	{
		if (proc->arena->aff)
			proc->arena->aff = ft_strjoinfree(proc->arena->aff, t, 1);
		else
			proc->arena->aff = ft_strdup(t);
	}
}

void	i_zjmp(t_proc *proc)
{
	int		addr;

	if (get_value(proc, &addr, 0, V_VALUE))
		return ;
	if (proc->arena->verbose_lvl & V_LVL_OP)
		ft_printf("P %4d | zjmp %d %s\n", proc->id, addr, proc->carry ? "OK" :
			"FAILED");
	if (!proc->carry)
		return ;
	proc->pc = idx_mod(proc->pc, addr);
}
