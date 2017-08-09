/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/08 17:48:43 by cchaumar          #+#    #+#             */
/*   Updated: 2017/08/09 08:53:56 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				load_source(t_champ *c)
{
	int			fd;
	struct stat	file;

	if ((fd = open(c->file_name, O_RDONLY)) == -1)
		return (err(ERR, "[%s] : Error (ERR_OPEN_FILE)\n", c->file_name));
	if (fstat(fd, &file) == -1)
		return (err(ERR, "[%s] : Error (ERR_UNKNOWN_ERROR)\n", c->file_name));
	if (file.st_size == 0)
		return (err(ERR, "[%s] : Error (ERR_BAD_FILE)\n", c->file_name));
	if (read(fd, &c->head, sizeof(t_header)) != sizeof(t_header))
		return (err(ERR, "[%s] : Error (ERR_BAD_HEADER)\n", c->file_name));
	ft_endian(&c->head.prog_size, 4);
	ft_endian(&c->head.magic, 4);
	if (c->head.magic != COREWAR_EXEC_MAGIC)
		return (err(ERR, "[%s] : Error (ERR_BAD_MAGIC)\n", c->file_name));
	c->source = try(c->head.prog_size);
	if (read(fd, c->source, c->head.prog_size) != c->head.prog_size)
		return (err(ERR, "[%s] : Error (ERR_CORRUPT)\n", c->file_name));
	close(fd);
	return (0);
}

static t_champ	new_champion(char *name, char *number, t_arena *a)
{
	static int		id = 0;
	t_champ			c;
	int				ret;

	ft_bzero(&c, sizeof(t_champ));
	c.head = empty_head();
	c.file_name = name;
	if (load_source(&c))
	{
		ft_memdel((void **)&c.source);
		return (c);
	}
	if (number)
	{
		if (check_set(a->champs, a->champ_count,
			(ret = ft_atoi(number))))
			err(WARN, "[%s] : Duplicate player number\n", c.file_name);
		else
		{
			c.set = 1;
			c.num = ret;
		}
	}
	c.id = --id;
	return (c);
}

void			player(t_expr **e, t_arena *a)
{
	const char	*warn[] = {"Warning : Didn't load champion \"%s\"%s",
		" because there is already 4 champions loaded.\n"};
	t_champ		c;
	char		*file;
	char		*number;

	*e = (*e)->next;
	number = ft_strcmp((*e)->rule, "NUMBER") == 0 ? (*e)->expr : NULL;
	if (number)
		*e = (*e)->next;
	file = (*e)->expr;
	c = new_champion(file, number, a);
	if (c.source == NULL)
		return ;
	if (a->champ_count >= 4)
		err(WARN, warn[0], c.head.prog_name, warn[1]);
	else
		ft_pushback((void **)&a->champs, sizeof(t_champ), a->champ_count++, &c);
}

void			read_args(t_expr *expr, t_arena *a)
{
	const char	*rules[] = {"OPTION_G", "OPTION_V", "OPTION_D", "OPTION_O",
		"OPTION_A", "OPTION_S", "PLAYER", NULL};
	static void	(*handlers[])(t_expr **, t_arena *) = {
		option_g, option_v, option_d, option_o, option_a, option_s,
		player, NULL};
	int			i;

	while (expr)
	{
		i = 0;
		while (rules[i])
			if (!ft_strncmp(rules[i], expr->rule, ft_strlen(rules[i])))
			{
				handlers[i](&expr, a);
				break ;
			}
			else
				i++;
		if (!rules[i])
			die(EXIT_FAILURE, "Error : Bad options\n");
		expr = expr->next;
	}
}
