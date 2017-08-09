/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/19 06:54:51 by cchaumar          #+#    #+#             */
/*   Updated: 2017/07/19 07:54:26 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_generics.h"

char	*acol(int r, int g, int b)
{
	static char	buff[17] = "\033[38;5;";
	int			col;

	col = 16 + 36 * (r % 6) + 6 * (g % 6) + b;
	*((unsigned long *)buff + 1) = 0L;
	ft_itoa_buff(buff + 7, col);
	ft_strcat(buff, "m");
	return (buff);
}
