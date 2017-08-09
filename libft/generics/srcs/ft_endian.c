/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_endian.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 06:47:26 by cchaumar          #+#    #+#             */
/*   Updated: 2017/01/25 06:47:28 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_generics.h"

void	ft_endian(void *p, int size)
{
	unsigned char	*o;
	unsigned char	*t;
	int				i;

	if (!(o = ft_memalloc(size)))
		return ;
	t = p;
	i = 0;
	while (i < size)
	{
		o[i] = t[size - i - 1];
		i++;
	}
	ft_memcpy(p, o, size);
	ft_memdel((void **)&o);
}
