/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 17:54:54 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/11/05 10:56:12 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
** cмена координат двух точек
*/

int				inside_sector(t_game *game, double x, double y, t_sector sector)
{
	t_vec2	f_point;
	t_vec2	s_point;
	int		i;

	i = 0;
	while (i < sector.count_wall)
	{
		f_point = *(game->points + *(sector.index_points + i));
		if (i == sector.count_wall - 1)
			s_point = *(game->points + *(sector.index_points));
		else
			s_point = *(game->points + *(sector.index_points + i + 1));
		s_point.x = s_point.x - f_point.x;
		s_point.y = s_point.y - f_point.y;
		f_point.x = x - f_point.x;
		f_point.y = y - f_point.y;
		if (cross_product(f_point, s_point) < 0)
			return (0);
		i++;
	}
	return (1);
}

/*
** поварачивает точки в систему координат игрока
*/

void			give_points_cam(t_vec2 *points_cam, t_vec2 *points,
	t_player *player, int count_points)
{
	int		i;
	double	points_x;
	double	points_y;
	t_vec2	*points_i;

	i = 0;
	while (i < count_points)
	{
		points_i = points + i;
		points_y = points_i->y - player->pos.y;
		points_x = points_i->x - player->pos.x;
		(points_cam + i)->x = points_y * sin(player->angle) + points_x *
			cos(player->angle);
		(points_cam + i)->y = points_y * cos(player->angle) - points_x *
			sin(player->angle);
		i++;
	}
}

double			calc(char word, t_player player, t_sprite *sprite)
{
	double pos_y;
	double pos_x;

	pos_y = (sprite)->pos.y - player.pos.y;
	pos_x = (sprite)->pos.x - player.pos.x;
	if (word == 'x')
		return (pos_y * sin(player.angle) + pos_x * cos(player.angle));
	return (pos_y * cos(player.angle) - pos_x * sin(player.angle));
}

void			give_sprites_cam(t_game *game)
{
	double		angle;
	double		x;
	double		y;
	t_sprite	*sprite;

	sprite = game->sprites;
	while (sprite != 0)
	{
		(sprite)->pos_in_cam.x = calc('x', game->player, sprite);
		(sprite)->pos_in_cam.y = calc('y', game->player, sprite);
		(sprite)->pos_in_cam.z = (sprite)->pos.z - game->player.pos.z;
		y = -(sprite)->pos.y + game->player.pos.y;
		x = -(sprite)->pos.x + game->player.pos.x;
		angle = atan(y / x);
		x < 0 ? angle = angle - 3.14 : 0;
		angle = angle - (sprite)->angle;
		while (angle < 0)
			angle = angle + 6.28;
		while (angle > 6.28)
			angle = angle - 6.28;
		(sprite)->angle_in_cam = angle;
		sprite = sprite->next;
	}
}

void			get_pos_z(t_player *player, t_sector *sectors)
{
	t_sector *sum;

	sum = sectors + player->curr_sector;
	if (player->z_accel > 0)
	{
		player->pos.z + player->z_accel >= sum->ceil ? player->z_accel = 0 : 0;
		player->pos.z += player->z_accel;
		player->z_accel -= ACCEL;
	}
	else if (player->z_accel == 0)
	{
		player->foots > sum->floor ? player->z_accel -= ACCEL : 0;
	}
	else if (player->z_accel < 0)
	{
		if (player->foots + player->z_accel < sum->floor)
		{
			player->z_accel = 0;
			player->pos.z = sum->floor + player->b_foots;
		}
		player->pos.z += player->z_accel;
		player->z_accel -= ACCEL;
	}
	player->foots = player->pos.z - 0.5;
	player->knees = player->pos.z - player->b_knees;
}
