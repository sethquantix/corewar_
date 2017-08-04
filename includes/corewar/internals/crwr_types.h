/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crwr_types.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 12:40:33 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/06 12:40:34 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CRWR_TYPES_H
# define CRWR_TYPES_H
# include "includes.h"

struct s_champ;
struct s_proc;
struct s_arena;

typedef int				(*t_f_get)(struct s_proc *, uint8_t[]);
typedef int				(*t_f_fill)(struct s_proc *, uint8_t[]);
typedef void			(*t_f_filter)(struct s_arena *);
typedef struct s_proc	*(*t_f_add)(struct s_arena *, void *, int);

#endif
