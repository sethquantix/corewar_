/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgan <jgan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/19 16:17:39 by jgan              #+#    #+#             */
/*   Updated: 2015/11/19 16:17:48 by jgan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_generics.h"

static int	base_toi(char c, const char *base)
{
	int		i;

	i = 0;
	while (base[i])
	{
		if (base[i] == c)
			return (i);
		++i;
	}
	return (-1);
}

int			ft_atoi_base(const char *str, const char *base)
{
	int		tot;
	int		sign;
	int		i;
	int		len;

	tot = 0;
	sign = 1;
	i = 0;
	len = ft_strlen(base);
	while (ft_iswhite(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		++i;
	}
	while (base_toi(str[i], base) != -1)
	{
		tot = tot * len + base_toi(str[i], base);
		++i;
	}
	return (tot * sign);
}
