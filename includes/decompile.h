/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decompile.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 03:34:06 by tsedigi           #+#    #+#             */
/*   Updated: 2017/06/26 03:34:07 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DECOMPILE_H
# define DECOMPILE_H

# include "op.h"

# define PROC_CODE(o, i)	((o >> (2 * (3 - i))) & 3)
# define PROC_TYPE(o)		(1 << (o - 1))


typedef struct 	s_dec_op
{
	char			opcode;
	char 			octal;
	int				addr;
	int				param_size[MAX_ARGS_NUMBER];
	int				param_type[MAX_ARGS_NUMBER];
	int				param_value[MAX_ARGS_NUMBER];
	struct s_dec_op	*next;
}				t_dec_op;

typedef struct 	s_deco
{
	header_t	head;
	int			fd;
	t_dec_op	*lst;
}				t_deco;

#endif