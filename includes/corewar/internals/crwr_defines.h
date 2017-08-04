/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crwr_defines.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 13:22:48 by cchaumar          #+#    #+#             */
/*   Updated: 2017/08/01 08:36:17 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CRWR_DEFINES_H
# define CRWR_DEFINES_H
# include "includes.h"

# define COLOR_END			"\033[0m"

# define WARN				0x0
# define ERR				0x1

# define CHAMP_FLAG_ID		0x01
# define PROC_CODE(o, i)	((o >> (2 * (3 - i))) & 3)
# define PROC_TYPE(o)		(1 << (o - 1))

# define G_OPT				0x01
# define V_OPT				0x02
# define D_OPT				0x04
# define O_OPT				0x08
# define S_OPT				0x10
# define A_OPT				0x20

# define DUMP_OUT			0x20
# define DUMP_64			0x40

# define V_LVL_LIVES		0x01
# define V_LVL_CYCLES		0x02
# define V_LVL_OP			0x04
# define V_LVL_DEATH		0x08
# define V_LVL_PC			0x10

# define UNSET_PLAYER(x, p)	(x &= (0xFFFFFFFF & ~(1 << p)))
# define SET_PLAYER(x, p)	(x |= (1 << p))

# define RULES_PATH			"assets/rules/"
# define FONT_PATH			"assets/fonts/"
# define IMG_PATH			"assets/img/"
# define OPTS_RULES_PATH	"assets/rules/crwr_opts"

#endif
