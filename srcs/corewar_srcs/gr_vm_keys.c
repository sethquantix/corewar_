/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gr_vm_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 07:04:49 by cchaumar          #+#    #+#             */
/*   Updated: 2017/06/14 07:04:50 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gr_vm_internals.h"

static int	add_key(t_key **keys, int keycode, t_f_key press, t_f_key hold)
{
	static int		n = 0;
	static t_key	**p = NULL;
	t_key			key;

	if (p != keys)
	{
		p = keys;
		n = 0;
	}
	key = (t_key){keycode, 0, press, hold, 0, 0};
	ft_pushback((void **)keys, sizeof(t_key), n++, &key);
	return (1);
}

void		set_keys(t_key **keys, int *nkeys)
{
	*nkeys += add_key(keys, SDLK_ESCAPE, quit_press, NULL);
	*nkeys += add_key(keys, SDLK_w, cam_trans_forwad, cam_trans_forwad);
	*nkeys += add_key(keys, SDLK_s, cam_trans_back, cam_trans_back);
	*nkeys += add_key(keys, SDLK_d, cam_trans_right, cam_trans_right);
	*nkeys += add_key(keys, SDLK_a, cam_trans_left, cam_trans_left);
	*nkeys += add_key(keys, SDLK_q, cam_trans_down, cam_trans_down);
	*nkeys += add_key(keys, SDLK_e, cam_trans_up, cam_trans_up);
	*nkeys += add_key(keys, SDLK_BACKSLASH, toggle_opt, NULL);
	*nkeys += add_key(keys, SDLK_SLASH, toggle_opt, NULL);
	*nkeys += add_key(keys, SDLK_r, toggle_opt, NULL);
	*nkeys += add_key(keys, SDLK_KP_PLUS, speed, speed);
	*nkeys += add_key(keys, SDLK_KP_MINUS, speed, speed);
	*nkeys += add_key(keys, SDLK_r, toggle_42, NULL);
	*nkeys += add_key(keys, SDLK_LEFT, select_proc, select_proc);
	*nkeys += add_key(keys, SDLK_RIGHT, select_proc, select_proc);
	*nkeys += add_key(keys, SDLK_UP, select_proc, select_proc);
	*nkeys += add_key(keys, SDLK_DOWN, select_proc, select_proc);
}
