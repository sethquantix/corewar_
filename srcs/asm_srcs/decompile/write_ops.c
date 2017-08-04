/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 08:01:59 by tsedigi           #+#    #+#             */
/*   Updated: 2017/06/28 08:02:00 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "decompile.h"

static void			write_label_ins(t_deco *all, t_dec_op *tmp, char *name)
{
	if (tmp->lbl != -1)
	{
		tmp->addr != 0 ? ft_dprintf(all->fd, "\n") : 0;
		ft_dprintf(all->fd, "label%d:\n", tmp->lbl);
	}
	ft_dprintf(all->fd, "%s%-15s", all->lbl ? "        " : "", name);
}

static void			write_ins_param(t_deco *all, t_dec_op *tmp, int i)
{
	if (tmp->param_type[i] == DIR_CODE)
	{
		if (tmp->param_lbl[i] != -1)
			ft_dprintf(all->fd, " %s:label%d", "%", tmp->param_lbl[i]);
		else
			ft_dprintf(all->fd, " %s%d", "%", tmp->param_value[i]);
	}
	else if (tmp->param_type[i] == IND_CODE)
	{
		if (tmp->param_lbl[i] != -1)
			ft_dprintf(all->fd, " :label%d", tmp->param_lbl[i]);
		else
			ft_dprintf(all->fd, " %d", tmp->param_value[i]);
	}
	else
		ft_dprintf(all->fd, " r%d", tmp->param_value[i]);
}

void				write_ops(t_deco *all)
{
	t_dec_op		*tmp;
	t_op			op;
	int				i;

	tmp = all->lst;
	while (tmp)
	{
		op = g_op_tab[tmp->opcode - 1];
		write_label_ins(all, tmp, op.name);
		i = 0;
		while (i < op.argc)
		{
			write_ins_param(all, tmp, i);
			i++;
			(i < op.argc) ? ft_dprintf(all->fd, ",") : 0;
		}
		ft_dprintf(all->fd, "\n");
		tmp = tmp->next;
	}
}
