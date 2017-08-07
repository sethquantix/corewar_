/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gr_vm_run.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 08:17:20 by cchaumar          #+#    #+#             */
/*   Updated: 2017/08/07 10:39:37 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "gr_vm_internals.h"

static void	update_name(t_gr_vm *ctx, t_arena *a)
{
	char	*t;

	t = NULL;
	ft_sprintf(&t, "corewar : %d cycles  -  %d cycles / s",
		a->cycles, ctx->cps);
	SDL_SetWindowTitle(ctx->arena, t);
	free(t);
}

static void	render_loop(void *data, t_gr_vm *ctx)
{
	void		(*handler)(void *, t_gr_vm *, SDL_Event *);
	SDL_Event	e;
	int			i;

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
	render_opengl(ctx, data);
}

void		gr_vm_run(t_vm_loop loop, void *data, t_gr_vm *ctx)
{
	SDL_Event	e;
	int			ticks;

	ticks = SDL_GetTicks();
	while (SDL_PollEvent(&e))
		;
	SDL_GL_MakeCurrent(ctx->arena, ctx->arena_context);
	while (ctx->run)
	{
		update_name(ctx, data);
		while (ctx->cps > 0 &&
			SDL_GetTicks() - ticks > (1000.0 / (float)ctx->cps))
			if (loop(data) == 0)
			{
				ctx->cps = -1;
				break ;
			}
			else
				ticks += 1000 / (float)ctx->cps;
		render_loop(data, ctx);
	}
}

void		gr_vm_end(t_gr_vm *ctx)
{
	int		i;

	SDL_FreeSurface(ctx->screen);
	SDL_DestroyWindow(ctx->arena);
	SDL_GL_DeleteContext(ctx->arena_context);
	i = 0;
	while (i < ctx->sst.nstyle)
		TTF_CloseFont(ctx->sst.styles[i++].font);
	free(ctx->sst.styles);
	SDL_Quit();
	TTF_Quit();
}
