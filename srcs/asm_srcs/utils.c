/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnagy <lnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:24:13 by lnagy             #+#    #+#             */
/*   Updated: 2017/03/08 14:24:15 by lnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	die(char *s, int exit_code, ...)
{
	va_list		args;

	va_start(args, exit_code);
	ft_vaprintf(s, args);
	va_end(args);
	exit(exit_code);
}

void	usage(char *path)
{
	ft_printf("Usage: %s [-ax] <source.s> ...\n", path);
	ft_printf("-a: instead of creating a .cor, outputs a stripped and");
	ft_printf(" annotated version of the code to the standard output.\n");
	ft_printf("-x: outputs a readable version of a .cor to the standard");
	ft_printf(" output. Will try to output labels, if possible.\n");
}

void	find_rule(void *data, t_expr **expr, const char *s[], t_f_rule f[])
{
	int			i;

	i = 0;
	while (s[i])
	{
		if (!ft_strcmp(s[i], (*expr)->rule))
		{
			f[i](data, expr);
			return ;
		}
		i++;
	}
}

void	print_expr(t_expr *expr)
{
	while (expr)
	{
		ft_printf("%s (%s)\n", expr->rule, expr->expr);
		expr = expr->next;
	}
}
