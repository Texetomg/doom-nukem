/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 19:25:52 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/04/01 13:49:55 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

//считывание самой первой строки и возврат значения из нее
static int	vertex_count(int fd)
{
	char	*line;
	int		count;
	int		gnl;

	if ((gnl = (get_next_line(fd, &line))) != 0)
	{
		if (gnl == -1)
		{
			check_error_n_exit(1, "gnl return -1");
			return (0);
		}
		else
		{
			count = ft_atoi(line);
			free(line);
			return (count);	
		}
	}
	else
		return (0);
}
//поиск координат x/y(й) в строке
static void	define_coords(vec2 *points, char *line)
{
	int		j;
	int		i;
	char	buff[4];

	j = 0;
	i = 2;
	while (line[i] && line[i] != '\t')
		buff[j++] = line[i++];
	points->x = ft_atoi(buff);
	ft_strclr(buff);
	i += 2;
	j = 0;
	while (line[i] && line[i] != '\t')
		buff[j++] = line[i++];
	points->y = ft_atoi(buff);
}
//чтение карты
vec2		*read_map(char *name)
{
	char	*line;
	int		fd;
	int		i;
	vec2	*points;
	int		gnl;
	
	i = 0;
	if ((fd = open(name, O_RDONLY)) < 0)
		check_error_n_exit(1, "file descriptor < 0");
	if ((points = (vec2*)malloc(sizeof(vec2) * vertex_count(fd))) == 0)
		check_error_n_exit(1, "malloc error");
	while ((gnl = (get_next_line(fd, &line))) != 0)
	{
		if (gnl == -1)
			check_error_n_exit(1, "gnl return -1");
		else if (line[0] == 'v')
		{
			define_coords(points + i, line);
			i++;
		}
		else if (line[0] == 's')
		{
			define_coords(points + i, line);
			i++;
		}
		free(line);
	}	
	close(fd);
	return(points);
}
