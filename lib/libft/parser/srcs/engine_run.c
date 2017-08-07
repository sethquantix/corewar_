/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_run.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 12:52:54 by cchaumar          #+#    #+#             */
/*   Updated: 2017/08/07 10:37:33 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_marching.h"

static t_path	*rule_path(t_rule **rules, char *s)
{
	while (*rules)
	{
		if (ft_strcmp((*rules)->name, s) == 0)
			return ((*rules)->path);
		else
			rules++;
	}
	return (NULL);
}

char			*run_parser(t_parser *parser, char *file, char *rule,
	t_expr **start)
{
	char	*s;
	char	*p;
	t_path	*path;

	*start = NULL;
	ft_lstdel(&parser->err, ft_del);
	ft_lstdel(&parser->stack, ft_del);
	parser->err = NULL;
	parser->stack = NULL;
	path = rule_path(parser->rules, rule);
	path = path ? path : parser->path;
	if ((s = file) == NULL)
		return (0);
	while (*s)
	{
		p = s;
		if (march_path(path, &s, start, parser) || (s == p))
			break ;
		ft_lstdel(&parser->stack, ft_del);
		ft_lstdel(&parser->err, ft_del);
	}
	ft_lstdel(&parser->stack, ft_del);
	if (!*s)
		ft_lstdel(&parser->err, ft_del);
	return (*s ? s : 0);
}
