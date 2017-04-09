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

struct			s_champ;
struct			s_proc;
struct			s_arena;

typedef int				(*t_f_load)(struct s_arena *, struct s_champ *);
typedef int				(*t_f_get)(struct s_proc *, uint8_t []);
typedef int				(*t_f_fill)(struct s_proc *, uint8_t []);
typedef void			(*t_f_kill)(struct s_proc *);
typedef void			(*t_f_filter)(struct s_arena *);
typedef void			(*t_f_exec)(struct s_proc *);
typedef struct s_proc	*(*t_f_add)(struct s_arena *, void *, int);
typedef int				(*t_f_cmp)(void *, void *);

#endif
