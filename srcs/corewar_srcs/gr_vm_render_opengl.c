#include "corewar.h"
#include "gr_vm_internals.h"

static void		stream_transform(t_gr_vm *cxt, t_arena *a)
{
	int			i;

	i = 0;
	while (i < MEM_SIZE)
	{
		cxt->scale[i] = 1 + 4 * (float)a->arena[i] / 255.0;
        cxt->model[i][7] += (cxt->scale[i] - cxt->model[i][7]) / TIME_TRAVEL;
		i++;
	}
	glBindVertexArray(cxt->vao);
	glBindBuffer(GL_ARRAY_BUFFER, cxt->matVBO);
	glBufferData(GL_ARRAY_BUFFER, MEM_SIZE * 9 * sizeof(float), cxt->model, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, cxt->valVBO);
	glBufferData(GL_ARRAY_BUFFER, MEM_SIZE * sizeof(uint32_t), a->mem, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

static void		push_uniform(t_gr_vm *cxt)
{
	static int 		time = 0;
	GLint			loc;
	GLfloat			mat[16];
	static float	light[MEM_SIZE * 4];

	if (!time)
		time = SDL_GetTicks();
	loc = glGetUniformLocation(cxt->program, "V");
	glUniformMatrix4fv(loc, 1, GL_FALSE, cxt->camera.m.t);
	loc = glGetUniformLocation(cxt->program, "P");
	load_projection(mat, 1, 1000, 1.3);
	glUniformMatrix4fv(loc, 1, GL_FALSE, mat);
	loc = glGetUniformLocation(cxt->program, "textNoise");
	glUniform1i(loc, cxt->diffuseTexture);
	loc = glGetUniformLocation(cxt->program, "in_time");
	glUniform1f(loc, (SDL_GetTicks() - time) / 1000.0f);
}

void			render_opengl(t_gr_vm *cxt, t_arena *arena)
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	stream_transform(cxt, arena);
	glUseProgram(cxt->program);
	push_uniform(cxt);
	glDrawArraysInstanced(GL_TRIANGLES, 0, 36, MEM_SIZE);
	SDL_GL_SwapWindow(cxt->arena);
}
