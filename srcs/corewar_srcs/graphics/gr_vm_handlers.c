/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gr_vm_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 15:40:42 by cchaumar          #+#    #+#             */
/*   Updated: 2017/03/31 15:40:43 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "gr_vm_internals.h"

void		quit_handler(void *data, t_gr_vm *vm, SDL_Event *e)
{
	(void)data;
	ft_printf("vm will exit after %d ticks\n", e->quit.timestamp);
	vm->run = 0;
}

void		mouse_button_handler(void *data, t_gr_vm *vm, SDL_Event *e)
{
	int		i;
	
	i = 0;
	while (vm->keys && i < vm->nkeys)
	{
		if (e->button.button == vm->keys[i].keycode)
		{
			if ((vm->keys[i].pressed =
				e->button.state == SDL_PRESSED ? 1 : 0) == 1)
			{
				vm->keys[i].x = e->button.x;
				vm->keys[i].y = e->button.y;
				if (vm->keys[i].press)
					vm->keys[i].press(data, vm, vm->keys + i);
			}
			break ;
		}
		i++;
	}
}

void		mouse_move_handler(void *data, t_gr_vm *vm, SDL_Event *e)
{
	(void)data;
	rotate(vm, e->motion.xrel, e->motion.yrel);
}

void		key_handler(void *data, t_gr_vm *vm, SDL_Event *e)
{
	int		i;

	if (e->key.repeat)
		return ;
	i = 0;
	while (vm->keys && i < vm->nkeys)
	{
		if (e->key.keysym.sym == vm->keys[i].keycode)
		{
			if ((vm->keys[i].pressed =
				e->key.state == SDL_PRESSED ? 1 : 0) == 1 && vm->keys[i].press)
				vm->keys[i].press(data, vm, vm->keys + i);
			break ;
		}
		i++;
	}
}

t_handler	get_handler(int type)
{
	t_event	events[] = {
		{SDL_QUIT, quit_handler}, {SDL_MOUSEBUTTONDOWN, mouse_button_handler},
		{SDL_MOUSEBUTTONUP, mouse_button_handler}, {SDL_KEYDOWN, key_handler},
		{SDL_KEYUP, key_handler}, {SDL_MOUSEMOTION, mouse_move_handler}, {0, 0}};
	int		i;

	i = 0;
	while (events[i].handler)
		if (events[i].sdl_event_type == type)
			return (events[i].handler);
		else
			i++;
	return (NULL);
}
