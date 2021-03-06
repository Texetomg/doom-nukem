/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 16:57:31 by thorker           #+#    #+#             */
/*   Updated: 2019/11/05 10:52:25 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void		draw_wall_x(t_game *game, t_vec2 first_point,
		t_vec2 second_point, int color)
{
	int		x;
	double	y;
	double	grad;

	grad = (second_point.y - first_point.y) / (second_point.x - first_point.x);
	x = round(first_point.x);
	y = first_point.y + grad * (x - first_point.x);
	while (x < second_point.x)
	{
		if (x >= 0 && x < game->pre_calc.screen_w_div_10 && y >= 0 &&
				y < game->pre_calc.screen_h_div_10)
			((int*)game->screen->pixels)[(int)y * game->screen->w + x] =
				ft_bright(color, y - (int)y);
		if (x >= 0 && x < game->pre_calc.screen_w_div_10 && y > -1 &&
				y < game->pre_calc.screen_h_div_10 - 1)
			((int*)game->screen->pixels)[((int)y + 1) * game->screen->w + x] =
				ft_bright(color, 1 - (y - (int)y));
		x++;
		y += grad;
	}
}

static void		draw_wall_y(t_game *game, t_vec2 first_point,
		t_vec2 second_point, int color)
{
	int		y;
	double	x;
	double	grad;

	grad = (second_point.x - first_point.x) / (second_point.y - first_point.y);
	y = round(first_point.y);
	x = first_point.x + grad * (y - first_point.y);
	while (y < second_point.y)
	{
		if (x >= 0 && x < game->pre_calc.screen_w_div_10 &&
				y >= 0 && y < game->pre_calc.screen_h_div_10)
			((int*)game->screen->pixels)[y * game->screen->w + (int)x] =
				ft_bright(color, x - (int)x);
		if (x > -1 && x < game->pre_calc.screen_w_div_10 - 1 &&
				y >= 0 && y < game->pre_calc.screen_h_div_10)
			((int*)game->screen->pixels)[y * game->screen->w + (int)x + 1] =
				ft_bright(color, 1 - (x - (int)x));
		y++;
		x += grad;
	}
}

static void		draw_2dsector(t_game *game, int curr_sector)
{
	int		i;
	t_vec2	first_point;
	t_vec2	second_point;

	i = -1;
	while (++i < (game->sectors + curr_sector)->count_wall)
	{
		get_first_point(game, curr_sector, &first_point, i);
		get_second_point(game, curr_sector, &second_point, i);
		if (fabs(first_point.x - second_point.x) >
				fabs(first_point.y - second_point.y))
		{
			if (first_point.x > second_point.x)
				swap_vec2(&first_point, &second_point);
			draw_wall_x(game, first_point, second_point, 0);
		}
		else
		{
			if (first_point.y > second_point.y)
				swap_vec2(&first_point, &second_point);
			draw_wall_y(game, first_point, second_point, 0);
		}
	}
}

void			draw_minimap(t_game *game)
{
	int		i;
	t_vec2	left_fov;
	t_vec2	right_fov;
	t_vec2	pos0;

	i = 0;
	while (i < game->count_sectors)
	{
		draw_2dsector(game, i);
		i++;
	}
	pos0.x = game->pre_calc.screen_w_div_20;
	pos0.y = game->pre_calc.screen_h_div_20;
	left_fov.x = game->pre_calc.screen_w_div_20 + 5 * 20;
	right_fov.x = game->pre_calc.screen_w_div_20 + 5 * 20;
	left_fov.y = game->pre_calc.screen_h_div_20 - 5 * 20;
	right_fov.y = game->pre_calc.screen_h_div_20 + 5 * 20;
	draw_wall_x(game, pos0, left_fov, 0xFFFFFF);
	draw_wall_x(game, pos0, right_fov, 0xFFFFFF);
}
