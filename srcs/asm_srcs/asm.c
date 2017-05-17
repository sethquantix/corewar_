/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnagy <lnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 16:41:01 by lnagy             #+#    #+#             */
/*   Updated: 2017/03/05 16:41:03 by lnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	main(int ac, char **av)
{
	t_expr	*expr;
	t_env	e;

	if (ac == 1)
	return (usage(av[0]));
	ft_bzero(&e, sizeof(t_env));
	expr = parse_opts(av + 1);
	t_expr *ex = expr;
	for (; ex; ex = ex->next)
		ft_printf("(%s)->%s\n", ex->rule, ex->expr);
	read_opts(&e, expr);
	parser_clear_expr(&expr);
	if ((e.opts & OPT_X) == 0)
		compile(&e);
	return (ac - ac);
}
