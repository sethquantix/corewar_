/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gr_gl_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 13:02:56 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/01 13:02:57 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	glerror(int i)
{
	GLenum err;
	while((err = glGetError()) != GL_NO_ERROR)
	{
		ft_printf("%d : gl error : %#x\n", i, err);
	}
}

void CHECK_FRAMEBUFFER_STATUS()
{
	GLenum status;
	status = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER); 
	switch(status) {
	case GL_FRAMEBUFFER_COMPLETE:
		ft_printf("framebuffer complete\n");
		break;
	case GL_FRAMEBUFFER_UNSUPPORTED:
		break;
	default:
		exit(-1);
	}
}

GLuint	createGLBuffer(int w, int h, GLuint *color, GLuint *depth)
{
	GLuint	buffer;

	glGenFramebuffers(1, &buffer);
	glBindFramebuffer(GL_FRAMEBUFFER, buffer);
	glGenTextures(1, color);
	glGenRenderbuffers(1, depth);
	glBindTexture(GL_TEXTURE_2D, *color);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE,
		NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
		GL_TEXTURE_2D, *color, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, *depth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, w, h);
	glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
		GL_RENDERBUFFER, *depth);
	CHECK_FRAMEBUFFER_STATUS();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	ft_printf("framebuffer : %d\n", buffer);
	return (buffer);
}

void	renderGLBuffer(GLuint buffer, GLuint color, int w, int h)
{
	glBindTexture(GL_TEXTURE_2D, color);
	glActiveTexture(GL_TEXTURE0);
	glBindFramebuffer(GL_FRAMEBUFFER, buffer);
	glViewport(0, 0, w, h);
	glClearColor(0.0f,1.0f,0.0f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void	readColor(GLuint buffer, int w, int h, void *p)
{
	ft_printf("reading from : %d\n", buffer);
	glBindFramebuffer(GL_FRAMEBUFFER, buffer);
	glReadPixels(0, 0, w, h, GL_RGBA, GL_UNSIGNED_BYTE, p);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
