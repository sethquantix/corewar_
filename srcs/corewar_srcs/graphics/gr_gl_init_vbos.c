/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gr_gl_init_vbos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/04 08:43:48 by cchaumar          #+#    #+#             */
/*   Updated: 2017/08/04 08:43:49 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>
#include <gr_vm_internals.h>

GLuint		init_instancing(void)
{
	GLuint instance_vbo;

	glGenBuffers(1, &instance_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, instance_vbo);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE,
		9 * sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribDivisor(4, 1);
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 3, GL_FLOAT,
		GL_FALSE, 9 * sizeof(GLfloat), (void*)(sizeof(GLfloat) * 3));
	glVertexAttribDivisor(5, 1);
	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 3, GL_FLOAT,
		GL_FALSE, 9 * sizeof(GLfloat), (void*)(sizeof(GLfloat) * 6));
	glVertexAttribDivisor(6, 1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return (instance_vbo);
}

GLuint		init_transfer(void)
{
	GLuint	transfer_vbo;

	glGenBuffers(1, &transfer_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, transfer_vbo);
	glEnableVertexAttribArray(7);
	glVertexAttribIPointer(7, 1, GL_UNSIGNED_INT, sizeof(GLuint), (void *)(0));
	glVertexAttribDivisor(7, 1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return (transfer_vbo);
}

GLuint		init_values(void)
{
	GLuint	val_vbo;

	glGenBuffers(1, &val_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, val_vbo);
	glEnableVertexAttribArray(8);
	glVertexAttribIPointer(8, 1, GL_UNSIGNED_INT, sizeof(GLuint), (void *)(0));
	glVertexAttribDivisor(8, 1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return (val_vbo);
}

void		init_pos(t_gr_vm *cxt)
{
	uint i;

	i = 0;
	while (i < MEM_SIZE)
	{
		cxt->model[i][0] = (float)((i % (int)sqrt(MEM_SIZE) -
			(sqrt(MEM_SIZE)) / 2) * 2.3);
		cxt->model[i][1] = 0;
		cxt->model[i][2] = (float)((i / (int)sqrt(MEM_SIZE) -
			(sqrt(MEM_SIZE)) / 2) * 2.3);
		cxt->model[i][6] = 1;
		cxt->model[i][7] = 1;
		cxt->model[i][8] = 1;
		cxt->scale[i] = 1;
		i++;
	}
}
