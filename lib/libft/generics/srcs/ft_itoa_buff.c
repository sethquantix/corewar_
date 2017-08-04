/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_buff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/19 06:59:04 by cchaumar          #+#    #+#             */
/*   Updated: 2017/07/19 08:04:30 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_generics.h"

void	ft_itoa_buff(char *buff, int i)
{
	char	*n;

	n = ft_itoa(i);
	ft_strcpy(buff, n);
	ft_memdel((void **)&n);
}
