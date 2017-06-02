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

#define CENTER_NONE 0
#define CENTER_X    1
#define CENTER_Y    2

typedef enum 	e_faces
{
	F_DOWN,
	F_UP,
	F_LEFT,
	F_RIGHT,
	F_FRONT,
	F_BACK
}				t_faces;

typedef enum    e_styles
{
    WHITE_SMALL,
    BLUE_SMALL,
    BLUE_BIG,
    BLUE_BIG_CENTERED,
    WHITE_ITALIC_MEDIUM
}               t_styles;

typedef struct	s_cam
{
	t_vec4		pos;
	t_mat		m;
	int			x;
	int			y;
}				t_cam;

typedef struct s_style
{
    int         centered;
    SDL_Color   c;
    TTF_Font    *font;
}               t_style;

typedef struct  s_text_p
{
    SDL_Rect    pos;
    t_style     *styles;
    int         style;
    int         nstyle;
}               t_text_p;

typedef struct	s_gr_vm
{
	SDL_Window		*arena;
	SDL_Window		*UI;
    SDL_Surface     *ui_screen;
	SDL_GLContext	arena_context;
	GLuint			glbuffer;
	GLuint			glcolor;
	GLuint			gldepth;
	GLuint			program;
	GLuint			matVBO;
	GLuint			valVBO;
	GLuint 			faceVBO;
	GLuint			vao;
	GLuint			diffuseTexture;
	GLfloat			model[MEM_SIZE][9];
    float           scale[MEM_SIZE];
	int				anim42;
	char			text42[4 * 64 * 64];
	t_cam			camera;
	struct s_key	*keys;
	int				nkeys;
	int				run;
	int 			cpf;
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
