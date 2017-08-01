/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 13:29:31 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/06 13:29:33 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

header_t	empty_head(void)
{
	header_t	head;

	ft_bzero(&head, sizeof(header_t));
	return (head);
}

int		err(const char *format, ...)
{
	va_list	va;

	va_start(va, format);
	ft_vadprintf(2, format, va);
	va_end(va);
	return (-1);
}

void	die(int exit_status, const char *format, ...)
{
	va_list	va;

	va_start(va, format);
	ft_vadprintf(2, format, va);
	va_end(va);
	exit(exit_status);
} 

void	dump(uint8_t mem[], int mod)
{
	int		i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (!(i % mod))
			ft_printf(i ? "%#.4x : " : "0x%.4x : ", i);
		ft_printf("%x%x%s", mem[i] >> 4, mem[i] & 0xf, (i + 1) % mod ? " " :
			"\n");
		i++;
	}
}
