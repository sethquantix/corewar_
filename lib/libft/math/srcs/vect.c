/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/12 16:27:12 by cchaumar          #+#    #+#             */
/*   Updated: 2016/09/12 17:14:56 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math3d.h"

t_vec4	vec3(t_vec4 v)
{
	return ((t_vec4){v.x, v.y, v.z, 0});
}

t_vec4	vec4(float x, float y, float z, float w)
{
	return ((t_vec4){x, y, z, w});
}

t_vec4	v_cross(t_vec4 u, t_vec4 v)
{
	t_vec4	s;

	s.x = u.y * v.z - u.z * v.y;
	s.y = u.z * v.x - u.x * v.z;
	s.z = u.x * v.y - u.y * v.x;
	s.w = 0;
	return (s);
}

float	v_len(t_vec4 v)
{
	return (sqrt(v_dot(v, v)));
}

t_vec3	v_norm(t_vec4 v)
{
	return (v_mult_k(v, 1.0 / v_len(v)));
}
