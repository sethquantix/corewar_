/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/04 05:27:30 by tsedigi           #+#    #+#             */
/*   Updated: 2017/08/04 05:27:31 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_op		*op_for_name(char *name)
{
	int	i;

	i = 0;
	while (g_op_tab[i].name)
		if (ft_strcmp(name, g_op_tab[i].name) == 0)
			return (&g_op_tab[i]);
		else
			i++;
	return (NULL);
}

char		*err(int err_code, ...)
{
	static const char	*tab[] = {
		"Invalid argument",
		"Unexpected token %s : \"%s\"",
		"Unexpected symbol \"%.1s\"",
		"Error : %s : File too small to be a champion.\n",
		"Error : %s : This does not appear to be a champion.\n",
		"Error : %s : Corrupted source (size doesn't match (%zu))\n",
		"Can't open %s for writing\n"
	};
	va_list				va;
	char				*e;

	va_start(va, err_code);
	e = NULL;
	ft_vasprintf(&e, tab[err_code], va);
	va_end(va);
	return (e);
}
