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

void print_text(t_text_p *params, t_styles style, SDL_Surface *dst, const char *text, ...)
{
    t_style     st;
    va_list     va;
    char        *s;
    SDL_Surface *surface;
    SDL_Rect    p;

    va_start(va, text);
    ft_vasprintf(&s, text, va);
    va_end(va);
    st = params->styles[style];
    p = params->pos;
    surface = TTF_RenderText_Solid(st.font, s, st.c);
    p.w = surface->w;
    p.h = surface->h;
    if (st.centered & CENTER_X)
        p.x += (dst->w - surface->w) / 2;
    if (st.centered & CENTER_Y)
        p.y += (dst->h - surface->h) / 2;
    SDL_BlitSurface(surface, NULL, dst, &p);
    params->pos.h = p.h;
    params->pos.w = p.w;
    SDL_FreeSurface(surface);
}

void    create_styles(t_style *styles)
{
    t_style style;

    style.centered = CENTER_NONE;
    style.font = TTF_OpenFont("assets/Prototype.ttf", 12);
    style.c = (SDL_Color){255, 255, 255};
    styles[WHITE_SMALL] = style;
    style.c = (SDL_Color){0, 0, 255};
    styles[BLUE_SMALL] = style;
    style.font = TTF_OpenFont("assets/Prototype.ttf", 42);
    styles[BLUE_BIG] = style;
    style.centered = CENTER_X;
    styles[BLUE_BIG_CENTERED] = style;
}

void set_ui(t_gr_vm *cxt, t_arena *arena)
{
    TTF_Font    *font;
    SDL_Surface *title;
    SDL_Surface *cycle;
    SDL_Surface *procs;
    SDL_Surface *player1;
    SDL_Surface *player2;
    SDL_Surface *last_live;
    SDL_Surface *champ_name;
    SDL_Rect    pos;
    t_text_p    params;

    ft_bzero(&params, sizeof(t_text_p));
    params.styles = try(sizeof(t_style) * 12);
    if (TTF_Init() == -1)
        exit(EXIT_FAILURE);
    create_styles(params.styles);
    cxt->ui_screen = SDL_GetWindowSurface(cxt->UI);
    ft_bzero(cxt->ui_screen->pixels, 4 * cxt->ui_screen->w * cxt->ui_screen->h);
    params.pos = (SDL_Rect){0, 20, 0, 0};
    print_text(&params, BLUE_BIG_CENTERED, cxt->ui_screen, "COREWAR");
    params.pos.y += params.pos.h * 2;
    print_text(&params, WHITE_SMALL, cxt->ui_screen, "PLAYER 1");
    TTF_Quit();
}
