/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramory-l <ramory-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 19:25:52 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/10/30 15:10:32 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/* считывание самой первой строки и возврат значения из нее */
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

/* считывание инф-ии со строки 'v' */
static void	define_vertex(t_vec2 *points, char **line)
{
	points->y = ft_atod(line[1]);
	points->x = ft_atod(line[2]);
}
/* считывание инф-ии со строки 's' */
static void	define_sector(t_sector *sector, char **line)
{
	int		counter;
	int		i;
	char	**buffer;
	counter = 0;
	i = 0;
	/* считывание пола и потолка */
	buffer = ft_strsplit(line[1], ' ');
	sector->ceil = ft_atod(buffer[1]);
	sector->floor = ft_atod(buffer[0]);
	clean_buffer(buffer);
	/* кол-во стен (кол-во инексов векторов) */
	while(line[3][i])
	{
		if (line[3][i] == ' ')
			counter++;
		i++;
	}
	i = 0;
	sector->count_wall = counter + 1;
	if ((sector->index_points = (int*)malloc(sizeof(int) * sector->count_wall)) == 0)
		check_error_n_exit(1, "malloc error");
	buffer = ft_strsplit(line[3], ' ');
	while(i < sector->count_wall)
	{
		*(sector->index_points + i) = ft_atoi(buffer[i]);
		i++;
	}
	clean_buffer(buffer);
	i = 0;
	if ((sector->neighbors = (int*)malloc(sizeof(int) *  sector->count_wall)) == 0)
		check_error_n_exit(1, "malloc error");
	buffer = ft_strsplit(line[4], ' ');
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
	// buffer = ft_strsplit(line[4], ' ');
	while(i < sector->count_wall)
	{
		*(sector->grid + i) = 0;
		i++;
	}
	// clean_buffer(buffer);
	sector->brightness = (double)ft_atoi(line[2]) / 100;
}

static void	read_player_pos(t_game *game, char **line)
{
	char	**buffer;
	
	buffer = ft_strsplit(line[1], ' ');
	game->player.pos.x = ft_atoi(buffer[0]);
	game->player.pos.y = ft_atoi(buffer[1]);
	clean_buffer(buffer);
	buffer = ft_strsplit(line[2], ' ');
	game->player.angle = ft_atoi(buffer[0]);
	game->player.curr_sector = 1;
	clean_buffer(buffer);
}

/* чтение карты */
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
	if ((game->points = (t_vec2*)malloc(sizeof(t_vec2) * game->count_points)) == 0)
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
		else if (line[0] == 'p')
		{
			buffer = ft_strsplit(line, '\t');
			read_player_pos(game, buffer);
			clean_buffer(buffer);
		}
		free(line);
	}	
	close(fd);
}
