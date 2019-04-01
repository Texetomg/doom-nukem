/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 19:25:52 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/04/01 17:22:35 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

//считывание самой первой строки и возврат значения из нее
static int	count(int fd)
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

static int	find_number(char *line, int *i)
{
	char	buff[4];
	int		j;

	j = 0;
	ft_strclr(buff);
	while (line[*i] && (line[*i] == '\t' || line[*i] == ' '))
		*i += 1;
	while (line[*i] && line[*i] != '\t' && line[*i] != ' ')
	{
		buff[j] = line[*i];
		j++;
		*i += 1;
	}
	return(ft_atoi(buff));
}
//поиск координат x/y в строке
static void	define_vertex(vec2 *points, char *line)
{

	int		i;

	i = 2;
	points->y = find_number(line, &i);
	points->x = find_number(line, &i);
}


static void	define_sector(t_sector *sector, char *line)
{
	int		i;

	i = 2;
	sector->ceil = find_number(line, &i);
	sector->floor = find_number(line, &i);
}

//чтение карты
void		read_map(char *name, t_game *game)
{
	char	*line;
	int		fd;
	int		i;
	int		j;
	int		gnl;
	
	i = 0;
	j = 0;
	if ((fd = open(name, O_RDONLY)) < 0)
		check_error_n_exit(1, "file descriptor < 0");

	game->count_points = count(fd);
	game->count_sectors = count(fd);
	
	if ((game->points = (vec2*)malloc(sizeof(vec2) * game->count_points)) == 0)
		check_error_n_exit(1, "malloc error");
	while ((gnl = (get_next_line(fd, &line))) != 0)
	{
		
		if (gnl == -1)
			check_error_n_exit(1, "gnl return -1");
		else if (line[0] == 'v')
		{
			define_vertex(game->points + i, line);
			i++;
		}
		else if (line[0] == 's')
		{
			define_sector(game->sectors + j, line);
			j++;
		}
		free(line);
	}	
	close(fd);
}
