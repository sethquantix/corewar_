#include "corewar.h"
#include "gr_vm_internals.h"

static void		stream_transform(t_gr_vm *cxt)
{
	int			i;

	i = 0;
	while (i < MEM_SIZE)
	{
		//cxt->model[i][1] += (((float)rand() / RAND_MAX) - 0.5f) * 0.5;
		i++;
	}
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
	glUniformMatrix4fv(loc, 1, GL_FALSE, cxt->camera.t);
	loc = glGetUniformLocation(cxt->program, "P");
	load_projection(mat, 1, 1000, 1.3);
	glUniformMatrix4fv(loc, 1, GL_FALSE, mat);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, cxt->diffuseTexture);
}

void			render_opengl(t_gr_vm *cxt, t_arena arena)
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	stream_transform(cxt);
	glUseProgram(cxt->program);
	push_uniform(cxt);
	glDrawArraysInstanced(GL_TRIANGLES, 0, 36, MEM_SIZE);
	SDL_GL_SwapWindow(cxt->arena);
}
