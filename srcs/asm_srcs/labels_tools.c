/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   labels_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/04 07:20:50 by tsedigi           #+#    #+#             */
/*   Updated: 2017/08/04 07:20:51 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				cmp_label(t_inst *inst, char *label)
{
	return (inst->type == LBL && ft_strcmp(inst->name, label) == 0);
}

void			read_label(t_file *f, t_expr **expr)
{
	t_inst	*inst;
	t_list	*node;
	char	*name;
	int		l;
	int		c;

	name = (*expr)->expr;
	name = ft_strsub(name, 0, ft_strchr(name, LABEL_CHAR[0]) - name);
	if (ft_lstfind(f->inst, name, (int (*)(void *, void *))cmp_label))
	{
		parser_get_pos((*expr)->pos, f->source, &l, &c);
		die(EXIT_FAILURE, "Compiling %s : %sFAILED%s!\
			\nduplicate label %s at [%d : %d]\n", f->name, COLOR_RED,
			COLOR_END, name, l, c);
	}
	inst = new_inst(name, LBL, f->addr);
	free(name);
	node = ft_lstnew(NULL, 0);
	node->content = inst;
	ft_lstadd_end(&f->inst, node);
}

t_inst			*addr_label(t_file *file, char *label, t_list *inst)
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

static int		get_label(t_list *start, t_file *file, t_inst *in, int i)
{
	in->labels[i] = NULL;
	if (!in->label[i])
		return (0);
	in->labels[i] = addr_label(file, in->label[i], start);
	if (!in->labels[i])
		return (-1);
	in->params[i] = in->labels[i]->addr - in->addr;
	return (0);
}

int				get_labels(t_file *file, t_list *inst)
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
			if (get_label(start, file, in, i) == -1)
				return (-1);
			else
				i++;
		inst = inst->next;
	}
	return (0);
}
