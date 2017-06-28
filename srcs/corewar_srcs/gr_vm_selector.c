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

#include "gr_vm_internals.h"
#include "corewar.h"

//int 		next_proc(t_arena *arena, t_cursor *cursor, int dir)
//{
//	int 	i;
//
//	i = cursor->proc;
//	if (dir == 1)
//		while (i < arena->proc_count)
//			if (i >= 0 && arena->procs[i]->player == cursor->player)
//				return (i);
//			else
//				i++;
//	else
//		while (i >= 0)
//			if (i < arena->proc_count &&
//				arena->procs[i]->player == cursor->player)
//				return (i);
//			else
//				i--;
//	return (cursor->proc);
//}

static void	prev_proc(t_arena *arena, t_cursor *cursor, int key)
{
	int 	i;
	int		found;

	found = 0;
	i = cursor->proc;

	if (i < 0)
	{
		cursor->proc = PROC_NONE;
		return ;
	}
	while (--i > 0)
		if (i < arena->proc_count && arena->procs[i]->player ==
			-arena->champs[cursor->player].id - 1)
		{
			found = 1;
			break;
		}
	cursor->proc = found ? i : PROC_ALL;
}

static void	next_proc(t_arena *arena, t_cursor *cursor, int key)
{
	int		i;
	int		found;

	found = 0;
	i = cursor->proc;
	while (++i < arena->proc_count)
		if (i >= 0 && arena->procs[i]->player ==
			-arena->champs[cursor->player].id - 1)
		{
			found = 1;
			break ;
		}
	cursor->proc = found ? i : cursor->proc;
}

static void	next_player(t_arena *arena, t_cursor *cursor, int key)
{
	int 		i;

	i = cursor->player;
	if (key == SDLK_UP && --cursor->player < PLAYER_NONE)
		cursor->player = PLAYER_NONE;
	if (key == SDLK_DOWN && ++cursor->player >= arena->champ_count)
		cursor->player = arena->champ_count - 1;
	if (cursor->player != i)
		cursor->proc = PROC_ALL;
}

static void	move_cursor(t_arena *arena, t_cursor *cursor, int key)
{
	cursor->pos = key == SDLK_LEFT ? SELECT_PLAYER : SELECT_PROC;
	if (cursor->player == PLAYER_NONE && cursor->pos == SELECT_PROC)
		cursor->pos = SELECT_PLAYER;
}

void		select_proc(void *data, t_gr_vm *vm, t_key *key)
{
	static void	(*funcs[])(t_arena *, t_cursor *, int) = {
		move_cursor, move_cursor, prev_proc, next_proc, next_player, next_player
	};
	const int 	keycodes[] = {
		SDLK_LEFT, SDLK_RIGHT, SDLK_UP, SDLK_DOWN
	};
	int			i;
	int			k;

	i = 0;
	while (keycodes[i] != key->keycode && i < 4)
		i++;
	k = i + (i > 1 && vm->cursor.pos == SELECT_PLAYER ? 2 : 0);
	funcs[k](data, &vm->cursor, keycodes[i]);
}
