/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gr_gl_update.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/04 07:28:01 by cchaumar          #+#    #+#             */
/*   Updated: 2017/08/04 07:28:01 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>
#include <gr_vm_internals.h>

static void	uniform_vec4(GLuint location, t_vec4 v)
{
	glUniform4f(location, v.x, v.y, v.z, v.w);
}

static void	push_mats(GLuint program, t_gr_vm *cxt)
{
	GLfloat		mat[16];
	int			loc;

	loc = glGetUniformLocation(program, "V");
	glUniformMatrix4fv(loc, 1, GL_FALSE, cxt->camera.m.t);
	loc = glGetUniformLocation(program, "P");
	load_projection(mat, 1, 10000, 1.3);
	glUniformMatrix4fv(loc, 1, GL_FALSE, mat);
}

void		push_uniform(t_gr_vm *cxt)
{
	static int		ltime = 0;
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

void		push_board_uni(t_gr_vm *cxt)
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
	uniform_vec4(loc, cxt->cursor.player_box);
	loc = glGetUniformLocation(cxt->program_board, "proc_box_pos");
	uniform_vec4(loc, cxt->cursor.proc_box);
	loc = glGetUniformLocation(cxt->program_board, "proc_reg_pos");
	uniform_vec4(loc, cxt->cursor.reg_box);
}
