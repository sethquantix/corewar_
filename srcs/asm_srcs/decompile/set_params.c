/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 08:12:16 by tsedigi           #+#    #+#             */
/*   Updated: 2017/06/28 08:12:17 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "decompile.h"

static void			set_value(unsigned char *file,
	t_dec_op *node, int i, int size)
{
	int				j;
	short			s;
	unsigned int	conv;

	j = 0;
	if (size == 4)
	{
		conv = (file[0] << 24) | (file[1] << 16) | (file[2] << 8) | file[3];
		node->param_value[i] = conv;
	}
	else if (size == 2)
	{
		s = (file[0] << 8) | file[1];
		node->param_value[i] = s;
	}
	else
		node->param_value[i] = file[0];
}

int					set_param_no_octal(char *file, t_dec_op *node)
{
	t_op			op;
	int				iter;

	op = g_op_tab[node->opcode - 1];
	iter = 0;
	if (op.argc)
	{
		if (op.args[0] & T_REG)
		{
			node->param_size[0] = REG_SIZE;
			node->param_type[0] = REG_CODE;
			set_value((unsigned char *)file, node, 0, REG_SIZE);
			iter = REG_SIZE;
		}
		else
		{
			node->param_size[0] = op.dir_size;
			node->param_type[0] = DIR_CODE;
			set_value((unsigned char *)file, node, 0, op.dir_size);
			iter = op.dir_size;
		}
	}
	return (iter);
}

int					set_param_with_octal(char *file, t_dec_op *node)
{
	static int		sizes[] = {0, REG_NUMBER_SIZE, DIR_SIZE, IND_SIZE};
	t_op			op;
	int				i;
	int				iter;

	op = g_op_tab[node->opcode - 1];
	sizes[2] = op.dir_size;
	iter = 1;
	i = 0;
	while (i < op.argc)
	{
		if ((PROC_TYPE((node->param_type[i] =
			PROC_CODE(file[0], i))) & op.args[i]) == 0)
		{
			die(EXIT_FAILURE, "Error with encoding octet or param");
		}
		node->param_size[i] = sizes[node->param_type[i]];
		set_value((unsigned char *)&file[iter], node, i, node->param_size[i]);
		iter += node->param_size[i++];
	}
	return (iter - 1);
}
