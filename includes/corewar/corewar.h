/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnagy <lnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 16:44:30 by lnagy             #+#    #+#             */
/*   Updated: 2017/08/01 08:12:00 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <graphics/gr_vm.h>
# include <internals/crwr_structs.h>
# include <internals/crwr_globals.h>
# include <../op.h>

t_expr		*parse_opts(char **av);
t_expr		*parse_opts(char **av);

void		option_a(t_expr **e, t_arena *a);
void		option_o(t_expr **e, t_arena *a);
void		option_g(t_expr **e, t_arena *a);
void		option_v(t_expr **e, t_arena *a);
void		option_d(t_expr **e, t_arena *a);
void		option_s(t_expr **e, t_arena *a);
int			check_set(t_champ *champs, int n, int num);
header_t	empty_head(void);
void		read_args(t_expr *expr, t_arena *a);

void		init(t_arena *a);

void		check_process(t_arena *a);
int			cmp_id(int *ref, t_champ *data);
int			check_set(t_champ *champs, int count, int n);

t_proc		*add_proc(t_arena *a, t_champ *c, int pc);
t_proc		*fork_proc(t_arena *a, t_proc *p, int pc);
void		proc_exec_inst(t_proc *p);
int			proc_read_inst(t_proc *p, uint8_t mem[]);
int			proc_read_params(t_proc *p, uint8_t mem[]);

void		i_live(t_proc *proc);
void		i_ld(t_proc *proc);
void		i_st(t_proc *proc);
void		i_aff(t_proc *proc);
void		i_zjmp(t_proc *proc);
void		i_add(t_proc *proc);
void		i_sub(t_proc *proc);
void		i_and(t_proc *proc);
void		i_or(t_proc *proc);
void		i_xor(t_proc *proc);
void		i_ldi(t_proc *proc);
void		i_sti(t_proc *proc);
void		i_lld(t_proc *proc);
void		i_lldi(t_proc *proc);
void		i_fork(t_proc *proc);
void		i_lfork(t_proc *proc);

t_val		val(void *p, uint8_t s);
int			mem_mod(int addr);
int			idx_mod(int pc, int addr);
void		winner(t_arena *arena);
void		write_mem(int addr, t_val v, uint8_t mem[]);
void		read_mem(int addr, t_val v, uint8_t mem[]);
void		set_mem(uint32_t *mem, int addr, int size, int player);
int			get_value(t_proc *p, int *v, int index, t_type type);

int			err(int level, const char *format, ...);
void		die(int exit_status, const char *format, ...);
void		dump(uint8_t mem[], int mod);
void		proc_set(t_proc *p, int state);


extern t_op g_tab[17];

#endif
