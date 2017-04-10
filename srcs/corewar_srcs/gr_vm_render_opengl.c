#include "corewar.h"
#include "gr_vm_internals.h"

static void		stream_transform(t_gr_vm *cxt)
{
	int			i;

	i = 0;
	glBindVertexArray(cxt->vao);
	glBindBuffer(GL_ARRAY_BUFFER, cxt->matVBO);
	glBufferData(GL_ARRAY_BUFFER, MEM_SIZE * 6 * sizeof(float), cxt->model, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

static void		push_uniform(t_gr_vm *cxt)
{

}

void			render_opengl(t_gr_vm *cxt)
{
	stream_transform(cxt);
	glUseProgram(cxt->program);
	push_uniform(cxt);
	glDrawArraysInstanced(GL_TRIANGLES, 0, 36, MEM_SIZE);
	printf("%d\n", glGetError());
//	exit(0);
}
