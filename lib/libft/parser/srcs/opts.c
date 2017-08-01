/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opts.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 06:15:43 by cchaumar          #+#    #+#             */
/*   Updated: 2017/02/03 06:15:44 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*next_outer_delim(char *s, char delim)
{
	int		depth;

	if (!s || !*s)
		return (NULL);
	depth = 0;
	while (*s)
	{
		if (*s == delim && depth == 0)
			return (s);
		if (*s == '(')
			depth++;
		if (*s == ')' && depth)
			depth--;
		s++;
	}
	return (NULL);
}

static int	count_delims(char *s, char delim)
{
	int		n;
	char	*p;

	n = 0;
	while ((p = next_outer_delim(s, delim)))
	{
		s = p + 1;
		n++;
	}
	return (n);
}

t_rule		**parser_build_nodes(t_parser *parser, char *s, t_rule **path)
{
	char	*p;
	int		i;
	int		r;
	int		n;

	r = 0;
	n = count_delims(s, ',');
	if (n == 0)
		return (NULL);
	path = try(sizeof(t_rule *) * (n + 2));
	p = s;
	i = 0;
	while (i < n + 1)
	{
		s = next_outer_delim(p, ',');
		p = ft_strsub(p, 0, s ? s - p : ft_strlen(p));
		parser_format_rule(p, &p, &r);
		path[i] = parser_new_rule(parser, p, p, r);
		free(p);
		p = s + 1;
		i++;
	}
	return (path);
}

void		parser_format_rule(char *str, char **rule, int *repeat)
{
	char	*end;

	ft_trim(&str);
	if (next_outer_delim(str, '|'))
	{
		*rule = str;
		return ;
	}
	*repeat = *str == '+';
	*rule = ft_strdup(str + *repeat);
	free(str);
	str = *rule;
	end = *rule + ft_strlen(*rule);
	if (**rule == '(')
	{
		(*rule)++;
		while (end != *rule && *end != ')')
			end--;
	}
	*rule = ft_strsub(*rule, 0, end == *rule ?
		ft_strlen(*rule) : end - *rule);
	ft_trim(rule);
	free(str);
}

t_rule		**parser_get_opts(t_parser *parser, char *s, int i)
{
	t_rule	**opts;
	char	*p;
	int		n;
	int		r;

	p = s;
	n = count_delims(p, '|');
	opts = n ? try(sizeof(t_rule *) * (n + 2)) : NULL;
	if (n == 0)
		return (NULL);
	while (i < n + 1)
	{
		s = next_outer_delim(p, '|');
		p = ft_strsub(p, 0, s ? s - p : ft_strlen(p));
		parser_format_rule(p, &p, &r);
		opts[i] = parser_new_rule(parser, p, p, r);
		i++;
		free(p);
		p = s + 1;
	}
	return (opts);
}
