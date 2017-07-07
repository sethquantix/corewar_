/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gr_vm_ui_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 05:45:51 by cchaumar          #+#    #+#             */
/*   Updated: 2017/06/28 05:45:51 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "gr_vm_internals.h"

t_vec4	box(SDL_Rect pos)
{
	return (vec4(
		(float)pos.x / (float)BOARD_WIDTH,
		(float)pos.y / (float)BOARD_HEIGHT,
		(float)pos.w / (float)BOARD_WIDTH,
		(float)pos.h / (float)BOARD_HEIGHT
	));
}

SDL_Surface	*print_text(t_text_p *sst, t_styles style, const char *text, ...)
{
	t_style     st;
	va_list     va;
	char        *s;

	va_start(va, text);
	ft_vasprintf(&s, text, va);
	va_end(va);
	st = sst->styles[style];
	return (TTF_RenderText_Shaded(st.font, s, st.c, (SDL_Color){0, 0, 0,0}));
}

SDL_Rect	draw_text(SDL_Surface *dst, SDL_Surface *s, SDL_Rect pos, int al)
{
	pos.w = s->w;
	pos.h = s->h;
	if (al & X_LEFT)
		pos.x = X_MARGIN * BOARD_WIDTH;
	if (al & X_RIGHT)
		pos.x = BOARD_WIDTH - X_MARGIN * (float)BOARD_WIDTH - pos.w;
	if (al & X_CENTER)
		pos.x = (BOARD_WIDTH - pos.w) / 2;
	if (al & Y_TOP)
		pos.y = Y_MARGIN * BOARD_HEIGHT;
	if (al & Y_BOT)
		pos.y = BOARD_HEIGHT - Y_MARGIN * (float)BOARD_HEIGHT - pos.h;
	if (al & Y_CENTER)
		pos.y = (BOARD_HEIGHT - pos.h) / 2;
	SDL_BlitSurface(s, NULL, dst, &pos);
	free(s);
	return (pos);
}

static void	print_players(t_text_p *sst, SDL_Surface *board, SDL_Rect *pos,
	t_arena *arena)
{
	int				i;
	SDL_Surface		*s;

	i = 0;
	while (i < arena->champ_count)
	{
		s = print_text(sst, WHITE_MEDIUM, "P%d : ", arena->champs[i].num);
		*pos = draw_text(board, s, *pos, X_LEFT);
		pos->x += pos->w;
		s = print_text(sst, P_1MEDIUM + i, "%.20s%s",
			arena->champs[i].head.prog_name,
			ft_strlen(arena->champs[i].head.prog_name) > 20 ? "..." : "");
		*pos = draw_text(board, s, *pos, 0);
		pos->y += 1.1 * pos->h;
		i++;
	}
}

void 	draw_base(t_gr_vm *cxt, t_arena *arena, SDL_Rect *pos, SDL_Surface *s)
{
	static int		start = 0;
	static SDL_Rect	rect = (SDL_Rect){0, 0, 0, 0};

	if (start)
		*pos = rect;
	s = print_text(&cxt->sst, WHITE_HUGE, "COREWAR");
	rect = draw_text(cxt->screen, s, rect, X_CENTER | Y_TOP);
	rect.y += 1.3 * rect.h;
	*pos = rect;
	print_players(&cxt->sst, cxt->screen, &rect, arena);
	*pos = rect;
	start = 1;
}
