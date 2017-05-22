/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crwr_types.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 12:40:33 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/06 12:40:34 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "gr_vm_internals.h"

void		cam_trans_forwad(void *data, t_gr_vm *vm, t_key *key)
{
	vm->camera.pos = v_add(vm->camera.pos, v_mult_k(vm->camera.fw, vm->camera.v));
}

void		cam_trans_back(void *data, t_gr_vm *vm, t_key *key)
{
	vm->camera.pos = v_add(vm->camera.pos, v_mult_k(vm->camera.fw, -vm->camera.v));
}

void		cam_trans_right(void *data, t_gr_vm *vm, t_key *key)
{
	vm->camera.pos = v_add(vm->camera.pos, v_mult_k(vm->camera.lt, -vm->camera.v));
}

void		cam_trans_left(void *data, t_gr_vm *vm, t_key *key)
{
	vm->camera.pos = v_add(vm->camera.pos, v_mult_k(vm->camera.lt, vm->camera.v));
}