/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 16:57:31 by thorker           #+#    #+#             */
/*   Updated: 2019/03/26 19:53:01 by thorker          ###   ########.fr       */
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

void	draw_wall_x(SDL_Surface *screen, t_wall world_wall)
{
	int	x;
	double y;
	double grad;

	grad = (world_wall.pos2.y - world_wall.pos1.y) / (world_wall.pos2.x - world_wall.pos1.x);
	x = round(world_wall.pos1.x);
	y = world_wall.pos1.y + grad * (x - world_wall.pos1.x);
	while (x < world_wall.pos2.x)
	{
		if (x >= 0 && x < 1000 && y >= 0 && y < 1000)
			((int*)screen->pixels)[(int)y * 1000 + x] = bright(world_wall.color, y - (int)y);
		if (x >= 0 && x < 1000 && y > -1 && y < 999)
			((int*)screen->pixels)[((int)y + 1) * 1000 + x] = bright(world_wall.color, 1 - (y - (int)y));
		x++;
		y += grad;
	}
}

void	draw_wall_y(SDL_Surface *screen, t_wall world_wall)
{
	int	y;
	double x;
	double grad;

	grad = (world_wall.pos2.x - world_wall.pos1.x) / (world_wall.pos2.y - world_wall.pos1.y);
	y = round(world_wall.pos1.y);
	x = world_wall.pos1.x + grad * (y - world_wall.pos1.y);
	while (y < world_wall.pos2.y)
	{
		if (x >= 0 && x < 1000 && y >= 0 && y < 1000)
			((int*)screen->pixels)[y * 1000 + (int)x] = bright(world_wall.color, x - (int)x);
		if (x > -1 && x < 999 && y >= 0 && y < 1000)
			((int*)screen->pixels)[ y * 1000 + (int)x + 1] = bright(world_wall.color, 1 - (x - (int)x));
		y++;
		x += grad;
	}
}


void	draw_wall(SDL_Surface *screen, t_wall world_wall)
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
		draw_wall_x(screen, world_wall);
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
		draw_wall_y(screen, world_wall);
	}
}
void	draw_minimap(SDL_Surface *screen, t_wall *world_wall)
{
	int i;

	i = 0;
	while (i < 3)
	{
		draw_wall(screen, *(world_wall + i));
		i++;
	}
}
