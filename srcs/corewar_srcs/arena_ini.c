/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_ini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 13:21:53 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/06 13:21:54 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		load_champ(t_champ *c)
{
	int		fd;

	if ((fd = open(c->file_name, O_RDONLY)) == -1)
		return (-1);
	if (read(fd, &c->head, sizeof(header_t)) != sizeof(header_t))
		return (err("Error : %s : File too small to be a champion.\n",
		c->file_name));
	if (c->head.magic != COREWAR_EXEC_MAGIC)
		return (err("Error : %s : This does not appear to be a champion.\n",
		c->file_name));
	close(fd);
	return (0);
}

void	add_proc(t_arena *a, t_champ *c)
{
	t_proc	*proc;
	
	proc = try(sizeof(t_proc));
	proc->pc = c->id * (MEM_SIZE / a->champ_count);
	proc->id = a->proc_id++;
	proc->oct = 0;
	proc->exec = proc_exec_inst;
	proc->get_inst = proc_read_inst;
	proc->get_params = proc_read_params;
	proc->reg[1] = c->num;
	proc->arena = a;
	proc->op = NULL;
	proc->last_live = 0;
	ft_lstadd_end(&a->procs, ft_lstnew(&proc, sizeof(t_proc *)));
}
