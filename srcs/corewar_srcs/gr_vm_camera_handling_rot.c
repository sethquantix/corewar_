#include "corewar.h"
#include "gr_vm_internals.h"

void		toggle_42(void *data, t_gr_vm *vm, t_key *key)
{
	vm->anim42 = !vm->anim42;
}

void		rotate(t_gr_vm *vm, int relx, int rely)
{
	t_mat	x;
	t_mat	y;

	vm->camera.x += relx;
	vm->camera.y += rely;
	mat_ident(&x);
	x.r[0].x = cos(-ROT * M_PI * (float)vm->camera.x / 180.0);
	x.r[2].z = cos(-ROT * M_PI * (float)vm->camera.x / 180.0);
	x.r[2].x = -sin(-ROT * M_PI * (float)vm->camera.x / 180.0);
	x.r[0].z = sin(-ROT * M_PI * (float)vm->camera.x / 180.0);
	mat_ident(&y);
	y.r[1].y = cos(-ROT * M_PI * (float)vm->camera.y / 180.0);
	y.r[1].z = -sin(-ROT * M_PI * (float)vm->camera.y / 180.0);
	y.r[2].y = sin(-ROT * M_PI * (float)vm->camera.y / 180.0);
	y.r[2].z = cos(-ROT * M_PI * (float)vm->camera.y / 180.0);
	x = mat_mult_mat(x, y);
	x.r[0].w = vm->camera.m.r[0].w;
	x.r[1].w = vm->camera.m.r[1].w;
	x.r[2].w = vm->camera.m.r[2].w;
	vm->camera.m = x;
}
