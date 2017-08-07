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

t_env	*env(void)
{
	static t_env	e;

	return (&e);
}

void	die(int exit_code, char *s, ...)
{
	va_list		args;

	va_start(args, s);
	ft_vaprintf(s, args);
	va_end(args);
	exit(exit_code);
}

int		usage(char *path)
{
	ft_printf("Usage: %s [-ax] <source.s> ...\n", path);
	ft_printf("\t-a : instead of compiling the file, output stripped ");
	ft_printf("and annotated version of the code to the standard output\n");
	ft_printf("\t-x : decompile .cor file. Will try to mark labels if ");
	ft_printf("address parameters are relevant.\n");
	ft_printf("\tNote : [-a] and [-x] options are mutually exclusive.\n");
	return (0);
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
