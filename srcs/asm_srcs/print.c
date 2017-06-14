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


int		addr_label(const char *file, char *label, t_list *inst)
{
	t_list	*ret;

	ret = ft_lstfind(inst, label, (int (*)(void *, void *))cmp_label);
	if (!ret)
		die(EXIT_FAILURE, "Compiling %s : %sFailure%s!\
			\nUnknown label %s\n", file, COLOR_RED, COLOR_END, label);
	return (INST(ret)->addr);
}

void 	get_labels(const char *file, t_list *inst)
{
	int		i;
	t_list	*start;
	t_inst	*in;

	start = inst;
	while (inst)
	{
		in = INST(inst);
		i = 0;
		if (in->type == LBL)
		{
			inst = inst->next;
			continue ;
		}
		while (i < in->op->argc)
		{
			if (in->label[i])
				in->params[i] = addr_label(file, in->label[i], start) -
					in->addr;
			i++;
		}
		inst = inst->next;
	}
}

void	hex_print(int v, int size)
{
	int	i;
	unsigned char	c[4];

	ft_memcpy(c, &v, size);
	i = 0;
	while (i < size)
	{
		ft_printf("%-4d", c[size - 1 - i]);
		i++;
	}
	while (i < 4)
	{
		ft_printf("    ");
		i++;
	}
	ft_printf("  ");
}

void	print_params(t_inst *inst, int type)
{
	int		i;

	i = 0;
	ft_printf("%20s%-4d%-5.0d ", "", inst->op->opcode, inst->oct);
	while (i < inst->op->argc)
	{
		type == 0 ? hex_print(inst->params[i], inst->p_size[i]) :
			ft_printf("%-18d", inst->params[i]);
		i++;
	}
	ft_putchar('\n');
}

void 	print_inst(t_inst *inst, t_file *file)
{
	int		i;

	(void)file;
	ft_printf("%-5d", inst->addr);
	ft_printf((inst->type == LBL ? "      :" : "(%-3d) :"), inst->size);
	if (inst->type == LBL)
	{
		ft_printf("    %s:\n", inst->name);
		return ;
	}
	ft_printf("        %-10s", inst->name);
	i = 0;
	while (i < inst->op->argc)
		ft_printf("%-18s", inst->args[i++]);
	ft_putchar('\n');
	print_params(inst, 0);
	print_params(inst, 1);
	ft_putchar('\n');
}

void	write_inst(t_inst *inst, t_file *file)
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

void	del_inst(t_inst *inst, size_t size)
{
	int 	i;

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

void	print_instructions(t_file *file)
{
	t_list	*inst;

	get_labels(file->name, file->inst);
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

char	*output_file(char *path)
{
	char	*t;

	t = ft_strrchr(path, '/');
	t = ft_strrchr(t ? t + 1 : path, '.');
	t = ft_strsub(path, 0, t ? t - path : ft_strlen(path));
	return (ft_strjoinfree(t, ".cor", 1));
}

void	write_file_header(t_file *file)
{
	char			*o;

	file->head.prog_size = ft_endian_int(file->addr);
	o = output_file(file->name);
	ft_printf("Writing output to %s\n", o);
	if ((file->fd = open(o, O_WRONLY | O_CREAT | O_TRUNC, 0777)) == -1)
		die(EXIT_FAILURE, "Compilation of %s %sfailed%s !\
			\nCan't open %s for writing\n", o);
	free(o);
	write(file->fd, &file->head, sizeof(header_t));
}

void	print_file_header(t_file *file)
{
	ft_printf("Dumping annotated program on standard output\n");
	ft_printf("Program size : %d bytes\n", file->addr);
	ft_printf("Name : \"%s\"\n", file->head.prog_name);
	ft_printf("Comment : \"%s\"\n\n", file->head.prog_desc);
}
