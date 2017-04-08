/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 18:50:05 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/06 18:50:06 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		mem_mod(int addr)
{
	addr %= MEM_SIZE;
	if (addr < 0)
		addr += MEM_SIZE;
	return (addr);
}

int		idx_mod(int addr)
{
	return (mem_mod(addr % IDX_MOD));
}

void	write_mem(int pc, t_val v, int mod, uint8_t mem[])
{
	static int	(*f_mod[])(int) = {mem_mod, idx_mod};
	uint8_t		*t;

	ft_endian(v.p, v.s);
	t = v.p;
	while (v.s--)
		mem[f_mod[mod](pc++)] = *(t++);
	ft_endian(v.p, v.s);
}

void	read_mem(int addr, t_val v, int mod, uint8_t mem[])
{
	static int	(*f_mod[])(int) = {mem_mod, idx_mod};
	uint8_t		*t;

	t = v.p;
	while (v.s--)
		*(t++) = mem[f_mod[mod](addr++)];
	ft_endian(v.p, v.s);
}
