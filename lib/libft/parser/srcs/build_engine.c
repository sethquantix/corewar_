/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_engine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 11:49:03 by cchaumar          #+#    #+#             */
/*   Updated: 2017/06/27 01:49:22 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "build.h"

static void		build_opts_paths(t_parser *p, t_rule **opts)
{
	int		i;

	i = 0;
	while (opts[i])
	{
		if (opts[i]->tok && ++i)
			continue;
		if (opts[i]->path && ++i)
			continue;
		build_rule_path(p, opts[i++]);
	}
}

static t_path	*new_path(t_rule *rule, t_rule **opts)
{
	t_path	*path;

	path = try(sizeof(t_path));
	path->rule = rule;
	path->options = opts;
	return (path);
}

static void		build_path(t_parser *p, t_path *path, t_rule **seq)
{
	if (!seq)
	{
		if ((seq = parser_build_nodes(p, path->rule->rule, NULL)) != NULL)
		{
			path->next = new_path(seq[0], 0);
			build_rule_path(p, seq[0]);
			build_path(p, path->next, seq + 1);
			free(seq);
		}
	}
	else if (seq && seq[0])
	{
		path->next = new_path(seq[0], 0);
		build_rule_path(p, seq[0]);
		build_path(p, path->next, seq + 1);
	}
	else
		build_rule_path(p, path->rule);
}

static void		build_rule_path(t_parser *p, t_rule *rule)
{
	t_rule	**seq;

	if (rule->tok)
		return ;
	if (rule->path)
		return ;
	if ((seq = parser_build_nodes(p, rule->rule, NULL)))
	{
		rule->path = new_path(seq[0], 0);
		build_rule_path(p, seq[0]);
		build_path(p, rule->path, seq + 1);
		free(seq);
	}
	else
	{
		rule->path = new_path(rule, parser_get_opts(p, rule->rule, 0));
		if (rule->path->options)
			build_opts_paths(p, rule->path->options);
	}
}

void			parser_build(t_parser *p)
{
	int		i;

	i = 0;
	while (i < p->n_rules)
		build_rule_path(p, p->rules[i++]);
}
