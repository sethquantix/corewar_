/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crwr_defines.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 13:22:48 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/06 13:22:48 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CRWR_DEFINES_H
# define CRWR_DEFINES_H
# include "includes.h"

# define CHAMP_FLAG_ID		0x01
# define PROC_ARG_T(o, i)	((o >> (2 * (3 - i))) & 3)
# define PROC_ARG(o, i)		(1 << (PROC_ARG_T(o, i) - 1))

# define MOD_MEM			0
# define MOD_IDX			1 

# define G_OPT				0x01
# define V_OPT				0x02
# define D_OPT				0x04
# define O_OPT				0x08
# define S_OPT				0x10

# define DUMP_OUT			0x20
# define DUMP_64			0x40

# define VAL(p, s)			(t_val){p, s}

#endif
