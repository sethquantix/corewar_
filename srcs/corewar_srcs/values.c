/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   values.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 05:03:20 by cchaumar          #+#    #+#             */
/*   Updated: 2017/05/19 05:03:21 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_val	val(void *p, uint8_t s)
{
	return ((t_val){p, s});
}

int 	wrap_size(int v, int size)
{
	if (size == 4)
		return (v);
	if (size == 2)
		return ((short)v);
	return ((char)v);
}


int 	get_value(t_proc *p, int *v, int i, t_type type)
{
	*v = wrap_size(p->params[i], p->p_sizes[i]);
	if (p->p_types[i] == REG_CODE)
	{
		if (*v <= 0 || *v > REG_NUMBER)
			return (-1);
		*v = type == V_REFERENCE ? *v : p->reg[*v];
		return (0);
	}
	if (type == V_REFERENCE || p->p_types[i] == DIR_CODE)
		return (0);
	*v = mem_mod(type == V_VALUE_NOIDX ? p->pc + *v : idx_mod(p->pc, *v));
	read_mem(*v, val(v, sizeof(int)), p->arena->arena);
	return (0);
}
