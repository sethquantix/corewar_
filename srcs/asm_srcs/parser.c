/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 08:33:40 by cchaumar          #+#    #+#             */
/*   Updated: 2017/06/09 08:33:41 by cchaumar         ###   ########.fr       */
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
	free(line);
	return (source);
}

t_expr	*parse_asm(char *file, char **source)
{
	t_expr	*ret;

	if ((*source = getfile(file)) == NULL)
	{
		ft_printf("Can't read file %s\n", file);
		return (NULL);
	}

	return (ret);
}