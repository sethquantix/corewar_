/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gr_vm_init_cube.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 05:41:36 by tsedigi           #+#    #+#             */
/*   Updated: 2017/08/01 05:41:37 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>
#include <gr_vm_internals.h>

static const float g_cube[] = {
	-0.5, 0, 0.5, 0, -1, 0, 0, 1,
	0.5, 0, 0.5, 0, -1, 0, 1, 1,
	0.5, 0, -0.5, 0, -1, 0, 1, 0,
	0.5, 0, -0.5, 0, -1, 0, 1, 0,
	-0.5, 0, -0.5, 0, -1, 0, 0, 0,
	-0.5, 0, 0.5, 0, -1, 0, 0, 1,

	-0.5, 1, 0.5, 0, 1, 0, 0, 1,
	0.5, 1, 0.5, 0, 1, 0, 1, 1,
	0.5, 1, -0.5, 0, 1, 0, 1, 0,
	0.5, 1, -0.5, 0, 1, 0, 1, 0,
	-0.5, 1, -0.5, 0, 1, 0, 0, 0,
	-0.5, 1, 0.5, 0, 1, 0, 0, 1,

	-0.5, 0, 0.5, -1, 0, 0, 0, 1,
	-0.5, 0, -0.5, -1, 0, 0, 1, 1,
	-0.5, 1, -0.5, -1, 0, 0, 1, 0,
	-0.5, 1, -0.5, -1, 0, 0, 1, 0,
	-0.5, 1, 0.5, -1, 0, 0, 0, 0,
	-0.5, 0, 0.5, -1, 0, 0, 0, 1,

	0.5, 0, 0.5, 1, 0, 0, 0, 1,
	0.5, 0, -0.5, 1, 0, 0, 1, 1,
	0.5, 1, -0.5, 1, 0, 0, 1, 0,
	0.5, 1, -0.5, 1, 0, 0, 1, 0,
	0.5, 1, 0.5, 1, 0, 0, 0, 0,
	0.5, 0, 0.5, 1, 0, 0, 0, 1,

	0.5, 0, -0.5, 0, 0, -1, 0, 1,
	-0.5, 0, -0.5, 0, 0, -1, 1, 1,
	-0.5, 1, -0.5, 0, 0, -1, 1, 0,
	-0.5, 1, -0.5, 0, 0, -1, 1, 0,
	0.5, 1, -0.5, 0, 0, -1, 0, 0,
	0.5, 0, -0.5, 0, 0, -1, 0, 1,

	0.5, 0, 0.5, 0, 0, 1, 0, 1,
	-0.5, 0, 0.5, 0, 0, 1, 1, 1,
	-0.5, 1, 0.5, 0, 0, 1, 1, 0,
	-0.5, 1, 0.5, 0, 0, 1, 1, 0,
	0.5, 1, 0.5, 0, 0, 1, 0, 0,
	0.5, 0, 0.5, 0, 0, 1, 0, 1
};

static float g_board[] = {
	-71.3, 12, -128, 0, 1,
	-71.3, 0, -128, 0, 0,
	71.3, 0, -128, 1, 0,
	71.3, 0, -128, 1, 0,
	71.3, 12, -128, 1, 1,
	-71.3, 12, -128, 0, 1
};

static const int g_faces[] = {
	F_DOWN,
	F_DOWN,
	F_DOWN,
	F_DOWN,
	F_DOWN,
	F_DOWN,
	F_UP,
	F_UP,
	F_UP,
	F_UP,
	F_UP,
	F_UP,
	F_LEFT,
	F_LEFT,
	F_LEFT,
	F_LEFT,
	F_LEFT,
	F_LEFT,
	F_RIGHT,
	F_RIGHT,
	F_RIGHT,
	F_RIGHT,
	F_RIGHT,
	F_RIGHT,
	F_BACK,
	F_BACK,
	F_BACK,
	F_BACK,
	F_BACK,
	F_BACK,
	F_FRONT,
	F_FRONT,
	F_FRONT,
	F_FRONT,
	F_FRONT,
	F_FRONT
};

static uint32_t		create_vbo_vnt(float *vertices, int *faces,
	uint32_t vertex_size, GLuint vao_id)
{
	GLuint	vertex_buffer_id;
	GLuint	faces_buffer_id;

	glBindVertexArray(vao_id);
	glGenBuffers(1, &(vertex_buffer_id));
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
	glBufferData(GL_ARRAY_BUFFER,
		vertex_size * sizeof(float) * 8, &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
		sizeof(float) * 8, (void *)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
		sizeof(float) * 8, (void *)(sizeof(float) * 3));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
		sizeof(float) * 8, (void *)(sizeof(float) * 6));
	glGenBuffers(1, &faces_buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, faces_buffer_id);
	glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(int), faces, GL_STATIC_DRAW);
	glEnableVertexAttribArray(3);
	glVertexAttribIPointer(3, 1, GL_INT, sizeof(GLint), (void *)0);
	return (vertex_buffer_id);
}

static void			gen_board(t_gr_vm *cxt)
{
	GLuint	vbo;
	int		i;
	float	h;

	h = (g_board[10] - g_board[0]) / (float)WIN_WIDTH * (float)WIN_HEIGHT;
	i = -1;
	while (++i < 6)
	{
		if (g_board[5 * i + 1] == 0)
			g_board[5 * i + 1] = 12 + h;
	}
	glGenVertexArrays(1, &cxt->vao_board);
	glBindVertexArray(cxt->vao_board);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER,
		6 * sizeof(float) * 5, &g_board[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
		sizeof(float) * 5, (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
		sizeof(float) * 5, (void*)(sizeof(float) * 3));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

GLuint				generate_cube(t_gr_vm *cxt)
{
	GLuint		vao;

	glGenVertexArrays(1, &vao);
	create_vbo_vnt((float *)g_cube, (int *)g_faces,
		sizeof(g_cube) / sizeof(float) / 8, vao);
	cxt->vao = vao;
	cxt->mat_vbo = init_instancing();
	cxt->val_vbo = init_transfer();
	cxt->arena_vbo = init_values();
	init_pos(cxt);
	gen_board(cxt);
	return (vao);
}
