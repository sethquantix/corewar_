/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inst_opt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/04 07:13:23 by tsedigi           #+#    #+#             */
/*   Updated: 2017/08/04 07:13:24 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_inst		*new_inst(char *name, int type, int addr)
{
	t_inst	*inst;

	inst = try(sizeof(t_inst));
	inst->name = ft_strdup(name);
	inst->type = type;
	inst->addr = addr;
	inst->op = type == INS ? op_for_name(name) : NULL;
	return (inst);
}

void		read_instruction(t_file *f, t_expr **expr)
{
	t_inst	*inst;
	t_list	*node;

	*expr = (*expr)->next;
	inst = new_inst((*expr)->expr, INS, f->addr);
	inst->op = op_for_name((*expr)->expr);
	inst->size = 1 + inst->op->octal;
	*expr = get_params(inst, *expr);
	f->addr += inst->size;
	node = ft_lstnew(NULL, 0);
	node->content = inst;
	ft_lstadd_end(&f->inst, node);
}
