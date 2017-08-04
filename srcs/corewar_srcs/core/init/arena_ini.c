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

<<<<<<< HEAD:srcs/corewar_srcs/arena_ini.c
int		load_champ(t_arena *a, t_champ *c)
{
	int		fd;
	size_t	len;
	t_proc	*p;
	int		pc;

	if ((fd = open(c->file_name, O_RDONLY)) == -1)
		return (-1);
	if (read(fd, &c->head, sizeof(header_t)) != sizeof(header_t))
		return (err(3, c->file_name));
	ft_endian(&c->head.prog_size, 4);
	ft_endian(&c->head.magic, 4);
	ft_printf("* Player %d, %s (%d bytes) : %s\n", c->num, c->head.prog_name,
		c->head.prog_size, c->head.prog_desc);
	if (c->head.magic != COREWAR_EXEC_MAGIC)
		return (err(4, c->file_name));
	c->source = try(c->head.prog_size);
	if ((len = read(fd, c->source, c->head.prog_size)) != c->head.prog_size)
		return (err(5, c->file_name, len));
	close(fd);
	pc = (-c->id - 1) * (MEM_SIZE / a->champ_count);
	ft_memcpy(a->arena + (p = a->add_proc(a, c, pc))->pc, c->source, len);
	set_mem(a->mem, p->pc, len, p->player);
	SET_PLAYER(a->mem[p->pc], p->player);
	return (0);
}

=======
>>>>>>> 378561dd66dc5ff65f2a4e739cce3748d7e2ccb1:srcs/corewar_srcs/core/init/arena_ini.c
t_proc	*add_proc(t_arena *a, t_champ *c, int pc)
{
	t_proc	*proc;

	proc = try(sizeof(t_proc));
	proc->pc = pc;
	proc->id = ++a->proc_id;
	proc->get_inst = proc_read_inst;
	proc->get_params = proc_read_params;
	proc->reg[1] = (uint32_t)c->id;
	proc->arena = a;
	proc->op = NULL;
	proc->player = -c->id - 1;
	ft_pushback((void **)&a->procs, sizeof(t_proc *), a->proc_count++, &proc);
	a->alive++;
	return (proc);
}

t_proc	*fork_proc(t_arena *a, t_proc *p, int pc)
{
	t_proc	*proc;

	proc = try(sizeof(t_proc));
	proc->pc = pc;
	proc->id = ++a->proc_id;
	proc->oct = 0;
	proc->get_inst = proc_read_inst;
	proc->get_params = proc_read_params;
	memcpy(proc->reg, p->reg, sizeof(p->reg));
	proc->arena = a;
	proc->op = NULL;
	proc->cycles_left = 0;
	proc->last_live = p->last_live;
	proc->carry = p->carry;
	proc->player = p->player;
	ft_pushback((void **)&a->procs, sizeof(t_proc *), a->proc_count++, &proc);
	a->alive++;
	return (proc);
}

void	load_code(t_arena *a, t_champ *c)
{
<<<<<<< HEAD:srcs/corewar_srcs/arena_ini.c
	int		i;
	t_champ	*c;

=======
	int		pc;
	t_proc	*p;

	pc = (-c->id - 1) * (MEM_SIZE / a->champ_count);
	p = add_proc(a, c, pc);
	ft_memcpy(a->arena + p->pc, c->source, c->head.prog_size);
	set_mem(a->mem, p->pc, c->head.prog_size, p->player);
	SET_PLAYER(a->mem[p->pc], p->player);
}

void	init(t_arena *arena)
{
	int 		num;
	int 		i;

	arena->check = check_process;
	arena->add_proc = (t_f_add)add_proc;
	arena->ctd = CYCLE_TO_DIE;
>>>>>>> 378561dd66dc5ff65f2a4e739cce3748d7e2ccb1:srcs/corewar_srcs/core/init/arena_ini.c
	i = 0;
	num = 1;
	while (i < arena->champ_count)
	{
		if (!arena->champs[i].set)
		{
			while (check_set(arena->champs, arena->champ_count, num)) {
				ft_printf("%s => %d\n", arena->champs[i].head.prog_name, num);
				num++;
			}
			arena->champs[i].num = num++;
		}
		load_code(arena, arena->champs + i);
		i++;
	}
}
