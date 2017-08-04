/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 16:56:13 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/11 16:56:14 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math3d.h"

t_vec4		v_mult_k(t_vec4 v, float k)
{
	v.x *= k;
	v.y *= k;
	v.z *= k;
	v.w *= k;
	return (v);
}

float		v_dot(t_vec4 u, t_vec4 v)
{
	return (u.x * v.x + u.y * v.y + u.z * v.z + u.w * v.w);
}

t_vec4		v_inv(t_vec4 v)
{
	return (vec4(-v.x, -v.y, -v.z, -v.w));
}

t_vec4		v_add(t_vec4 u, t_vec4 v)
{
	return (vec4(u.x + v.x, u.y + v.y, u.z + v.z, u.w + v.w));
}

t_vec4		v_sub(t_vec4 u, t_vec4 v)
{
	return (vec4(u.x - v.x, u.y - v.y, u.z - v.z, u.w - v.w));
}
