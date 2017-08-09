/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnagy <lnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/11 17:07:48 by lnagy             #+#    #+#             */
/*   Updated: 2017/08/09 08:35:03 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

const char		*g_list[] = {"LIVE_NAME", "LD_NAME", "ST_NAME", "ADD_NAME",
	"SUB_NAME", "AND_NAME", "OR_NAME", "XOR_NAME", "ZJMP_NAME", "FORK_NAME",
	"LDI_NAME", "STI_NAME", "LLD_NAME", "LLDI_NAME", "LFORK_NAME",
	"AFF_NAME", "INSTRUCTION", "LABEL", "NAME_CMD_STRING", "NAME",
	"COMMENT_CMD_STRING", "DIRECT", "DIRECT_LABEL", "INDIRECT",
	"INDIRECT_LABEL", "REG", "STRING", 0
};

static void		get_error(int error)
{
	if (error == 0)
		return ;
	if (error == -1)
		die(EXIT_FAILURE, ERR_POS);
	if (error == -2)
		die(EXIT_FAILURE, ERR_LEN);
}

static int		get_cmd(t_expr **expr, int max_size, char *dest, char *cmd)
{
	if (!(*expr) || ft_strcmp((*expr)->rule, cmd))
		return (-1);
	*expr = (*expr)->next;
	if (ft_strlen((*expr)->expr) - 2 > (size_t)max_size)
		return (-2);
	ft_strncpy(dest, (*expr)->expr + 1, ft_strlen((*expr)->expr) - 2);
	*expr = (*expr)->next;
	return (0);
}

static t_file	*read_asm(t_env *e, t_expr *expr,
	char *source, char *file_name)
{
	t_file		*file;
	const char	*s[] = {"LABEL", "INSTRUCTION", 0};
	static void	(*f[])(t_file *, t_expr **) = {read_label, read_instruction, 0};

	file = try(sizeof(t_file));
	file->head.magic = ft_endian_int(COREWAR_EXEC_MAGIC);
	file->source = source;
	file->name = file_name;
	file->print_header = e->opts & OPT_A ? print_file_header :
		write_file_header;
	file->print_inst = e->opts & OPT_A ? print_inst : write_inst;
	get_error(get_cmd(&expr, PROG_NAME_LENGTH, file->head.prog_name,
		"NAME_CMD_STRING"));
	get_error(get_cmd(&expr, COMMENT_LENGTH, file->head.prog_desc,
		"COMMENT_CMD_STRING"));
	while (expr)
	{
		find_rule(file, &expr, s, (void (**)(void *, t_expr **))f);
		expr = expr->next;
	}
	return (file);
}

void			compile(t_env *e)
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
		expr = parse_asm(e->asm_parser, e->files[i], &source, NULL);
		if (expr != (void *)-1)
		{
			file = read_asm(e, expr, source, e->files[i]);
			if ((e->opts & OPT_A) == 0)
				ft_printf("Compiling %s : %sSuccess%s\n", file->name,
				acol(0, 5, 0), COLOR_END);
			print_instructions(file);
			parser_clear_expr(&expr);
			free(file);
			free(source);
		}
		i++;
	}
	destroy_engine(e->asm_parser);
}
