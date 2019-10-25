/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ceil.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 14:15:18 by thorker           #+#    #+#             */
/*   Updated: 2019/10/25 16:21:05 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

/*
 ** Дробная часть
 */

double	fractial_part(double a)
{
	if (a < 0)
		return (a - (int)a + 1);
	else
		return (a - (int)a);
}

/*
 ** Заполнение пространства для текстуры
 */

void	fill_texture(t_game *game, int start, int end,
		vec3 first,
		vec3 second,
		double bright,
		int i)
{
	int		k;
	double	a;
	double	x;
	double	y;
	int		color;

	k = (start + abs(start)) / 2;
	while (k < end && k < game->line_horiz)
	{
		a = (double)(k - start) / (end - start);
		x = ((1 - a) * first.x / first.z + a * second.x / second.z) /
			((1 - a) / first.z + a / second.z);
		x = fractial_part(x) * game->texture->w;
		y = ((1 - a) * first.y / first.z + a * second.y / second.z) /
			((1 - a) / first.z + a / second.z);
		y = fractial_part(y) * game->texture->h;
		if (x > 0 && x < game->texture->w && y > 0 && y < game->texture->h)
		{
			color = ((int*)game->texture->pixels)[((int)y) *
				game->texture->w + ((int)x)];
			((int*)game->screen->pixels)[k * game->screen->w + i] =
				ft_bright(color, bright);
		}
		k++;
	}
}

/*
 *	Костыль для нормы
 */


/*
 ** Отрисовывает потолок
 */

void	draw_ceil(t_game *game, t_draw for_draw, double dz, double bright)
{
	int i;
	vec3 first;
	vec3 second;
	int yt_window;
	int yt_wall;
	double a;
	vec3 first_left;
	vec3 first_right;
	vec3 second_left;
	vec3 second_right;

	i = ((int)for_draw.wall.x1 + abs((int)for_draw.wall.x1)) / 2;
	second_left = get_ceil(game, for_draw.wall.x1, for_draw.wall.y1t, dz);
	first_left = get_ceil(game, for_draw.window.x1, for_draw.window.y1t, dz);
	second_right = get_ceil(game, for_draw.wall.x2, for_draw.wall.y2t, dz);
	first_right = get_ceil(game, for_draw.window.x2, for_draw.window.y2t, dz);
	while (i < for_draw.wall.x2 && i < game->screen->w)
	{
		a = (i - for_draw.window.x1) / (for_draw.window.x2 -
				for_draw.window.x1);
		first.x = ((1 - a) * first_left.x / first_left.z + a * first_right.x
				/ first_right.z) / ((1 - a) / first_left.z + a / first_right.z);
		first.y = ((1 - a) * first_left.y / first_left.z + a * first_right.y
				/ first_right.z) / ((1 - a) / first_left.z + a / first_right.z);
		first.z = 1 / ((1 - a) / first_left.z + a / first_right.z);
		a = (i - for_draw.wall.x1) / (for_draw.wall.x2 - for_draw.wall.x1);
		second.x = ((1 - a) * second_left.x / second_left.z + a * second_right.x
				/ second_right.z) / ((1 - a) / second_left.z + a /
					second_right.z);
		second.y = ((1 - a) * second_left.y / second_left.z + a * second_right.y
				/ second_right.z) / ((1 - a) /
					second_left.z + a / second_right.z);
		second.z = 1 / ((1 - a) / second_left.z + a / second_right.z);
		yt_wall = (int)(for_draw.wall.y1t + (for_draw.wall.y2t -
					for_draw.wall.y1t) * (i - for_draw.wall.x1) /
				(for_draw.wall.x2 - for_draw.wall.x1));
		yt_window = (int)(for_draw.window.y1t + (for_draw.window.y2t -
					for_draw.window.y1t) * (i - for_draw.window.x1) /
				(for_draw.window.x2 - for_draw.window.x1));
		fill_texture(game, yt_window, yt_wall, first, second, bright, i);
		i++;
	}
}
