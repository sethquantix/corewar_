#include "corewar.h"
#include "gr_vm_internals.h"

void		cam_trans_forwad(void *data, t_gr_vm *vm, t_key *key)
{
	vm->camera.t[3 + 4 * 2] += 0.1f;
}

void		cam_trans_back(void *data, t_gr_vm *vm, t_key *key)
{
	vm->camera.t[3 + 4 * 2] -= 0.1f;
}

void		cam_trans_right(void *data, t_gr_vm *vm, t_key *key)
{
	vm->camera.t[3 + 4 * 0] -= 0.1f;
}

void		cam_trans_left(void *data, t_gr_vm *vm, t_key *key)
{
	vm->camera.t[3 + 4 * 0] += 0.1f;
}
