/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnagy <lnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/08 14:24:13 by lnagy             #+#    #+#             */
/*   Updated: 2017/08/07 10:34:21 by cchaumar         ###   ########.fr       */
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
	char		*buff;

	va_start(args, s);
	ft_vasprintf(&buff, s, args);
	va_end(args);
	ft_dprintf(2, "%sError : %s%s", acol(4, 0, 0), buff, COLOR_END);
	exit(exit_code);
}

t_tok	*tok(t_list *t)
{
	if (t && t->content)
		return (t->content);
	return (NULL);
}

int		usage(char *path)
{
	ft_printf("Usage: %s [-axc] <source.s> ...\n", path);
	ft_printf("\t-a : instead of compiling the file, output stripped ");
	ft_printf("and annotated version of the code to the standard output\n");
	ft_printf("\t-x : decompile .cor file. Will try to mark labels if ");
	ft_printf("address parameters are relevant.\n");
	ft_printf("\t-c : colorized output when annotating code.\n");
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
