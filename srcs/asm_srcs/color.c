/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/04 07:22:38 by tsedigi           #+#    #+#             */
/*   Updated: 2017/08/04 07:22:39 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	setup_ito(int nb, char type, int *ito)
{
	static int	f[18] = {0, 0, 0, 1, 2, 1, 1, 2, 2, 0, 0, 0, 1, 2, 1, 1, 2, 2};
	static int	s[18] = {0, 1, 2, 0, 0, 1, 2, 1, 2, 0, 1, 2, 0, 0, 1, 2, 1, 2};

	if (type == 'r')
	{
		*ito += nb <= 9 ? 36 * 4 : 36 * 5;
		*ito += 6 * f[nb];
		*ito += s[nb];
	}
	else
	{
		if (type == 'g')
			*ito += nb <= 9 ? 6 * 4 : 6 * 5;
		else
			*ito += nb <= 9 ? 4 : 5;
		*ito += 36 * f[nb];
		*ito += type == 'g' ? s[nb] : 6 * s[nb];
	}
}

char		*get_color_(int nb, char type)
{
	char		*ret;
	char		*ato;
	int			ito;

	if (nb == 0 || nb > 18)
		return (NULL);
	ret = ft_strnew(15);
	ft_strcat(ret, "\033[38;5;");
	ito = 16;
	setup_ito(nb, type, &ito);
	ft_strcat(ret, ato = ft_itoa(ito));
	ft_strcat(ret, "m");
	ft_memdel((void **)&ato);
	return (ret);
}
