/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gr_vm_inputs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 15:40:18 by cchaumar          #+#    #+#             */
/*   Updated: 2017/03/31 15:40:19 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "gr_vm_internals.h"

void		quit_press(void *data, t_gr_vm *vm, t_key *key)
{
	(void)key;
	(void)data;
	vm->run = 0;
}

void		speed(void *data, t_gr_vm *vm, t_key *key)
{
	(void)data;
	if (vm->cps < 0)
		return ;
	vm->cps += key->keycode == SDLK_KP_MINUS ? -1 : 1;
	vm->cps = vm->cps > 500 ? 500 : vm->cps;
	vm->cps = vm->cps < 0 ? 0 : vm->cps;
}

void		toggle_opt(void *data, t_gr_vm *vm, t_key *key)
{
	const int	opts[] = { SDLK_SLASH, SDLK_r, SDLK_BACKSLASH };
	int			i;

	(void)data;
	i = 0;
	while (i < 3)
	{
		if (opts[i] == key->keycode)
			break ;
		else
			i++;
	}
	vm->opts ^= (i != 3) * (1 << i);
}
