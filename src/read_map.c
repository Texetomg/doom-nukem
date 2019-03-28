/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 19:25:52 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/03/28 14:29:38 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

void	*read_coord(char *line, vec2 *points)
{
	char	point[5];
	int		j;
	int		x;

	x = 1;
	while (*line && *line == '\t')
	{
		++line;
		j = 0;
		while (*line && *line != '\t')
		{
			point[j] = *line;
			++j;
			++line;
		}
		x == 1 ? points->x = ft_atoi(point) : points->x;
		x == 0 ? points->y = ft_atoi(point) : points->y;
		x = 0;
	}
}

vec2 *read_map(char *name)
{
	char	*line;
	int		gnl;
	int		fd;
	vec2	*points;
	int		position;

	position = 0;
	if ((fd = open(name, O_RDONLY)) < 0)
		check_error_n_exit(1, "file descriptor < 0");
	while ((gnl = get_next_line(fd, &line)) != 0)
	{
		if (gnl == -1)
			return (0);
		if (line[0] == '&')
			points = (vec2*)malloc(sizeof(vec2) * ft_atoi(line[1]));
		if (line[0] == 'v')
		{
			++line;
			read_coord(&line, points + position);
		}
		++position;
		free(line);
	}
	close(fd);
	return (points);
}