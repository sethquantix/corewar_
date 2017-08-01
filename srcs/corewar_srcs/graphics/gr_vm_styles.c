/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gr_vm_styles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 09:46:43 by cchaumar          #+#    #+#             */
/*   Updated: 2017/08/01 08:01:04 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gr_vm_internals.h"

void	add_style(t_text_p *sst, t_style style)
{
	ft_pushback((void **)&sst->styles, sizeof(t_style), sst->nstyle++, &style);
}

static t_style		style(SDL_Color c, const char *font, int size)
{
	TTF_Font	*f;

	font = ft_strjoin("./assets/fonts/", font);
	f = TTF_OpenFont(font, size);
	free((void *)font);
	return ((t_style){c, f});
}

void	init_text_p(t_text_p *sst)
{
	const SDL_Color	colors[] = {
		{250, 250, 250, 255},
		{38, 71, 204, 255},
		{247, 33, 219, 255},
		{204, 88, 71, 255},
		{51, 229, 76, 255},
		{120, 120, 120, 255}};
	const char		*fonts[] = {
		"Prototype.ttf", "AnonymousPro.ttf", "SourceCodePro.ttf" };

	ft_bzero(sst, sizeof(t_text_p));
	add_style(sst, style(colors[0], fonts[2], SF_SMALL));
	add_style(sst, style(colors[0], fonts[2], SF_MEDIUM));
	add_style(sst, style(colors[0], fonts[1], SF_HUGE));
	add_style(sst, style(colors[5], fonts[2], SF_MEDIUM));
	add_style(sst, style(colors[1], fonts[2], SF_MEDIUM));
	add_style(sst, style(colors[2], fonts[2], SF_MEDIUM));
	add_style(sst, style(colors[3], fonts[2], SF_MEDIUM));
	add_style(sst, style(colors[4], fonts[2], SF_MEDIUM));
}
