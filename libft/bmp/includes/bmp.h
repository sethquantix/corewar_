/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 04:16:08 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/11 16:51:32 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_H
# define BMP_H

# include "../../libft.h"
# include "fcntl.h"
# include "structs.h"

# define HEAD_SIZE	(sizeof(t_header_bmp) + 2)

void	load_bmp(char *name, unsigned int **buffer, t_header_bmp *head);
void	write_bmp(char *name, void *data, size_t w, size_t h);

#endif
