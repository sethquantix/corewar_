/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gr_vm_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/04 07:14:46 by cchaumar          #+#    #+#             */
/*   Updated: 2017/08/04 07:14:46 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gr_vm.h>
#include <gr_vm_internals.h>

void	clear_surfaces(SDL_Surface **buff)
{
	int		i;

	i = 0;
	while (i < 16)
		SDL_FreeSurface(buff[i++]);
	free(buff);
}
