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

#include "corewar.h"

void	(*instructions[])(t_proc *, uint8_t []) = {
	NULL, i_live, i_ld, i_st, i_add, i_sub, i_and, i_or, i_xor, i_zjmp,
	i_ldi, i_sti, i_fork, i_lld, i_lldi, i_lfork, i_aff, NULL};

int		proc_read_inst(t_proc *p, uint8_t mem[])
{
	static uint8_t	sizes[] = {0, REG_SIZE, DIR_SIZE, IND_SIZE};
	uint8_t			op;
	int				i;

	op = mem[p->pc];
	if (!op || op > 16)
		return (-1);
	p->op = op_tab + op - 1;
	sizes[2] = (uint8_t)p->op->dir_size;
	if (p->op->octal)
		p->oct = mem[mem_mod(p->pc + 1)];
	i = 0;
	while (i < p->op->argc)
	{
		p->p_sizes[i] = sizes[PROC_ARG_T(p->oct, i + 1)];
		i++;
	}
	return (0);
}

int		proc_read_params(t_proc *p, uint8_t mem[])
{
	int		addr;
	int		i;
	
	i = 0;
	addr = mem_mod(p->pc + 1 + p->op->octal);
	while (i < p->op->argc)
	{
		if ((PROC_ARG(p->oct, i + 1) & p->op->args[i]) == 0)
			return (-1);
		read_mem(addr, val(p->params + i, p->p_sizes[i]), MOD_MEM, mem);
		addr += p->p_sizes[i++];
	}
	return (0);
}

int		inst_size(t_proc *p)
{

	int			i;
	int			r;

	i = 0;
	r = 0;
	if (!p->oct)
		return (p->op->dir_size);
	while (i < p->op->argc)
		r += p->p_sizes[i++];
	return (r);
}

void	proc_exec_inst(t_proc *p)
{
	if (!p->op && p->get_inst(p, p->arena->arena))
	{
		p->pc++;
		return ;
	}
	if (p->cycles_left && p->cycles_left--)
		return ;
	if (!p->get_params(p, p->arena->arena))
	{
		p->pc += inst_size(p);
		return ;
	}
	instructions[p->op->opcode](p, p->arena->arena);
}
