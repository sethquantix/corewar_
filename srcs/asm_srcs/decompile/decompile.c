/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decompile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 10:52:30 by tsedigi           #+#    #+#             */
/*   Updated: 2017/06/18 10:52:33 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "decompile.h"

static void		print_file(char *src, t_deco *all)
{
	char		*path;
	char		*chr;

	path = ft_strnew(ft_strlen(src));
	chr = ft_strchr(src, '.');
	chr[0] = 0;
	ft_strcat(path, src);
	ft_strcat(path, ".dec");
	chr[0] = '.';
	all->fd ? close(all->fd) : 0;
	all->fd = open(path, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (all->fd == -1)
		die(EXIT_FAILURE, "Cannot open/create file");
	write_head(all);
	set_check_lbl(all);
	write_ops(all);
	close(all->fd);
	del_all_op(all->lst);
}

void			decompile(char *src)
{
	t_deco		all;
	size_t		iter;
	char		file[CHAMP_MAX_SIZE + 1];

	ft_bzero((void *)&all, sizeof(t_deco));
	if ((all.fd = err_param(src)) == -1)
		return ;
	if (read(all.fd, &all.head, sizeof(t_header)) == -1)
		die(EXIT_FAILURE, "Read failed");
	ft_bzero(file, CHAMP_MAX_SIZE + 1);
	if (invalid_header(&all.head))
		return ;
	if (read(all.fd, file, CHAMP_MAX_SIZE) == -1)
		die(EXIT_FAILURE, "Invalid champ");
	iter = 0;
	while (file[iter])
		iter += check_op(&file[iter], &all, iter);
	print_file(src, &all);
	ft_bzero((void **)&all, sizeof(t_deco));
}
