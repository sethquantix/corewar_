/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 18:05:46 by cchaumar          #+#    #+#             */
/*   Updated: 2017/08/01 08:31:40 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			check_set(t_champ *champs, int count, int n)
{
	int		i;

	i = 0;
	while (i < count)
	{
		if (champs->set && champs->num == n)
			return (-1);
			i++;
	}
	return (0);
}

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
	const char	*list[] = {"OPTION_D", "OPTION_G", "OPTION_V", "OPTION_S",
		"OPTION_A", "PLAYER", "NUMBER", "VERBOSE", "PATH", 0};
	char		*arg;
	char		*err;

	arg = join_args(av);
	expr = NULL;
	p = parse_engine(OPTS_RULES_PATH, g_crwr_opts, (char **)list);
	err = run_parser(p, arg, "FORMAT", &expr);
	destroy_engine(p);
	parse_error(err);
	return (expr);
}
