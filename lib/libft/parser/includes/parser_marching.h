/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_marching.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 14:04:23 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/11 17:20:20 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_MARCHING_H
# define PARSER_MARCHING_H

# include "parser.h"

int		march_path(t_path *path, char **s, t_expr **expr, t_parser *p);
void	err_stack_push(t_parser *p, t_tok st, t_list **ps);
void	err_stack_pop(t_parser *p, t_list *ps, int r, t_list **s);
void	print_stak(t_list *stack);
void	stock_stack(t_list **st, t_list *o);

#endif
