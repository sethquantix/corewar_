/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/04 05:21:39 by cchaumar          #+#    #+#             */
/*   Updated: 2017/08/04 05:21:41 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

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

int		proc_get_args(t_proc *p, int addr, uint8_t mem[], uint8_t sizes[])
{
	int		i;
	int		err;

	i = 0;
	err = 0;
	while (i < p->op->argc)
	{
		p->p_types[i] = (uint8_t)PROC_CODE(p->oct, i);
		if ((PROC_TYPE(p->p_types[i]) & p->op->args[i]) == 0)
			err = -1;
		addr = mem_mod(addr);
		p->p_sizes[i] = sizes[p->p_types[i]];
		read_mem(addr, val(p->params + i, p->p_sizes[i]), mem);
		addr += p->p_sizes[i++];
	}
	return (err);
}

int		proc_read_params(t_proc *p, uint8_t mem[])
{
	static uint8_t	sizes[] = {
		0, REG_NUMBER_SIZE, DIR_SIZE, IND_SIZE};

	ft_bzero(p->params, sizeof(p->params));
	sizes[2] = (uint8_t)p->op->dir_size;
	sizes[2] = sizes[2] ? sizes[2] : 4;
	if (p->op->octal)
		read_mem(p->pc + 1, val(&p->oct, 1), mem);
	else
		p->oct = DIR_CODE << 6;
	return (proc_get_args(p, p->pc + 1 + p->op->octal, mem, sizes));
}
