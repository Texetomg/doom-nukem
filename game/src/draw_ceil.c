/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ceil.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 14:15:18 by thorker           #+#    #+#             */
/*   Updated: 2019/11/09 16:59:36 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
**	Дробная часть
*/

double			fractial_part(double a)
{
	if (a < 0)
		return (a - (int)a + 1);
	else
		return (a - (int)a);
}

/*
** Заполнение пространства для текстуры
*/

static void		fill_texture(t_game *game, int yt[3],
		t_vec3 point[2],
		double bright)
{
	int		k;
	double	a;
	double	x;
	double	y;
	int		color;

	k = (yt[0] + abs(yt[0])) / 2;
	while (k < yt[1] && k < game->line_horiz)
	{
		a = (double)(k - yt[0]) / (yt[1] - yt[0]);
		x = ((1 - a) * point[0].x / point[0].z + a * point[1].x / point[1].z) /
			((1 - a) / point[0].z + a / point[1].z);
		x = fractial_part(x) * game->texture->w;
		y = ((1 - a) * point[0].y / point[0].z + a * point[1].y / point[1].z) /
			((1 - a) / point[0].z + a / point[1].z);
		y = fractial_part(y) * game->texture->h;
		if (x > 0 && x < game->texture->w && y > 0 && y < game->texture->h)
		{
			color = ((int*)game->texture->pixels)[((int)y) *
				game->texture->w + ((int)x)];
			((int*)game->screen->pixels)[k * game->screen->w + yt[2]] =
				ft_bright(color, bright);
		}
		k++;
	}
}

/*
**	Костыль для нормы
*/

static t_vec3	to_cruch(double a, t_vec3 first, t_vec3 second)
{
	t_vec3	re;

	re.x = ((1 - a) * first.x / first.z + a * second.x
			/ second.z) / ((1 - a) / first.z + a / second.z);
	re.y = ((1 - a) * first.y / first.z + a * second.y
			/ second.z) / ((1 - a) / first.z + a / second.z);
	re.z = 1 / ((1 - a) / first.z + a / second.z);
	return (re);
}

/*
** Отрисовывает потолок
*/

void			draw_ceil(t_game *game,
		t_draw for_draw, double dz, double bright)
{
	t_vec3	points[2];
	int		yt[3];
	double	a;
	t_vec3	vec[4];

	yt[2] = ((int)for_draw.wall.x1 + abs((int)for_draw.wall.x1)) / 2 - 1;
	vec[0] = get_ceil(game, for_draw.wall.x1, for_draw.wall.y1t, dz);
	vec[1] = get_ceil(game, for_draw.window.x1, for_draw.window.y1t, dz);
	vec[2] = get_ceil(game, for_draw.wall.x2, for_draw.wall.y2t, dz);
	vec[3] = get_ceil(game, for_draw.window.x2, for_draw.window.y2t, dz);
	while (++yt[2] < for_draw.wall.x2 && yt[2] < game->screen->w)
	{
		a = (yt[2] - for_draw.window.x1) /
			(for_draw.window.x2 - for_draw.window.x1);
		points[0] = to_cruch(a, vec[1], vec[3]);
		a = (yt[2] - for_draw.wall.x1) / (for_draw.wall.x2 - for_draw.wall.x1);
		points[1] = to_cruch(a, vec[0], vec[2]);
		yt[1] = (int)(for_draw.wall.y1t + (for_draw.wall.y2t -
					for_draw.wall.y1t) * (yt[2] - for_draw.wall.x1) /
				(for_draw.wall.x2 - for_draw.wall.x1));
		yt[0] = (int)(for_draw.window.y1t + (for_draw.window.y2t -
					for_draw.window.y1t) * (yt[2] - for_draw.window.x1) /
				(for_draw.window.x2 - for_draw.window.x1));
		fill_texture(game, yt, points, bright);
	}
}
