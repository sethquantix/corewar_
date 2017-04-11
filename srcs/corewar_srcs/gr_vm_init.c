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

	*nkeys += add_key(keys, SDLK_UP, cam_rot_forwad, cam_rot_forwad);
	*nkeys += add_key(keys, SDLK_DOWN, cam_rot_back, cam_rot_back);
	*nkeys += add_key(keys, SDLK_RIGHT, cam_rot_right, cam_rot_right);
	*nkeys += add_key(keys, SDLK_LEFT, cam_rot_left, cam_rot_left);
}

void	gr_vm_init(t_gr_vm *cxt)
{
	t_gl_shader shaders[2];
	SDL_Init(SDL_INIT_VIDEO);

	cxt->arena = SDL_CreateWindow("corewar", WIN_WIDTH / 2, WIN_HEIGHT / 2, WIN_WIDTH,
		WIN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);
	cxt->UI = SDL_CreateWindow("UI", 0, 0, WIN_WIDTH / 2,
		WIN_HEIGHT / 2, 0);
	SDL_GL_SetSwapInterval(1);
	cxt->run = 1;
	set_keys(&cxt->keys, &cxt->nkeys);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	cxt->glcontext = SDL_GL_CreateContext(cxt->arena);
	shaders[0].file = ft_strdup("./shaders/vertex.shader");
	shaders[0].type = GL_VERTEX_SHADER;
	shaders[1].file = ft_strdup("./shaders/frag.shader");
	shaders[1].type = GL_FRAGMENT_SHADER;
	cxt->program = create_program(2, shaders);
	free(shaders[0].file);
	free(shaders[1].file);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0, 0, 0, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 32);
	mat_ident(&cxt->camera);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	cxt->vao = generate_cube(cxt);
	cxt->diffuseTexture = load_bmp_to_opengl("texture/coretext.bmp");
	glEnable(GL_MULTISAMPLE);
}
