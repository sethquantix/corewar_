/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gr_vm_internals.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 12:31:51 by cchaumar          #+#    #+#             */
/*   Updated: 2017/08/01 08:11:30 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GR_VM_INTERNALS_H
# define GR_VM_INTERNALS_H

# include <includes.h>
# include <../internals/crwr_structs.h>
# include "gr_structs.h"
# include "gr_types.h"

# define SDL_FLAGS	SDL_WINDOW_OPENGL

# define OPT_VALUES		0x1
# define OPT_ROTATION	0x2
# define OPT_LOWRES		0x4
# define OPT_PROC_HIGH	0x8

# define TIME_TRAVEL    10.0f
# define ROT			0.2f
# define SPEED			0.5f
# define CPF_DELTA		1

t_handler	get_handler(int type);

void		set_keys(t_key **keys, int *nkeys);
void		quit_press(void *data, t_gr_vm *vm, t_key *key);

void		render_opengl(t_gr_vm *cxt, t_arena *arena);
GLuint		generate_cube(t_gr_vm *c);

void		load_projection(float *out, float near, float far, float aspect);
void		load_identity(float *m);

void		cam_trans_forwad(void *data, t_gr_vm *vm, t_key *key);
void		cam_trans_back(void *data, t_gr_vm *vm, t_key *key);
void		cam_trans_right(void *data, t_gr_vm *vm, t_key *key);
void		cam_trans_left(void *data, t_gr_vm *vm, t_key *key);
void		cam_trans_up(void *data, t_gr_vm *vm, t_key *key);
void		cam_trans_down(void *data, t_gr_vm *vm, t_key *key);

void		speed(void *data, t_gr_vm *vm, t_key *key);
void		toggle_opt(void *data, t_gr_vm *vm, t_key *key);
void		rotate(t_gr_vm *vm, int relx, int rely);
void		select_proc(void *data, t_gr_vm *vm, t_key *key);

GLuint		gen_texture(const char *font_file);
void		init_text_p(t_text_p *sst);
void		init_gl(t_gr_vm *cxt, t_cam *cam);
void		init_pos(t_gr_vm *cxt);
GLuint		init_values(void);
GLuint		init_transfer(void);
GLuint		init_instancing(void);

void		draw_ui(t_gr_vm *cxt, t_arena *arena);
void		push_board_uni(t_gr_vm *cxt);
void		push_uniform(t_gr_vm *cxt);

t_vec4		box(SDL_Rect pos);
SDL_Surface	*print_text(t_text_p *sst, t_styles style, const char *text, ...);
SDL_Rect	draw_text(SDL_Surface *dst, SDL_Surface *s, SDL_Rect pos, int al);
void		draw_base(t_gr_vm *cxt, t_arena *arena, SDL_Rect *pos,
	SDL_Surface *s);

void		clear_surfaces(SDL_Surface **buff);

#endif
