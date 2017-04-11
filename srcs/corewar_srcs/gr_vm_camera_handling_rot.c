#include "corewar.h"
#include "gr_vm_internals.h"
/*
static float	*rcm_rotmat(float rotx, float roty, float rotz)
{
	t_mat new;
	t_mat new1;
	t_mat new2;

	new[0] = cos(rotz);
	new[1] = -sin(rotz);
	new[4] = sin(rotz);
	new[5] = cos(rotz);

	new2[0] = cos(roty);
	new2[8] = -sin(roty);
	new2[2] = sin(roty);
	new2[10] = cos(roty);

	new3[5] = cos(rotx);
	new3[6] = -sin(rotx);
	new3[9] = sin(rotx);
	new3[10] = cos(rotx);
}
*/
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