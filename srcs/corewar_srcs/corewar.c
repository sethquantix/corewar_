/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnagy <lnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 16:38:41 by lnagy             #+#    #+#             */
/*   Updated: 2017/03/05 16:38:55 by lnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "corewar.h"

int		loop(t_arena *a)
{
	(void)a;
	return (1);
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
	ft_printf("                    - 4  : Show operations (Params are NOT");
	ft_printf("litteral ...)s\n");
	ft_printf("                    - 8  : Show deaths\n");
	ft_printf("                    - 16 : Show PC movements (except zjmp)\n");
	ft_printf("##############################################\n");
	return (0);
}

void	init(t_arena *arena)
{
	int 		num;
	int 		i;

	arena->load = load_champ;
	arena->check = check_process;
	arena->add_proc = (t_f_add)add_proc;
	i = 0;
	num = 0;
	while (i < arena->champ_count)
	{
		if (!arena->champs[i].set)
		{
			while (check_set(arena->champs, arena->champ_count, num))
				num++;
			arena->champs[i].num = num++;
		}
		i++;
	}
}

void	print_expr(t_expr *expr)
{
	while (expr)
	{
		ft_printf("(%s) %s\n", expr->rule, expr->expr);
		expr = expr->next;
	}
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
	set_champs(&arena);
	if (arena.opts & G_OPT)
	{
		gr_vm_init(&context);
		gr_vm_run((t_vm_loop)loop, &arena, &context);
		gr_vm_end(&context);
	}
	else
		while (loop(&arena))
			;
	return (0);
}
