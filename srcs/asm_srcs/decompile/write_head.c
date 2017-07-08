/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_head.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 08:02:09 by tsedigi           #+#    #+#             */
/*   Updated: 2017/06/28 08:02:10 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decompile.h"
#include "asm.h"

void		write_head(t_deco *all)
{
	ft_dprintf(all->fd, ".name%11s%s%s\n", "\"", all->head.prog_name, "\"");
	ft_dprintf(all->fd, ".comment%8s%s%s\n", "\"", all->head.prog_desc, "\"");
	ft_dprintf(all->fd, "\n");
}
