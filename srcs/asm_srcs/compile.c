/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnagy <lnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 17:07:48 by lnagy             #+#    #+#             */
/*   Updated: 2017/08/01 03:35:25 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

const char	*g_list[] = {"LIVE_NAME", "LD_NAME", "ST_NAME", "ADD_NAME",
	"SUB_NAME", "AND_NAME", "OR_NAME", "XOR_NAME", "ZJMP_NAME", "FORK_NAME",
	"LDI_NAME", "STI_NAME", "LLD_NAME", "LLDI_NAME", "LFORK_NAME",
	"AFF_NAME",	"INSTRUCTION", "LABEL", "NAME_CMD_STRING",
	"COMMENT_CMD_STRING", "DIRECT", "DIRECT_LABEL", "INDIRECT",
	"INDIRECT_LABEL", "REG", "STRING", 0
};

t_op	*op_for_name(char *name)
{
	int	i;

	i = 0;
	while (op_tab[i].name)
		if (ft_strcmp(name, op_tab[i].name) == 0)
			return (&op_tab[i]);
		else
			i++;
	return (NULL);
}

t_inst	*new_inst(char *name, int type, int addr)
{
	t_inst	*inst;

	inst = try(sizeof(t_inst));
	inst->name = ft_strdup(name);
	inst->type = type;
	inst->addr = addr;
	inst->op = type == INS ? op_for_name(name) : NULL;
	return (inst);
}

int		cmp_label(t_inst *inst, char *label)
{
	return (inst->type == LBL && ft_strcmp(inst->name, label) == 0);
}

void	read_label(t_file *f, t_expr **expr)
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

void	fill_param(int type, t_inst *inst, t_expr *expr, int i)
{
	static int	size[] = {REG_NUMBER_SIZE, 0, IND_SIZE, 0, IND_SIZE};
	static int	oct[] = {REG_CODE, DIR_CODE, IND_CODE, DIR_CODE, IND_CODE};
	char		*s;
	char 		*p;

	size[1] = inst->op->dir_size;
	size[3] = inst->op->dir_size;
	inst->p_type[i] = type;
	inst->p_size[i] = size[type];
	inst->oct |= inst->op->octal ? oct[type] << (6 - 2 * i) : 0;
	s = ft_strdup(expr->expr);
	inst->args[i] = ft_strdup(expr->expr);
	p = inst->args[i];
	while (*p)
	{
		*p = ft_tolower(*p);
		p++;
	}
	if (type > 2)
	{
		inst->label[i] = ft_strsub(s, 1 + (type == 3), ft_strlen(s + 1 + (type == 3)));
		return ;
	}
	ft_strtolower(s);
	s += type != 2;
	inst->params[i] = s[1] == 'x' ? ft_atoi_base(s + 2, "0123456789abcdef")
		: ft_atoi(s);
	free(s - (type != 2));
}

t_expr	*get_params(t_inst *inst, t_expr *expr)
{
	const char	*types[] = {"REG", "DIRECT", "INDIRECT", "DIRECT_LABEL",
		"INDIRECT_LABEL"};
	int			i;
	int			j;

	i = 0;
	while (i < inst->op->argc)
	{
		expr = expr->next;
		j = 0;
		while (ft_strcmp(types[j], expr->rule))
			j++;
		fill_param(j, inst, expr, i);
		inst->size += inst->p_size[i];
		i++;
	}
	return (expr);
}

void	read_instruction(t_file *f, t_expr **expr)
{
	t_inst	*inst;
	t_list	*node;

	*expr = (*expr)->next;
	inst = new_inst((*expr)->expr, INS, f->addr);
	inst->op = op_for_name((*expr)->expr);
	inst->size = 1 + inst->op->octal;
	*expr = get_params(inst, *expr);
	f->addr += inst->size;
	node = ft_lstnew(NULL, 0);
	node->content = inst;
	ft_lstadd_end(&f->inst, node);
}

void 	print(t_list *list)
{
	int i;
	t_inst	*inst;

	while (list)
	{
		i = 0;
		inst = list->content;
		ft_printf("%s (%d) %d => %s\n", inst->op ? "INSTRUCTION" : "LABEL", inst->addr, inst->oct, inst->name);
		if (inst->op)
			while (i < inst->op->argc)
			{
				(inst->label[i]) ? ft_printf("(%d) => %s (%d)\n", i, inst->label[i], inst->p_size[i])
				: ft_printf("(%d) => %d (%d)\n", i, inst->params[i], inst->p_size[i]);
				i++;
			}
		list = list->next;
	}
}

void 	get_error(int error)
{
	if (error == 0)
		return ;
	if (error == -1)
		die(EXIT_FAILURE, ERR_POS);
	if (error == -2)
		die(EXIT_FAILURE, ERR_LEN);
}

int	get_cmd(t_expr **expr, int max_size, char *dest, char *cmd)
{
	if (ft_strcmp((*expr)->rule, cmd))
		return (-1);
	*expr = (*expr)->next;
	if (ft_strlen((*expr)->expr) - 2 > (size_t)max_size)
		return (-2);
	ft_strncpy(dest, (*expr)->expr + 1, ft_strlen((*expr)->expr) - 2);
	*expr = (*expr)->next;
	return (0);
}

t_file	*read_asm(t_env *e, t_expr *expr, char *source, char *file_name)
{
	t_file		*file;
	const char	*s[] = {"LABEL", "INSTRUCTION", 0};
	static void	(*f[])(t_file *, t_expr **) = {read_label, read_instruction, 0};

	file = try(sizeof(t_file));
	file->head.magic = ft_endian_int(COREWAR_EXEC_MAGIC);
	file->source = source;
	file->name = file_name;
	file->print_header = e->opts & OPT_A ? print_file_header : write_file_header;
	file->print_inst = e->opts & OPT_A ? print_inst : write_inst;
	get_error(get_cmd(&expr, PROG_NAME_LENGTH, file->head.prog_name, "NAME_CMD_STRING"));
	get_error(get_cmd(&expr, COMMENT_LENGTH, file->head.prog_desc, "COMMENT_CMD_STRING"));
	while (expr)
	{
		if (expr->rule)
			find_rule(file, &expr, s, (void (**)(void *, t_expr **))f);
		expr = expr->next;
	}
	return (file);
}

void	compile(t_env *e)
{
	t_expr	*expr;
	int		i;
	char	*source;
	t_file	*file;

	source = NULL;
	e->asm_parser = parse_engine(ASM_RULES, g_asm_tokens, (char **)g_list);
	i = 0;
	while (i < e->n_file)
	{
		if ((expr = parse_asm(e->asm_parser, e->files[i], &source)))
		{
			file = read_asm(e, expr, source, e->files[i]);
			if ((e->opts & OPT_A) == 0)
				ft_printf("Compiling %s : %sSuccess%s\n", file->name,
					  COLOR_GREEN, COLOR_END);
			print_instructions(file);
			parser_clear_expr(&expr);
			free(file);
		}
		free(source);
		i++;
	}
	destroy_engine(e->asm_parser);
}
