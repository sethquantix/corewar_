/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnagy <lnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 14:01:00 by lnagy             #+#    #+#             */
/*   Updated: 2017/03/20 14:01:01 by lnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			write_inst(t_inst *inst, t_file *file)
{
	int				i;
	unsigned short	s;

	if (inst->type == LBL)
		return ;
	write(file->fd, &inst->op->opcode, 1);
	if (inst->oct)
		write(file->fd, &inst->oct, 1);
	i = 0;
	while (i < inst->op->argc)
	{
		s = (unsigned short)inst->params[i];
		ft_endian(&s, 2);
		if (inst->p_size[i] == 4)
			ft_endian(&inst->params[i], 4);
		write(file->fd, inst->p_size[i] == 2 ? (void *)&s :
			(void *)&inst->params[i], inst->p_size[i]);
		i++;
	}
}

void			del_inst(t_inst *inst, size_t size)
{
	int		i;

	i = 0;
	ft_memdel((void **)&inst->name);
	while (i < 4)
	{
		ft_memdel((void **)&inst->label[i]);
		ft_memdel((void **)&inst->args[i]);
		i++;
	}
	ft_bzero(inst, size);
	ft_memdel((void **)&inst);
}

void			print_instructions(t_file *file)
{
	t_list	*inst;

	file->err_label = NULL;
	if (get_labels(file, file->inst) == -1)
	{
		ft_printf("Compiling %s : %sFailure%s\
			\nUnknown label %s\n", file->name, COLOR_RED, COLOR_END,
			file->err_label);
		return ;
	}
	file->print_header(file);
	inst = file->inst;
	while (inst)
	{
		file->print_inst(INST(inst), file);
		inst = inst->next;
	}
	ft_lstdel(&file->inst, (void (*)(void *, size_t))del_inst);
	if (file->fd)
		close(file->fd);
}

void			print_file_header(t_file *file)
{
	ft_printf("%sDumping : %s%s\n", acol(0, 4, 1), file->name, COLOR_END);
	ft_printf("Program size : %d bytes\n", file->addr);
	ft_printf("Name : \"%s\"\n", file->head.prog_name);
	ft_printf("Comment : \"%s\"\n\n", file->head.prog_desc);
}
