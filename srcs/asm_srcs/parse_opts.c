/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_opts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnagy <lnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:47:00 by lnagy             #+#    #+#             */
/*   Updated: 2017/03/08 14:47:03 by lnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char	*join_args(char **av)
{
	char	*s;

	s = NULL;
	while (*av)
	{
		s = ft_strjoinfree(s, ft_strjoin(*av, *(av + 1) ? " " : ""), 3);
		av++;
	}
	return (s);
}

void		parse_error(char *err)
{
	char	**t;

	if (err == NULL)
		return ;
	t = ft_strsplit(err, ' ');
	err = ft_strdup(*t);
	ft_deltab(t);
	if (*err == '-')
		die(EXIT_FAILURE, "error parsing %s : unsupported option\n", err);
}

t_expr		*parse_opts(char **av)
{
	t_expr		*expr;
	t_parser	*p;
	const char	*list[] = {"PATH", "OPTION_A", "OPTION_X", "OPTION_D", 0};
	char		*arg;
	char		*err;

	arg = join_args(av);
	expr = NULL;
	p = parse_engine("rules/asm_opts", g_asm_opts, (char **)list);
	err = run_parser(p, arg, "FORMAT", &expr);
	destroy_engine(p);
	parse_error(err);
	free(arg);
	return (expr);
}
