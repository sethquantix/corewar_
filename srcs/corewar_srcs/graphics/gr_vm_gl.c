/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gr_vm_gl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 07:05:10 by cchaumar          #+#    #+#             */
/*   Updated: 2017/06/14 07:05:10 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gr_vm_internals.h>

static GLuint	build_program(const char *vs, const char *fs)
{
	t_gl_shader	shaders[2];
	GLuint		program;

	shaders[0].file = ft_strdup(vs);
	shaders[0].type = GL_VERTEX_SHADER;
	shaders[1].file = ft_strdup(fs);
	shaders[1].type = GL_FRAGMENT_SHADER;
	program = create_program(2, shaders);
	free(shaders[0].file);
	free(shaders[1].file);
	return (program);
}

void			init_gl(t_gr_vm *cxt, t_cam *cam)
{
	const char	*shaders[][2] = {
		{"assets/shaders/vertex.shader", "assets/shaders/frag.shader"},
		{"assets/shaders/vertex_board.shader",
		"assets/shaders/frag_board.shader"}};

	glewInit();
	cxt->program = build_program(shaders[0][0], shaders[0][1]);
	cxt->program_board = build_program(shaders[1][0], shaders[1][1]);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0, 0, 0, 1);
	cam->pos = vec4(0, -10, -100, 0);
	mat_ident(&cam->m);
	cam->m.r[0].w = cam->pos.x;
	cam->m.r[1].w = cam->pos.y;
	cam->m.r[2].w = cam->pos.z;
	cam->x = 0;
	cam->y = 0;
}
