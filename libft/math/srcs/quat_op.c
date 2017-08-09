/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quat_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 17:00:08 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/11 17:00:09 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math3d.h"

float	quat_length(t_quat q)
{
	return (sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w));
}

t_quat	quat_mult_k(t_quat q, float k)
{
	return (quat(q.x * k, q.y * k, q.z * k, q.w * k));
}

t_quat	quat_norm(t_quat q)
{
	float len;

	len = quat_length(q);
	return (quat_mult_k(q, 1.0 / len));
}

t_quat	quat_conjug(t_quat q)
{
	return (quat(-q.x, -q.y, -q.z, q.w));
}

t_quat	quat_mult(t_quat ql, t_quat qr)
{
	t_quat	q;

	q.x = ql.w * qr.x + ql.x * qr.w + ql.y * qr.z - ql.z * qr.y;
	q.y = ql.w * qr.y + ql.y * qr.w + ql.z * qr.x - ql.x * qr.z;
	q.z = ql.w * qr.z + ql.z * qr.w + ql.x * qr.y - ql.y * qr.x;
	q.w = ql.w * qr.w - ql.x * qr.x - ql.y * qr.y - ql.z * qr.z;
	return (q);
}
