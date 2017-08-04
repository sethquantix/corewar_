/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gr_vm_ui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnagy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/01 16:07:25 by lnagy             #+#    #+#             */
/*   Updated: 2017/07/08 10:43:54 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>
#include <gr_vm_internals.h>

static void	info_proc(t_gr_vm *cxt, SDL_Surface *s, t_proc *proc, SDL_Rect pos)
{
	s = print_text(&cxt->sst, WHITE_MEDIUM, "%3d = 0x%08x", cxt->cursor.reg,
		proc->reg[cxt->cursor.reg]);
	pos = draw_text(cxt->screen, s, pos, X_RIGHT);
	s = print_text(&cxt->sst, WHITE_MEDIUM, "Reg ");
	pos.x -= s->w;
	pos = draw_text(cxt->screen, s, pos, 0);
	cxt->cursor.reg_box = box(pos);
	s = print_text(&cxt->sst, WHITE_MEDIUM, "(%s) | ",
		proc->dead ? "Dead " : "Alive");
	pos.x -= s->w;
	pos = draw_text(cxt->screen, s, pos, 0);
	pos.y += pos.h * 1.5;
	s = print_text(&cxt->sst, WHITE_MEDIUM, "Carry : %d  |  PC : 0x%03x",
		proc->carry, proc->pc);
	pos = draw_text(cxt->screen, s, pos, X_LEFT);
	pos.x += pos.w;
	s = print_text(&cxt->sst, WHITE_MEDIUM, "    Status : %-9s", proc->op ?
		"Executing" : "Waiting");
	draw_text(cxt->screen, s, pos, 0);
}

static void	proc_content(t_gr_vm *cxt, t_arena *arena, SDL_Surface *s,
	SDL_Rect pos)
{
	static int	cleaned = 1;

	if (cxt->cursor.proc >= 0)
	{
		cleaned = 0;
		info_proc(cxt, s, arena->procs[cxt->cursor.proc], pos);
		return ;
	}
	if (cleaned)
		return ;
	pos.x += 1 * pos.w;
	s = print_text(&cxt->sst, WHITE_MEDIUM, "%40s", " ");
	pos = draw_text(cxt->screen, s, pos, 0);
	pos.y += 1.1 * pos.h;
	ft_bzero(cxt->screen->pixels + 4 * pos.y * BOARD_WIDTH,
		BOARD_WIDTH * (BOARD_HEIGHT - pos.y) * 4);
	cleaned = 1;
}

static void	draw_proc(t_gr_vm *cxt, t_arena *arena, SDL_Surface *s)
{
	const char	*proc[] = {0, "All", "None"};
	SDL_Rect	pos;
	char		*p;

	pos.y = 0.55 * BOARD_HEIGHT;
	p = cxt->cursor.player == PLAYER_NONE ? ft_strdup("NONE") :
		ft_itoa(arena->champs[cxt->cursor.player].num);
	s = print_text(&cxt->sst, WHITE_MEDIUM, "Player : %-5s", p);
	free(p);
	pos = draw_text(cxt->screen, s, pos, X_LEFT);
	cxt->cursor.player_box = box(pos);
	pos.y = 0.55 * BOARD_HEIGHT;
	pos.x += 1.1 * pos.w;
	p = cxt->cursor.proc >= 0 ? ft_itoa(cxt->cursor.proc) :
		ft_strdup(proc[-cxt->cursor.proc]);
	s = print_text(&cxt->sst, WHITE_MEDIUM, "Process : %-4s", p);
	free(p);
	pos = draw_text(cxt->screen, s, pos, 0);
	cxt->cursor.proc_box = box(pos);
	proc_content(cxt, arena, s, pos);
}

static void	draw_info(int start, t_gr_vm *cxt, t_arena *arena, SDL_Surface *s)
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

void		draw_ui(t_gr_vm *cxt, t_arena *arena)
{
	static int	start = 0;
	SDL_Surface	*s;
	SDL_Rect	pos;

	pos = (SDL_Rect){0, 0, 0, 0};
	s = NULL;
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
