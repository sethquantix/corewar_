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

GLuint		createGLBuffer(int w, int h, GLuint *color, GLuint *depth);
void		renderGLBuffer(GLuint buffer, GLuint color, int w, int h);
void		readColor(GLuint buffer, int w, int h, void *p);

/*
**
*/


#endif