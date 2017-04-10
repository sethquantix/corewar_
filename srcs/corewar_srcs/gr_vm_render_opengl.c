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
	GLuint		loc;
	GLfloat		mat[16];

	loc = glGetUniformLocation(cxt->program, "V");
	load_identity(mat);
	glUniformMatrix4fv(loc, 1, GL_FALSE, mat);
	loc = glGetUniformLocation(cxt->program, "P");
	load_projection(mat, 0.001, 100, 1);
	glUniformMatrix4fv(loc, 1, GL_FALSE, mat);
}

void			render_opengl(t_gr_vm *cxt)
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	stream_transform(cxt);
	glUseProgram(cxt->program);
	push_uniform(cxt);
	glDrawArraysInstanced(GL_TRIANGLES, 0, 36, MEM_SIZE);
	SDL_GL_SwapWindow(cxt->arena);
	if (glGetError())
	{
		printf("Opengl error: %d\n", glGetError());
		exit(0);
	}
}
