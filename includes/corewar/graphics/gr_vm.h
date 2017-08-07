/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gr_vm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 12:28:52 by cchaumar          #+#    #+#             */
/*   Updated: 2017/08/07 12:11:55 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GR_VM_H
# define GR_VM_H
# include "includes.h"
# include "../internals/crwr_structs.h"
# include "gr_structs.h"
# include "gr_types.h"

# define WIN_WIDTH	1920
# define WIN_HEIGHT	1080

void	gr_vm_init(t_gr_vm *cxt);
void	gr_vm_run(t_vm_loop loop, void *data, t_gr_vm *ctx);
void	gr_vm_end(t_gr_vm *ctx);

#endif
