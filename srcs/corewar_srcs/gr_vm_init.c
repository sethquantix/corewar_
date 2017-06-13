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
#include "../../libs/glhandler/includes/gl_handler.h"

int		add_key(t_key **keys, int keycode, t_f_key press, t_f_key hold)
{
	static int		n = 0;
	static t_key	**p = NULL;
	t_key	key;

	if (p != keys)
	{
		p = keys;
		n = 0;
	}
	key = (t_key){keycode, 0, press, hold, 0, 0};
	ft_pushback((void **)keys, sizeof(t_key), n++, &key);
	return (1);
}

void	set_keys(t_key **keys, int *nkeys)
{
	*nkeys += add_key(keys, SDLK_ESCAPE, quit_press, NULL);
	*nkeys += add_key(keys, SDLK_w, cam_trans_forwad, cam_trans_forwad);
	*nkeys += add_key(keys, SDLK_s, cam_trans_back, cam_trans_back);
	*nkeys += add_key(keys, SDLK_d, cam_trans_right, cam_trans_right);
	*nkeys += add_key(keys, SDLK_a, cam_trans_left, cam_trans_left);
	*nkeys += add_key(keys, SDLK_q, cam_trans_down, cam_trans_down);
	*nkeys += add_key(keys, SDLK_e, cam_trans_up, cam_trans_up);
	*nkeys += add_key(keys, SDLK_SLASH, toggle_mem, NULL);
	*nkeys += add_key(keys, SDLK_r, toggle_rot, NULL);
	*nkeys += add_key(keys, SDLK_KP_PLUS, speed, NULL);
	*nkeys += add_key(keys, SDLK_KP_MINUS, speed, NULL);
	*nkeys += add_key(keys, SDLK_r, 	toggle_42, NULL);
}

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

void 	init_gl(t_gr_vm *cxt, t_cam *cam)
{
	t_gl_shader shaders[2];
	t_gl_shader	shaders_box[2];

	glewInit();
	shaders[0].file = ft_strdup("./shaders/vertex.shader");
	shaders[0].type = GL_VERTEX_SHADER;
	shaders[1].file = ft_strdup("./shaders/frag.shader");
	shaders[1].type = GL_FRAGMENT_SHADER;
	shaders_box[0].file = ft_strdup("./shaders/vertex_box.shader");
	shaders_box[0].type = GL_VERTEX_SHADER;
	shaders_box[1].file = ft_strdup("./shaders/frag_box.shader");
	shaders_box[1].type = GL_FRAGMENT_SHADER;
	cxt->program = create_program(2, shaders);
	cxt->program_box = create_program(2, shaders_box);
	free(shaders[0].file);
	free(shaders[1].file);
	free(shaders_box[0].file);
	free(shaders_box[1].file);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0, 0, 0, 1);
	cam->pos = vec4(0, -10, -100, 0);
	mat_ident(&cam->m);
	cam->m.r[0].w = cam->pos.x;
	cam->m.r[1].w = cam->pos.y;
	cam->m.r[2].w = cam->pos.z;
	cam->x = 0;
	cam->y = 0;
	cxt->pixie = vec4(1.15, 0.4, 1.15, 0);
	cxt->pv = vec4(0, 0, 0, 0);
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

void	gr_vm_init(t_gr_vm *cxt, t_arena *arena)
{
	set_sdl_attributes();
	srand(time(NULL));
//    cxt->UI = SDL_CreateWindow("UI", 0, 0, WIN_WIDTH / 4, WIN_HEIGHT, 0);
	cxt->arena = SDL_CreateWindow("corewar", WIN_WIDTH / 4, 0,
		WIN_WIDTH - WIN_WIDTH / 4, WIN_HEIGHT, SDL_WINDOW_OPENGL);
//	cxt->arena = SDL_CreateWindow("corewar", 0, 0,
//		WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_OPENGL);
	SDL_SetWindowGrab(cxt->arena, SDL_TRUE);
    cxt->arena_context = SDL_GL_CreateContext(cxt->arena);
//    SDL_SetWindowGrab(cxt->UI, SDL_FALSE);
	SDL_GL_SetSwapInterval(1);
	cxt->run = 1;
	cxt->cpf = 0;
	set_keys(&cxt->keys, &cxt->nkeys);
	init_gl(cxt, &cxt->camera);
	load_noise(cxt);
	cxt->glyphs = gen_texture("assets/Prototype.ttf");
	cxt->vao = generate_cube(cxt);
	cxt->anim42 = 0;
//    set_ui(cxt, arena);
}
