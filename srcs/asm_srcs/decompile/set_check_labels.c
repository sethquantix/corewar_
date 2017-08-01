/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_check_labels.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 08:06:44 by tsedigi           #+#    #+#             */
/*   Updated: 2017/06/28 08:06:45 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decompile.h"
#include "asm.h"

static int		add_lbl(void)
{
	static int	lbl = 0;

	return (lbl++);
}

static int		check_lbl(t_dec_op *lst, t_dec_op *current,
	int i, t_deco *all)
{
	while (lst)
	{
		if (current->addr + current->param_value[i] == lst->addr)
		{
			if (lst->lbl == -1)
				lst->lbl = add_lbl();
			all->lbl = 1;
			return (lst->lbl);
		}
		lst = lst->next;
	}
	return (-1);
}

static void		loop_check_lbl(t_deco *all, t_dec_op *tmp, int argc, int i)
{
	while (i < argc)
	{
		tmp->param_lbl[i] = -1;
		if (tmp->param_type[i] == DIR_CODE || tmp->param_type[i] == IND_CODE)
		{
			if (!tmp->param_value[i] || (
				tmp->param_value[i] + tmp->addr < 0 ||
				tmp->param_value[i] + tmp->addr >= (int)all->head.prog_size))
			{
				i++;
				continue ;
			}
			tmp->param_lbl[i] = check_lbl(all->lst, tmp, i, all);
		}
		i++;
	}
}

void			set_check_lbl(t_deco *all)
{
	t_dec_op	*tmp;
	t_op		op;

	tmp = all->lst;
	while (tmp)
	{
		op = op_tab[(int)tmp->opcode];
		loop_check_lbl(all, tmp, op.argc, 0);
		tmp = tmp->next;
	}
}
