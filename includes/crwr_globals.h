/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crwr_globals.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 18:04:26 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/07 18:04:30 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CRWR_GLOBALS_H
# define CRWR_GLOBALS_H

#include "includes.h"

extern void		(*instructions[])(t_proc *, uint8_t []);
extern t_token	g_crwr_opts[];


#endif
