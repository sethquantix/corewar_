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

void	*memory;

int	main(int ac, char **av)
{
	t_expr	*expr;
	t_env	e;
	int 	i;

	if (ac == 1)
	return (usage(av[0]));
	ft_bzero(&e, sizeof(t_env));
	expr = parse_opts(av + 1);
	read_opts(&e, expr);
	parser_clear_expr(&expr);
	if ((e.opts & OPT_X) == 0)
		compile(&e);
	i = 0;
	while (i < e.n_file)
		free(e.files[i++]);
	free(e.files);
	while (1)
		;
	return (0);
}
