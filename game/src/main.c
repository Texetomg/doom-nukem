/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:38:27 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/04/03 19:29:11 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"
//поварачивает точки в систему координат игрока
void			give_points_cam(t_game *game)
{
	int		i;
	//ft_putendl("give_point_cam");
	i = 0;
	while (i < game->count_points)
	{
		(game->points_cam + i)->x = ((game->points + i)->y - game->player.pos.y) * sin(game->player.angle) + ((game->points + i)->x - game->player.pos.x) * cos(game->player.angle);
		(game->points_cam + i)->y = ((game->points + i)->y - game->player.pos.y) * cos(game->player.angle) - ((game->points + i)->x - game->player.pos.x) * sin(game->player.angle);
		i++;
	}
}
// векторное проиведение
double   cross_product(vec2 first_point, vec2 second_point)
{
	return (first_point.x * second_point.y - second_point.x * first_point.y);
}
//пересечение прямой и фова
static void     cross(vec2 *first_point, vec2 second_point, vec2 fov)
{
	double new_x;
	double new_y;
	double det;

	//ft_putendl("cross");
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

	//ft_putendl("intersection");
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
	//ft_putendl("draw_Sector");
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
	int color_sector;
	double	y2ceil;
	double	y2floor;
	double sy1t;
	double sy1b;
	double sy2t;
	double sy2b;
	double syt;
	double syb;

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
			if (*((game->sectors + curr_sector)->neighbors + i) == -1)
			{
				color_sector = 0xAA00;
				y2ceil = yceil;
				y2floor = yfloor;
			}
			else
			{
				y2ceil = (game->sectors + *((game->sectors + curr_sector)->neighbors + i))->ceil - game->player.pos.z;
				y2floor = (game->sectors + *((game->sectors + curr_sector)->neighbors + i))->floor - game->player.pos.z;
				color_sector = 0xAA0000;
			}
			sy1t = -yscale1 * y2ceil + game->display_mode.h / 2;
			sy1b = -yscale1 * y2floor + game->display_mode.h / 2;
			sy2t = -yscale2 * y2ceil + game->display_mode.h / 2;
			sy2b = -yscale2 * y2floor + game->display_mode.h / 2;
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
				for_swap = sy1b;
				sy1b = sy2b;
				sy2b = for_swap;
				for_swap = sy1t;
				sy1t = sy2t;
				sy2t = for_swap;
			}
			k = (int)x1a;
			while (k < x2a)
			{
				yt = y1t + (y2t - y1t) * (k - x1a) / (x2a - x1a);
				syt = sy1t + (sy2t - sy1t) * (k - x1a) / (x2a - x1a);
				yb = y1b + (y2b - y1b) * (k - x1a) / (x2a - x1a);
				syb = sy1b + (sy2b - sy1b) * (k - x1a) / (x2a - x1a);
				m = 0;
				while (m < game->display_mode.h)
				{
					if (m < yt)
						color = 0x88;
					else if (m < yb)
					{
						if (k == (int)x1a || k == (int)x2a)
							color = 0;
						else if (m < syt)
							color = 0xBBBB00;
						else if (m > syb)
							color = 0xAAAA;
						else
							color = color_sector;
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
	
	//ft_putendl("draw_3d_wall");
	fov_left.x = 8.66;
	fov_left.y = 5;
	fov_right.x = 8.66;
	fov_right.y = -5;
	give_points_cam(game);
	draw_sector(game, game->player.curr_sector, fov_left, fov_right);
	draw_minimap(game);
}

int 		main(void)
{
	t_game		*game;
	int loop;

	game = create_struct();
	loop = 1;
	while (loop)
	{
		player_move(game, &loop);
		get_pos_z(game);
		draw_3d_wall(game);
		//put_fps(game);
		SDL_UpdateWindowSurface(game->window);
	}
	SDL_DestroyWindow(game->window);
	SDL_Quit();
	return (0);
}
