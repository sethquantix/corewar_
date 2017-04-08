/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnagy <lnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 15:23:53 by lnagy             #+#    #+#             */
/*   Updated: 2017/03/07 15:23:55 by lnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		tok_func_path(char **s)
{
	if (*s && (**s == '-' || !**s))
		return (1);
	while (**s && !ft_iswhite(**s))
		(*s)++;
	return (0);
}

int		tok_func_none(char **s)
{
	(void)s;
	return (0);
}

t_token	g_asm_opts[] = {
	{"PATH", tok_func_path, 0, TOKEN_TYPE_FNC},
	{"WS", 0, " \t", TOKEN_TYPE_STR},
	{"OPT_A", 0, "-a", TOKEN_TYPE_EXP},
	{"OPT_X", 0, "-x", TOKEN_TYPE_EXP},
	{"OPT_D", 0, "-d", TOKEN_TYPE_EXP},
	{"NONE", tok_func_none, 0, TOKEN_TYPE_FNC},
	{0, 0, 0, 0}
};
