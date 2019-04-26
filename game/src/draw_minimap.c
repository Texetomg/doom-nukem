/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 16:57:31 by thorker           #+#    #+#             */
/*   Updated: 2019/04/16 18:14:46 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

static int		bright(int color, double bri)
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

static void	draw_wall_x(SDL_Surface *screen, SDL_DisplayMode display_mode, vec2 first_point, vec2 second_point, int color)
{
	//ft_putendl("draw_wall_x");
	int	x;
	double y;
	double grad;

	grad = (second_point.y - first_point.y) / (second_point.x - first_point.x);
	x = round(first_point.x);
	y = first_point.y + grad * (x - first_point.x);
	while (x < second_point.x)
	{
		if (x >= 0 && x < display_mode.w / 10 && y >= 0 && y < DISPMODH10)
			((int*)screen->pixels)[(int)y * display_mode.w + x] = bright(color, y - (int)y);
		if (x >= 0 && x < display_mode.w / 10 && y > -1 && y < DISPMODH10 - 1)
			((int*)screen->pixels)[((int)y + 1) * display_mode.w + x] = bright(color, 1 - (y - (int)y));
		x++;
		y += grad;
	}
}

static void	draw_wall_y(SDL_Surface *screen, SDL_DisplayMode display_mode, vec2 first_point, vec2 second_point, int color)
{
	//ft_putendl("draw_wall_y");
	int	y;
	double x;
	double grad;

	grad = (second_point.x - first_point.x) / (second_point.y - first_point.y);
	y = round(first_point.y);
	x = first_point.x + grad * (y - first_point.y);
	while (y < second_point.y)
	{
		if (x >= 0 && x < display_mode.w / 10 && y >= 0 && y < DISPMODH10)
			((int*)screen->pixels)[y * display_mode.w + (int)x] = bright(color, x - (int)x);
		if (x > -1 && x < display_mode.w / 10 - 1 && y >= 0 && y < DISPMODH10)
			((int*)screen->pixels)[ y * display_mode.w + (int)x + 1] = bright(color, 1 - (x - (int)x));
		y++;
		x += grad;
	}
}


static void	draw_2dsector(SDL_Surface *screen, SDL_DisplayMode display_mode, t_sector *sectors, vec2 *points_cam, int curr_sector)
{
	//ft_putendl("draw_2dsector");
	double for_swap;
	int i;
	vec2	first_point;
	vec2	second_point;
	i = 0;
	while (i < (sectors + curr_sector)->count_wall)
	{
		first_point = *(points_cam + *((sectors + curr_sector)->index_points + i));
		if (i == (sectors + curr_sector)->count_wall - 1)
			second_point = *(points_cam + *((sectors + curr_sector)->index_points));
		else
			second_point = *(points_cam + *((sectors + curr_sector)->index_points + i + 1));
		first_point.x = first_point.x * 20  + DISPMODW20;
		first_point.y = -first_point.y * 20 + DISPMODH20;
		second_point.x = second_point.x * 20 + DISPMODW20;
		second_point.y = -second_point.y * 20 +  DISPMODH20;
		if (fabs(first_point.x - second_point.x) > fabs(first_point.y - second_point.y))
		{
			if (first_point.x > second_point.x)
			{
				for_swap = first_point.x;
				first_point.x = second_point.x;
				second_point.x = for_swap;
				for_swap = first_point.y;
				first_point.y = second_point.y;
				second_point.y = for_swap;
			}
			draw_wall_x(screen, display_mode, first_point, second_point, 0);
		}
		else
		{
			if (first_point.y > second_point.y)
			{
				for_swap = first_point.x;
				first_point.x = second_point.x;
				second_point.x = for_swap;
				for_swap = first_point.y;
				first_point.y = second_point.y;
				second_point.y = for_swap;
			}
			draw_wall_y(screen, display_mode, first_point, second_point, 0);
		}
		i++;
	}
}
// переделать минимапу
void	draw_minimap(SDL_Surface *screen, SDL_DisplayMode display_mode, t_sector *sectors, vec2 *points_cam, int count_sectors)
{
	//ft_putendl("draw_minimap");
	int i;
	vec2 left_fov;
	vec2 right_fov;
	vec2 pos0;
	i = 0;
	while (i < count_sectors)
	{
		//draw_2dsector(SDL_Surface *screen, SDL_DisplayMode display_mode, t_sector *sectors, vec2 *points_cam, int curr_sector)
		draw_2dsector(screen, display_mode, sectors, points_cam, i);
		i++;
	}
	pos0.x = DISPMODW20;
	pos0.y = DISPMODH20;
	left_fov.x = DISPMODW20 + 5 * 20;
	right_fov.x = DISPMODW20 + 5 * 20;
	left_fov.y = DISPMODH20 - 5 * 20;
	right_fov.y = DISPMODH20 + 5 * 20;
	draw_wall_x(screen, display_mode, pos0, left_fov, 0xFFFFFF);
	draw_wall_x(screen, display_mode, pos0, right_fov, 0xFFFFFF);
}
