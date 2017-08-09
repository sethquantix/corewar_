/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/24 06:10:05 by cchaumar          #+#    #+#             */
/*   Updated: 2017/07/13 07:15:46 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include <stdio.h>

char			*string(char *s, t_data *d)
{
	int		k;

	k = 0;
	while (s[k] != '%' && s[k])
		k++;
	if (d->pos + (size_t)k > d->size + d->buff)
		p_realloc(d);
	ft_memcpy(d->pos, s, k);
	d->pos += k;
	return (s + k);
}

void			handle_wildcards(t_field *f, t_data *d)
{
	if (f->wc & 1)
		if ((f->padd = va_arg(d->args, int)) < 0)
		{
			f->flag |= NEG;
			f->padd = -f->padd;
		}
	if (f->wc & 2)
	{
		f->prec = va_arg(d->args, int);
		f->prec = MAX(-1, f->prec);
	}
}

inline char		*param(char *s, t_data *d)
{
	t_field		f;
	char		*p;

	p = s;
	ft_bzero(&f, sizeof(t_field));
	f.prec = -1;
	s++;
	while (*s && !f.spec)
		s += conv(s, &f);
	handle_wildcards(&f, d);
	p_reduce(&f);
	p_output(&f, d);
	return (s);
}
