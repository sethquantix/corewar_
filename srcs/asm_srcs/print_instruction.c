/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_instruction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/04 07:49:27 by tsedigi           #+#    #+#             */
/*   Updated: 2017/08/04 07:49:28 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	print_colored(const char *format, char *color, char *data)
{
	if (env()->opts & OPT_C)
		ft_printf(format, color, data, COLOR_END);
	else
		ft_printf(format, "", data, "");
}

static void	print_lbl(t_file *file, t_inst *inst)
{
	print_colored("      :", inst->color, NULL);
	if (!inst->color)
		addr_label(file, inst->name, file->inst);
	print_colored("    %s%s%s:\n", inst->color, inst->name);
}

static void	print_args(t_inst *inst)
{
	int		i;
	char	*col;

	i = 0;
	while (i < inst->op->argc)
	{
		col = inst->p_type[i] > 2 ?
			ft_strdup(inst->labels[i]->color) :
			get_color_(inst->p_type[i] + 1, 'g');
		print_colored("%s%-18s%s", col, inst->args[i++]);
		ft_memdel((void **)&col);
	}
}

void		print_inst(t_inst *inst, t_file *file)
{
	char	*col;

	col = ft_itoa(inst->addr);
	print_colored("%s%-5s%s", COLOR_ADDR, col);
	free(col);
	if (inst->type == LBL)
	{
		print_lbl(file, inst);
		return ;
	}
	col = ft_itoa(inst->size);
	print_colored("(%s%-3s%s) :", COLOR_SIZE, col);
	free(col);
	col = get_color_(inst->op->opcode, 'r');
	print_colored("        %s%-10s%s", col, inst->name);
	ft_memdel((void **)&col);
	print_args(inst);
	ft_putchar('\n');
	print_params(inst, 0);
	print_params(inst, 1);
	ft_putchar('\n');
}
