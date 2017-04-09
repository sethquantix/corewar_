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

int		load_champ(t_arena *a, t_champ *c)
{
	int		fd;
	size_t	len;
	t_proc	*p;
	int		pc;

	if ((fd = open(c->file_name, O_RDONLY)) == -1)
		return (-1);
	if (read(fd, &c->head, sizeof(header_t)) != sizeof(header_t))
		return (err("Error : %s : File too small to be a champion.\n",
		c->file_name));
	ft_endian(&c->head.prog_size, 4);
	ft_endian(&c->head.magic, 4);
	ft_printf("* Player %d, %s (%d bytes) : %s\n", c->id, c->head.prog_name,
		c->head.prog_size, c->head.prog_desc);
	if (c->head.magic != COREWAR_EXEC_MAGIC)
		return (err("Error : %s : This does not appear to be a champion.\n",
		c->file_name));
	c->source = try(c->head.prog_size);
	if ((len = read(fd, c->source, c->head.prog_size)) != c->head.prog_size)
		return (err("Error : %s : Corrupted source (size doesn't match (%zu))\n",
		c->file_name, len));
	close(fd);
	pc = (c->id - 1) * (MEM_SIZE / a->champ_count);
	ft_memcpy(a->arena + (p = a->add_proc(a, c, pc))->pc, c->source, len);
	return (0);
}

int		check_set(t_champ *champs, int n, int num)
{
	int		i;

	i = 0;
	while (i < n)
		if (champs->set && champs->num == num)
			return (1);
		else
		{
			i++;
			champs++;
		}
	return (0);
}

t_proc	*add_proc(t_arena *a, t_champ *c, int pc)
{
	t_proc	*proc;
	
	proc = try(sizeof(t_proc));
	proc->pc = pc;
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
	return (proc);
}

void	set_champs(t_arena *a)
{
	int		i;
	t_champ	*c;
	
	i = 0;
	ft_printf("Introducing contestants :\n");
	c = a->champs;
	while (i < a->champ_count)
		if (a->load(a, c++))
			die("", EXIT_FAILURE);
		else
			i++;
}
