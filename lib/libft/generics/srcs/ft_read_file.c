/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 07:02:19 by cchaumar          #+#    #+#             */
/*   Updated: 2017/02/17 07:09:04 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_generics.h"

char	*ft_read_file(char *name)
{
	int		fd;
	char	*s;
	char	*line;

	s = NULL;
	if ((fd = open(name, O_RDONLY)) == -1)
		return (NULL);
	while (get_next_line(fd, &line) > 0)
		s = ft_strjoinfree(s, ft_strjoinfree(line, "\n", 1), s ? 3 : 2);
	close(fd);
	return (s);
}
