#include "corewar.h"
#include "gr_vm_internals.h"

void		toggle_42(void *data, t_gr_vm *vm, t_key *key)
{
	vm->anim42 = !vm->anim42;
}

void		cam_rot_forwad(void *data, t_gr_vm *vm, t_key *key)
{
	t_mat n;

	mat_ident(&n);
	n.t[5] = cos(-0.1);
	n.t[6] = -sin(-0.1);
	n.t[9] = sin(-0.1);
	n.t[10] = cos(-0.1);
	vm->camera = mat_mult_mat(vm->camera, n);
}

void		cam_rot_back(void *data, t_gr_vm *vm, t_key *key)
{
	t_mat n;

	mat_ident(&n);
	n.t[5] = cos(0.1);
	n.t[6] = -sin(0.1);
	n.t[9] = sin(0.1);
	n.t[10] = cos(0.1);
	vm->camera = mat_mult_mat(vm->camera, n);
}

void		cam_rot_right(void *data, t_gr_vm *vm, t_key *key)
{
	t_mat n;

	mat_ident(&n);
	n.t[0] = cos(0.1);
	n.t[8] = -sin(0.1);
	n.t[2] = sin(0.1);
	n.t[10] = cos(0.1);
	vm->camera = mat_mult_mat(vm->camera, n);
}

void		cam_rot_left(void *data, t_gr_vm *vm, t_key *key)
{
	t_mat n;

	mat_ident(&n);
	n.t[0] = cos(-0.1);
	n.t[8] = -sin(-0.1);
	n.t[2] = sin(-0.1);
	n.t[10] = cos(-0.1);
	vm->camera = mat_mult_mat(vm->camera, n);
}