/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gr_vm_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/01 06:01:32 by tsedigi           #+#    #+#             */
/*   Updated: 2017/08/01 06:01:33 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "gr_vm_internals.h"

void	load_identity(float *m)
{
	m[0] = 1;
	m[1] = 0;
	m[2] = 0;
	m[3] = 0;
	m[4] = 0;
	m[5] = 1;
	m[6] = 0;
	m[7] = 0;
	m[8] = 0;
	m[9] = 0;
	m[10] = 1;
	m[11] = 0;
	m[12] = 0;
	m[13] = 0;
	m[14] = 0;
	m[15] = 1;
}

void	load_projection(float *out, float near, float far, float aspect)
{
	float	x_scale;
	float	y_scale;
	float	frustrum;

	load_identity(out);
	y_scale = (float)((1.0f / tan((60.0f / 2.0f) / 57.295)) * aspect);
	x_scale = y_scale / aspect;
	frustrum = far - near;
	out[0] = x_scale;
	out[5] = y_scale;
	out[10] = -((far + near) / frustrum);
	out[11] = -((2 * near * far) / frustrum);
	out[14] = -1;
	out[15] = 0;
}
