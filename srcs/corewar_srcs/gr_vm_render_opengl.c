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
		cxt->values[i] = a->arena[i];
		i++;
	}
	glBindVertexArray(cxt->vao);
	glBindBuffer(GL_ARRAY_BUFFER, cxt->matVBO);
	glBufferData(GL_ARRAY_BUFFER, MEM_SIZE * 9 * sizeof(float), cxt->model, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, cxt->valVBO);
	glBufferData(GL_ARRAY_BUFFER, MEM_SIZE * sizeof(uint32_t), a->mem, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, cxt->arenaVBO);
	glBufferData(GL_ARRAY_BUFFER, MEM_SIZE * sizeof(uint32_t), cxt->values, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void		move_pix(t_gr_vm *cxt, t_vec4 dest)
{
	t_vec4	k;
	float 	r1;
	float 	r2;

	k.x = fabs(fmod(cxt->pixie.x, 2.3)) - 0.5;
	k.y = 0;
	k.z = fabs(fmod(cxt->pixie.z, 2.3)) - 0.5;
	v_norm(k);
	r1 = (float)rand() / (float)RAND_MAX;
	r2 = (float)rand() / (float)RAND_MAX;
	cxt->pv = v_add(cxt->pv, v_mult_k(v_add(
		v_mult_k(k, r1), v_mult_k(v_sub(dest, cxt->pixie), r2)), 0.01));
	cxt->pixie = v_add(cxt->pixie, v_mult_k(cxt->pv, 0.01));
}

void			pixie(t_gr_vm *cxt)
{
	static t_vec4	dest = {1.15, 0.5, 1.15};
	const t_vec4	dir[] = { {-1, 0, 0, 0}, {1, 0, 0, 0},
							  {0, 0, -1, 0}, {0, 0, 1, 0}};
	static int 		d = 0;

	if ((rand() % 100) > 90)
	{
		if (rand() % 2)
			d = rand() % 4;
		dest = v_add(dest, v_mult_k(dir[d], 2.3));
		printf("%f %f %f\n", dest.x, dest.y, dest.z);
	}
	move_pix(cxt, dest);
	printf("%f %f %f\n", cxt->pixie.x, cxt->pixie.y, cxt->pixie.z);
}

static void		push_uniform(t_gr_vm *cxt)
{
	static int 		time = 0;
	static int 		ltime = 0;
	static int		rtime = 0;
	GLint			loc;
	GLfloat			mat[16];

	glBindVertexArray(cxt->vao);
 	if (!rtime)
		rtime = SDL_GetTicks();
	if (!time)
		time = rtime;
	ltime += cxt->opts & ROTATING ? SDL_GetTicks() - rtime : 0;
	rtime = SDL_GetTicks();
	loc = glGetUniformLocation(cxt->program, "V");
	glUniformMatrix4fv(loc, 1, GL_FALSE, cxt->camera.m.t);
	loc = glGetUniformLocation(cxt->program, "P");
	load_projection(mat, 1, 10000, 1.3);
	glUniformMatrix4fv(loc, 1, GL_FALSE, mat);
	loc = glGetUniformLocation(cxt->program, "textNoise");
	glUniform1i(loc, cxt->diffuseTexture);
	loc = glGetUniformLocation(cxt->program, "font");
	glUniform1i(loc, cxt->glyphs);
	loc = glGetUniformLocation(cxt->program, "in_time");
	glUniform1f(loc, (SDL_GetTicks() - time) / 1000.0f);
	loc = glGetUniformLocation(cxt->program, "time");
	glUniform1f(loc, ltime / 1000.0f);
	loc = glGetUniformLocation(cxt->program, "opts");
	glUniform1i(loc, cxt->opts);
	pixie(cxt);
	loc = glGetUniformLocation(cxt->program, "L1");
	glUniform3f(loc, cxt->pixie.x, cxt->pixie.y, cxt->pixie.z);
}

static void		push_box_uni(t_gr_vm *cxt)
{
	GLint			loc;
	GLfloat			mat[16];

	loc = glGetUniformLocation(cxt->program_box, "V");
	glUniformMatrix4fv(loc, 1, GL_FALSE, cxt->camera.m.t);
	loc = glGetUniformLocation(cxt->program_box, "P");
	load_projection(mat, 1, 10000, 1.3);
	glUniformMatrix4fv(loc, 1, GL_FALSE, mat);
	loc = glGetUniformLocation(cxt->program_box, "L1");
	glUniform3f(loc, cxt->pixie.x, cxt->pixie.y, cxt->pixie.z);
}

void			render_opengl(t_gr_vm *cxt, t_arena *arena)
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	stream_transform(cxt, arena);
	glUseProgram(cxt->program);
	push_uniform(cxt);
	glDrawArraysInstanced(GL_TRIANGLES, 0, 36, MEM_SIZE);
	glBindVertexArray(cxt->vao_box);
	glUseProgram(cxt->program_box);
	push_box_uni(cxt);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	SDL_GL_SwapWindow(cxt->arena);
}
