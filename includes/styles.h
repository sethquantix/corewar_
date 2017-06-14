/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   styles.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 09:51:21 by cchaumar          #+#    #+#             */
/*   Updated: 2017/06/13 09:51:22 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STYLES_H
# define STYLES_H

# define X_MARGIN		0.01
# define Y_MARGIN		0.01

# define BOARD_HEIGHT	1800
# define BOARD_WIDTH	2560

typedef enum 	e_fontsize
{
	SF_SMALL = 40,
	SF_MEDIUM = 80,
	SF_LARGE = 160,
	SF_HUGE = 320
}				t_fontsize;

typedef enum    e_styles
{
	WHITE_SMALL,
	WHITE_MEDIUM,
	WHITE_HUGE,
	GREY_MEDIUM,
	P_1MEDIUM,
	P_2MEDIUM,
	P_3MEDIUM,
	P_4MEDIUM
}               t_styles;

typedef enum	e_align
{
	X_LEFT = 1,
	X_CENTER = 2,
	X_RIGHT = 4,
	Y_TOP = 8,
	Y_BOT = 16,
	Y_CENTER = 32
}				t_align;

#endif