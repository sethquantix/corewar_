/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 17:36:39 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/07 17:36:42 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	proc_should_die(void *unused, t_proc *proc)
{
	(void)unused;
	return (proc->die != 0);
}

static void	check(t_proc *p, int last)
{
	if (p->last_live < last)
		p->die = 1;
}

void		check_process(t_arena *a)
{
	t_list	*p;
	int		die;

	die = 1;
	p = a->procs;
	while (p)
	{
		check(p->content, a->last_check);
		p = p->next;
	}
	ft_lst_remove_if(&a->procs, 0, (t_f_cmp)proc_should_die, ft_dummy);
}

int 		cmp_id(uint32_t	*ref, t_champ *data)
{
	return (*ref == data->id);
}
