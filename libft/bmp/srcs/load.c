/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/07 10:42:36 by cchaumar          #+#    #+#             */
/*   Updated: 2017/08/07 10:42:37 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "bmp.h"

void	load_bmp(char *name, unsigned int **buffer, t_header_bmp *head)
{
	int				fd;
	int				i;
	char			marker[3];
	unsigned char	*off;

	if ((fd = open(name, O_RDONLY)) == -1)
		return ;
	read(fd, marker, 2);
	read(fd, head, sizeof(t_header_bmp));
	off = ft_memalloc(head->image_data_offset - HEAD_SIZE + 1);
	read(fd, off, head->image_data_offset - HEAD_SIZE);
	free(off);
	*buffer = ft_memalloc(head->size);
	i = 0;
	off = ((unsigned char *)(*buffer)) + head->size;
	while (i < head->height)
	{
		off -= 4 * head->width;
		read(fd, off, head->width * sizeof(int));
		i++;
	}
	close(fd);
}
