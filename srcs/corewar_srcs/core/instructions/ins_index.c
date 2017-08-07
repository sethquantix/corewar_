/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ins_index.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/29 08:38:24 by cchaumar          #+#    #+#             */
/*   Updated: 2017/08/07 11:11:47 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

void	i_ldi(t_proc *proc)
{
	int		addr;
	int		off;
	int		dest;

	if (get_value(proc, &addr, 0, V_REFERENCE))
		return ;
	if (proc->p_types[0] == REG_CODE)
		addr = proc->reg[addr];
	if (get_value(proc, &off, 1, V_VALUE))
		return ;
	if (get_value(proc, &dest, 2, V_REFERENCE))
		return ;
	if (proc->arena->verbose_lvl & V_LVL_OP)
	{
		ft_printf("P %4d | ldi %d %d r%d\n", proc->id, addr, off, dest);
		ft_printf("%7s| -> load from %d + %d = %d (with pc and mod %d)\n", "",
			addr, off, addr + off, proc->pc + (addr + off) % IDX_MOD);
	}
	addr += off;
	read_mem(idx_mod(proc->pc, addr), val(&proc->reg[dest], sizeof(int)),
		proc->arena->arena);
}

void	i_sti(t_proc *proc)
{
	int		reg;
	int		addr;
	int		off;

	if (get_value(proc, &reg, 0, V_REFERENCE))
		return ;
	if (get_value(proc, &addr, 1, V_VALUE))
		return ;
	if (get_value(proc, &off, 2, V_VALUE))
		return ;
	if (proc->arena->verbose_lvl & V_LVL_OP)
	{
		ft_printf("P %4d | sti r%d %d %d\n", proc->id, reg, addr, off);
		ft_printf("%7s| -> store to %d + %d = %d (with pc and mod %d)\n", "",
			addr, off, addr + off, proc->pc + (addr + off) % IDX_MOD);
	}
	addr += off;
	addr = idx_mod(proc->pc, addr);
	write_mem(addr, val(&proc->reg[reg], sizeof(int)),
		proc->arena->arena);
	set_mem(proc->arena->mem, addr, 4, proc->player);
}

void	i_lld(t_proc *proc)
{
	int		value;
	int		dest;

	if (get_value(proc, &value, 0, V_VALUE_NOIDX))
		return ;
	if (get_value(proc, &dest, 1, V_REFERENCE))
		return ;
	if (proc->arena->verbose_lvl & V_LVL_OP)
		ft_printf("P %4d | lld %d r%d\n", proc->id, value, dest);
	proc->reg[dest] = value;
	proc->carry = value == 0;
}

void	i_lldi(t_proc *proc)
{
	int		addr;
	int		off;
	int		dest;

	if (get_value(proc, &addr, 0, V_VALUE_NOIDX))
		return ;
	if (get_value(proc, &off, 1, V_VALUE))
		return ;
	if (get_value(proc, &dest, 2, V_REFERENCE))
		return ;
	if (proc->arena->verbose_lvl & V_LVL_OP)
	{
		ft_printf("P %4d | lldi %d %d r%d\n", proc->id, addr, off, dest);
		ft_printf("%7s| -> load from %d + %d = %d (with pc %d)\n", "",
			addr, off, addr + off, proc->pc + (addr + off));
	}
	addr += off + proc->pc;
	read_mem(addr, val(&proc->reg[dest], sizeof(int)), proc->arena->arena);
	proc->carry = proc->reg[dest] == 0;
}
