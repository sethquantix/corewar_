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

int	usage(void)
{
	ft_printf("Usage : ./asm [-x][-a] <source.s> ...\n");
	ft_printf("\t-a : instead of compiling the file, output stripped ");
	ft_printf("and annotated version of the code to the standard output\n");
	ft_printf("\t-x : decompile .cor file. Will try to mark labels if ");
	ft_printf("address parameters are relevant.\n");
	ft_printf("\tNote : [-a] and [-x] options are mutually exclusive.\n");
	return (0);
}

int	main(int ac, char **av)
{
	t_expr	*expr;
	t_env	e;

	ft_bzero(&e, sizeof(t_env));
	if (ac == 1)
		return (usage());
	expr = parse_opts(av + 1);
	read_opts(&e, expr);
	parser_clear_expr(&expr);
	if ((e.opts & OPT_X) == 0)
		compile(&e);
	return (ac - ac);
}
