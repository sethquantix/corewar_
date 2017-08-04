/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dec_err_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 08:14:15 by tsedigi           #+#    #+#             */
/*   Updated: 2017/06/28 08:14:16 by tsedigi          ###   ########.fr       */
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

int	invalid_header(header_t *head)
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
