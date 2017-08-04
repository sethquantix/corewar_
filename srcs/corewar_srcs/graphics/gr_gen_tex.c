/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gr_gen_tex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 07:35:36 by cchaumar          #+#    #+#             */
/*   Updated: 2017/05/29 11:40:30 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gr_vm.h"
#include "gr_vm_internals.h"

static void	add_tex(TTF_Font *font, int v, SDL_Surface **buff)
{
	const char 		text[17] = "0123456789ABCDEF";
	const SDL_Color	color = {255, 255, 255, 255};

	buff[v] = TTF_RenderGlyph_Blended(font, text[v], color);
}

static void	gen_glyphs(const char *font_name, SDL_Surface ***buff)
{
	TTF_Font	*font;
	int 		i;

	*buff = try(sizeof(SDL_Surface *) * 16);
	if (TTF_Init() == -1)
		exit(EXIT_FAILURE);
	font = TTF_OpenFont(font_name, 42);
	i = 0;
	while (i <= 0xF)
		add_tex(font, i++, *buff);
	TTF_Quit();
}

static void	fill(int pad, SDL_Surface *buff, uint32_t *tex)
{
	int	w;
	int h;

	h = 0;
	while (h < buff->h)
	{
		w = 0;
		while (w < buff->w)
		{
			tex[(6 + h) * 64 + pad + w] =
				((int *)buff->pixels)[h * buff->w + w];
			w++;
		}
		h++;
	}
}

static void	assemble(SDL_Surface **buff, int l, int r, uint32_t *tex)
{
	int		pad;

	pad = (64 - (buff[l]->w + buff[r]->w + 5)) / 2;
	fill(pad, buff[l], tex);
	pad += buff[l]->w + 5;
	fill(pad, buff[r], tex);
}

static void	clear_surfaces(SDL_Surface **buff)
{
	int 	i;

	i = 0;
	while (i < 16)
		SDL_FreeSurface(buff[i++]);
	free(buff);
}

GLuint		gen_texture(const char *font_file)
{
	GLuint 		tex_array;
	SDL_Surface **buff;
	uint32_t 	tex[64 * 64];
	int 		i;

	glActiveTexture(GL_TEXTURE2);
	glGenTextures(1, &tex_array);
	glBindTexture(GL_TEXTURE_2D_ARRAY, tex_array);
	glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
	glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA8, 64, 64, 256);
	gen_glyphs(font_file, &buff);
	i = 0;
	while (i <= 0xff)
	{
		ft_bzero(tex, 64 * 64 * sizeof(int));
		assemble(buff, i >> 4, i & 0xF, tex);
		glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i++,
			64, 64, 1, GL_RGBA, GL_UNSIGNED_BYTE, tex);
	}
	clear_surfaces(buff);
	return (tex_array);
}
