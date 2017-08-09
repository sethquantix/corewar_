/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dprintf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/08 17:28:57 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/08 17:28:58 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int		ft_dprintf(int fd, const char *format, ...)
{
	va_list		args;
	int			ret;
	char		*buff;

	va_start(args, format);
	ret = ft_vasprintf(&buff, format, args);
	va_end(args);
	write(fd, buff, ret);
	free(buff);
	return (ret);
}

int		ft_vadprintf(int fd, const char *format, va_list va)
{
	va_list		args;
	int			ret;
	char		*buff;

	va_copy(args, va);
	ret = ft_vasprintf(&buff, format, args);
	va_end(args);
	write(fd, buff, ret);
	free(buff);
	return (ret);
}
