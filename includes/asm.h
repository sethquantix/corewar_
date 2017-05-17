/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnagy <lnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 16:44:19 by lnagy             #+#    #+#             */
/*   Updated: 2017/03/05 16:44:22 by lnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include "libft.h"
# include "op.h"

# define ASM_RULES	"rules/asm_parse"
# define OPT_A		0x1
# define OPT_X		0x2
# define INS		1
# define LBL		2

# define INST(x)	((t_inst *)(x->content))

# define ERR_POS	"Champion name or comment not at the top of the file\n"
# define ERR_LEN	"Champion name or comment too long\n"
extern t_token	g_asm_opts[];
extern t_token	g_asm_tokens[];
extern t_op    	op_tab[17];

typedef struct	s_env
{
	t_parser	*asm_parser;
	char		**files;
	int			n_file;
	int			opts;
	int			debug;
}				t_env;

typedef struct	s_inst
{
	char			*name;
	t_op			*op;
	int				type;
	int				addr;
	int				size;
	int				oct;
	unsigned int	params[4];
	int				p_size[4];
	char			*label[4];
	char			*args[4];
}				t_inst;

typedef struct	s_file
{
	header_t	head;
	t_list		*inst;
	char		*source;
	int			addr;
	void		(*print_header)(struct s_file *);
	void		(*print_inst)(t_inst *, struct s_file *);
	char		*name;
	int			fd;
}				t_file;

typedef void	(*t_f_rule)(void *, t_expr **);

t_expr		*parse_opts(char **av);
t_expr		*parse_asm(t_parser *p, char *file, char **source);
void		die(char *s, int exit_code, ...);
int 		usage(char *path);
void		find_rule(void *data, t_expr **expr, const char *s[], t_f_rule f[]);
void		read_opts(t_env *e, t_expr *expr);
void		compile(t_env *e);
void		write_file_header(t_file *file);
void		print_file_header(t_file *file);
int			cmp_label(t_inst *inst, char *label);
void 		print_inst(t_inst *inst, t_file *file);
void		write_inst(t_inst *inst, t_file *file);
void		print_instructions(t_file *file);

int			tok_func_none(char **s);
int			tok_func_string(char **s);
int			tok_func_ascii(char **s);
int			tok_func_number(char **s);
int			tok_func_reg_nbr(char **s);

void		print_expr(t_expr *expr);

#endif
