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

static char		*get_color_(int nb, char type)
{
	char		*ret;
	static int	first[18] = {0, 0, 0, 1, 2, 1, 1, 2, 2, 0, 0, 0, 1, 2, 1, 1, 2, 2};
	static int	scd[18] = {0, 1, 2, 0, 0, 1, 2, 1, 2, 0, 1, 2, 0, 0, 1, 2, 1, 2};
	char		*ato;
	int			ito;

	if (nb == 0 || nb > 18)
		return (NULL);
	ret = ft_strnew(15);
	ft_strcat(ret, "\033[38;5;");
	ito = 16;
	if (type == 'r')
	{
		ito += nb <= 9 ? 36 * 4 : 36 * 5;
		ito += 6 * first[nb];
		ito += scd[nb];
	}
	else
	{
		if (type == 'g')
			ito += nb <= 9 ? 6 * 4 : 6 * 5;
		else
			ito += nb <= 9 ? 4 : 5;
		ito += 36 * first[nb];
		ito += type == 'g' ? scd[nb] : 6 * scd[nb];
	}
	ft_strcat(ret, ato = ft_itoa(ito));
	ft_strcat(ret, "m");
	ft_memdel((void **)&ato);
	return (ret);
}

t_inst	*addr_label(t_file *file, char *label, t_list *inst)
{
	static int		color = 1;
	t_list			*ret;

	ret = ft_lstfind(inst, label, (int (*)(void *, void *))cmp_label);
	if (!ret)
	{
		file->err_label = ft_strdup(label);
		return (NULL);
	}
	if (!INST(ret)->color)
	{
		color = (color % 16) + 1;
		INST(ret)->color = get_color_(color, 'b');
	}
	return (INST(ret));
}

int 	get_labels(t_file *file, t_list *inst)
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
			in->labels[i] = NULL;
			if (in->label[i] && (in->labels[i] = addr_label(file,
				in->label[i], start)) == NULL)
				return (-1);
			if (in->label[i])
				in->params[i] = in->labels[i]->addr - in->addr;
			i++;
		}
		inst = inst->next;
	}
	return (0);
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

void	print_colored(const char *format, char *color, char *data)
{
	if (env()->opts & OPT_C)
		ft_printf(format, color, data, COLOR_END);
	else
		ft_printf(format, "", data, "");
}

void 	print_inst(t_inst *inst, t_file *file)
{
	int		i;
	char	*col;

	(void)file;
	col = ft_itoa(inst->addr);
	print_colored("%s%-5s%s",COLOR_ADDR, col);
	free(col);
	col = ft_itoa(inst->size);
	print_colored((inst->type == LBL ? "      :" : "(%s%-3s%s) :"),COLOR_SIZE, col);
	free(col);
	if (inst->type == LBL)
	{
		if (!inst->color)
			addr_label(file, inst->name, file->inst);
		print_colored("    %s%s%s:\n",inst->color, inst->name);
		return ;
	}
	col = get_color_(inst->op->opcode, 'r');
	print_colored("        %s%-10s%s",col, inst->name);
	ft_memdel((void **)&col);
	i = 0;
	while (i < inst->op->argc)
	{
		col = inst->p_type[i] > 2 ? ft_strdup(inst->labels[i]->color) :
			get_color_(inst->p_type[i] + 1, 'g');
		print_colored("%s%-18s%s", col, inst->args[i++]);
		ft_memdel((void **)&col);
	}
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
