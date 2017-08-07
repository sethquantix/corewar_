/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dec_err_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/07 10:37:45 by cchaumar          #+#    #+#             */
/*   Updated: 2017/08/07 10:37:47 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "decompile.h"

int	err_param(char *src)
{
	int			fd;
	char		*chr;

	if ((fd = open(src, O_RDONLY)) == -1)
	{
		ft_dprintf(STDERR_FILENO, "Unable to read file %s\n", src);
		return (fd);
	}
	if (!(chr = ft_strchr(src, '.')) || ft_strcmp(chr, ".cor"))
	{
		close(fd);
		ft_dprintf(STDERR_FILENO, "File must be a .cor \n");
		return (-1);
	}
	return (fd);
}

int	invalid_header(t_header *head)
{
	if (!head)
	{
		ft_dprintf(STDERR_FILENO, "Failed to read header \n");
		return (1);
	}
	ft_endian(&head->magic, 4);
	ft_endian(&head->prog_size, 4);
	if (head->magic != COREWAR_EXEC_MAGIC)
	{
		ft_dprintf(STDERR_FILENO, "Bad magic number\n");
		return (1);
	}
	return (0);
}
