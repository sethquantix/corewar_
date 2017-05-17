#include "corewar.h"
#include "gr_vm_internals.h"

void		cam_trans_forwad(void *data, t_gr_vm *vm, t_key *key)
{
	int 	i;

	i = 0;
	while (i < 3)
	{
		vm->camera.t[3 + 4 * i] -= 0.4f * vm->camera.t[2 + 4 * i];
		i++;
	}
//	vm->camera.t[3 + 4 * 2] += 0.4f * ;
}

void		cam_trans_back(void *data, t_gr_vm *vm, t_key *key)
{
	int 	i;

	i = 0;
	while (i < 3)
	{
		vm->camera.t[3 + 4 * i] += 0.4f * vm->camera.t[2 + 4 * i];
		i++;
	}
//	vm->camera.t[3 + 4 * 2] -= 0.4f;
}

void		cam_trans_right(void *data, t_gr_vm *vm, t_key *key)
{
	int 	i;

	i = 0;
	while (i < 3)
	{
		vm->camera.t[3 + 4 * i] += 0.4f * vm->camera.t[4 * i];
		i++;
	}
//	vm->camera.t[3 + 4 * 0] -= 0.4f;
}

void		cam_trans_left(void *data, t_gr_vm *vm, t_key *key)
{
	int 	i;

	i = 0;
	while (i < 3)
	{
		vm->camera.t[3 + 4 * i] -= 0.4f * vm->camera.t[4 * i];
		i++;
	}
//	vm->camera.t[3 + 4 * 0] += 0.4f;
}