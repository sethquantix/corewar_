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