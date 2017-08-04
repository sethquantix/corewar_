/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr_find.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 11:03:54 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/04 11:04:15 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_generics.h"

t_ft_arr	ft_array(void *t, size_t size, int n)
{
	return ((t_ft_arr){t, size, n});
}

void		*ft_arr_find(t_ft_arr t, void *ref, int (*f)(void *r, void *c))
{
	int		i;
	void	*p;

	i = 0;
	p = t.t;
	while (i < t.n)
	{
		if (f(ref, p))
			return (p);
		p += t.size;
		i++;
	}
	return (NULL);
}
