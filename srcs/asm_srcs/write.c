/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnagy <lnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 14:00:52 by lnagy             #+#    #+#             */
/*   Updated: 2017/03/20 14:00:53 by lnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char		*output_file(char *path)
{
	char	*t;

	t = ft_strrchr(path, '/');
	t = ft_strrchr(t ? t + 1 : path, '.');
	t = ft_strsub(path, 0, t ? t - path : ft_strlen(path));
	return (ft_strjoinfree(t, ".cor", 1));
}

static char		*local(char **path)
{
	char	*p;

	p = ft_strrchr(*path, '/');
	p = p ? p + 1 : *path;
	p = ft_strsub(*path, p - *path, ft_strlen(p));
	free(*path);
	return (*path = p);
}

void			write_file_header(t_file *file)
{
	char			*o;

	file->head.prog_size = ft_endian_int(file->addr);
	o = output_file(file->name);
	if ((file->fd = open(o, OPEN_FLAGS, 0644)) == -1)
	{
		if ((file->fd = open(local(&o), OPEN_FLAGS, 0644)) == -1)
			die(EXIT_FAILURE,
				"%sFailure%s : Can't open %s for writing\n",
				COLOR_RED, COLOR_END, o);
		ft_printf("%sWarning%s : Could not write to inital directory",
			COLOR_WARN, COLOR_END);
		ft_printf(", output to working directory instead\n");
	}
	ft_printf("Writing output to %s\n", o);
	free(o);
	write(file->fd, &file->head, sizeof(t_header));
}
