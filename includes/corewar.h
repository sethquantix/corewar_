/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnagy <lnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/05 16:44:30 by lnagy             #+#    #+#             */
/*   Updated: 2017/03/29 14:08:03 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# include "gr_vm.h"
# include "crwr_structs.h"
# include "crwr_globals.h"


t_expr	*parse_opts(char **av);
void	read_args(t_expr *expr, t_arena *a);

int		load_champ(t_champ *c);

void	add_proc(t_arena *a, t_champ *c);
void	proc_exec_inst(t_proc *p);
int		proc_read_inst(t_proc *p, uint8_t mem[]);
int		proc_read_params(t_proc *p, uint8_t mem[]);

void	read_args(t_expr *expr, t_arena *a);
void	check_process(t_arena *a);
int 	cmp_id(uint32_t	*ref, t_champ *data);
int		check_set(t_champ *champs, int count, int n);

void	i_live(t_proc *proc, uint8_t mem[]);
void	i_ld(t_proc *proc, uint8_t mem[]);
void	i_st(t_proc *proc, uint8_t mem[]);
void	i_aff(t_proc *proc, uint8_t mem[]);
void	i_zjmp(t_proc *proc, uint8_t mem[]);
void	i_add(t_proc *proc, uint8_t mem[]);
void	i_sub(t_proc *proc, uint8_t mem[]);
void	i_and(t_proc *proc, uint8_t mem[]);
void	i_or(t_proc *proc, uint8_t mem[]);
void	i_xor(t_proc *proc, uint8_t mem[]);
void	i_ldi(t_proc *proc, uint8_t mem[]);
void	i_sti(t_proc *proc, uint8_t mem[]);
void	i_lld(t_proc *proc, uint8_t mem[]);
void	i_lldi(t_proc *proc, uint8_t mem[]);
void	i_fork(t_proc *proc, uint8_t mem[]);
void	i_lfork(t_proc *proc, uint8_t mem[]);

t_val	val(void *p, uint8_t s);
int		mem_mod(int addr);
void	write_mem(int pc, t_val v, int mod, uint8_t mem[]);
void	read_mem(int addr, t_val v, int mod, uint8_t mem[]);

int		err(const char *format, ...);
void	die(const char *format, int exit_status, ...);

#endif
