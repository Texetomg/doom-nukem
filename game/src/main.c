/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:38:27 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/04/12 16:56:47 by thorker          ###   ########.fr       */
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
//меняет местами два числа
void	swap(double *a, double *b)
{
	double c;

	c = *a;
	*a = *b;
	*b = c;
}
//отрисовывает стену
void	draw_wall(t_game *game, t_draw for_draw)
{
	int i;
	int k;
	double yb_wall;
	double yt_wall;
	double yb_window;
	int color;
	i = (int)for_draw.wall.x1;
	while (i < for_draw.wall.x2)
	{ 
		k = (int)(for_draw.window.y1t + (for_draw.window.y2t - for_draw.window.y1t) * (i - for_draw.window.x1) / (for_draw.window.x2 - for_draw.window.x1));
		yb_window = for_draw.window.y1b + (for_draw.window.y2b - for_draw.window.y1b) * (i - for_draw.window.x1) / (for_draw.window.x2 - for_draw.window.x1);
		yt_wall = for_draw.wall.y1t + (for_draw.wall.y2t - for_draw.wall.y1t) * (i - for_draw.wall.x1) / (for_draw.wall.x2 - for_draw.wall.x1);
		yb_wall = for_draw.wall.y1b + (for_draw.wall.y2b - for_draw.wall.y1b) * (i - for_draw.wall.x1) / (for_draw.wall.x2 - for_draw.wall.x1);
		if (k < 0)
			k = 0;
		while (k < yb_window && k < game->display_mode.h)
		{
			if (k == (int)yt_wall || k == (int)yb_wall || (i == (int)for_draw.wall.x1 && k < yb_wall && k > yt_wall) || (i == (int)for_draw.wall.x2 && k < yb_wall && k > yt_wall))
				color = 0;
			else if (k < yt_wall)
				color = COLOR_CEIL;
			else if (k < yb_wall)
				color = COLOR_WALL;
			else
				color = COLOR_FLOOR;
			if (i < game->display_mode.w)
				((int*)game->screen->pixels)[k * game->display_mode.w + i] = color;
			k++;
		}
		i++;
	}
}
//отрисовывет промежутки между потолком/полом и сектором 
void	pre_draw_sector(t_game *game, t_draw for_draw)
{
	int i;
	int k;
	double yb_wall;
	double yt_wall;
	double yb_window;

	/*if (for_draw.wall.y1t < for_draw.window.y1t &&
			for_draw.wall.y2t < for_draw.window.y2t &&
			for_draw.wall.y1b > for_draw.window.y1b &&
			for_draw.wall.y2b > for_draw.window.y2b)
		return ;
		*/
	i = (int)for_draw.window.x1;
	while (i < for_draw.window.x2)
	{
		k = (int)(for_draw.window.y1t + (for_draw.window.y2t - for_draw.window.y1t) * (i - for_draw.window.x1) / (for_draw.window.x2 - for_draw.window.x1));
		yb_window = for_draw.window.y1b + (for_draw.window.y2b - for_draw.window.y1b) * (i - for_draw.window.x1) / (for_draw.window.x2 - for_draw.window.x1);
		yt_wall = for_draw.wall.y1t + (for_draw.wall.y2t - for_draw.wall.y1t) * (i - for_draw.window.x1) / (for_draw.window.x2 - for_draw.window.x1);
		yb_wall = for_draw.wall.y1b + (for_draw.wall.y2b - for_draw.wall.y1b) * (i - for_draw.window.x1) / (for_draw.window.x2 - for_draw.window.x1);
		if (k < 0)
			k = 0;
		while (k < yb_window && k < game->display_mode.h)
		{
			if (k < yt_wall || k > yb_wall)
				if (i < game->display_mode.w)
					((int*)game->screen->pixels)[k * game->display_mode.w + i] = COLOR_BETW;
			k++;
		}
		i++;
	}
}
//рекурсивная функиця(в будущем), которая отрисовывает сектор;
void	draw_sector(t_game *game, t_draw for_draw)
{
	//ft_putendl("draw_Sector");
	int i;
	t_draw	for_next_draw;
	vec2	first_point;
	vec2	second_point;
	double yscale1;
	double yscale2;
	double yceil;
	double yfloor;
	double	y2ceil;
	double	y2floor;
	i = 0;
	while (i < (game->sectors + for_draw.curr_sector)->count_wall)
	{
		first_point = *(game->points_cam + *((game->sectors + for_draw.curr_sector)->index_points + i));
		if (i == (game->sectors + for_draw.curr_sector)->count_wall - 1)
			second_point = *(game->points_cam + *((game->sectors + for_draw.curr_sector)->index_points));
		else
			second_point = *(game->points_cam + *((game->sectors + for_draw.curr_sector)->index_points + i + 1));
		if (first_point.x < 0 && second_point.x < 0)
		{
			i++;
			continue;
		}
		if (intersection(&first_point, &second_point, for_draw.fov_left, for_draw.fov_right) > 0)
		{
			yceil = (game->sectors + for_draw.curr_sector)->ceil - game->player.pos.z;
			yfloor = (game->sectors + for_draw.curr_sector)->floor - game->player.pos.z;
			yscale1 = 500 / first_point.x;
			yscale2 = 500 / second_point.x;
			for_draw.wall.x1 = -first_point.y * (game->display_mode.w / 2) / 5 * 8.66 / first_point.x + game->display_mode.w / 2;
			for_draw.wall.x2 = -second_point.y * (game->display_mode.w / 2) / 5 * 8.66 / second_point.x + game->display_mode.w / 2;
			for_draw.wall.y2t = -yscale2 * yceil + game->display_mode.h / 2;
			for_draw.wall.y1t = -yscale1 * yceil + game->display_mode.h / 2;
			for_draw.wall.y2b = -yscale2 * yfloor + game->display_mode.h / 2;
			for_draw.wall.y1b = -yscale1 * yfloor + game->display_mode.h / 2;
			draw_wall(game, for_draw);
			if (*((game->sectors + for_draw.curr_sector)->neighbors + i) >= 0)
			{
				if (*((game->sectors + for_draw.curr_sector)->neighbors + i) != for_draw.last_sector)
				{
					for_next_draw.window = for_draw.wall;
					y2ceil = (game->sectors + *((game->sectors + for_draw.curr_sector)->neighbors + i))->ceil - game->player.pos.z;
					y2floor = (game->sectors + *((game->sectors + for_draw.curr_sector)->neighbors + i))->floor - game->player.pos.z;
					for_next_draw.wall.y1t = -yscale1 * y2ceil + game->display_mode.h / 2;
					for_next_draw.wall.y1b = -yscale1 * y2floor + game->display_mode.h / 2;
					for_next_draw.wall.y2t = -yscale2 * y2ceil + game->display_mode.h / 2;
					for_next_draw.wall.y2b = -yscale2 * y2floor + game->display_mode.h / 2;
					for_next_draw.wall.x1 = for_next_draw.window.x1;
					for_next_draw.wall.x2 = for_next_draw.window.x2;
					for_next_draw.curr_sector = *((game->sectors + for_draw.curr_sector)->neighbors + i);
					for_next_draw.last_sector = for_draw.curr_sector;
					for_next_draw.fov_left = first_point;
					for_next_draw.fov_right = second_point;
					draw_sector(game, for_next_draw);
					pre_draw_sector(game, for_next_draw);
				}
			}
			else
				draw_wall(game, for_draw);
		}
		i++;
	}
}
//запускает отрисовку всех стен
static void	draw_3d_wall(t_game *game)
{
	t_draw	for_draw;
	
	//ft_putendl("draw_3d_wall");
	for_draw.fov_left.x = 8.66;
	for_draw.fov_left.y = 5;
	for_draw.fov_right.x = 8.66;
	for_draw.fov_right.y = -5;
	for_draw.window.x1 = 0;
	for_draw.window.x2 = game->display_mode.w;
	for_draw.window.y1b = game->display_mode.h;
	for_draw.window.y1t = 0;
	for_draw.window.y2b = game->display_mode.h;
	for_draw.window.y2t = 0;
	for_draw.last_sector = -2;
	for_draw.curr_sector = game->player.curr_sector;
	give_points_cam(game);
	draw_sector(game, for_draw);
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
		SDL_FillRect(game->screen,0, 0);
		draw_3d_wall(game);
		put_fps(game);
		SDL_UpdateWindowSurface(game->window);
	}
	SDL_DestroyWindow(game->window);
	SDL_Quit();
	return (0);
}
