/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 22:51:03 by cchaumar          #+#    #+#             */
/*   Updated: 2017/02/18 06:42:54 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math3d.h"

t_quat	new_quat(t_vec3 axis, float angle)
{
	t_quat	q;
	float	rad;
	float	sin_half;
	float	cos_half;

	rad = angle * M_PI / 360.0;
	sin_half = sin(rad);
	cos_half = cos(rad);
	q.x = axis.x * sin_half;
	q.y = axis.y * sin_half;
	q.z = axis.z * sin_half;
	q.w = cos_half;
	return (q);
}

t_quat	quat(float x, float y, float z, float w)
{
	return (vec4(x, y, z, w));
}

t_quat	quat_vect(t_vec4 v)
{
	return (quat(v.x, v.y, v.z, 0));
}

t_vec4	quat_part_vect(t_quat q)
{
	return (vec4(q.x, q.y, q.z, 0));
}

void	quat_rotate(t_vec4 *d, t_vec4 *r, int dir, float angle)
{
	t_quat		q;
	t_vec4		axis;

	if (dir == AXIS_Z)
		axis = *d;
	else if (dir == AXIS_X)
		axis = *r;
	else
		axis = v_cross(*d, *r);
	q = quat_norm(new_quat(axis, angle));
	*d = quat_part_vect(quat_mult(q, quat_mult(quat_vect(*d), quat_conjug(q))));
	*r = quat_part_vect(quat_mult(q, quat_mult(quat_vect(*r), quat_conjug(q))));
	*d = v_norm(*d);
	*r = v_norm(*r);
}
