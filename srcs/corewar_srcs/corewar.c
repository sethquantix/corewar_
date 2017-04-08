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
	arena->load = load_champ;
	arena->check = check_process;
	arena->add_proc = (t_f_add)add_proc;
}

int		main(int ac, char **av)
{
	t_arena		arena;
	t_expr		*expr;
	t_gr_vm		context;
	(void)ac;
	(void)av;
	init(&arena);
	//expr = parse_opts(av + 1);
	//read_opts(&arena, expr);
	gr_vm_init(&context);
	gr_vm_run(loop, &arena, &context);
	gr_vm_end(&context);
	return (0);
}
