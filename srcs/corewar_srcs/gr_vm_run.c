/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gr_vm_run.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 08:17:20 by cchaumar          #+#    #+#             */
/*   Updated: 2017/03/19 08:17:21 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "gr_vm_internals.h"

void		gr_vm_run(t_vm_loop loop, void *data, t_gr_vm *ctx)
{
	SDL_Event	e;
	void 		(*handler)(void *, t_gr_vm *, SDL_Event *);
	int			i;

	while (ctx->run)
	{
		loop(data);
		while (SDL_PollEvent(&e))
			if ((handler = get_handler(e.type)))
				handler(data, ctx, &e);
		i = 0;
		while (i < ctx->nkeys)
		{
			if (ctx->keys[i].pressed && ctx->keys[i].hold)
				ctx->keys[i].hold(data, ctx, ctx->keys + i);
			i++;
		}
		render_opengl(ctx, *(t_arena*)data);
		SDL_UpdateWindowSurface(ctx->UI);
	}
}

void		gr_vm_end(t_gr_vm *ctx)
{
	SDL_DestroyWindow(ctx->arena);
	SDL_GL_DeleteContext(ctx->glcontext);
	SDL_Quit();
}
