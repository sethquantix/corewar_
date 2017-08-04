/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 14:44:12 by cchaumar          #+#    #+#             */
/*   Updated: 2017/02/04 14:44:13 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	check_tok_one(t_token *tok, char **s)
{
	if (**s != tok->specifiers[0])
		return (1);
	(*s) += !!tok->specifiers[0];
	return (0);
}

static int	check_tok_exp(t_token *tok, char **s)
{
	int	len;

	len = ft_strlen(tok->specifiers);
	if (ft_strncmp(*s, tok->specifiers, len))
		return (1);
	(*s) += len;
	return (0);
}

static int	check_tok_str(t_token *tok, char **s)
{
	int	ret;

	ret = 1;
	while (**s && ft_strchr(tok->specifiers, **s))
	{
		ret = 0;
		if (**s)
			(*s)++;
		else
			break ;
	}
	return (ret);
}

static int	check_tok_fnc(t_token *tok, char **s)
{
	return (tok->f(s));
}

int			parser_check_tok(t_token *tok, char **s)
{
	static int	(*tokens[])(t_token *, char **) = {
		check_tok_one,
		check_tok_exp,
		check_tok_str,
		check_tok_fnc};
	int			ret;

	ret = tokens[tok->type](tok, s);
	return (ret);
}
