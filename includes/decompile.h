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

typedef struct		s_dec_op
{
	char			opcode;
	char			octal;
	int				addr;
	int				lbl;
	int				param_lbl[MAX_ARGS_NUMBER];
	int				param_size[MAX_ARGS_NUMBER];
	int				param_type[MAX_ARGS_NUMBER];
	int				param_value[MAX_ARGS_NUMBER];
	struct s_dec_op	*next;
}					t_dec_op;

typedef struct		s_deco
{
	header_t		head;
	int				fd;
	int				lbl;
	t_dec_op		*lst;
}					t_deco;

void				decompile(char *src);
int					err_param(char *src);
int					invalid_header(header_t *head);
int					check_op(char *file, t_deco *all, int iter);
int					set_param_no_octal(char *file, t_dec_op *node);
int					set_param_with_octal(char *file, t_dec_op *node);
void				set_check_lbl(t_deco *all);
void				add_deco_op(t_deco *all, t_dec_op *node);
void				write_head(t_deco *all);
void				write_ops(t_deco *all);
void				del_all_op(t_dec_op *lst);

#endif
