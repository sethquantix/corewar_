/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evals.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 03:54:29 by cchaumar          #+#    #+#             */
/*   Updated: 2017/06/27 01:49:32 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_token	*get_token(t_parser *p, char *rule)
{
	int		i;
	t_token	*tokens;

	tokens = p->tokens;
	i = 0;
	while (tokens[i].name)
		if (ft_strcmp(rule, tokens[i].name) == 0)
			return (&tokens[i]);
		else
			++i;
	return (NULL);
}

t_rule			*parser_new_rule(t_parser *p, char *name, char *rule,
	int repeat)
{
	t_rule			*t;
	int				i;

	i = 0;
	while (i < p->n_rules)
		if (ft_strcmp(p->rules[i]->name, rule) == 0)
			return (p->rules[i]);
		else
			++i;
	t = try(sizeof(t_rule));
	*t = (t_rule){ft_strdup(name), ft_strdup(rule), 0,
		repeat, get_token(p, rule), 0};
	ft_pushback((void **)&p->rules, sizeof(t_rule *), p->n_rules++, &t);
	return (p->rules[i]);
}
