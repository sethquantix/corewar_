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
	*nkeys += add_key(keys, SDL_BUTTON_RIGHT, quit_press, NULL);
}

void	gr_vm_init(t_gr_vm *cxt)
{
	t_gl_shader shaders[2];
	SDL_Init(SDL_INIT_VIDEO);

	cxt->arena = SDL_CreateWindow("corewar", SDL_POS, SDL_POS, WIN_WIDTH / 2,
		WIN_HEIGHT / 2, SDL_WINDOW_OPENGL);
	cxt->UI = SDL_CreateWindow("UI", SDL_POS, SDL_POS, WIN_WIDTH / 2,
		WIN_HEIGHT / 2, 0);
	cxt->glcontext = SDL_GL_CreateContext(cxt->arena);
	SDL_GL_SetSwapInterval(1);
	cxt->run = 1;
	set_keys(&cxt->keys, &cxt->nkeys);
	//mglewInit();
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	shaders[0].file = ft_strdup("./shaders/vertex.shader");
	shaders[0].type = GL_VERTEX_SHADER;
	shaders[1].file = ft_strdup("./shaders/frag.shader");
	shaders[1].type = GL_FRAGMENT_SHADER;

	cxt->program = create_program(2, shaders);
	free(shaders[0].file);
	free(shaders[1].file);
	printf("%d\n", cxt->program);
}

/*
	cxt->glcontext = SDL_GL_CreateContext(cxt->arena);
	cxt->screen = SDL_GetWindowSurface(cxt->arena);
	SDL_FillRect(cxt->screen, NULL, SDL_MapRGB(cxt->screen->format, 0, 0, 0));
	cxt->main = SDL_CreateRGBSurfaceWithFormat(0, 2048, WIN_HEIGHT, 32,
		SDL_PIXELFORMAT_RGBA32);
	cxt->ui = SDL_CreateRGBSurfaceWithFormat(0, WIN_WIDTH, WIN_HEIGHT, 32,
		SDL_PIXELFORMAT_RGBA32);
	SDL_FillRect(cxt->main, NULL, SDL_MapRGBA(cxt->main->format, 0, 0, 0, 0));
	SDL_FillRect(cxt->ui, NULL, SDL_MapRGBA(cxt->ui->format, 0, 0, 0, 0));
	if (cxt->arena == NULL)
		ft_printf("Couldnt create window\nSDL error : %s\n", SDL_GetError());
*/