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

#include <corewar.h>
#include <gr_vm_internals.h>

static void		update_values(t_gr_vm *cxt, t_arena *a, t_proc *current,
	uint32_t values[])
{
	int				i;

	i = 0;
	while (i < MEM_SIZE)
	{
		a->mem[i] &= 0xFFFF00FF;
		(current && current->pc == i) ? a->mem[i] |= 0x100 : 0;
		values[i] = a->arena[i];
		cxt->scale[i] = 1 + 4 * (float)a->arena[i] / 255.0;
		cxt->model[i][7] += (cxt->scale[i] - cxt->model[i][7]) / TIME_TRAVEL;
		i++;
	}
	if (cxt->cursor.proc != PROC_ALL || cxt->cursor.player < 0)
		return ;
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
	static uint32_t	values[MEM_SIZE];
	t_proc			*p;

	p = NULL;
	(cxt->cursor.proc >= 0) ? p = a->procs[cxt->cursor.proc] : 0;
	update_values(cxt, a, p, values);
	glBindVertexArray(cxt->vao);
	glBindBuffer(GL_ARRAY_BUFFER, cxt->mat_vbo);
	glBufferData(GL_ARRAY_BUFFER,
		MEM_SIZE * 9 * sizeof(float), cxt->model, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, cxt->val_vbo);
	glBufferData(GL_ARRAY_BUFFER,
		MEM_SIZE * sizeof(uint32_t), a->mem, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, cxt->arena_vbo);
	glBufferData(GL_ARRAY_BUFFER,
		MEM_SIZE * sizeof(uint32_t), values, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
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
