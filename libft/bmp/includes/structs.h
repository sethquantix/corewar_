/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 04:16:12 by cchaumar          #+#    #+#             */
/*   Updated: 2017/02/01 04:16:13 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/*
**	header should contain bmp markers, though it destroys structure alignment
** i will then get them manually beforehand
*/

typedef struct		s_header_bmp
{
	unsigned int	bf_size;
	short			unused1;
	short			unused2;
	unsigned int	image_data_offset;
	unsigned int	bi_size;
	int				width;
	int				height;
	short			planes;
	short			bit_pix;
	unsigned int	bi_compression;
	unsigned int	size;
	int				bi_xpels_per_meter;
	int				bi_ypels_per_meter;
	unsigned int	bi_clrused;
	unsigned int	bi_clr_important;
}					t_header_bmp;

#endif
