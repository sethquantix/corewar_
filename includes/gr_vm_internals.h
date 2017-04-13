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
#include "gr_types.h"

# define SDL_POS	SDL_WINDOWPOS_UNDEFINED
# define SDL_FLAGS	SDL_WINDOW_OPENGL

t_handler	get_handler(int type);
void		glerror(int i);

void		quit_press(void *data, t_gr_vm *vm, t_key *key);

/* unused for now. I may be coming back to 3D arena, but that would just be
**	for kicks. And because I can
*/

void		render_opengl(t_gr_vm *cxt, t_arena arena);
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

void		cam_rot_forwad(void *data, t_gr_vm *vm, t_key *key);
void		cam_rot_back(void *data, t_gr_vm *vm, t_key *key);
void		cam_rot_right(void *data, t_gr_vm *vm, t_key *key);
void		cam_rot_left(void *data, t_gr_vm *vm, t_key *key);

GLuint		load_bmp_to_opengl(char *b);
GLuint		light_to_texture(float l[MEM_SIZE]);
void		load_light(uint32_t in[MEM_SIZE], float out[4 * MEM_SIZE], float models[][6], t_gr_vm *cxt);
void		load_bmp_to_42(char *b, uint32_t *out);
void		toggle_42(void *data, t_gr_vm *vm, t_key *key);

/*
**
*/


#endif
