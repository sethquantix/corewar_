/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 11:43:39 by cchaumar          #+#    #+#             */
/*   Updated: 2017/06/27 03:01:32 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PARSER_H
# define FT_PARSER_H
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include "../../libft.h"

# define TOKEN_TYPE_ONE		0
# define TOKEN_TYPE_EXP		1
# define TOKEN_TYPE_STR		2
# define TOKEN_TYPE_FNC		3

# define PARSER_RESET		(void *)-1

struct s_path;

typedef struct	s_token
{
	char		*name;
	int			(*f)(char **);
	char		*specifiers;
	int			type;
}				t_token;

typedef struct	s_rule
{
	char			*name;
	char			*rule;
	int				processed;
	int				repeat;
	t_token			*tok;
	struct s_path	*path;
}				t_rule;

typedef struct	s_expr
{
	char			*pos;
	char			*rule;
	char			*expr;
	struct s_expr	*next;
	struct s_expr	*prev;
}				t_expr;

typedef struct	s_tok
{
	t_rule			*rule;
	char			*pos;
}				t_tok;

typedef struct	s_parser
{
	t_token			*tokens;
	t_rule			**rules;
	struct s_path	*path;
	char			**list;
	t_list			*err;
	t_list			*stack;
	int				n_rules;
	void			(*destroy)(struct s_parser *);
}				t_parser;

t_parser		*parse_engine(char *rules_file, t_token *toks, char **list);
char			*run_parser(t_parser *parser, char *source,
	char *rule, t_expr **start);
void			parser_clear_expr(t_expr **expr);
void			destroy_engine(t_parser *p);
void			parser_get_pos(char *pos, char *s, int *l, int *c);
char			*parser_getl(char *s);

#endif
