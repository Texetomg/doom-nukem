/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 19:25:52 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/05/28 19:03:46 by thorker          ###   ########.fr       */
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

//считывание инф-ии со строки 'v'
static void	define_vertex(vec2 *points, char **line)
{
	points->y = ft_atod(line[1]);
	points->x = ft_atod(line[2]);
}
//считывание инф-ии со строки 's'
static void	define_sector(t_sector *sector, char **line)
{
	int		counter;
	int		i;
	char	**buffer;
	counter = 0;
	i = 0;
	//считывание пола и потолка
	buffer = ft_strsplit(line[1], ' ');
	sector->ceil = ft_atod(buffer[0]);
	sector->floor = ft_atod(buffer[1]);
	clean_buffer(buffer);
	//кол-во стен (кол-во инексов векторов)
	while(line[2][i])
	{
		if (line[2][i] == ' ')
			counter++;
		i++;
	}
	i = 0;
	sector->count_wall = counter + 1;
	if ((sector->index_points = (int*)malloc(sizeof(int) * sector->count_wall)) == 0)
		check_error_n_exit(1, "malloc error");
	buffer = ft_strsplit(line[2], ' ');
	while(i < sector->count_wall)
	{
		*(sector->index_points + i) = ft_atoi(buffer[i]);
		i++;
	}
	clean_buffer(buffer);
	i = 0;
	if ((sector->neighbors = (int*)malloc(sizeof(int) *  sector->count_wall)) == 0)
		check_error_n_exit(1, "malloc error");
	buffer = ft_strsplit(line[3], ' ');
	while(i < sector->count_wall)
	{
		*(sector->neighbors + i) = ft_atoi(buffer[i]);
		i++;
	}
	clean_buffer(buffer);
	/*
	 *      * костыль
	 *           */
	if ((sector->grid = (int*)malloc(sizeof(int) *  sector->count_wall)) == 0)
		check_error_n_exit(1, "malloc error");
	i = 0;
	buffer = ft_strsplit(line[4], ' ');
	while(i < sector->count_wall)
	{
		*(sector->grid + i) = ft_atoi(buffer[i]);
		i++;
	}
	clean_buffer(buffer);
	sector->brightness = (double)ft_atoi(line[5]) / 100;
}


//чтение карты
void		read_map(char *name, t_game *game)
{
	char	*line;
	int		fd;
	int		i;
	int		j;
	int		gnl;
	char	**buffer;
	i = 0;
	j = 0;
	if ((fd = open(name, O_RDONLY)) < 0)
		check_error_n_exit(1, "file descriptor < 0");
	game->count_points = count(fd);
	game->count_sectors = count(fd);
	if ((game->points = (vec2*)malloc(sizeof(vec2) * game->count_points)) == 0)
		check_error_n_exit(1, "malloc error");
	if ((game->sectors = (t_sector*)malloc(sizeof(t_sector) * game->count_sectors)) == 0)
		check_error_n_exit(1, "malloc error");
	while ((gnl = (get_next_line(fd, &line))) != 0)
	{
		if (gnl == -1)
			check_error_n_exit(1, "gnl return -1");
		else if (line[0] == 'v')
		{
			buffer = ft_strsplit(line, '\t');
			define_vertex(game->points + i, buffer);
			clean_buffer(buffer);
			i++;
		}
		else if (line[0] == 's')
		{
			buffer = ft_strsplit(line, '\t');
			define_sector(game->sectors + j, buffer);
			clean_buffer(buffer);
			j++;
		}
		free(line);
	}	
	close(fd);
}
