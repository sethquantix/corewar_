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

t_val	val(void *p, uint8_t s)
{
	return ((t_val){p, s});
}

int		err(const char *format, ...)
{
	va_list	va;

	va_start(va, format);
	ft_vadprintf(2, format, va);
	return (-1);
}

void	die(const char *format, int exit_status, ...)
{
	va_list	va;

	va_start(va, exit_status);
	ft_vadprintf(2, format, va);
	exit(exit_status);
} 
