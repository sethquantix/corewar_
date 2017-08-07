/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ins_fork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/29 10:48:13 by cchaumar          #+#    #+#             */
/*   Updated: 2017/08/07 12:39:17 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	i_fork(t_proc *proc)
{
	int		addr;
	int		dest;

	if (get_value(proc, &addr, 0, V_VALUE))
		return ;
	dest = idx_mod(proc->pc, addr);
	if (proc->arena->verbose_lvl & V_LVL_OP)
		ft_printf("P %4d | fork %d (%d)\n", proc->id,
			addr, dest);
	proc->arena->add_proc(proc->arena, proc, dest);
}

void	i_lfork(t_proc *proc)
{
	int		addr;

	if (get_value(proc, &addr, 0, V_VALUE))
		return ;
	if (proc->arena->verbose_lvl & V_LVL_OP)
		ft_printf("P %4d | lfork %d (%d)\n", proc->id,
			addr, mem_mod(addr + proc->pc));
	addr = mem_mod(addr + proc->pc);
	proc->arena->add_proc(proc->arena, proc, addr);
}
