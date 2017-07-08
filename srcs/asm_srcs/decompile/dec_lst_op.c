/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dec_lst_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 08:15:52 by tsedigi           #+#    #+#             */
/*   Updated: 2017/06/28 08:15:52 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "decompile.h"

void			add_deco_op(t_deco *all, t_dec_op *node)
{
	t_dec_op	*tmp;

	node->lbl = -1;
	if (all && !all->lst)
		all->lst = node;
	else if (all)
	{
		tmp = all->lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}

void			del_all_op(t_dec_op *lst)
{
	t_dec_op	*tmp;

	while (lst)
	{
		tmp = lst->next;
		ft_memdel((void **)&lst);
		lst = tmp;
	}
}
