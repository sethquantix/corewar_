/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 08:16:58 by tsedigi           #+#    #+#             */
/*   Updated: 2017/06/28 08:16:59 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "decompile.h"

int			check_op(char *file, t_deco *all, int iter)
{
	t_dec_op	*node;
	t_op		op;
	int			ret;

	if (!file)
		die(EXIT_FAILURE, "Unknown");
	if (file[0] < 1 || file[0] > 16)
		die(EXIT_FAILURE, "Invalid, operation");
	if (!(node = (t_dec_op *)ft_memalloc(sizeof(t_dec_op))))
		die(EXIT_FAILURE, "Malloc failed");
	node->opcode = file[0];
	op = g_op_tab[node->opcode - 1];
	ret = op.octal ? 2 : 1;
	ret == 2 ? node->octal = 1 : 0;
	node->addr = iter;
	add_deco_op(all, node);
	if (ret == 2 && file[1])
		ret += set_param_with_octal(&file[1], node);
	else if (ret == 1)
		ret += set_param_no_octal(&file[1], node);
	return (ret);
}
