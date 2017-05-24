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

int		proc_read_inst(t_proc *p, uint8_t mem[])
{
	uint8_t			op;

	op = mem[p->pc];
	if (!op || op > 16)
		return (-1);
	p->op = g_tab + op - 1;
	p->cycles_left = p->op->cycles;
	return (0);
}

int		proc_read_params(t_proc *p, uint8_t mem[])
{
	static uint8_t	sizes[] = {0, REG_NUMBER_SIZE, DIR_SIZE, IND_SIZE};
	int				addr;
	int				i;
	int				err;

	ft_bzero(p->params, sizeof(p->params));
	sizes[2] = (uint8_t)p->op->dir_size;
	sizes[2] = sizes[2] ? sizes[2] : 4;
	if (p->op->octal)
		read_mem(p->pc + 1, val(&p->oct, 1), mem);
	else
		p->oct = DIR_CODE << 6;
	i = 0;
	err = 0;
	addr = p->pc + 1 + p->op->octal;
	while (i < p->op->argc)
	{
		if ((PROC_TYPE((p->p_types[i] = PROC_CODE(p->oct, i))) &
			p->op->args[i]) == 0)
			err = -1;
		addr = mem_mod(addr);
		p->p_sizes[i] = sizes[p->p_types[i]];
		read_mem(addr, val(p->params + i, p->p_sizes[i]), mem);
		addr += p->p_sizes[i++];
	}
	return (err);
}

int		inst_size(t_proc *p)
{

	int			i;
	int			r;

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

void	proc_exec_inst(t_proc *p)
{
	static void		(*instructions[])(t_proc *) = {
		NULL, i_live, i_ld, i_st, i_add, i_sub, i_and, i_or, i_xor, i_zjmp,
		i_ldi, i_sti, i_fork, i_lld, i_lldi, i_lfork, i_aff, NULL};
	int 			err;

	if (!p->op && p->get_inst(p, p->arena->arena))
	{
		UNSET_PLAYER(p->arena->mem[p->pc], p->player);
		p->pc = mem_mod(p->pc + 1);
		SET_PLAYER(p->arena->mem[p->pc], p->player);
		return ;
	}
	if (p->cycles_left && --p->cycles_left)
		return ;
	UNSET_PLAYER(p->arena->mem[p->pc], p->player);
	err = p->get_params(p, p->arena->arena);
	if (!err)
		instructions[p->op->opcode](p);
	if ((p->op->opcode != 9 || p->carry == 0) &&
		(p->arena->verbose_lvl & V_LVL_PC))
		verb_mem(p->arena->arena, p, p->pc, inst_size(p));
	if (p->op->opcode != 9 || p->carry == 0)
		p->pc += inst_size(p);
	p->pc = mem_mod(p->pc);
	p->op = NULL;
	SET_PLAYER(p->arena->mem[p->pc], p->player);
}
