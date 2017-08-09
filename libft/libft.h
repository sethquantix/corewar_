/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <cchaumar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 18:14:30 by cchaumar          #+#    #+#             */
/*   Updated: 2017/07/13 07:15:19 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include "generics/includes/ft_generics.h"
# include "bmp/includes/bmp.h"
# include "parser/includes/ft_parser.h"
# include "math/includes/math3d.h"
# include "opencl/includes/ft_opencl.h"
# include "graphics.h"

int		ft_printf(const char *format, ...);
int		ft_dprintf(int fd, const char *format, ...);
int		ft_vaprintf(const char *format, va_list args);
int		ft_vasprintf(char **buff, const char *format, va_list args);
int		ft_vadprintf(int fd, const char *format, va_list args);
int		ft_sprintf(char **buff, const char *format, ...);

#endif
