/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crwr_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 13:20:49 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/06 13:20:49 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CRWR_STRUCTS_H
# define CRWR_STRUCTS_H

# include "crwr_types.h"
# include "crwr_defines.h"

typedef enum	e_type
{
	V_VALUE,
	V_VALUE_NOIDX,
	V_REFERENCE
}				t_type;


typedef struct	s_val
{
	void	*p;
	uint8_t	s;
}				t_val;

typedef struct	s_champ
{
	char		*file_name;
	uint8_t		*source;
	header_t	head;
	int			id;
	int			num;
	int			set;
	int 		nbr_live;
	int 		last_live;
}				t_champ;

typedef struct	s_proc
{
	struct s_arena	*arena;
	unsigned int	reg[REG_NUMBER + 1];
	t_op			*op;
	t_f_get			get_inst;
	t_f_fill		get_params;
	uint32_t		params[MAX_ARGS_NUMBER];
	uint8_t			p_sizes[MAX_ARGS_NUMBER];
	uint8_t			p_types[MAX_ARGS_NUMBER];
	int				cycles_left;
	int				id;
	int				pc;
	int				carry;
	int				last_live;
	int				die;
	unsigned char	oct;
	int				player;
}				t_proc;

typedef struct	s_arena
{
	t_champ		*champs;
	t_list		*procs;
	uint8_t		arena[MEM_SIZE];
	uint32_t	mem[MEM_SIZE];
	t_f_load	load;
	t_f_add		add_proc;
	t_f_filter	check;
	int			champ_count;
	int			proc_id;
	int			ctd;
	int			last_check;
	int 		cycles;
	int			check_cycles;
	int 		nbr_lives;
	int			dump_cycles;
	int			opts;
	int			alive;
	int			debug_fd;
	int			verbose_lvl;
}				t_arena;

#endif
