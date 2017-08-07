/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gr_vm_camera_handling.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/07 10:40:42 by cchaumar          #+#    #+#             */
/*   Updated: 2017/08/07 10:40:43 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "gr_vm_internals.h"

void		cam_trans_forwad(void *data, t_gr_vm *vm, t_key *key)
{
	t_vec4	tr;

	tr.x = vm->camera.m.r[0].z;
	tr.y = vm->camera.m.r[1].z;
	tr.z = vm->camera.m.r[2].z;
	tr.w = 0;
	tr = v_mult_k(tr, -SPEED);
	vm->camera.pos = v_add(vm->camera.pos, tr);
	vm->camera.m.r[0].w -= tr.x;
	vm->camera.m.r[1].w -= tr.y;
	vm->camera.m.r[2].w -= tr.z;
	(void)data;
	(void)key;
}

void		cam_trans_back(void *data, t_gr_vm *vm, t_key *key)
{
	t_vec4	tr;

	tr.x = vm->camera.m.r[0].z;
	tr.y = vm->camera.m.r[1].z;
	tr.z = vm->camera.m.r[2].z;
	tr.w = 0;
	tr = v_mult_k(tr, SPEED);
	vm->camera.pos = v_add(vm->camera.pos, tr);
	vm->camera.m.r[0].w -= tr.x;
	vm->camera.m.r[1].w -= tr.y;
	vm->camera.m.r[2].w -= tr.z;
	(void)data;
	(void)key;
}

void		cam_trans_right(void *data, t_gr_vm *vm, t_key *key)
{
	t_vec4	tr;

	tr.x = vm->camera.m.r[0].x;
	tr.y = vm->camera.m.r[1].x;
	tr.z = vm->camera.m.r[2].x;
	tr.w = 0;
	tr = v_mult_k(tr, SPEED);
	vm->camera.pos = v_add(vm->camera.pos, tr);
	vm->camera.m.r[0].w -= tr.x;
	vm->camera.m.r[1].w -= tr.y;
	vm->camera.m.r[2].w -= tr.z;
	(void)data;
	(void)key;
}

void		cam_trans_left(void *data, t_gr_vm *vm, t_key *key)
{
	t_vec4	tr;

	tr.x = vm->camera.m.r[0].x;
	tr.y = vm->camera.m.r[1].x;
	tr.z = vm->camera.m.r[2].x;
	tr.w = 0;
	tr = v_mult_k(tr, -SPEED);
	vm->camera.pos = v_add(vm->camera.pos, tr);
	vm->camera.m.r[0].w -= tr.x;
	vm->camera.m.r[1].w -= tr.y;
	vm->camera.m.r[2].w -= tr.z;
	(void)data;
	(void)key;
}
