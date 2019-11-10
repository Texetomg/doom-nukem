/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramory-l <ramory-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 19:02:35 by ramory-l          #+#    #+#             */
/*   Updated: 2019/11/09 19:20:30 by ramory-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static int	one_sec_check(t_game *game, t_sprite *sprite, int num)
{
	int			i;
	t_vec2		f_point;
	t_vec2		s_point;
	t_sector	*cur_sec;
	double		cross;

	cur_sec = game->sectors + num;
	i = 0;
	while (i < cur_sec->count_wall)
	{
		f_point = *(game->points + *(cur_sec->index_points + i));
		if (i == cur_sec->count_wall - 1)
			s_point = *(game->points + *(cur_sec->index_points));
		else
			s_point = *(game->points + *(cur_sec->index_points + i + 1));
		s_point.x = s_point.x - f_point.x;
		s_point.y = s_point.y - f_point.y;
		f_point.x = sprite->pos.x - f_point.x;
		f_point.y = sprite->pos.y - f_point.y;
		cross = cross_product(f_point, s_point);
		if (cross < 0)
			return (0);
		i++;
	}
	return (1);
}

static int	check_cross(t_game *game, t_sprite *sprite, t_sc *sc)
{
	if (sc->cross < -0.0001)
	{
		sc->j = 0;
		while (sc->j < sc->cur_sec->count_wall)
		{
			if (sc->cur_sec->neighbors[sc->j] == -1)
			{
				sc->j++;
				continue;
			}
			if (one_sec_check(game, sprite, sc->cur_sec->neighbors[sc->j]))
			{
				sprite->sector = sc->cur_sec->neighbors[sc->j];
				sprite->pos.z = sprite->heigth + (game->sectors +
				sc->cur_sec->neighbors[sc->j])->floor;
				return (0);
			}
			sc->j++;
		}
	}
	return (1);
}

int			sector_check(t_game *game, t_sprite *sprite)
{
	t_sc sc;

	sc.cur_sec = game->sectors + sprite->sector;
	sc.i = 0;
	while (sc.i < sc.cur_sec->count_wall)
	{
		sc.f_point = *(game->points + *(sc.cur_sec->index_points + sc.i));
		if (sc.i == sc.cur_sec->count_wall - 1)
			sc.s_point = *(game->points + *(sc.cur_sec->index_points));
		else
			sc.s_point = *(game->points +
			*(sc.cur_sec->index_points + sc.i + 1));
		sc.s_point.x = sc.s_point.x - sc.f_point.x;
		sc.s_point.y = sc.s_point.y - sc.f_point.y;
		sc.f_point.x = sprite->pos.x - sc.f_point.x;
		sc.f_point.y = sprite->pos.y - sc.f_point.y;
		sc.cross = cross_product(sc.f_point, sc.s_point);
		if (!check_cross(game, sprite, &sc))
			return (0);
		sc.i++;
	}
	return (0);
}
