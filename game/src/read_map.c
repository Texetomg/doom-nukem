/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 19:25:52 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/11/01 16:59:31 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
** считывание инф-ии со строки 'v'
*/

static void	define_vertex(t_vec2 *points, char **line)
{
	points->y = ft_atod(line[1]);
	points->x = ft_atod(line[2]);
}

/*
** считывание инф-ии со строки 's'
*/

static void	define_sector(t_sector *sector, char **line)
{
	int		counter;
	int		i;
	char	**buffer;

	i = 0;
	buffer = ft_strsplit(line[1], ' ');
	sector->ceil = ft_atod(buffer[1]);
	sector->floor = ft_atod(buffer[0]);
	clean_buffer(buffer);
	counter = count_wall(line);
	sector->count_wall = counter + 1;
	malloc_sector_values(sector);
	buffer = ft_strsplit(line[3], ' ');
	fill_index_points(sector, buffer);
	clean_buffer(buffer);
	buffer = ft_strsplit(line[4], ' ');
	while (i < sector->count_wall)
	{
		*(sector->neighbors + i) = ft_atoi(buffer[i]);
		i++;
	}
	clean_buffer(buffer);
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

/*
** чтение карты
*/

void		main_cycle(t_game *game, int fd)
{
	char	**buffer;
	int		gnl;
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while ((gnl = (get_next_line(fd, &line))) != 0)
	{
		gnl == -1 ? check_error_n_exit(1, "gnl return -1") : 0;
		buffer = ft_strsplit(line, '\t');
		line[0] == 'v' ? define_vertex(game->points + i++, buffer) : 0;
		line[0] == 's' ? define_sector(game->sectors + j++, buffer) : 0;
		line[0] == 'p' ? read_player_pos(game, buffer) : 0;
		clean_buffer(buffer);
		free(line);
	}
}

void		read_map(char *name, t_game *game)
{
	int		fd;

	if ((fd = open(name, O_RDONLY)) < 0)
		check_error_n_exit(1, "file descriptor < 0");
	game->count_points = count(fd);
	game->count_sectors = count(fd);
	if ((game->points = (t_vec2*)malloc(sizeof(t_vec2) *
		game->count_points)) == 0)
		check_error_n_exit(1, "malloc error");
	if ((game->sectors = (t_sector*)malloc(sizeof(t_sector) *
		game->count_sectors)) == 0)
		check_error_n_exit(1, "malloc error");
	main_cycle(game, fd);
	close(fd);
}
