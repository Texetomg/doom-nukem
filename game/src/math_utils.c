/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 16:06:32 by thorker           #+#    #+#             */
/*   Updated: 2019/10/17 15:26:12 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

/*
** переводит координаты экраны в координаты потолка
*/

vec3	get_ceil(t_game *game, int x, int y, double dz)
{
	vec3	re;
	double	x1;
	double	y1;

	x1 = game->pre_calc.screen_h_div_2 * (dz) / (game->line_horiz - y);
	y1 = -x1 * (x - game->pre_calc.screen_w_div_2) / game->screen->w * 2;
	re.x = y1 * cos(game->player.angle) + x1 * sin(game->player.angle) +
		game->player.pos.y;
	re.y = x1 * cos(game->player.angle) - y1 * sin(game->player.angle) +
		game->player.pos.x;
	re.z = x1;
	return (re);
}

/*
** переводит координаты экраны в координаты пола
*/

vec3	get_floor(t_game *game, int x, int y, double dz)
{
	vec3	re;
	double	x1;
	double	y1;

	x1 = game->pre_calc.screen_h_div_2 * (dz) / (y - game->line_horiz);
	y1 = -x1 * (x - game->pre_calc.screen_w_div_2) / game->screen->w * 2;
	re.x = y1 * cos(game->player.angle) + x1 * sin(game->player.angle) +
		game->player.pos.y;
	re.y = x1 * cos(game->player.angle) - y1 * sin(game->player.angle) +
		game->player.pos.x;
	re.z = x1;
	return (re);
}

/*
** векторное проиведение
*/

double	cross_product(vec2 first_point, vec2 second_point)
{
	return (first_point.x * second_point.y - second_point.x * first_point.y);
}

/*
** пересечение прямой и фова
*/

void	cross(vec2 *first_point, vec2 second_point, vec2 fov)
{
	double new_x;
	double new_y;
	double det;

	det = cross_product(*first_point, second_point) /
		((-fov.x) * (first_point->y - second_point.y) +
		fov.y * (first_point->x - second_point.x));
	new_x = fov.x * det;
	new_y = fov.y * det;
	first_point->x = new_x;
	first_point->y = new_y;
}

/*
** находит точки в фове(их пересечения) возращает ноль если не в фове;
*/

int		intersection(vec2 *first_point, vec2 *second_point, vec2 left_fov,
	vec2 right_fov)
{
	double	x;
	double	y;

	x = cross_product(left_fov, *first_point);
	y = cross_product(left_fov, *second_point);
	if (x > 0 && y > 0)
		return (0);
	if (x > 0 || y > 0)
	{
		if (x > 0)
			cross(first_point, *second_point, left_fov);
		else
			cross(second_point, *first_point, left_fov);
	}
	x = cross_product(right_fov, *first_point);
	y = cross_product(right_fov, *second_point);
	if (x < 0 && y < 0)
		return (0);
	if (x < 0 || y < 0)
	{
		if (x < 0)
			cross(first_point, *second_point, right_fov);
		else
			cross(second_point, *first_point, right_fov);
	}
	return (1);
}
