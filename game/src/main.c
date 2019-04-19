/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:38:27 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/04/18 19:02:58 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"
//поварачивает точки в систему координат игрока
static void			give_points_cam(vec2 *points_cam, vec2 *points, t_player *player, int count_points)
{
	int		i;
	//ft_putendl("give_point_cam");
	i = 0;
	while (i < count_points)
	{
		(points_cam + i)->x = ((points + i)->y - player->pos.y) * sin(player->angle) + ((points + i)->x - player->pos.x) * cos(player->angle);
		(points_cam + i)->y = ((points + i)->y - player->pos.y) * cos(player->angle) - ((points + i)->x - player->pos.x) * sin(player->angle);
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
static int             intersection(vec2 *first_point, vec2 *second_point, vec2 left_fov, vec2 right_fov)
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
/*
static void	swap(double *a, double *b)
{
	double c;

	c = *a;
	*a = *b;
	*b = c;
}
*/
//отрисовывает стену
static void	draw_wall(SDL_DisplayMode display_mode,
						t_gif *gif,
						SDL_Surface *texture,
						t_draw for_draw,
						SDL_Surface *screen,
						double x1,
						double x2,
						double y1,
						double y2)
{
	int i;
	int k;
	int yb_wall;
	int yt_wall;
	int yb_window;
	int color;
	int x;
	int y;
	double a;
	i = (int)for_draw.wall.x1;
	while (i < for_draw.wall.x2)
	{ 
		k = (int)(for_draw.window.y1t + (for_draw.window.y2t - for_draw.window.y1t) * (i - for_draw.window.x1) / (for_draw.window.x2 - for_draw.window.x1));
		yb_window = (int)(for_draw.window.y1b + (for_draw.window.y2b - for_draw.window.y1b) * (i - for_draw.window.x1) / (for_draw.window.x2 - for_draw.window.x1));
		yt_wall = (int)(for_draw.wall.y1t + (for_draw.wall.y2t - for_draw.wall.y1t) * (i - for_draw.wall.x1) / (for_draw.wall.x2 - for_draw.wall.x1));
		yb_wall = (int)(for_draw.wall.y1b + (for_draw.wall.y2b - for_draw.wall.y1b) * (i - for_draw.wall.x1) / (for_draw.wall.x2 - for_draw.wall.x1));
		if (k < 0)
			k = 0;
		while (k < yb_window && k < display_mode.h)
		{
			if (k == yt_wall || k == yb_wall || (i == (int)for_draw.wall.x1 && k < yb_wall && k > yt_wall) || (i == (int)for_draw.wall.x2 && k < yb_wall && k > yt_wall))
				color = 0;
			else if (k < yt_wall)
				color = COLOR_CEIL;
			else if (k < yb_wall)
			{
				a = (double)(i - (int)for_draw.wall.x1) / ((int)for_draw.wall.x2 - (int)for_draw.wall.x1);
				x = ((1 - a) * x1 / y1 + a * x2 / y2) / ((1 - a) / y1 + a / y2) * texture->w;
				y = (double)(k - yt_wall) / (yb_wall - yt_wall) * texture->h;
				if (for_draw.curr_sector == 2)
				{
					x = ((1 - a) * x1 / y1 + a * x2 / y2) / ((1 - a) / y1 + a / y2) * (*(gif[0].array + gif[0].curr_frame))->w;
					y = (double)(k - yt_wall) / (yb_wall - yt_wall) * (*(gif[0].array + gif[0].curr_frame))->h;
					color = ((int*)(*(gif[0].array + gif[0].curr_frame))->pixels)[y * (*(gif[0].array + gif[0].curr_frame))->w + x];
				}
				else
					color = ((int*)texture->pixels)[y * texture->w + x];
				//color = 0xAAAA00;
			}
			else
				color = COLOR_FLOOR;
			if (i < display_mode.w)
				((int*)screen->pixels)[k * display_mode.w + i] = color;
			k++;
		}
		i++;
	}
}
//отрисовывет промежутки между потолком/полом и сектором. И пол и потолок портала.
static void	pre_draw_sector(SDL_Surface *screen,
							SDL_DisplayMode display_mode,
							t_draw for_draw,
							t_draw for_draw_past)
{
	int i;
	int k;
	double yb_wall;
	double yt_wall;
	double yb_window;
	double yb_window_past;
	double yt_window;
	int color;
	/*if (for_draw.wall.y1t < for_draw.window.y1t &&
			for_draw.wall.y2t < for_draw.window.y2t &&
			for_draw.wall.y1b > for_draw.window.y1b &&
			for_draw.wall.y2b > for_draw.window.y2b)
		return ;
		*/
	i = (int)for_draw.window.x1;
	while (i < for_draw.window.x2)
	{
		k = for_draw_past.window.y1t + (for_draw_past.window.y2t - for_draw_past.window.y1t) * (i - for_draw_past.window.x1) / (for_draw_past.window.x2 - for_draw_past.window.x1);
		yb_window_past = for_draw_past.window.y1b + (for_draw_past.window.y2b - for_draw_past.window.y1b) * (i - for_draw_past.window.x1) / (for_draw_past.window.x2 - for_draw_past.window.x1);
		yt_window = (for_draw.window.y1t + (for_draw.window.y2t - for_draw.window.y1t) * (i - for_draw.window.x1) / (for_draw.window.x2 - for_draw.window.x1));
		yb_window = for_draw.window.y1b + (for_draw.window.y2b - for_draw.window.y1b) * (i - for_draw.window.x1) / (for_draw.window.x2 - for_draw.window.x1);
		yt_wall = for_draw.wall.y1t + (for_draw.wall.y2t - for_draw.wall.y1t) * (i - for_draw.window.x1) / (for_draw.window.x2 - for_draw.window.x1);
		yb_wall = for_draw.wall.y1b + (for_draw.wall.y2b - for_draw.wall.y1b) * (i - for_draw.window.x1) / (for_draw.window.x2 - for_draw.window.x1);
		if (k < 0)
			k = 0;
		while (k < yb_window_past && k < display_mode.h)
		{
			if (k <= yt_window)
				color = COLOR_CEIL;
			else if (k >= (int)yb_window)
				color = COLOR_FLOOR;
			else if (k < yt_wall || k > yb_wall)
				color = COLOR_BETW;
			else
				color = -1;
			if (i < display_mode.w && color >= 0)
					((int*)screen->pixels)[k * display_mode.w + i] = color;
			k++;
		}
		i++;
	}
}
//рекурсивная функиця(в будущем), которая отрисовывает сектор;
static void	draw_sector(t_gif *gif,
							SDL_Surface *texture,
							SDL_Surface *screen,
							t_player *player,
							SDL_DisplayMode display_mode,
							t_sector *sectors,
							vec2 *points_cam,
							t_draw for_draw)
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
	double x1, x2;
	double x1a, x2a;
	double y1, y2;
	i = 0;
	while (i < (sectors + for_draw.curr_sector)->count_wall)
	{
		first_point = *(points_cam + *((sectors + for_draw.curr_sector)->index_points + i));
		if (i == (sectors + for_draw.curr_sector)->count_wall - 1)
			second_point = *(points_cam + *((sectors + for_draw.curr_sector)->index_points));
		else
			second_point = *(points_cam + *((sectors + for_draw.curr_sector)->index_points + i + 1));
		if (first_point.x < 0 && second_point.x < 0)
		{
			i++;
			continue;
		}
		x1 = -first_point.y;
		x2 = -second_point.y;
		if (intersection(&first_point, &second_point, for_draw.fov_left, for_draw.fov_right) > 0)
		{
			x1a = (-first_point.y - x1) / (x2 - x1);
			x2a = (-second_point.y - x1) / (x2 - x1);
			y1 = first_point.x;
			y2 = second_point.x;
			yceil = (sectors + for_draw.curr_sector)->ceil - player->pos.z;
			yfloor = (sectors + for_draw.curr_sector)->floor - player->pos.z;
			yscale1 = 500 / first_point.x;
			yscale2 = 500 / second_point.x;
			for_draw.wall.x1 = -first_point.y * (display_mode.w / 2) / first_point.x + display_mode.w / 2;
			for_draw.wall.x2 = -second_point.y * (display_mode.w / 2) / second_point.x + display_mode.w / 2;
			for_draw.wall.y2t = -yscale2 * yceil + display_mode.h / 2;
			for_draw.wall.y1t = -yscale1 * yceil + display_mode.h / 2;
			for_draw.wall.y2b = -yscale2 * yfloor + display_mode.h / 2;
			for_draw.wall.y1b = -yscale1 * yfloor + display_mode.h / 2;
			if (*((sectors + for_draw.curr_sector)->neighbors + i) >= 0)
			{
				if (*((sectors + for_draw.curr_sector)->neighbors + i) != for_draw.last_sector)
				{
					for_next_draw.window = for_draw.wall;
					y2ceil = (sectors + *((sectors + for_draw.curr_sector)->neighbors + i))->ceil - player->pos.z;
					y2floor = (sectors + *((sectors + for_draw.curr_sector)->neighbors + i))->floor - player->pos.z;
					for_next_draw.wall.y1t = -yscale1 * y2ceil + display_mode.h / 2;
					for_next_draw.wall.y1b = -yscale1 * y2floor + display_mode.h / 2;
					for_next_draw.wall.y2t = -yscale2 * y2ceil + display_mode.h / 2;
					for_next_draw.wall.y2b = -yscale2 * y2floor + display_mode.h / 2;
					for_next_draw.wall.x1 = for_next_draw.window.x1;
					for_next_draw.wall.x2 = for_next_draw.window.x2;
					for_next_draw.curr_sector = *((sectors + for_draw.curr_sector)->neighbors + i);
					for_next_draw.last_sector = for_draw.curr_sector;
					for_next_draw.fov_left = first_point;
					for_next_draw.fov_right = second_point;
					draw_sector(gif, texture, screen, player, display_mode, sectors, points_cam, for_next_draw);
					pre_draw_sector(screen, display_mode, for_next_draw, for_draw);
				}
			}
			else
				draw_wall(display_mode, gif, texture, for_draw, screen, x1a, x2a, y1, y2);
		}
		i++;
	}
}
//запускает отрисовку всех стен
static void	draw_3d_wall(SDL_Surface *screen,
							SDL_Surface *texture,
							vec2 *points,
							int count_points,
							vec2 *points_cam,
							SDL_DisplayMode display_mode,
							t_player *player,
							t_sector *sectors,
							int count_sectors,
							t_gif *gif)
{
	t_draw	for_draw;
	
	//ft_putendl("draw_3d_wall");
	for_draw.fov_left.x = 5;
	for_draw.fov_left.y = 5;
	for_draw.fov_right.x = 5;
	for_draw.fov_right.y = -5;
	for_draw.window.x1 = 0;
	for_draw.window.x2 = display_mode.w;
	for_draw.window.y1b = display_mode.h;
	for_draw.window.y1t = 0;
	for_draw.window.y2b = display_mode.h;
	for_draw.window.y2t = 0;
	for_draw.last_sector = -2;
	for_draw.curr_sector = player->curr_sector;

	give_points_cam(points_cam, points, player, count_points);
	draw_sector(gif, texture, screen, player, display_mode, sectors, points_cam, for_draw);
	draw_minimap(screen, display_mode, sectors, points_cam, count_sectors);
}
//отрисовка рук/оружия 
static void		draw_hands(SDL_Surface *screen, t_gif *gif)
{
	int		x = 0;
	int		y = 0;
	int		new_x = 0;
	int		new_y = 0;
	int		color;

	while (y < screen->h / 3)
	{
		while (x < screen->w / 3)
		{
			new_x = (double)x / (screen->w / 3) * (*(gif[1].array + gif[1].curr_frame))->w;
			new_y = (double)y / (screen->h / 3) * (*(gif[1].array + ((int)(gif[1].curr_frame))))->h;
			color = ((int*)((*(gif[1].array + ((int)(gif[1].curr_frame))))->pixels))[new_y * (*(gif[1].array + ((int)(gif[1].curr_frame))))->w + new_x];
			((int*)(screen->pixels))[(int)(y + screen->h / 100 * 65) * screen->w + x + (screen->w / 100 * 45)] = color;
			x++;
		}
		x = 0;
		y++;
	}
}



static void		draw_sprites(SDL_Surface *screen, t_sector *sectors, t_sprites sprites, t_player player)
{
	int i;
	int j;

	sprites.new_pos.x = (sprites.pos.y - player.pos.y) * sin(player.angle) + (sprites.pos.x - player.pos.x) * cos(player.angle);
	sprites.new_pos.y = (sprites.pos.y - player.pos.y) * cos(player.angle) - (sprites.pos.x - player.pos.x) * sin(player.angle);
	sprites.shift = (-sprites.new_pos.y / sprites.new_pos.x) * (screen->w / 2) + screen->w / 2;
	sprites.h = 200 / sprites.new_pos.x;
	sprites.w = 200 / sprites.new_pos.x;
	i = (sectors + sprites.sector)->floor;
	while (i < (sectors + sprites.sector)->floor + sprites.h)
	{
		j = (sprites.shift ) - sprites.w / 2;
		while (j < (sprites.shift) + sprites.w / 2)
		{
			if (i >= 0 && i < screen->h && j >= 0 && j < screen->w )
			{
				((int*)(screen->pixels))[(int)(screen->w * i + (int)(j))] = 0x000000;
			}
			j++;
		}
		i++;
	}
}

int			main(void)
{
	t_game		*game;
	int loop;
	int k;
	game = create_struct();
	loop = 1;		
	k = -3;
	int	leaks_flag = 0;
	while (loop)
	{
		player_move(game->display_mode, &game->mouse, game->window, game->sounds, game->gif, &game->keystate, game->points, game->sectors, &game->player, &loop);
		get_pos_z(&game->player, game->sectors);
		SDL_FillRect(game->screen,0, 0x00FF00);
		draw_3d_wall(game->screen, game->texture, game->points, game->count_points, game->points_cam, game->display_mode, &game->player, game->sectors, game->count_sectors, game->gif);
		draw_sprites(game->screen, game->sectors, game->sprites, game->player);
		draw_hands(game->screen, game->gif);
		put_fps(game->screen, game->hud, &game->time);
		SDL_UpdateWindowSurface(game->window);
		// временный блок для проверки ликов при полной отрисовки
		if (leaks_flag == 0)
		{
		//	system("leaks doom-nukem");
			leaks_flag = 1;
		}
		//запуск гифок
		if(game->keystate.mouse_l == 1)
		{
			game->gif[1].curr_frame++;
			if (game->gif[1].curr_frame == game->gif[1].frame)
			{
				game->gif[1].curr_frame = 0;
				game->keystate.mouse_l = 0;
			}
		}
		if (k == 0)
		{
			game->gif[0].curr_frame++;
			if (game->gif[0].curr_frame == game->gif[0].frame)
				game->gif[0].curr_frame = 0;
			k = -3;
		}
		else
			k++;
	}
	//закрытие sdl
	free_SDL(game);
	return (0);
}
