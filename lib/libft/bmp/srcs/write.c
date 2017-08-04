/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 04:16:31 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/11 16:52:55 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmp.h"
#include "structs.h"

static void	write_data(int fd, unsigned int *data, size_t w, size_t h)
{
	size_t			i;
	size_t			j;
	unsigned int	c;

	j = 0;
	while (j < h)
	{
		i = 0;
		while (i < w)
		{
			c = data[(h - 1 - j) * w + i];
			c = (c >> 8) | (c << 24);
			write(fd, &c, 4);
			i++;
		}
		j++;
	}
}

void		write_bmp(char *name, void *data, size_t w, size_t h)
{
	t_header_bmp	head;
	unsigned char	offset[16];
	int				fd;

	ft_bzero(offset, 16);
	ft_bzero(&head, sizeof(t_header_bmp));
	head.width = w;
	head.height = h;
	head.size = w * h * sizeof(int);
	head.bit_pix = 8 * sizeof(int);
	head.bi_compression = 3;
	head.bi_size = 56;
	head.planes = 1;
	head.image_data_offset = 70;
	head.bf_size = head.image_data_offset + head.size;
	head.bi_xpels_per_meter = 2835;
	head.bi_ypels_per_meter = 2835;
	if ((fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0606)) == -1)
		return ;
	write(fd, "BM", 2);
	write(fd, &head, sizeof(t_header_bmp));
	write(fd, offset, 16);
	write_data(fd, (unsigned int *)data, w, h);
	close(fd);
}
