/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 03:51:31 by cchaumar          #+#    #+#             */
/*   Updated: 2017/06/27 02:45:12 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "ft_parser.h"

struct s_path;

typedef struct	s_path
{
	t_rule			*rule;
	t_rule			**options;
	int				repeat;
	struct s_path	*next;
}				t_path;

t_expr			*end_expr(t_expr *e);

void			parser_die(char *s, int exit_code);

void			parser_build(t_parser *p);

t_rule			*parser_new_rule(t_parser *p, char *name, char *rule,
	int repeat);
t_rule			**parser_build_nodes(t_parser *p, char *s, t_rule **seq);
t_rule			**parser_get_opts(t_parser *p, char *s, int i);
void			parser_format_rule(char *str, char **rule, int *repeat);

void			parser_print_rule(t_rule *rule);
void			parser_print_path(t_path *path);

void			parser_add_expr(t_expr **expr, char *pos);
int				parser_tab_find(char **list, char *str);
int				parser_check_tok(t_token *tok, char **s);

void			parser_destroy_path(t_path *path);

#endif
