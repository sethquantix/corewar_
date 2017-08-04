/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 08:27:47 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/11 16:54:17 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH3D_H
# define MATH3D_H

# include <math.h>
# include "../../libft.h"

# define AXIS_X	0
# define AXIS_Y	1
# define AXIS_Z	2

typedef struct		s_vec4
{
	float	x;
	float	y;
	float	z;
	float	w;
}					t_vec4;

typedef t_vec4		t_vec3;
typedef t_vec4		t_quat;

typedef union		u_mat
{
	float			t[16];
	t_vec4			r[4];
}					t_mat;

void				mat_ident(t_mat *m);
t_mat				mat_mult_mat(t_mat left, t_mat right);
t_vec4				mat_mult_vect(t_mat m, t_vec4 v);
t_vec4				v_mult_k(t_vec4 v, float k);
t_vec3				v_inv(t_vec4 v);
float				v_len(t_vec3 v);
float				v_dot(t_vec3 u, t_vec3 v);
t_vec3				v_sub(t_vec3 v1, t_vec3 v2);
t_vec3				v_add(t_vec3 v1, t_vec3 v2);
t_vec4				v_cross(t_vec4 u, t_vec4 v);
t_vec4				v_norm(t_vec4 v);
t_vec4				vec3(t_vec4 v);
t_vec4				vec4(float x, float y, float z, float w);

t_quat				quat(float x, float y, float z, float w);
t_quat				quat_norm(t_quat q);
t_quat				quat_conjug(t_quat q);
t_quat				quat_mult(t_quat ql, t_quat qr);
void				quat_rotate(t_vec4 *d, t_vec4 *r, int dir, float a);

#endif
