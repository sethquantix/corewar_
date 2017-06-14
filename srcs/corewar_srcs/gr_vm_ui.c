/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gr_vm_ui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnagy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 16:07:25 by lnagy             #+#    #+#             */
/*   Updated: 2017/06/01 16:07:26 by lnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "gr_vm_internals.h"

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

static void	gl_board(t_gr_vm *cxt, SDL_Surface *board)
{
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, cxt->board);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		board->w, board->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, board->pixels);
}

static SDL_Rect		draw_text(SDL_Surface *dst, SDL_Surface *s,
	SDL_Rect pos, int al)
{
	pos.w = s->w;
	pos.h = s->h;
	if (al & X_LEFT)
		pos.x = X_MARGIN * BOARD_WIDTH;
	if (al & X_RIGHT)
		pos.x = BOARD_WIDTH - X_MARGIN * BOARD_WIDTH - pos.w;
	if (al & X_CENTER)
		pos.x = (BOARD_WIDTH - pos.w) / 2;
	if (al & Y_TOP)
		pos.y = Y_MARGIN * BOARD_HEIGHT;
	if (al & Y_BOT)
		pos.y = BOARD_HEIGHT - Y_MARGIN * BOARD_HEIGHT - pos.h;
	if (al & Y_CENTER)
		pos.y = (BOARD_HEIGHT - pos.h) / 2;
	SDL_BlitSurface(s, NULL, dst, &pos);
	free(s);
	return (pos);
}

void print_players(t_text_p *sst, SDL_Surface *board, SDL_Rect *pos, t_arena *arena)
{
	int				i;
	SDL_Surface		*s;

	i = 0;
	while (i < arena->champ_count)
	{
		s = print_text(sst, P_1MEDIUM + i, "Player %d : ", arena->champs[i].num);
		*pos = draw_text(board, s, *pos, X_LEFT);
		pos->x += pos->w;
		s = print_text(sst, WHITE_SMALL, "%.20s%s", arena->champs[i].head.prog_name,
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
	print_players(&cxt->sst, cxt->screen, &rect, arena);
	*pos = rect;
	start = 1;
}

void draw_ui(t_gr_vm *cxt, t_arena *arena)
{
	static int 	start = 0;
    SDL_Surface *s;
	SDL_Rect	pos;

	pos = (SDL_Rect){0, 0, 0, 0};
	if (!start)
		draw_base(cxt, arena, &pos, s);
	gl_board(cxt, cxt->screen);
	start = 1;
}
