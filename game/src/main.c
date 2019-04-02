/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:38:27 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/04/02 16:56:11 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"
//поварачивает точки в систему координат игрока
void			give_points_cam(t_game *game)
{
	int		i;

	i = 0;
	while (i < game->count_points)
	{
		(game->points_cam + i)->x = ((game->points + i)->y - game->player.pos.y) * sin(game->player.angle) + ((game->points + i)->x - game->player.pos.x) * cos(game->player.angle);
		(game->points_cam + i)->y = ((game->points + i)->y - game->player.pos.y) * cos(game->player.angle) - ((game->points + i)->x - game->player.pos.x) * sin(game->player.angle);
		i++;
	}
}
// векторное проиведение
static double   cross_product(vec2 first_point, vec2 second_point)
{
	return (first_point.x * second_point.y - second_point.x * first_point.y);
}
//пересечение прямой и фова
static void     cross(vec2 *first_point, vec2 second_point, vec2 fov)
{
	double new_x;
	double new_y;
	double det;

	det = cross_product(*first_point, second_point) / ((-fov.x) * (first_point->y - second_point.y) + fov.y * (first_point->x - second_point.x));
	new_x = fov.x * det;
	new_y = fov.y * det;
	first_point->x = new_x;
	first_point->y = new_y;
}
//находит точки в фове(их пересечения) возращает ноль если не в фове;
int             intersection(vec2 *first_point, vec2 *second_point, vec2 left_fov, vec2 right_fov)
{
	double x;
	double y;

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
//рекурсивная функиця(в будущем), которая отрисовывает сектор;
void	draw_sector(t_game *game, int curr_sector, vec2 fov_left, vec2 fov_right)
{
	int i;
	vec2	first_point;
	vec2	second_point;
	double x1a;
	double y1t;
	double y1b;
	double x2a;
	double y2t;
	double y2b;
	int m;
	int k;
	double yt;
	double yb;
	double for_swap;
	double yscale1;
	double yscale2;
	double yceil;
	double yfloor;
	int color;

	i = 0;
	while (i < (game->sectors + curr_sector)->count_wall)
	{
		first_point = *(game->points_cam + *((game->sectors + curr_sector)->index_points + i));
		if (i == (game->sectors + curr_sector)->count_wall - 1)
			second_point = *(game->points_cam + *((game->sectors + curr_sector)->index_points));
		else
			second_point = *(game->points_cam + *((game->sectors + curr_sector)->index_points + i + 1));
		if (first_point.x < 0 && second_point.x < 0)
		{
			i++;
			continue;
		}
		if (intersection(&first_point, &second_point, fov_left, fov_right) > 0)
		{
			yceil = (game->sectors + curr_sector)->ceil - game->player.pos.z;
			yfloor = (game->sectors + curr_sector)->floor - game->player.pos.z;
			yscale1 = 500 / first_point.x;
			yscale2 = 500 / second_point.x;
			x1a = -first_point.y * (game->display_mode.w / 2) / 5 * 8.66 / first_point.x + game->display_mode.w / 2;
			y1t = -yscale1 * yceil + game->display_mode.h / 2;
			y1b = -yscale1 * yfloor + game->display_mode.h / 2;
			x2a = -second_point.y * (game->display_mode.w / 2) / 5 * 8.66 / second_point.x + game->display_mode.w / 2;
			y2t = -yscale2 * yceil + game->display_mode.h / 2;
			y2b = -yscale2 * yfloor + game->display_mode.h / 2;
			if (x1a > x2a)
			{
				for_swap = x1a;
				x1a = x2a;
				x2a = for_swap;
				for_swap = y1b;
				y1b = y2b;
				y2b = for_swap;
				for_swap = y1t;
				y1t = y2t;
				y2t = for_swap;
			}
			k = (int)x1a;
			while (k < x2a)
			{
				yt = y1t + (y2t - y1t) * (k - x1a) / (x2a - x1a);
				yb = y1b + (y2b - y1b) * (k - x1a) / (x2a - x1a);
				m = 0;
				while (m < game->display_mode.h)
				{
					if (m < yt)
						color = 0;
					else if (m < yb)
					{
						if (*((game->sectors + curr_sector)->neighbors + i) == -1)
							color = 0xAA00;
						else
							color = 0xAA0000;
					}
					else
						color = 0xAAAAAA;
					if (m >= 0 && m < game->display_mode.h && k >= 0 && k < game->display_mode.w)
						((int*)game->screen->pixels)[m * game->display_mode.w + k] = color;
					m++;
				}
				k++;
			}
		}
		i++;
	}
}
//запускает отрисовку всех стен
static void	draw_3d_wall(t_game *game)
{
	vec2	fov_left;
	vec2	fov_right;
	
	fov_left.x = 8.66;
	fov_left.y = 5;
	fov_right.x = 8.66;
	fov_right.y = -5;
	give_points_cam(game);
	draw_sector(game, game->player.curr_sector, fov_left, fov_right);
	//draw_minimap(game); минимапа здесь
}

int 		main(void)
{
	t_game		*game;
	int loop;
	t_fps	*fps;

	fps = (t_fps*)malloc(sizeof(t_fps));
	game = create_struct();
	loop = 1;
	while (loop)
	{
		player_move(game, &loop);
		SDL_FillRect(game->screen, 0, 0);
		draw_3d_wall(game);
		//put_fps(fps); переделать фпс без структры и мышь;
		SDL_UpdateWindowSurface(game->window);
	}
	SDL_DestroyWindow(game->window);
	SDL_Quit();
	return (0);
}
