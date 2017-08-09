/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/12 16:25:18 by cchaumar          #+#    #+#             */
/*   Updated: 2016/09/12 17:14:32 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math3d.h"

void	mat_ident(t_mat *m)
{
	int		i;

	ft_bzero(m, sizeof(t_mat));
	i = -1;
	while (++i < 4)
		m->r[i] = vec4(i == 0, i == 1, i == 2, i == 3);
}

t_mat	mat_trans(t_mat m)
{
	t_mat	r;

	r.r[0] = vec4(m.r[0].x, m.r[1].x, m.r[2].x, m.r[3].x);
	r.r[1] = vec4(m.r[0].y, m.r[1].y, m.r[2].y, m.r[3].y);
	r.r[2] = vec4(m.r[0].z, m.r[1].z, m.r[2].z, m.r[3].z);
	r.r[3] = vec4(m.r[0].w, m.r[1].w, m.r[2].w, m.r[3].w);
	return (r);
}

t_mat	mat_mult_mat(t_mat l, t_mat r)
{
	t_mat		o;
	t_mat		t;
	int			i;

	t = mat_trans(r);
	i = -1;
	while (++i < 4)
	{
		o.r[i] = vec4(
			v_dot(l.r[i], t.r[0]),
			v_dot(l.r[i], t.r[1]),
			v_dot(l.r[i], t.r[2]),
			v_dot(l.r[i], t.r[3]));
	}
	return (o);
}

t_vec4	mat_mult_vect(t_mat m, t_vec4 v)
{
	return (vec4(
		v_dot(v, m.r[0]),
		v_dot(v, m.r[1]),
		v_dot(v, m.r[2]),
		v_dot(v, m.r[3])));
}
