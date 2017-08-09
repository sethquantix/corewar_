/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pushback.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 07:30:52 by cchaumar          #+#    #+#             */
/*   Updated: 2017/02/17 07:30:54 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_generics.h"

void	ft_pushback(void **data, size_t size, int count, void *o)
{
	unsigned char	*p;
	unsigned char	*u;

	p = try(size * (count + 1));
	u = (unsigned char *)*data;
	ft_memcpy(p, u, count * size);
	ft_memcpy(p + count * size, o, size);
	free(*data);
	*data = p;
}
