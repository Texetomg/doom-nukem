/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 19:25:52 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/03/28 16:36:59 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

void	read_coord(char *line, vec2 *points)
{
	char	point[5];
	int		i;
	int		j;
	int		x;

	i = 0;
	x = 1;
	while (line[i] != 0)
	{
		if (line[i] == '\t')
			++i;
		else
		{
			j = 0;
			while (line[i] && line[i] != '\t')
				point[++j] = line[++i];
		}
		x == 1 ? points->x = ft_atoi(point) : points->x;
		x == 0 ? points->y = ft_atoi(point) : points->y;
		x = 0;
		ft_strclr(point);
	}
}

vec2	*read_map(char *name, vec2 *points)
{
	char	*line;
	int		gnl;
	int		fd;
	int		position;

	position = 0;
	if ((fd = open(name, O_RDONLY)) < 0)
		check_error_n_exit(1, "file descriptor < 0");
	while ((gnl = get_next_line(fd, &line)) != 0)
	{
		if (gnl == -1)
			check_error_n_exit(1, "gnl -1");
		if (line[0] == '&')
			points = (vec2*)malloc(sizeof(vec2) * ft_atoi(&line[1]));
		if (line[0] == 'v')
		{
			read_coord(line + 1, points + position);
			++position;
		}
		free(line);
	}
	close(fd);
	return (points);
}
