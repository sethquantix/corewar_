/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 15:27:12 by cchaumar          #+#    #+#             */
/*   Updated: 2017/02/05 15:28:06 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_token		g_asm_tokens[] = {
	{"COMMENT_CMD_STRING", 0, COMMENT_CMD_STRING, TOKEN_TYPE_EXP},
	{"NAME_CMD_STRING", 0, NAME_CMD_STRING, TOKEN_TYPE_EXP},
	{"LIVE_NAME", 0, "live", TOKEN_TYPE_EXP},
	{"LD_NAME", 0, "ld", TOKEN_TYPE_EXP},
	{"ST_NAME", 0, "st", TOKEN_TYPE_EXP},
	{"ADD_NAME", 0, "add", TOKEN_TYPE_EXP},
	{"SUB_NAME", 0, "sub", TOKEN_TYPE_EXP},
	{"AND_NAME", 0, "and", TOKEN_TYPE_EXP},
	{"OR_NAME", 0, "or", TOKEN_TYPE_EXP},
	{"XOR_NAME", 0, "xor", TOKEN_TYPE_EXP},
	{"ZJMP_NAME", 0, "zjmp", TOKEN_TYPE_EXP},
	{"FORK_NAME", 0, "fork", TOKEN_TYPE_EXP},
	{"LDI_NAME", 0, "ldi", TOKEN_TYPE_EXP},
	{"STI_NAME", 0, "sti", TOKEN_TYPE_EXP},
	{"LLD_NAME", 0, "lld", TOKEN_TYPE_EXP},
	{"LLDI_NAME", 0, "lldi", TOKEN_TYPE_EXP},
	{"LFORK_NAME", 0, "lfork", TOKEN_TYPE_EXP},
	{"AFF_NAME", 0, "aff", TOKEN_TYPE_EXP},
	{"LABEL_STRING", 0, LABEL_CHARS, TOKEN_TYPE_STR},
	{"NEWLINE", 0, "\n", TOKEN_TYPE_STR},
	{"WS", 0, " \t", TOKEN_TYPE_STR},
	{"COMMENT_CHAR", 0, COMMENT_CHAR, TOKEN_TYPE_ONE},
	{"SEPARATOR", 0, SEPARATOR_CHAR, TOKEN_TYPE_ONE},
	{"DIRECT_CHAR", 0, DIRECT_CHAR, TOKEN_TYPE_ONE},
	{"LABEL_CHAR", 0, LABEL_CHAR, TOKEN_TYPE_ONE},
	{"REG_CHAR", 0, REG_CHAR, TOKEN_TYPE_ONE},
	{"ENDLINE", 0, "\0", TOKEN_TYPE_ONE},
	{"REG_NBR", tok_func_reg_nbr, 0, TOKEN_TYPE_FNC},
	{"NUMBER", tok_func_number, 0, TOKEN_TYPE_FNC},
	{"STRING", tok_func_string, 0, TOKEN_TYPE_FNC},
	{"ASCII", tok_func_ascii, 0, TOKEN_TYPE_FNC},
	{"NONE", tok_func_none, 0, TOKEN_TYPE_FNC},
	{0, 0, 0, 0}
};

int		tok_func_string(char **s)
{
	char	*p;

	p = *s;
	if (**s != '"')
		return (1);
	(*s)++;
	while (**s && **s != '"')
		(*s)++;
	if (**s)
	{
		(*s)++;
		return (0);
	}
	*s = p;
	return (1);
}

int		tok_func_ascii(char **s)
{
	char	*p;

	p = *s;
	while (**s && **s != '\n')
		(*s)++;
	return (p == *s ? 1 : 0);
}

int		tok_func_number(char **s)
{
	const char	*valid[2] = {
		"0123456789", "0123456789abcdef"
	};
	char	*p;
	int		hex;
	int		n;

	p = *s;
	hex = 0;
	if ((ft_strncmp(*s, "0x", 2) == 0 || ft_strncmp(*s, "0X", 2) == 0) && (hex = 1))
		*s += 2;
	else if (**s == '+' || **s == '-')
		*s += 1;
	n = 0;
	while (**s && ft_strchr(valid[hex], ft_tolower(**s)))
	{
		n++;
		(*s)++;
	}
	if (!n)
		*s = p;
	return (n ? 0 : 1);
}

int		tok_func_reg_nbr(char **s)
{
	char	*p;
	char	*t;
	int		n;

	p = *s;
	while (ft_isdigit(**s))
		(*s)++;
	if (*s == p)
		return (1);
	t = ft_strsub(p, 0, *s - p);
	n = ft_atoi(t);
	free(t);
	if (n <= 0 || n > REG_NUMBER)
		*s = p;
	return (n > 0 && n <= REG_NUMBER ? 0 : 1);
}
