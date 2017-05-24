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

void	set_mem(uint32_t *mem, int addr, int size, int player)
{
	int 	i;

	i = 0;
	while (i < size)
	{
		mem[mem_mod(i + addr)] &= 0xF;
		mem[mem_mod(i + addr)] |= (600 << 16);
		mem[mem_mod(i + addr)] |= (1 << (4 + player));
		i++;
	}
}

int		mem_mod(int addr)
{
	addr %= MEM_SIZE;
	if (addr < 0)
		addr += MEM_SIZE;
	return (addr);
}

int		idx_mod(int pc, int addr)
{
	return (mem_mod(pc + (addr % IDX_MOD)));
}

void	write_mem(int addr, t_val v, uint8_t mem[])
{
	uint8_t		*t;
	int			i;

	ft_endian(v.p, v.s);
	i = 0;
	t = v.p;
	while (i++ < v.s)
		mem[mem_mod(addr++)] = *(t++);
	ft_endian(v.p, v.s);
}

void	read_mem(int addr, t_val v, uint8_t mem[])
{
	uint8_t		*t;
	int			i;

	ft_bzero(v.p, v.s);
	t = v.p;
	i = 0;
	while (i++ < v.s)
		*(t++) = mem[mem_mod(addr++)];
	ft_endian(v.p, v.s);
}
