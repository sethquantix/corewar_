/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gr_vm_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 08:17:11 by cchaumar          #+#    #+#             */
/*   Updated: 2017/03/19 08:17:11 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "gr_vm_internals.h"

void	set_sdl_attributes()
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
		SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 4);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 32);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_ShowCursor(SDL_DISABLE);
}

void	load_noise(t_gr_vm *cxt)
{
	glActiveTexture(GL_TEXTURE1);
	cxt->diffuseTexture = SOIL_load_OGL_texture("assets/noise.png",
		SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y |
		SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_MIPMAPS |
		SOIL_FLAG_COMPRESS_TO_DXT);
	if (cxt->diffuseTexture == -1)
		die(EXIT_FAILURE, "failed to load texture\n");
	glBindTexture(GL_TEXTURE_2D, cxt->diffuseTexture);
}

GLuint	gen_board_tex(void)
{
	GLuint 	id;

	glActiveTexture(GL_TEXTURE3);
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	return (id);
}

void	gr_vm_init(t_gr_vm *cxt, t_arena *arena)
{
	if (TTF_Init() == -1)
		exit(EXIT_FAILURE);
	srand(time(NULL));
	cxt->run = 1;
	cxt->cpf = 0;
	cxt->anim42 = 0;
	set_sdl_attributes();
	cxt->arena = SDL_CreateWindow("corewar", 0, 0,
		WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_OPENGL);
	SDL_SetWindowGrab(cxt->arena, SDL_TRUE);
	cxt->arena_context = SDL_GL_CreateContext(cxt->arena);
	SDL_GL_SetSwapInterval(1);
	set_keys(&cxt->keys, &cxt->nkeys);
	init_gl(cxt, &cxt->camera);
	load_noise(cxt);
	init_text_p(&cxt->sst);
	cxt->screen = SDL_CreateRGBSurface(0, BOARD_WIDTH, BOARD_HEIGHT, 32,
		0, 0, 0, 0);
	cxt->glyphs = gen_texture("assets/Prototype.ttf");
	cxt->vao = generate_cube(cxt);
	cxt->board = gen_board_tex();
}
