/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gr_vm_render_opengl.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 06:02:02 by tsedigi           #+#    #+#             */
/*   Updated: 2017/08/01 06:02:03 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "gr_vm_internals.h"

static void		set_procs(t_gr_vm *cxt, t_arena *a)
{
	int		i;

	i = 0;
	while (i < a->proc_count)
	{
		if (a->procs[i]->player == -a->champs[cxt->cursor.player].id - 1)
			a->mem[a->procs[i]->pc] |= 0x100;
		i++;
	}
}

static void		stream_transform(t_gr_vm *cxt, t_arena *a)
{
	static uint32_t		values[MEM_SIZE];
	int					i;
	t_proc				*p;

	p = NULL;
	(cxt->cursor.proc >= 0) ? p = a->procs[cxt->cursor.proc] : 0;
	i = 0;
	while (i < MEM_SIZE)
	{
		a->mem[i] &= 0xFFFF00FF;
		(p && p->pc == i) ? a->mem[i] |= 0x100 : 0;
		values[i] = a->arena[i];
		cxt->scale[i] = 1 + 4 * (float)a->arena[i] / 255.0;
		cxt->model[i][7] += (cxt->scale[i] - cxt->model[i][7]) / TIME_TRAVEL;
		i++;
	}
	if (cxt->cursor.proc == PROC_ALL && cxt->cursor.player >= 0)
		set_procs(cxt, a);
	glBindVertexArray(cxt->vao);
	glBindBuffer(GL_ARRAY_BUFFER, cxt->matVBO);
	glBufferData(GL_ARRAY_BUFFER,
		MEM_SIZE * 9 * sizeof(float), cxt->model, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, cxt->valVBO);
	glBufferData(GL_ARRAY_BUFFER,
		MEM_SIZE * sizeof(uint32_t), a->mem, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, cxt->arenaVBO);
	glBufferData(GL_ARRAY_BUFFER,
		MEM_SIZE * sizeof(uint32_t), values, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void			uniform_vec4(GLuint location, t_vec4 v)
{
	glUniform4f(location, v.x, v.y, v.z, v.w);
}

static void		push_mats(GLuint program, t_gr_vm *cxt)
{
	GLfloat		mat[16];
	int 		loc;

	loc = glGetUniformLocation(program, "V");
	glUniformMatrix4fv(loc, 1, GL_FALSE, cxt->camera.m.t);
	loc = glGetUniformLocation(program, "P");
	load_projection(mat, 1, 10000, 1.3);
	glUniformMatrix4fv(loc, 1, GL_FALSE, mat);
}

static void		push_uniform(t_gr_vm *cxt)
{
	static int 		ltime = 0;
	static int		rtime = 0;
	GLint			loc;

	glBindVertexArray(cxt->vao);
 	if (!rtime)
		rtime = SDL_GetTicks();
	ltime += cxt->opts & OPT_ROTATION ? SDL_GetTicks() - rtime : 0;
	rtime = SDL_GetTicks();
	push_mats(cxt->program, cxt);
	loc = glGetUniformLocation(cxt->program, "textNoise");
	glUniform1i(loc, cxt->diffuseTexture);
	loc = glGetUniformLocation(cxt->program, "font");
	glUniform1i(loc, cxt->glyphs);
	loc = glGetUniformLocation(cxt->program, "in_time");
	glUniform1f(loc, (SDL_GetTicks() - cxt->time) / 1000.0f);
	loc = glGetUniformLocation(cxt->program, "time");
	glUniform1f(loc, ltime / 1000.0f);
	loc = glGetUniformLocation(cxt->program, "opts");
	glUniform1i(loc, cxt->opts);
}

static void		push_board_uni(t_gr_vm *cxt)
{
	GLint			loc;

	push_mats(cxt->program_board, cxt);
	loc = glGetUniformLocation(cxt->program, "res");
	glUniform2f(loc, (float)WIN_WIDTH, (float)WIN_HEIGHT);
	loc = glGetUniformLocation(cxt->program_board, "board");
	glUniform1i(loc, cxt->board);
	loc = glGetUniformLocation(cxt->program_board, "texNoise");
	glUniform1i(loc, cxt->diffuseTexture);
	loc = glGetUniformLocation(cxt->program_board, "_time");
	glUniform1f(loc, (SDL_GetTicks() - cxt->time) / 1000.0f);
	loc = glGetUniformLocation(cxt->program_board, "cursor_pos");
	glUniform1i(loc, cxt->cursor.pos);
	loc = glGetUniformLocation(cxt->program_board, "player_box_pos");
	uniform_vec4
(loc, cxt->cursor.player_box);
	loc = glGetUniformLocation(cxt->program_board, "proc_box_pos");
	uniform_vec4
(loc, cxt->cursor.proc_box);
	loc = glGetUniformLocation(cxt->program_board, "proc_reg_pos");
	uniform_vec4
(loc, cxt->cursor.reg_box);
}

void			render_opengl(t_gr_vm *cxt, t_arena *arena)
{
	draw_ui(cxt, arena);
	if (!cxt->time)
		cxt->time = SDL_GetTicks();
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glBindVertexArray(cxt->vao);
	stream_transform(cxt, arena);
	glUseProgram(cxt->program);
	push_uniform(cxt);
	glDrawArraysInstanced(GL_TRIANGLES, 0, 36, MEM_SIZE);
	glBindVertexArray(cxt->vao_board);
	glUseProgram(cxt->program_board);
	push_board_uni(cxt);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	SDL_GL_SwapWindow(cxt->arena);
}
