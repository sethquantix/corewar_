/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gr_structs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 12:30:05 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/06 12:30:06 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GR_STRUCTS_H
# define GR_STRUCTS_H

#include "includes.h"
#include "gr_types.h"

typedef struct	s_gr_vm
{
	SDL_Window		*arena;
	SDL_Window		*UI;
	SDL_GLContext	glcontext;
	GLuint			glbuffer;
	GLuint			glcolor;
	GLuint			gldepth;
	GLuint			program;
	GLuint			matVBO;
	GLuint			vao;
	GLuint			lightText;
	GLuint			diffuseTexture;
	GLfloat			model[MEM_SIZE][6];
	char			text42[4 * 64 * 64];
	t_mat			camera;
	void			*buffer;
	struct s_key	*keys;
	int				nkeys;
	int				run;
}				t_gr_vm;

typedef struct	s_key
{
	int			keycode;
	int			pressed;
	t_f_key		press;
	t_f_key		hold;
	int			x;
	int			y;
}				t_key;

typedef struct	s_event
{
	int			sdl_event_type;
	t_handler	handler;
}				t_event;

#endif
