/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/08 03:37:01 by cchaumar          #+#    #+#             */
/*   Updated: 2017/08/08 03:52:03 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		get_size(char *file)
{
	int			fd;
	char		line[65537];
	int			len;
	int			sz;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (-2);
	bzero(line, sizeof(line));
	sz = 0;
	while ((len = read(fd, line, 65536)) > 0)
	{
		sz += len;
		if (sz > MAX_SIZE)
			return (-1);
	}
	close(fd);
	return (sz);
}

char			*getfile(char *file)
{
	int			fd;
	int			len;
	char		*source;

	if ((len = get_size(file)) == -2)
		return (NULL);
	if (len == -1)
		return ((void *)-1);
	if ((fd = open(file, O_RDONLY)) == -1)
		return (NULL);
	source = try(len + 1);
	if (read(fd, source, len) != len)
		return (NULL);
	close(fd);
	return (source);
}


