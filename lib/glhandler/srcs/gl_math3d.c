/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gl_math3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/18 08:25:05 by cchaumar          #+#    #+#             */
/*   Updated: 2017/02/26 05:07:59 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gl_handler.h"

t_mat	gl_proj_mat(float ratio, float near, float far, float fov)
{
	float	range;
	float	tan_half;
 	t_mat	m;

	range = near - far;
	tan_half = tan(fov * CL_M_PI / 360.0);

	m.r[0] = vec4(1.0 / (ratio * tan_half), 0, 0, 0);
	m.r[1] = vec4(0, 1.0 / tan_half, 0.0, 0.0);
	m.r[2] = vec4(0.0, 0.0, (-near - far) / range, 2 * far * near / range);
	m.r[3] = vec4(0.0, 0.0, 1.0, 0.0);
	return (m);
}

t_mat	gl_trans_mat(float t_x, float t_y, float t_z)
{
	t_mat	m;

	mat_ident(&m);
	m.r[0].w = t_x;
	m.r[1].w = t_y;
	m.r[2].w = t_z;
	return (m);
}

t_mat	gl_scale_mat(float s_x, float s_y, float s_z)
{
	t_mat	m;

	mat_ident(&m);
	m.r[0].x = s_x;
	m.r[1].y = s_y;
	m.r[2].z = s_z;
	return (m);
}

t_mat	gl_cam_mat(t_vec4 dir, t_vec4 r, t_vec4 up)
{
	t_mat	m;

	m.r[0] = r;
	m.r[1] = up;
	m.r[2] = dir;
	m.r[3] = vec4(0, 0, 0, 1.0);
	return (m);
}

t_mat	gl_get_trans(t_mat matrices[5])
{
	t_mat	m;

	m = mat_mult_mat(matrices[GL_M_TRANS], matrices[GL_M_SCALE]);
	m = mat_mult_mat(matrices[GL_M_CAM_POS], m);
	m = mat_mult_mat(matrices[GL_M_CAM_ROT], m);
	m = mat_mult_mat(matrices[GL_M_PROJ], m);
	return (m);
}
