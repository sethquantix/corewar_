/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gr_vm_selector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 08:18:38 by cchaumar          #+#    #+#             */
/*   Updated: 2017/06/28 08:18:39 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>
#include <gr_vm_internals.h>

static void	next_proc(t_arena *arena, t_cursor *cursor, int key)
{
	int		i;
	int		found;

	found = 0;
	i = cursor->proc;
	if (key == SDLK_DOWN)
	{
		while (++i < arena->proc_count)
			if (i >= 0 && arena->procs[i]->player ==
				-arena->champs[cursor->player].id - 1)
			{
				found = 1;
				break ;
			}
	}
	else
		while (--i >= 0)
			if (i < arena->proc_count && arena->procs[i]->player ==
				-arena->champs[cursor->player].id - 1)
			{
				found = 1;
				break ;
			}
	cursor->proc = found || key == SDLK_UP ? i : cursor->proc;
	cursor->proc = cursor->proc < PROC_NONE ? PROC_NONE : cursor->proc;
}

static void	next_player(t_arena *arena, t_cursor *cursor, int key)
{
	int		i;

	i = cursor->player;
	if (key == SDLK_UP && --cursor->player < PLAYER_NONE)
		cursor->player = PLAYER_NONE;
	if (key == SDLK_DOWN && ++cursor->player >= arena->champ_count)
		cursor->player = arena->champ_count - 1;
	if (cursor->player != i)
		cursor->proc = PROC_ALL;
}

static void	next_reg(t_arena *arena, t_cursor *cursor, int key)
{
	(void)arena;
	cursor->reg += key == SDLK_DOWN ? -1 : 1;
	if (cursor->reg == 0)
		cursor->reg = 1;
	if (cursor->reg > REG_NUMBER)
		cursor->reg = REG_NUMBER;
}

static void	move_cursor(t_arena *arena, t_cursor *cursor, int key)
{
	(void)arena;
	cursor->pos += key == SDLK_LEFT ? -1 : 1;
	if (cursor->pos > SELECT_REG)
		cursor->pos = SELECT_REG;
	if (cursor->pos < SELECT_PLAYER)
		cursor->pos = SELECT_PLAYER;
	if (cursor->player == PLAYER_NONE && cursor->pos == SELECT_PROC)
		cursor->pos = SELECT_PLAYER;
	if (cursor->proc < 0 && cursor->pos == SELECT_REG)
		cursor->pos = SELECT_PROC;
}

void		select_proc(void *data, t_gr_vm *vm, t_key *key)
{
	static void	(*funcs[])(t_arena *, t_cursor *, int) = {
		move_cursor, move_cursor, next_player, next_player, next_proc,
		next_proc, next_reg, next_reg};
	const int	keycodes[] = {
		SDLK_LEFT, SDLK_RIGHT, SDLK_UP, SDLK_DOWN
	};
	int			i;
	int			k;
	static int	last = 0;

	if (SDL_GetTicks() - last < 100)
		return ;
	last = SDL_GetTicks();
	i = 0;
	while (keycodes[i] != key->keycode && i < 4)
		i++;
	k = i + (i > 1 ? 2 * vm->cursor.pos : 0);
	funcs[k](data, &vm->cursor, keycodes[i]);
}
