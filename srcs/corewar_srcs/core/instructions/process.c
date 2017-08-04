/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 17:16:47 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/06 17:16:48 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

int		inst_size(t_proc *p)
{
	int		i;
	int		r;

	i = 0;
	r = p->op->octal + 1;
	if (!p->op->octal)
		return (r + p->op->dir_size);
	while (i < p->op->argc)
		r += p->p_sizes[i++];
	return (r);
}

void	verb_mem(uint8_t *mem, t_proc *p, int pc, int n)
{
	int i;

	ft_printf("ADV %d (0x%04.4x -> 0x%04.4x) ", n, mem_mod(p->pc),
		mem_mod(p->pc + n));
	i = 0;
	while (i < n)
	{
		ft_printf("%02.2x ", mem[mem_mod(pc + i)]);
		i++;
	}
	ft_putchar('\n');
}

void	move_proc(t_proc *p, int addr)
{
	proc_set(p, UNSET_PLAYER);
	p->pc = mem_mod(addr);
	proc_set(p, SET_PLAYER);
}

void	proc_exec_inst(t_proc *p)
{
	static void		(*instructions[])(t_proc *) = {
		NULL, i_live, i_ld, i_st, i_add, i_sub, i_and, i_or, i_xor, i_zjmp,
		i_ldi, i_sti, i_fork, i_lld, i_lldi, i_lfork, i_aff, NULL};

	if (p->dead)
		return ;
	if (!p->op && p->get_inst(p, p->arena->arena))
	{
		move_proc(p, p->pc + 1);
		return ;
	}
	proc_set(p, SET_PLAYER);
	if (p->cycles_left && --p->cycles_left)
		return ;
	proc_set(p, UNSET_PLAYER);
	if (!p->get_params(p, p->arena->arena))
		instructions[p->op->opcode](p);
	if ((p->op->opcode != 9 || p->carry == 0) &&
		(p->arena->verbose_lvl & V_LVL_PC))
		verb_mem(p->arena->arena, p, p->pc, inst_size(p));
	if (p->op->opcode != 9 || p->carry == 0)
		p->pc += inst_size(p);
	p->pc = mem_mod(p->pc);
	p->op = NULL;
	proc_set(p, SET_PLAYER);
}
