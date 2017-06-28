/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decompile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/18 10:52:30 by tsedigi           #+#    #+#             */
/*   Updated: 2017/06/18 10:52:33 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include <sys/stat.h>
#include "decompile.h"

void		write_head(t_deco *all)
{
	ft_dprintf(all->fd, ".name%11s%s%s\n","\"", all->head.prog_name, "\"");
	ft_dprintf(all->fd, ".comment%8s%s%s\n\n","\"", all->head.prog_desc, "\"");
}


void			write_ops(t_deco *all)
{
	t_dec_op	*tmp;
	t_op		op;
	int			i;

	tmp = all->lst;
	while (tmp)
	{
		op = op_tab[tmp->opcode - 1];
		ft_dprintf(all->fd, "%-15s", op.name);
		i = 0;
		while (i < op.argc)
		{
			if (tmp->param_type[i] != IND_CODE)
				ft_dprintf(all->fd, " %s%d",tmp->param_type[i] == REG_CODE ? "r" : "%", tmp->param_value[i]);
			else
				ft_dprintf(all->fd, " %d", tmp->param_value[i]);
			i++;
			(i < op.argc) ? ft_dprintf(all->fd, ",") : 0;
		}
		ft_dprintf(all->fd, "\n");
		tmp = tmp->next;
	}
}


void		print_file(char *src, t_deco *all)
{
	char	*path;
	char	*chr;

	path = ft_strnew(ft_strlen(src));
	chr = ft_strchr(src, '.');
	chr[0] = 0;
	ft_strcat(path, src);
	ft_strcat(path, ".dec");
	chr[0] = '.';
	all->fd ? close(all->fd) : 0;
	all->fd = open(path, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (all->fd == -1)
		die(EXIT_FAILURE, "Cannot open/create file");
	write_head(all);
//	set_check_lbl(all);
	write_ops(all);
	close(all->fd);		
//	del_all_op(all->lst);
}

void		set_value(unsigned char *file, t_dec_op *node, int i, int size)
{
	int		j;
	short	s;
	unsigned int conv;

	j = 0;
	if (size == 4)
	{
		conv = (file[0] << 24) | (file[1] << 16) | (file[2] << 8) | file[3];
		node->param_value[i] = conv;
	}
	else if (size == 2)
	{
		s = (file[0] << 8) | file[1];	
		node->param_value[i] = s;
	}
	else
		node->param_value[i] = file[0];
}

int			set_param_no_octal(char *file, t_dec_op *node)
{
	t_op	op;
	int		iter;

	op = op_tab[node->opcode - 1];
	iter = 0;
	if (op.argc)
	{
		if (op.args[0] & T_REG)
		{
			node->param_size[0] = REG_SIZE;
			node->param_type[0] = REG_CODE;
			set_value((unsigned char *)file, node, 0, REG_SIZE);
			iter = REG_SIZE;
		}
		else
		{
			node->param_size[0] = op.dir_size;
			node->param_type[0] = DIR_CODE;
			set_value((unsigned char *)file, node, 0, op.dir_size);
			iter = op.dir_size;
		}
	}
	return (iter);
}

int			set_param_with_octal(char *file, t_dec_op *node)
{
	static int	sizes[] = {0, REG_NUMBER_SIZE, DIR_SIZE, IND_SIZE};
	t_op		op;
	int			i;
	int			iter;

	op = op_tab[node->opcode - 1];
	sizes[2] = op.dir_size;
	iter = 1;
	i = 0;
	while (i < op.argc)
	{
		if ((PROC_TYPE((node->param_type[i] = PROC_CODE(file[0], i))) & op.args[i]) == 0)
			die(EXIT_FAILURE, "Error with encoding octet or param");
		node->param_size[i] = sizes[node->param_type[i]];
		set_value((unsigned char *)&file[iter], node, i, node->param_size[i]);
		iter += node->param_size[i++];
	}
	return (iter - 1);
}

void			add_deco_op(t_deco *all, t_dec_op *node)
{
	t_dec_op	*tmp;

	if (all && !all->lst)
		all->lst = node;
	else if (all)
	{
		tmp = all->lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}

int			check_op(char *file, t_deco *all, int iter)
{
	t_dec_op	*node;
	t_op		op;
	int			ret;
	int			i;

	if (!file)
		die(EXIT_FAILURE, "Unknown");
	if (file[0] < 1 || file[0] > 16)
		die(EXIT_FAILURE, "Invalid, operation");
	if (!(node = (t_dec_op *)ft_memalloc(sizeof(t_dec_op))))
		die(EXIT_FAILURE, "Malloc failed");
	node->opcode = file[0];
	op = op_tab[node->opcode - 1];
	ret = op.octal ? 2 : 1;
	ret == 2 ? node->octal = 1 : 0;
	node->addr = iter + 1;
	add_deco_op(all, node);
	if (ret == 2 && file[1])
		ret += set_param_with_octal(&file[1], node);
	else if (ret == 1)
		ret += set_param_no_octal(&file[1], node);
	return (ret);
}

static	int	err_param(char *src)
{
	int			fd;
	header_t	*head;
	char		*chr;

	if ((fd = open(src, O_RDONLY)) == -1)
	{
		ft_dprintf(STDERR_FILENO, "Unable to read file %s\n", src);
		return (fd);
	}
	if (!(chr = ft_strchr(src, '.')) || ft_strcmp(chr, ".cor"))
	{
		close(fd);
		ft_dprintf(STDERR_FILENO, "File must be a .cor \n");
		return (-1);
	}
	return (fd);
}

static int	invalid_header(header_t *head)
{
	if (!head)
	{
		ft_dprintf(STDERR_FILENO, "Failed to read header \n");
		return (1);
	}
	ft_endian(&head->magic, 4);
	ft_endian(&head->prog_size, 4);
	if (head->magic != COREWAR_EXEC_MAGIC)
	{
		ft_dprintf(STDERR_FILENO ,"Bad magic number\n");
		return (1);
	}
	return (0);
}

void		decompile(char *src)
{
	t_deco		all;
	struct stat sts;
	size_t		iter;
	char		file[CHAMP_MAX_SIZE + 1];


	ft_bzero((void *)&all, sizeof(t_deco));
	if ((all.fd = err_param(src)) == -1)
		return ;
	if (stat(src, &sts) == -1)
		return ;
	if (read(all.fd, &all.head, sizeof(header_t)) == -1)
		die(EXIT_FAILURE, "Read failed");
	ft_bzero(file, CHAMP_MAX_SIZE + 1);
	if (invalid_header(&all.head))
		return ;
	if (read(all.fd, file, CHAMP_MAX_SIZE) == -1)
		die(EXIT_FAILURE, "Invalid champ");
	iter = 0;
	while (file[iter])
		iter += check_op(&file[iter], &all, iter);
	print_file(src, &all);
}