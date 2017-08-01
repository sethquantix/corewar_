/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_endian_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 04:17:06 by cchaumar          #+#    #+#             */
/*   Updated: 2017/01/25 04:17:08 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_generics.h"

unsigned int		ft_endian_int(unsigned int x)
{
	unsigned int	o;
	unsigned int	i;

	o = 0;
	i = 0;
	while (i < 4)
	{
		o += ((x & (0xff << (8 * i))) >> (8 * i)) << (24 - 8 * i);
		i++;
	}
	return (o);
}
