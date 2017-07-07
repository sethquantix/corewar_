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

void	draw_registers(t_gr_vm *cxt, SDL_Surface *s, t_proc *p, SDL_Rect *pos)
{
	int		j;
	int		i;
	int		delta;

	j = 0;
	i = 0;
	pos->y += pos->h * 1.5;
	printf("%f\n", (float)pos->y / (float)BOARD_HEIGHT);
	delta = BOARD_WIDTH / 8;
	while (j < 2)
	{
		i = 0;
		while (i < 8)
		{
			pos->x = i * delta;
			if (p)
				s = print_text(&cxt->sst, WHITE_SMALL, "0x%08x",
					p->reg[8 * j + i + 1]);
			else
				s = print_text(&cxt->sst, WHITE_SMALL, "          ");
			*pos = draw_text(cxt->screen, s, *pos, 0);
			i++;
		}
		j++;
		pos->y += pos->h * 1.1;
	}
}

void	info_proc(t_gr_vm *cxt, SDL_Surface *s, t_proc *proc, SDL_Rect pos)
{
	pos.x += 1.5 * pos.w;
	s = print_text(&cxt->sst, WHITE_MEDIUM, "%s",
		proc->dead ? "Dead " : "Alive");
	pos = draw_text(cxt->screen, s, pos, 0);
	pos.y += 1.2 * pos.h;
	draw_registers(cxt, s, proc, &pos);
}

void	clean(t_gr_vm *cxt, SDL_Surface *s, SDL_Rect pos)
{
	pos.x += 1.5 * pos.w;
	s = print_text(&cxt->sst, WHITE_MEDIUM, "     ");
	pos = draw_text(cxt->screen, s, pos, 0);
	draw_registers(cxt, s, NULL, &pos);
}

void	draw_proc(t_gr_vm *cxt, t_arena *arena, SDL_Surface *s)
{
	const char 	*proc[] = {0, "All", "None"};
	SDL_Rect	pos;
	char 		*p;

	pos.x = 0;
	pos.y = 0.55 * BOARD_HEIGHT;
	p = cxt->cursor.player == PLAYER_NONE ? ft_strdup("NONE") :
		ft_itoa(arena->champs[cxt->cursor.player].num);
	free(p);
	s = print_text(&cxt->sst, WHITE_MEDIUM, "Player : %-5s", p);
	pos = draw_text(cxt->screen, s, pos, X_LEFT);
	cxt->cursor.player_box = box(pos);
	pos.y = 0.55 * BOARD_HEIGHT;
	pos.x += 1.1 * pos.w;
	p = cxt->cursor.proc >= 0 ? ft_itoa(cxt->cursor.proc) :
		ft_strdup(proc[-cxt->cursor.proc]);
	s = print_text(&cxt->sst, WHITE_MEDIUM, "Process : %-5s", p);
	free(p);
	pos = draw_text(cxt->screen, s, pos, 0);
	cxt->cursor.proc_box = box(pos);
	if (cxt->cursor.proc >= 0)
		info_proc(cxt, s, arena->procs[cxt->cursor.proc], pos);
	else
		clean(cxt, s, pos);
}

void	draw_info(int start, t_gr_vm *cxt, t_arena *arena, SDL_Surface *s)
{
	SDL_Rect	pos;

	pos.x = 0.56 * BOARD_WIDTH;
	pos.y = 0.24 * BOARD_HEIGHT;
	s = print_text(&cxt->sst, GREY_MEDIUM, "CYCLES_TO_DIE : %-4d", arena->ctd);
	pos = draw_text(cxt->screen, s, pos, 0);
	if (start)
		return ;
	pos.y += 1.7 * pos.h;
	s = print_text(&cxt->sst, GREY_MEDIUM, "NBR_LIVES     : %d", NBR_LIVE);
	pos = draw_text(cxt->screen, s, pos, 0);
	pos.y += 1.7 * pos.h;
	s = print_text(&cxt->sst, GREY_MEDIUM, "CYCLES_DELTA  : %d", CYCLE_DELTA);
	pos = draw_text(cxt->screen, s, pos, 0);
}

void draw_ui(t_gr_vm *cxt, t_arena *arena)
{
	static int 	start = 0;
    SDL_Surface *s;
	SDL_Rect	pos;

	pos = (SDL_Rect){0, 0, 0, 0};
	if (!start)
		draw_base(cxt, arena, &pos, s);
	draw_info(start, cxt, arena, s);
	draw_proc(cxt, arena, s);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, cxt->board);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, cxt->screen->w, cxt->screen->h, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, cxt->screen->pixels);
	start = 1;
}
