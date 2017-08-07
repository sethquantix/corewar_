/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opts_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 17:58:38 by cchaumar          #+#    #+#             */
/*   Updated: 2017/08/07 06:14:26 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

int		tok_func_path(char **s)
{
	if (*s && (**s == '-' || !**s))
		return (1);
	while (**s && !ft_iswhite(**s))
		(*s)++;
	return (0);
}

int		tok_func_verbose(char **s)
{
	int		n;
	char	*p;

	p = *s;
	n = 0;
	while (ft_isdigit(**s))
	{
		n = 10 * n + (**s) - '0';
		(*s)++;
	}
	if (!ft_iswhite(**s))
	{
		*s = p;
		return (1);
	}
	return (0);
}

int		tok_func_none(char **s)
{
	(void)s;
	return (0);
}

int		tok_func_number(char **s)
{
	char	*p;
	int		n;

	p = *s;
	if (**s == '+' || **s == '-')
		(*s)++;
	n = 0;
	while (**s && ft_isdigit(**s))
	{
		n++;
		(*s)++;
	}
	if (!n)
		*s = p;
	return (n ? 0 : 1);
}

t_token	g_crwr_opts[] = {
	{"PATH", tok_func_path, 0, TOKEN_TYPE_FNC},
	{"WS", 0, " \t", TOKEN_TYPE_STR},
	{"OPT_G", 0, "-g", TOKEN_TYPE_EXP},
	{"INTERRUPT", 0, "--", TOKEN_TYPE_EXP},
	{"OPT_GRAPHIC", 0, "--graphic", TOKEN_TYPE_EXP},
	{"OPT_AFF", 0, "--aff", TOKEN_TYPE_EXP},
	{"OPT_N", 0, "-n", TOKEN_TYPE_EXP},
	{"OPT_A", 0, "-a", TOKEN_TYPE_EXP},
	{"OPT_O", 0, "-o", TOKEN_TYPE_EXP},
	{"OPT_V", 0, "-v", TOKEN_TYPE_EXP},
	{"OPT_VERBOSE", 0, "--verbose", TOKEN_TYPE_EXP},
	{"OPT_DUMP", 0, "--dump", TOKEN_TYPE_EXP},
	{"OPT_D", 0, "-d", TOKEN_TYPE_EXP},
	{"OPT_STEP", 0, "--step", TOKEN_TYPE_EXP},
	{"OPT_S", 0, "-s", TOKEN_TYPE_EXP},
	{"NUMBER", tok_func_number, 0, TOKEN_TYPE_FNC},
	{"VERBOSE", tok_func_verbose, 0, TOKEN_TYPE_FNC},
	{"ENDLINE", 0, "\0", TOKEN_TYPE_ONE},
	{"NONE", tok_func_none, 0, TOKEN_TYPE_FNC},
	{0, 0, 0, 0}
};
