/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnagy <lnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 16:38:41 by lnagy             #+#    #+#             */
/*   Updated: 2017/08/01 04:04:27 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	update_mem(uint32_t *mem)
{
	int			i;
	uint32_t	o;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (mem[i] & 0xFFFF0000)
		{
			o = (mem[i] >> 16) - 1;
			mem[i] &= 0xFF;
			mem[i] |= o << 16;
		}
		i++;
	}
}

int		loop(t_arena *a)
{
	int			i;

	i = a->proc_count - 1;
	update_mem(a->mem);
	a->cycles++;
	if (a->verbose_lvl & V_LVL_CYCLES)
		ft_printf("It is now cycle %d\n", a->cycles);
	while (i >= 0)
		if (!a->procs[i]->dead)
			proc_exec_inst(a->procs[i--]);
		else
			--i;
	if (a->cycles >= a->last_check + a->ctd)
		a->check(a);
	if (a->dump_cycles && a->cycles % a->dump_cycles == 0)
	{
		if (!(a->opts & S_OPT) && !a->cycles)
			return (0);
		dump(a->arena, DUMP_64);
		if (a->opts & D_OPT)
			return (0);
	}
	return (a->alive != 0);
}

int		usage(char *s)
{
	ft_printf("Usage: %s [-d N -s N -v N | -g] [-a] [[-n N] <champ1.cor>]", s);
	ft_printf(" [...] \n");
	ft_printf(" -a               : Prints output from \"aff\"");
	ft_printf("(Default is to hide it)\n");
	ft_printf(" (--graphic) -g   : Graphical mode\n");
	ft_printf("############ TEXT OUTPUT MODE #################\n");
	ft_printf(" (--dump) -d N    : Dumps memory after N cycles then exits\n");
	ft_printf(" (--step) -s N    : Runs N cycles, dumps memory, pauses, then");
	ft_printf("repeats\n");
	ft_printf(" (--verbose) -v N : Verbosity levels, can be added\n");
	ft_printf("                    - 0  : Show only essentials\n");
	ft_printf("                    - 1  : Show lives\n");
	ft_printf("                    - 2  : Show cycles\n");
	ft_printf("                    - 4  : Show operations (Params are not ");
	ft_printf("litteral ...)\n");
	ft_printf("                    - 8  : Show deaths\n");
	ft_printf("                    - 16 : Show PC movements (except zjmp)\n");
	ft_printf("##############################################\n");
	return (0);
}

void	winner(t_arena *arena)
{
	int		i;
	int		w;

	i = 0;
	w = -1;
	while (i < arena->champ_count)
	{
		ft_printf("last live %d : %d\n", arena->champs[i].num,
			arena->champs[i].last_live);
		if (w == -1 || arena->champs[i].last_live > arena->champs[w].last_live)
			w = i;
		i++;
	}
	if (w != -1)
		ft_printf("\n%sContestant %d, \"%s\", has won !\n%s", acol(3, 2, 5),
			arena->champs[w].num, arena->champs[w].head.prog_name, COLOR_END);
}

int		main(int ac, char **av)
{
	t_arena		arena;
	t_expr		*expr;
	t_gr_vm		context;

	ft_bzero(&context, sizeof(t_gr_vm));
	if (ac == 1)
		return (usage(av[0]));
	ft_bzero(&arena, sizeof(t_arena));
	expr = parse_opts(av + 1);
	read_args(expr, &arena);
	init(&arena);
	if (!arena.champ_count)
		return(usage(av[0]));
	if (arena.opts & G_OPT)
	{
		gr_vm_init(&context);
		gr_vm_run((t_vm_loop)loop, &arena, &context);
		gr_vm_end(&context);
	}
	else
		while (loop(&arena))
			;
	if (arena.opts & A_OPT)
		ft_printf("aff buffer: %s\n", arena.aff);
	winner(&arena);
	return (0);
}
