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
		"Invalid argument \"%s\" parsing %s",
		"Unexpected token %s : \"%s\"",
		"Unexpected symbol \"%.1s\"",
		"Unexpected instruction %s"};
	va_list				va;
	char				*e;

	va_start(va, err_code);
	e = NULL;
	ft_vasprintf(&e, tab[err_code], va);
	va_end(va);
	return (e);
}

t_list		*get_rule(t_list *stack)
{
	char			**t;
	t_list			*rule;
	t_tok			*e;

	rule = NULL;
	while (stack)
	{
		e = tok(stack);
		t = (char **)g_list;
		while (*t)
			if (!ft_strcmp(*t, e->rule->name))
			{
				rule = stack;
				break ;
			}
			else
				t++;
		stack = stack->next;
	}
	return (rule);
}

char		*getword(char *s)
{
	char	*p;

	while (ft_iswhite(*s))
		s++;
	p = s;
	while (!ft_iswhite(*p))
		p++;
	return (ft_strsub(s, 0, p - s));
}
