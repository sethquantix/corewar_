/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gr_types.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 12:33:09 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/06 12:33:10 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GR_TYPES_H
# define GR_TYPES_H

# include "includes.h"

struct s_key;
struct s_gr_vm;

typedef int		(*t_vm_loop)(void *);
typedef void	(*t_f_key)(void *, struct s_gr_vm *, struct s_key *);
typedef void	(*t_handler)(void *, struct s_gr_vm *, SDL_Event *);

#endif
