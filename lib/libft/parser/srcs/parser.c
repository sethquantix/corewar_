/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 03:42:32 by cchaumar          #+#    #+#             */
/*   Updated: 2017/08/01 08:26:22 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	nline(char *name)
{
	int		fd;
	char	*line;
	int		n;

	line = NULL;
	if ((fd = open(name, O_RDONLY)) == -1)
		parser_die("Can't open rules", EXIT_FAILURE);
	n = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] != '#')
			n++;
		free(line);
	}
	free(line);
	close(fd);
	return (n);
}

static void	parse_line(t_parser *parser, char *line)
{
	char	*s;
	char	**t;
	char	*p;
	int		r;

	t = ft_strsplit(line, '=');
	s = ft_strtrim(t[1]);
	p = ft_strsub(s, 1, ft_strlen(s) - 2);
	free(s);
	parser_format_rule(p, &p, &r);
	s = ft_strdup(t[0]);
	ft_trim(&s);
	parser_new_rule(parser, s, p, r);
	free(s);
	free(p);
	ft_deltab(t);
}

static void	get_rules(t_parser *e, char *rules_file)
{
	int		n;
	int		i;
	char	*line;

	line = NULL;
	n = nline(rules_file);
	e->rules = try((n + 1) * sizeof(t_rule));
	if ((n = open(rules_file, O_RDONLY)) == -1)
		parser_die("Can't read rules", O_RDONLY);
	i = 0;
	while (get_next_line(n, &line) > 0)
	{
		if (line[0] != '#')
			parse_line(e, line);
		free(line);
		i++;
	}
	free(line);
	close(n);
}

void		destroy_engine(t_parser *p)
{
	int		i;

	parser_destroy_path(p->path);
	i = 0;
	while (i < p->n_rules)
	{
		ft_memdel((void **)&p->rules[i]->name);
		ft_memdel((void **)&p->rules[i]->rule);
		parser_destroy_path(p->rules[i]->path);
		ft_memdel((void **)&p->rules[i]);
		i++;
	}
	ft_lstdel(&p->err, ft_del);
	ft_lstdel(&p->stack, ft_del);
	ft_memdel((void **)&p->rules);
	ft_memdel((void **)&p);
}

t_parser	*parse_engine(char *rules_file, t_token *tokens, char **list)
{
	t_parser	*p;

	p = try(sizeof(t_parser));
	p->list = list;
	p->tokens = tokens;
	p->destroy = destroy_engine;
	get_rules(p, rules_file);
	parser_build(p);
	return (p);
}
