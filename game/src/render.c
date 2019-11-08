/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramory-l <ramory-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 16:12:49 by thorker           #+#    #+#             */
/*   Updated: 2019/11/08 16:25:38 by ramory-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int	ft_bright(int color, double bright)
{
	int r;
	int g;
	int b;
	int new_color;

	r = (color & 0xFF0000) >> 16;
	r = r * bright;
	g = (color & 0xFF00) >> 8;
	g = g * bright;
	b = (color & 0xFF);
	b = b * bright;
	new_color = r * 256 * 256 + g * 256 + b;
	return (new_color);
}

/*
** рекурсивная функция, которая отрисовывает сектор;
*/

static void init(t_ds *ds, t_game *game, t_draw *for_draw)
{
	ds->first_point = *(game->points_cam +
	*((game->sectors + for_draw->curr_sector)->index_points + ds->i));
	ds->x1 = (game->points +
	*((game->sectors + for_draw->curr_sector)->index_points + ds->i))->x;
	ds->y1 = (game->points +
	*((game->sectors + for_draw->curr_sector)->index_points + ds->i))->y;
	if (ds->i == (game->sectors + for_draw->curr_sector)->count_wall - 1)
	{
		ds->x2 = (game->points +
		*((game->sectors + for_draw->curr_sector)->index_points))->x;
		ds->y2 = (game->points +
		*((game->sectors + for_draw->curr_sector)->index_points))->y;
		ds->second_point = *(game->points_cam +
		*((game->sectors + for_draw->curr_sector)->index_points));
	}
	else
	{
		ds->x2 = (game->points +
		*((game->sectors + for_draw->curr_sector)->index_points + ds->i + 1))->x;
		ds->y2 = (game->points +
		*((game->sectors + for_draw->curr_sector)->index_points + ds->i + 1))->y;
		ds->second_point = *(game->points_cam +
		*((game->sectors + for_draw->curr_sector)->index_points + ds->i + 1));
	}
}

static void draw_sprites_loop(t_ds *ds, t_game *game, t_draw *for_draw)
{
	ds->sprite = game->sprites;
	while (ds->sprite != 0)
	{
		if (ds->sprite->sector == for_draw->curr_sector)
		{
			draw_sprites(game, *for_draw, ds->sprite,
			(game->sectors + for_draw->curr_sector)->brightness);
		}
		ds->sprite = ds->sprite->next;
	}
}

void    draw_sector(t_game *game, t_draw for_draw)
{
	t_ds		ds;
	t_dw_a      dw_a;
	t_pds_a		pds_a;
	t_inter		inter;
	
	ds.i = 0;
	inter.ds = &ds;
	inter.dw_a = &dw_a;
	inter.pds_a = &pds_a;
	inter.for_draw = &for_draw;
	inter.game = game;
	while (ds.i < (game->sectors + for_draw.curr_sector)->count_wall)
	{
		init(&ds, game, &for_draw);
		if (ds.first_point.x < 0 && ds.second_point.x < 0 && ++ds.i)
			continue;
		ds.x1_b4 = -ds.first_point.y;
		ds.x2_b4 = -ds.second_point.y;
		ds.y1a = ds.first_point.x;
		ds.y2a = ds.second_point.x;
		intersections(&inter);
	}
	draw_sprites_loop(&ds, game, &for_draw);
}
