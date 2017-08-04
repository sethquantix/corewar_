/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ins_calc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/29 07:48:19 by cchaumar          #+#    #+#             */
/*   Updated: 2017/01/29 07:48:20 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	i_add(t_proc *proc)
{
	int		r1;
	int		r2;
	int		r3;

	if (get_value(proc, &r1, 0, V_REFERENCE))
		return ;
	if (get_value(proc, &r2, 1, V_REFERENCE))
		return ;
	if (get_value(proc, &r3, 2, V_REFERENCE))
		return ;
	if (proc->arena->verbose_lvl & V_LVL_OP)
		ft_printf("P %4d | sub r%d r%d r%d\n", proc->id, r1, r2, r3);
	proc->reg[r3] = proc->reg[r1] + proc->reg[r2];
	proc->carry = proc->reg[r3] == 0;
}

void	i_sub(t_proc *proc)
{
	int		r1;
	int		r2;
	int		r3;

	if (get_value(proc, &r1, 0, V_REFERENCE))
		return ;
	if (get_value(proc, &r2, 1, V_REFERENCE))
		return ;
	if (get_value(proc, &r3, 2, V_REFERENCE))
		return ;
	if (proc->arena->verbose_lvl & V_LVL_OP)
		ft_printf("P %4d | sub r%d r%d r%d\n", proc->id, r1, r2, r3);
	proc->reg[r3] = proc->reg[r1] - proc->reg[r2];
	proc->carry = proc->reg[r3] == 0;
}

void	i_and(t_proc *proc)
{
	int		v1;
	int		v2;
	int		r;

	if (get_value(proc, &v1, 0, V_VALUE))
		return ;
	if (get_value(proc, &v2, 1, V_VALUE))
		return ;
	if (get_value(proc, &r, 2, V_REFERENCE))
		return ;
	if (proc->arena->verbose_lvl & V_LVL_OP)
		ft_printf("P %4d | and %d %d r%d\n", proc->id, v1, v2, r);
	proc->reg[r] = v1 & v2;
	proc->carry = proc->reg[r] == 0;
}

void	i_or(t_proc *proc)
{
	int		v1;
	int		v2;
	int		r;

	if (get_value(proc, &v1, 0, V_VALUE))
		return ;
	if (get_value(proc, &v2, 1, V_VALUE))
		return ;
	if (get_value(proc, &r, 2, V_REFERENCE))
		return ;
	if (proc->arena->verbose_lvl & V_LVL_OP)
		ft_printf("P %4d | or %d %d r%d\n", proc->id, v1, v2, r);
	proc->reg[r] = v1 | v2;
	proc->carry = proc->reg[r] == 0;
}

void	i_xor(t_proc *proc)
{
	int		v1;
	int		v2;
	int		r;

	if (get_value(proc, &v1, 0, V_VALUE))
		return ;
	if (get_value(proc, &v2, 1, V_VALUE))
		return ;
	if (get_value(proc, &r, 2, V_REFERENCE))
		return ;
	if (proc->arena->verbose_lvl & V_LVL_OP)
		ft_printf("P %4d | xor %d %d r%d\n", proc->id, v1, v2, r);
	proc->reg[r] = v1 ^ v2;
	proc->carry = proc->reg[r] == 0;
}
