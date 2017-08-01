/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 13:56:59 by cchaumar          #+#    #+#             */
/*   Updated: 2017/02/05 13:56:59 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_BUILD_H
# define PARSER_BUILD_H

# include "parser.h"

static void	build_rule_path(t_parser *p, t_rule *rule);
static void	build_path(t_parser *p, t_path *path, t_rule **seq);

#endif
