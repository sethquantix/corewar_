/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_objects.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 05:39:28 by cchaumar          #+#    #+#             */
/*   Updated: 2017/02/26 05:09:25 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_handler.h"

/* TODO
** I need a way to properly do this. I wanna be able to instantiate buffer
** relatively to vao (make sense, i guess), with type argument, and fill it
** I want this to be flexible and generic, so I guess I depend on knowing
** what's must have and what's not. maybe keep a reference to the buffer with
** different parameters ? dunno what to do here
*/

// GLuint	create_buffer(GLuint vao, GLuint type)
// {
// 	GLuint	id;
//
// 	glBindVertexArray(vao);
// 	glGenBuffers(1, &id);
// 	glBindBuffer(type, id);
// 	glBindVertexArray(0);
// 	return (id);
// }

static void	release_shaders(GLuint program, int count, t_gl_shader *shaders)
{
	int		i;

	i = 0;
	while (i < count)
	{
		glDetachShader(program, shaders[i].id);
		glDeleteShader(shaders[i].id);
		i++;
	}
}

static GLuint	gl_link_info(GLuint program)
{
	int		success;
	char	*log_info;
	GLint	size;

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &size);
		log_info = try(size + 1);
		glGetProgramInfoLog(program, size, NULL, log_info);
		ft_printf("Error linking program\n%s", log_info);
		free(log_info);
		return (0);
	}
	ft_printf("compiled !\n");
	return (program);
}

void			validate(GLuint program)
{
	char	*log_info;
	GLint	size;

	glValidateProgram(program);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &size);
	log_info = try(size + 1);
	glGetProgramInfoLog(program, size, NULL, log_info);
	ft_printf("program validation :\n%s", log_info);
	free(log_info);
}

GLuint			create_program(int shader_count, t_gl_shader *shaders)
{
	GLuint	program;
	int		i;
	int		success;

	i = 0;
	program = glCreateProgram();
	while (i < shader_count)
	{
		success = compile_shader(&shaders[i]);
		if (!success)
		{
			release_shaders(program, i, shaders);
			glDeleteProgram(program);
			return (0);
		}
		glAttachShader(program, shaders[i].id);
		i++;
	}
	glLinkProgram(program);
	release_shaders(program, shader_count, shaders);
	return (gl_link_info(program));
}
