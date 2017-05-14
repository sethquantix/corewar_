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

int		loop(void *d)
{
	(void)d;
	return (1);
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

int		main(int ac, char **av)
{
	t_arena		arena;
	t_expr		*expr;
	t_gr_vm		context;

	expr = parse_opts(av + 1);

	read_args(expr, &arena);
	init(&arena);
//	gr_vm_init(&context);
//	gr_vm_run(loop, &arena, &context);
//	gr_vm_end(&context);
	return (0);
}
