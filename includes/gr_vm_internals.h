/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gr_vm_internals.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 12:31:51 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/06 12:31:52 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GR_VM_INTERNALS_H
# define GR_VM_INTERNALS_H

#include "includes.h"
#include "gr_structs.h"
#include "crwr_structs.h"
#include "gr_types.h"

# define SDL_POS	SDL_WINDOWPOS_UNDEFINED
# define SDL_FLAGS	SDL_WINDOW_OPENGL

# define TIME_TRAVEL    10.0f
# define ROT			0.5f
# define SPEED			1.0f
# define CPF_DELTA		1

t_handler	get_handler(int type);
void		glerror(int i);

void		quit_press(void *data, t_gr_vm *vm, t_key *key);

void		render_opengl(t_gr_vm *cxt, t_arena *arena);
GLuint		generate_cube(t_gr_vm *c);
GLuint		createGLBuffer(int w, int h, GLuint *color, GLuint *depth);
void		renderGLBuffer(GLuint buffer, GLuint color, int w, int h);
void		readColor(GLuint buffer, int w, int h, void *p);

void		load_projection(float *out, float near, float far, float aspect);
void		load_identity(float *m);


void		cam_trans_forwad(void *data, t_gr_vm *vm, t_key *key);
void		cam_trans_back(void *data, t_gr_vm *vm, t_key *key);
void		cam_trans_right(void *data, t_gr_vm *vm, t_key *key);
void		cam_trans_left(void *data, t_gr_vm *vm, t_key *key);
void		cam_trans_up(void *data, t_gr_vm *vm, t_key *key);
void		cam_trans_down(void *data, t_gr_vm *vm, t_key *key);

void 		speed(void *data, t_gr_vm *vm, t_key *key);

void		rotate(t_gr_vm *vm, int relx, int rely);

GLuint		load_bmp_to_opengl(char *b);
GLuint		light_to_texture(float l[MEM_SIZE]);
void		load_light(uint32_t in[MEM_SIZE], float out[4 * MEM_SIZE], float models[][9], t_gr_vm *cxt);
void		load_bmp_to_42(char *b, uint32_t *out);
void		toggle_42(void *data, t_gr_vm *vm, t_key *key);
GLuint		gen_texture(const char *font_file);

#endif
