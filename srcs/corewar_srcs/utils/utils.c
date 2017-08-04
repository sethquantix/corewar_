/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 13:29:31 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/06 13:29:33 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_header	empty_head(void)
{
	t_header	head;

	ft_bzero(&head, sizeof(t_header));
	return (head);
}

void		proc_set(t_proc *p, int state)
{
	static t_arena	*a = NULL;

	if (!a)
		a = p->arena;
	if (state == SET_PLAYER)
		a->mem[p->pc] |= 1 << p->player;
	else
		a->mem[p->pc] &= (-1) & ~(1 << p->player);
}

int			err(int level, const char *format, ...)
{
	const int	colors[2][3] = {{4, 1, 0}, {5, 0, 0}};
	va_list		va;
	char		*col;

	col = acol(colors[level][0], colors[level][1], colors[level][2]);
	write(2, col, ft_strlen(col));
	va_start(va, format);
	ft_vadprintf(2, format, va);
	va_end(va);
	write(2, COLOR_END, sizeof(COLOR_END));
	return (-1);
}

void		die(int exit_status, const char *format, ...)
{
	va_list	va;

	va_start(va, format);
	ft_vadprintf(2, format, va);
	va_end(va);
	exit(exit_status);
}

void		dump(uint8_t mem[], int mod)
{
	int		i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (!(i % mod))
			ft_printf(i ? "%#.4x : " : "0x%.4x : ", i);
		ft_printf("%x%x%s", mem[i] >> 4, mem[i] & 0xf, (i + 1) % mod ? " " :
			"\n");
		i++;
	}
}
