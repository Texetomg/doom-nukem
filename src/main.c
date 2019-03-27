/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:38:27 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/03/27 19:27:28 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"


double	cross_product(double x1, double y1, double x2, double y2)
{
	return (x1 * y2 - x2 * y1);
}

void	cross(double *x1, double *y1, double x2, double y2, double x_fov, double y_fov)
{
	double new_x;
	double new_y;
	double det;

	det = cross_product(*x1, *y1, x2, y2) / ((-x_fov) * (*y1 - y2) + y_fov * (*x1 - x2));
	new_x = x_fov * det;
	new_y = y_fov * det;
	*x1 = new_x;
	*y1 = new_y;
}

int	intersection(double *x1, double *y1, double *x2, double *y2)
{
	double x1_fov;
	double x2_fov;
	double y1_fov;
	double y2_fov;
	double x;
	double y;

	x1_fov = 8.66;
	y1_fov = 5;
	x2_fov = 8.66;
	y2_fov = -5;
	x = cross_product(x1_fov, y1_fov, *x1, *y1);
	y = cross_product(x1_fov, y1_fov, *x2, *y2);
	if (x > 0 && y > 0)
		return (0);
	if (x > 0 || y > 0)
	{
		if (x > 0)
			cross(x1, y1, *x2, *y2, x1_fov, y1_fov);
		else
			cross(x2, y2, *x1, *y1, x1_fov, y1_fov);
	}
	x = cross_product(x2_fov, y2_fov, *x1, *y1);
	y = cross_product(x2_fov, y2_fov, *x2, *y2);
	if (x < 0 && y < 0)
		return (0);
	if (x < 0 || y < 0)
	{
		if (x < 0)
			cross(x1, y1, *x2, *y2, x2_fov, y2_fov);
		else
			cross(x2, y2, *x1, *y1, x2_fov, y2_fov);
	}
	return (1);
}
void	change_wall(t_wall *cam_wall)
{
	cam_wall->pos1.x = (5 + cam_wall->pos1.x) * 20;
	cam_wall->pos2.x = (5 + cam_wall->pos2.x) * 20;
	cam_wall->pos1.y = (5 - cam_wall->pos1.y) * 20;
	cam_wall->pos2.y = (5 - cam_wall->pos2.y) * 20;
}
void	change_world_in_cam(t_wall *world_wall, t_wall *cam_wall, t_player player)
{
	cam_wall->pos1.x = (world_wall->pos1.y - player.pos.y) * sin(player.angle) + (world_wall->pos1.x - player.pos.x) * cos(player.angle);
	cam_wall->pos2.x = (world_wall->pos2.y - player.pos.y) * sin(player.angle) + (world_wall->pos2.x - player.pos.x) * cos(player.angle);
	cam_wall->pos1.y = (world_wall->pos1.y - player.pos.y) * cos(player.angle) - (world_wall->pos1.x - player.pos.x) * sin(player.angle);
	cam_wall->pos2.y = (world_wall->pos2.y - player.pos.y) * cos(player.angle) - (world_wall->pos2.x - player.pos.x) * sin(player.angle);
	cam_wall->color = world_wall->color;
}

void	draw_3d_wall(SDL_Surface *screen, t_wall wall)
{
	double x1a;
	double y1t;
	double y1b;
	double x2a;
	double y2t;
	double y2b;
	int i;
	int k;
	double yt;
	double yb;
	double for_swap;

	if (wall.pos1.x < 0 && wall.pos2.x < 0)
		return ;
	if (intersection(&wall.pos1.x, &wall.pos1.y, &wall.pos2.x, &wall.pos2.y) != 0)
	{
		x1a = -wall.pos1.y * 700 / wall.pos1.x + 500;
		y1t = -500 / wall.pos1.x + 500;
		y1b = 500 / wall.pos1.x + 500;
		x2a = -wall.pos2.y * 700 / wall.pos2.x + 500;
		y2t = -500 / wall.pos2.x + 500;
		y2b = 500 / wall.pos2.x + 500;
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
		while (k < (int)x2a)
		{
			yt = y1t + (y2t - y1t) * (k - x1a) / (x2a - x1a);
			yb = y1b + (y2b - y1b) * (k - x1a) / (x2a - x1a);
			i = (int)yt;
			while (i < yb)
			{
				if (i >= 0 && i < 1000 && k >= 0 && k < 1000)
					((int*)screen->pixels)[i * 1000 + k] = wall.color;
				i++;
			}
			k++;
		}
	}
}
int main(void)
{
	SDL_Window	*window; 			//окно
	SDL_Surface	*screen; 			//поверхность
	SDL_DisplayMode	display_mode;	//параметры дисплея
	int request;					//обработка возвращаемых значений
	int loop;
	SDL_Event e;
	t_player	player;
	double x;
	double y;
	int i;
	double step;
	step = 0.1;
	t_wall	*world_wall;
	t_wall	*cam_wall;
	t_fps	*fps;
	t_mouse	*mouse;
	mouse = (t_mouse*)malloc(sizeof(t_mouse));
	fps = (t_fps*)malloc(sizeof(t_fps));
	world_wall = (t_wall*)malloc(sizeof(t_wall) * 4);
	cam_wall = (t_wall*)malloc(sizeof(t_wall) * 4);
	player.pos.x = 0;
	player.pos.y = 0;
	player.angle = 0;
	world_wall->pos1.y = 2;
	world_wall->pos1.x = 0;
	world_wall->pos2.y = -1;
	world_wall->pos2.x = 2;
	world_wall->color = 0xAA0000;

	(world_wall + 1)->pos1.y = -1;
	(world_wall + 1)->pos1.x = 2;
	(world_wall + 1)->pos2.y = -3;
	(world_wall + 1)->pos2.x = -2;
	(world_wall + 1)->color = 0xAA00;

	(world_wall + 2)->pos1.y = -3;
	(world_wall + 2)->pos1.x = -2;
	(world_wall + 2)->pos2.y = 2;
	(world_wall + 2)->pos2.x = 0;
	(world_wall + 2)->color = 0xAA;
	request = SDL_GetDesktopDisplayMode(0, &display_mode);
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		put_sdl_error(0);
	SDL_ShowCursor(SDL_DISABLE); //спрятать курсор в пределах окна
	window = SDL_CreateWindow("SDL2. Lessons 02",
			0,
			0,
			1000,
			1000,
			SDL_WINDOW_SHOWN);
	if (window == 0)
		put_sdl_error(0);
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	screen = SDL_GetWindowSurface(window);
	loop = 1;
	while (loop)
	{
		
		while (SDL_PollEvent( &e))
		{
			SDL_GetMouseState(&mouse->curr_x, &mouse->curr_y);
		SDL_WarpMouseInWindow(window, MOUSE_POS_X, MOUSE_POS_Y); //перемещать курсор в одну и ту же точку
		
			player.angle -= 3.14 / 600 * (mouse->curr_x - MOUSE_POS_X);
		
			if (e.type == SDL_KEYDOWN)
			{
				x = step * cos(player.angle);
				y = step * sin(player.angle);
				if (e.key.keysym.sym == SDLK_ESCAPE || e.type == SDL_QUIT)
					loop = 0;
				if (e.key.keysym.sym == SDLK_e)
					player.angle -= 3.14 / 60;
				if (e.key.keysym.sym == SDLK_q)
					player.angle += 3.14 / 60;
				if (e.key.keysym.sym == SDLK_w)
				{
					player.pos.x += x;
					player.pos.y += y;
				}
				if (e.key.keysym.sym == SDLK_s)
				{
					player.pos.x -= x;
					player.pos.y -= y;
				}
				if (e.key.keysym.sym == SDLK_d)
				{
						player.pos.x +=  y;
						player.pos.y -= x;
				}
				if (e.key.keysym.sym == SDLK_a)
				{
						player.pos.x -= y;
						player.pos.y += x;
				}
			}
		}

		SDL_FillRect(screen, 0, 0);
		i = 0;
		while (i < 3)
		{
			change_world_in_cam(world_wall + i, cam_wall + i, player);
			draw_3d_wall(screen, *(cam_wall + i));
			i++;
		}

		//put_fps(fps);
		i = 0;
		while (i < 3)
		{
			change_wall(cam_wall + i);
			i++;
		}
		draw_minimap(screen, cam_wall);
		SDL_UpdateWindowSurface(window);
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
	return (0);
}
