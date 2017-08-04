/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gr_structs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 12:30:05 by cchaumar          #+#    #+#             */
/*   Updated: 2017/08/04 08:47:00 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GR_STRUCTS_H
# define GR_STRUCTS_H

# include <includes.h>
# include "gr_types.h"
# include "styles.h"

# define PROC_ALL		-1
# define PROC_NONE		-2

# define PLAYER_NONE	-1

# define SELECT_PLAYER	0
# define SELECT_PROC	1
# define SELECT_REG		2

typedef enum		e_faces
{
	F_DOWN,
	F_UP,
	F_LEFT,
	F_RIGHT,
	F_FRONT,
	F_BACK
}					t_faces;

typedef struct		s_cam
{
	t_vec4			pos;
	t_mat			m;
	int				x;
	int				y;
}					t_cam;

typedef struct		s_pos
{
	SDL_Rect		p;
	SDL_Color		c;
}					t_pos;

typedef struct		s_style
{
	SDL_Color		c;
	TTF_Font		*font;
}					t_style;

typedef struct		s_text_p
{
	SDL_Rect		pos;
	t_style			*styles;
	int				style;
	int				nstyle;
}					t_text_p;

typedef struct		s_cursor
{
	int				player;
	int				proc;
	int				pos;
	int				reg;
	t_vec4			player_box;
	t_vec4			proc_box;
	t_vec4			reg_box;
}					t_cursor;

typedef struct		s_gr_vm
{
	SDL_Window		*arena;
	SDL_Window		*UI;
	SDL_Surface		*screen;
	SDL_GLContext	arena_context;
	GLuint			program;
	GLuint			program_board;
	GLuint			matVBO;
	GLuint			valVBO;
	GLuint			arenaVBO;
	GLuint			vao;
	GLuint			vao_board;
	GLuint			glyphs;
	GLuint			diffuseTexture;
	GLuint			board;
	GLfloat			model[MEM_SIZE][9];
	float			scale[MEM_SIZE];
	int				values[MEM_SIZE];
	int				anim42;
	char			text42[4 * 64 * 64];
	t_cam			camera;
	int				opts;
	struct s_key	*keys;
	t_cursor		cursor;
	int				nkeys;
	int				run;
	int				cps;
	int				time;
	t_text_p		sst;
}					t_gr_vm;

typedef struct		s_key
{
	int				keycode;
	int				pressed;
	t_f_key			press;
	t_f_key			hold;
	int				x;
	int				y;
}					t_key;

typedef struct		s_event
{
	int				sdl_event_type;
	t_handler		handler;
}					t_event;

#endif
