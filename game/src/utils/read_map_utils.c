/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 16:47:54 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/11/01 16:52:31 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		count_wall(char **line)
{
	int	i;
	int result;

	i = 0;
	result = 0;
	while (line[3][i])
	{
		if (line[3][i] == ' ')
			result++;
		i++;
	}
	return (result);
}

void	fill_index_points(t_sector *sector, char **buffer)
{
	int i;

	i = 0;
	while (i < sector->count_wall)
	{
		*(sector->index_points + i) = ft_atoi(buffer[i]);
		*(sector->grid + i) = 0;
		i++;
	}
}

void	malloc_sector_values(t_sector *sector)
{
	if ((sector->index_points = (int*)malloc(sizeof(int) *
		sector->count_wall)) == 0)
		check_error_n_exit(1, "malloc error");
	if ((sector->grid = (int*)malloc(sizeof(int) *
		sector->count_wall)) == 0)
		check_error_n_exit(1, "malloc error");
	if ((sector->neighbors = (int*)malloc(sizeof(int) *
		sector->count_wall)) == 0)
		check_error_n_exit(1, "malloc error");
}

int		count(int fd)
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
