/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_asm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnagy <lnagy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 16:51:13 by lnagy             #+#    #+#             */
/*   Updated: 2017/03/10 16:51:14 by lnagy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*getfile(char *file)
{
	int		fd;
	char	*line;
	char	*source;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (NULL);
	source = NULL;
	line = NULL;
	while (get_next_line(fd, &line) > 0)
		source = ft_strjoinfree(source, ft_strjoinfree(line, "\n", 1), 3);
	return (source);
}

t_expr	*parse_asm(t_parser *p, char *file, char **source)
{
	t_expr		*expr;
	char		*ret;

	if ((*source = getfile(file)) == NULL)
	{
		ft_printf("Can't read file %s\n", file);
		return (NULL);
	}
	expr = NULL;
	ret = run_parser(p, *source, "EXPR", &expr);
	return (expr);
}
