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

void		update_name(t_gr_vm *ctx, t_arena *a)
{
	const char 	title[] = "corewar ";
	char 		*t;

	t = ft_strjoinfree(title, ft_itoa(a->cycles), 2);
	SDL_SetWindowTitle(ctx->arena, t);
	free(t);
}

void		gr_vm_run(t_vm_loop loop, void *data, t_gr_vm *ctx)
{
	SDL_Event	e;
	void 		(*handler)(void *, t_gr_vm *, SDL_Event *);
	int			i;
	int			c;

	while (ctx->run)
	{
		c = 0;
		update_name(ctx, data);
		while (c++ < ctx->cpf)
			if (loop(data) == 0)
			{
				ctx->cpf = -1;
				winner(data);
				break ;
			}
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
		SDL_GL_MakeCurrent(ctx->arena, ctx->arena_context);
		render_opengl(ctx, data);
		SDL_UpdateWindowSurface(ctx->UI);
	}
}

void		gr_vm_end(t_gr_vm *ctx)
{
	SDL_DestroyWindow(ctx->arena);
	SDL_GL_DeleteContext(ctx->arena_context);
	SDL_Quit();
}
