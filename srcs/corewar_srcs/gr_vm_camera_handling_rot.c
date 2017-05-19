#include "corewar.h"
#include "gr_vm_internals.h"

void		toggle_42(void *data, t_gr_vm *vm, t_key *key)
{
	vm->anim42 = !vm->anim42;
}

