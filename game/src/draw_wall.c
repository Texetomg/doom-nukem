/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 16:57:31 by thorker           #+#    #+#             */
/*   Updated: 2019/03/29 10:09:47 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

int		bright(int color, double bri)
{
	int r;
	int g;
	int b;

	b = color % 256;
	g = color / 256 % 256;
	r = (color / 256) / 256;
	r = (int)(r * bri);
	g = (int)(g * bri);
	b = (int)(b * bri);
	color = b + g * 256 + r * 256 * 256;
	return (color);
}

void	draw_wall_x(t_game *game, t_wall world_wall)
{
	int	x;
	double y;
	double grad;

	grad = (world_wall.pos2.y - world_wall.pos1.y) / (world_wall.pos2.x - world_wall.pos1.x);
	x = round(world_wall.pos1.x);
	y = world_wall.pos1.y + grad * (x - world_wall.pos1.x);
	while (x < world_wall.pos2.x)
	{
		if (x >= 0 && x < game->display_mode.w && y >= 0 && y < game->display_mode.h)
			((int*)game->screen->pixels)[(int)y * game->display_mode.w + x] = bright(world_wall.color, y - (int)y);
		if (x >= 0 && x < game->display_mode.w && y > -1 && y < game->display_mode.h - 1)
			((int*)game->screen->pixels)[((int)y + 1) * game->display_mode.w + x] = bright(world_wall.color, 1 - (y - (int)y));
		x++;
		y += grad;
	}
}

void	draw_wall_y(t_game *game, t_wall world_wall)
{
	int	y;
	double x;
	double grad;

	grad = (world_wall.pos2.x - world_wall.pos1.x) / (world_wall.pos2.y - world_wall.pos1.y);
	y = round(world_wall.pos1.y);
	x = world_wall.pos1.x + grad * (y - world_wall.pos1.y);
	while (y < world_wall.pos2.y)
	{
		if (x >= 0 && x < game->display_mode.w && y >= 0 && y < game->display_mode.h)
			((int*)game->screen->pixels)[y * game->display_mode.w + (int)x] = bright(world_wall.color, x - (int)x);
		if (x > -1 && x < game->display_mode.w - 1&& y >= 0 && y < game->display_mode.h)
			((int*)game->screen->pixels)[ y * game->display_mode.w + (int)x + 1] = bright(world_wall.color, 1 - (x - (int)x));
		y++;
		x += grad;
	}
}


void	draw_wall(t_game *game, t_wall world_wall)
{
	double for_swap;

	if (fabs(world_wall.pos1.x - world_wall.pos2.x) > fabs(world_wall.pos1.y - world_wall.pos2.y))
	{
		if (world_wall.pos1.x > world_wall.pos2.x)
		{
			for_swap = world_wall.pos1.x;
			world_wall.pos1.x = world_wall.pos2.x;
			world_wall.pos2.x = for_swap;
			for_swap = world_wall.pos1.y;
			world_wall.pos1.y = world_wall.pos2.y;
			world_wall.pos2.y = for_swap;
		}
		draw_wall_x(game, world_wall);
	}
	else
	{
		if (world_wall.pos1.y > world_wall.pos2.y)
		{
			for_swap = world_wall.pos1.x;
			world_wall.pos1.x = world_wall.pos2.x;
			world_wall.pos2.x = for_swap;
			for_swap = world_wall.pos1.y;
			world_wall.pos1.y = world_wall.pos2.y;
			world_wall.pos2.y = for_swap;
		}
		draw_wall_y(game, world_wall);
	}
}
void	draw_minimap(t_game *game, t_wall *world_wall)
{
	int i;
	t_wall	fov1_wall;
	t_wall	fov2_wall;

	fov1_wall.pos1.x = 100;
	fov1_wall.pos1.y = 100;
	fov2_wall.pos1.x = 100;
	fov2_wall.pos1.y = 100;
	fov1_wall.pos2.x = 200;
	fov2_wall.pos2.x = 200;
	fov1_wall.pos2.y = 8.53 * 20;
	fov2_wall.pos2.y = (5 - 3.53) * 20;
	fov2_wall.color = 0xAAAAAA;
	fov1_wall.color = 0xAAAAAA;

	i = -1;
	while (++i < 3)
		change_wall(world_wall + i);
	i = -1;
	while (++i < 3)
		draw_wall(game, *(world_wall + i));
	draw_wall(game, fov1_wall);
	draw_wall(game, fov2_wall);
}
