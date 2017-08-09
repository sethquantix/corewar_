/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 03:33:33 by cchaumar          #+#    #+#             */
/*   Updated: 2017/02/05 11:08:56 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void		parser_die(char *s, int exit_code)
{
	ft_printf("%s\n", s);
	exit(exit_code);
}

char		*parser_getl(char *s)
{
	char	*p;

	if (!s)
		return (NULL);
	if (!*s)
		return (NULL);
	p = ft_strchr(s, '\n');
	p = p ? p : s + ft_strlen(s);
	return (ft_strsub(s, 0, p - s));
}

void		parser_get_pos(char *pos, char *s, int *l, int *c)
{
	*l = 1;
	*c = 1;
	while (pos != s)
	{
		*c = *s == '\n' ? 0 : *c;
		*l += *s == '\n';
		s++;
		(*c)++;
	}
}
