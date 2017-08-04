/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnagy <lnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 16:44:19 by lnagy             #+#    #+#             */
/*   Updated: 2017/08/01 08:22:20 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include <sys/stat.h>
# include <libft.h>
# include <../op.h>

# define ASM_RULES	"assets/rules/asm_parse"
# define OPT_A		0x1
# define OPT_X		0x2
# define OPT_C		0x4
# define INS		1
# define LBL		2

# define ERR_INV_ARG 0
# define ERR_BAD_TOK 1
# define ERR_BAD_SYM 2
# define EXA_CHAR	"0123456789abcdef"

# define INST(x)	((t_inst *)(x->content))

# define COLOR_RED	"\033[;1;31m"
# define COLOR_WARN	"\033[38;5;214m"
# define COLOR_GREEN	"\033[;1;32m"
# define COLOR_ADDR	"\033[38;5;46m"
# define COLOR_SIZE	"\033[38;5;34m"
# define COLOR_LBL	"\033[38;5;9m"
# define COLOR_END	"\033[0m"

# define OPEN_FLAGS	O_WRONLY | O_CREAT | O_TRUNC

# define ERR_POS	"Champion name or comment not at the top of the file\n"
# define ERR_LEN	"Champion name or comment too long\n"

extern t_token		g_asm_opts[];
extern t_token		g_asm_tokens[];
extern t_op			g_op_tab[17];

typedef struct		s_env
{
	t_parser		*asm_parser;
	char			**files;
	int				n_file;
	int				opts;
	int				debug;
}					t_env;

typedef struct		s_inst
{
	char			*name;
	t_op			*op;
	int				type;
	int				addr;
	int				size;
	int				oct;
	char			*color;
	unsigned int	params[4];
	int				p_type[4];
	int				p_size[4];
	struct s_inst	*labels[4];
	char			*label[4];
	char			*args[4];
}					t_inst;

typedef struct		s_file
{
	t_header		head;
	t_list			*inst;
	char			*source;
	int				addr;
	char			*err_label;
	void			(*print_header)(struct s_file *);
	void			(*print_inst)(t_inst *, struct s_file *);
	char			*name;
	int				fd;
}					t_file;

typedef void		(*t_f_rule)(void *, t_expr **);

t_env				*env(void);
t_expr				*parse_opts(char **av);
t_expr				*parse_asm(t_parser *p, char *file, char **source);
void				die(int exit_code, char *s, ...);
int					usage(char *path);
void				find_rule(void *data, t_expr **expr,
	const char *s[], t_f_rule f[]);
void				read_opts(t_env *e, t_expr *expr);
void				compile(t_env *e);
void				write_file_header(t_file *file);
void				print_file_header(t_file *file);
int					cmp_label(t_inst *inst, char *label);
void				print_inst(t_inst *inst, t_file *file);
void				write_inst(t_inst *inst, t_file *file);
void				print_instructions(t_file *file);
void				print_inst(t_inst *inst, t_file *file);

void				fill_param(int type, t_inst *inst, t_expr *expr, int i);
t_expr				*get_params(t_inst *inst, t_expr *expr);
void				print_params(t_inst *inst, int type);

void				read_instruction(t_file *f, t_expr **expr);
t_inst				*new_inst(char *name, int type, int addr);
t_op				*op_for_name(char *name);

int					cmp_label(t_inst *inst, char *label);
void				read_label(t_file *f, t_expr **expr);
t_inst				*addr_label(t_file *file, char *label, t_list *inst);
int					get_labels(t_file *file, t_list *inst);

int					tok_func_none(char **s);
int					tok_func_string(char **s);
int					tok_func_ascii(char **s);
int					tok_func_number(char **s);
int					tok_func_reg_nbr(char **s);

void				print_expr(t_expr *expr);
char				*err(int err_code, ...);

void				ft_strtolower(char *str);
char				*get_color_(int nb, char type);

#endif
