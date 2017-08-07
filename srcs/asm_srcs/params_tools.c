/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params_opt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/04 07:08:22 by tsedigi           #+#    #+#             */
/*   Updated: 2017/08/04 07:08:26 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	hex_print(int v, int size)
{
	int				i;
	unsigned char	c[4];

	ft_memcpy(c, &v, size);
	i = 0;
	while (i < size)
	{
		ft_printf("%-4d", c[size - 1 - i]);
		i++;
	}
	while (i < 4)
	{
		ft_printf("    ");
		i++;
	}
	ft_printf("  ");
}

void		print_params(t_inst *inst, int type)
{
	int		i;

	i = 0;
	ft_printf("%20s%-4d%-5.0d ", "", inst->op->opcode, inst->oct);
	while (i < inst->op->argc)
	{
		type == 0 ? hex_print(inst->params[i], inst->p_size[i]) :
			ft_printf("%-18d", inst->params[i]);
		i++;
	}
	ft_putchar('\n');
}

void		fill_param(int type, t_inst *inst, t_expr *expr, int i)
{
	static int	size[] = {REG_NUMBER_SIZE, 0, IND_SIZE, 0, IND_SIZE};
	static int	oct[] = {REG_CODE, DIR_CODE, IND_CODE, DIR_CODE, IND_CODE};
	char		*s;

	size[1] = inst->op->dir_size;
	size[3] = inst->op->dir_size;
	inst->p_type[i] = type;
	inst->p_size[i] = size[type];
	inst->oct |= inst->op->octal ? oct[type] << (6 - 2 * i) : 0;
	s = ft_strdup(expr->expr);
	inst->args[i] = ft_strdup(expr->expr);
	ft_strtolower(inst->args[i]);
	if (type > 2)
	{
		inst->label[i] = ft_strsub(s, 1 + (type == 3),
			ft_strlen(s + 1 + (type == 3)));
		free(s);
		return ;
	}
	ft_strtolower(s);
	s += type != 2;
	inst->params[i] = s[1] == 'x' ? ft_atoi_base(s + 2, EXA_CHAR) : ft_atoi(s);
	free(s - (type != 2));
}

t_expr		*get_params(t_inst *inst, t_expr *expr)
{
	const char	*types[] = {"REG", "DIRECT", "INDIRECT", "DIRECT_LABEL",
		"INDIRECT_LABEL"};
	int			i;
	int			j;

	i = 0;
	while (i < inst->op->argc)
	{
		expr = expr->next;
		j = 0;
		while (ft_strcmp(types[j], expr->rule))
			j++;
		fill_param(j, inst, expr, i);
		inst->size += inst->p_size[i];
		i++;
	}
	return (expr);
}
