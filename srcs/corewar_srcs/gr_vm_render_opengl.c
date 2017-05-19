#include "corewar.h"
#include "gr_vm_internals.h"

static void		stream_transform(t_gr_vm *cxt)
{
	int			i;
	static long e = 0;

	i = 0;
	float t = (float)(e++);
	while (i < MEM_SIZE)
	{
//        int change = (int)(10 * (float)rand() / RAND_MAX);
//		if (change > 8)
//            cxt->scale[i] = 1 + 10 * (float)rand() / RAND_MAX;
		cxt->scale[i] = 5 + 4 * sin(0.05 * (t - (float)i) / M_2_PI);
//		cxt->model[i][1] = 5 + 4 * sin(0.01 * (t - (float)i) / M_2_PI);
        cxt->model[i][7] += (cxt->scale[i] - cxt->model[i][7]) / (60 * TIME_TRAVEL);
		i++;
	}
	glBindVertexArray(cxt->vao);
	glBindBuffer(GL_ARRAY_BUFFER, cxt->matVBO);
	glBufferData(GL_ARRAY_BUFFER, MEM_SIZE * 9 * sizeof(float), cxt->model, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

static void		push_uniform(t_gr_vm *cxt)
{
	GLint			loc;
	GLfloat			mat[16];
	GLfloat			t[4];
	static float	light[MEM_SIZE * 4];

	loc = glGetUniformLocation(cxt->program, "textDiffuse");
	glUniform1i(loc, 0);
	loc = glGetUniformLocation(cxt->program, "textLight");
	glUniform1i(loc, 1);
	loc = glGetUniformLocation(cxt->program, "CamPos");
	ft_memcpy(t, &cxt->camera.pos, 16);
	glUniform4fv(loc, 4, t);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, cxt->diffuseTexture);
	load_light(light, light, cxt->model, cxt);
	if (cxt->lightText != 0)
		glDeleteTextures(1, &cxt->lightText);
	cxt->lightText = light_to_texture(light);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, cxt->lightText);
	loc = glGetUniformLocation(cxt->program, "P");
	load_projection(mat, 1, 1000, 1.3);
//	up = v_cross(cxt->camera.fw, cxt->camera.lt);
//	gluLookAt(cxt->camera.pos.x, cxt->camera.pos.y, cxt->camera.pos.z,
//		cxt->camera.fw.x, cxt->camera.fw.y, cxt->camera.fw.z,
//		up.x, up.y, up.z);
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
