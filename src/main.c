/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:38:27 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/03/26 19:51:27 by bfalmer-         ###   ########.fr       */
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
	double x_fov;
	double y1_fov;
	double y2_fov;
	double x;
	double y;

	x_fov = 8.66;
	y1_fov = 5;
	y2_fov = -5;
	x = cross_product(x_fov, y1_fov, *x1, *y1);
	y = cross_product(x_fov, y1_fov, *x2, *y2);
	if (x > 0 && y > 0)
	{
		ft_putendl("lol");
		return (0);
	}
	if (x > 0 || y > 0)
	{
		if (x > 0)
			cross(x1, y1, *x2, *y2, x_fov, y1_fov);
		else
			cross(x2, y2, *x1, *y1, x_fov, y1_fov);
	}
	x = cross_product(x_fov, y2_fov, *x1, *y1);
	y = cross_product(x_fov, y2_fov, *x2, *y2);
	if (x < 0 && y < 0)
	{
		ft_putstr("lol2");
		return (0);
	}
	if (x < 0 || y < 0)
	{
		if (x < 0)
			cross(x1, y1, *x2, *y2, x_fov, y2_fov);
		else
			cross(x2, y2, *x1, *y1, x_fov, y2_fov);
	}
	return (1);
}

int main(void)
{
	SDL_Window	*window; 			//окно
	SDL_Surface	*screen; 			//поверхность
	SDL_DisplayMode	display_mode;	//параметры дисплея
	int request;					//обработка возвращаемых значений
	int loop;
	SDL_Event e;
	double x1;
	double x2;
	double y1;
	double y2;
	double x_p;
	double y_p;
	double angle;
	double tx1;
	double tx2;
	double ty1;
	double ty2;
	double x1a;
	double x2a;
	double y1t;
	double y2t;
	double y1b;
	double y2b;
	double x;
	double y;
	int k;
	int i;
	double yt;
	double yb;
	double step;
	int color;
	step = 0.1;
	x_p = 0.0;
	y_p = 0;
	x1 = 2;
	y1 = 2;
	x2 = 2;
	y2 = -2;
	angle = 0;
	double for_swap;
	t_wall	*world_wall;
	t_wall	*cam_wall;
	t_fps	*fps;
	fps = (t_fps*)malloc(sizeof(t_fps));
	world_wall = (t_wall*)malloc(sizeof(t_wall) * 4);
	cam_wall = (t_wall*)malloc(sizeof(t_wall) * 4);
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

	(world_wall + 1)->pos1.y = -1;
	(world_wall + 1)->pos1.x = 2;
	(world_wall + 1)->pos2.y = -3;
	(world_wall + 1)->pos2.x = -2;
	(world_wall + 1)->color = 0xAA00;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		put_sdl_error(0);
	request = SDL_GetDesktopDisplayMode(0, &display_mode);
	SDL_ShowCursor(SDL_DISABLE); //спрятать курсор в пределах окна
	window = SDL_CreateWindow("SDL2. Lessons 02",
			0,
			0,
			1000,
			1000,
			SDL_WINDOW_SHOWN);
	if (window == 0)
		put_sdl_error(0);
	screen = SDL_GetWindowSurface(window);
	loop = 1;
	while (loop)
	{
		SDL_WarpMouseInWindow(window, display_mode.w / 2, display_mode.h / 2);
		while (SDL_PollEvent( &e))
		{
			if (e.type == SDL_KEYDOWN)
			{
				x = step * cos(angle);
				y = step * sin(angle);
				if (e.key.keysym.sym == SDLK_ESCAPE || e.type == SDL_QUIT)
					loop = 0;
				if (e.key.keysym.sym == SDLK_e)
					angle -= 3.14 / 60;
				if (e.key.keysym.sym == SDLK_q)
					angle += 3.14 / 60;
				if (e.key.keysym.sym == SDLK_w)
				{
					x_p += x;
					y_p -= y;
				}
				if (e.key.keysym.sym == SDLK_s)
				{
					x_p -= x;
					y_p += y;
				}
				if (e.key.keysym.sym == SDLK_d)
				{
						x_p += y;
						y_p += x;
				}
				if (e.key.keysym.sym == SDLK_a)
				{
						x_p -= y;
						y_p -= x;
				}
			}
		}
		SDL_FillRect(screen, 0, 0);
		tx1 = -(y1 - y_p) * sin(angle) + (x1 - x_p) * cos(angle);
		tx2 = -(y2 - y_p) * sin(angle) + (x2 - x_p) * cos(angle);
		ty1 = (y1 - y_p) * cos(angle) + (x1 - x_p) * sin(angle);
		ty2 = (y2 - y_p) * cos(angle) + (x2 - x_p) * sin(angle);
		if (ty1 > 0 || ty2 > 0)
		{
			if (intersection(&tx1, &ty1, &tx2, &ty2) != 0)
			{
				ft_putnbrln(tx1);
				ft_putnbrln(ty1);
				ft_putnbrln(tx2);
				ft_putnbrln(ty2);
				x1a = ty1 * 700 / tx1 + 500;
				y1t = -500 / tx1 + 500;
				y1b = 500 / tx1 + 500;
				x2a = ty2 * 700 / tx2 + 500;
                y2t = -500 / tx2 + 500;
                y2b = 500 / tx2 + 500;
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
					color = 0xAA0000;
				}
				else
					color = 0x00AA00;
				k = (int)x1a;
				while (k < (int)x2a)
				{
					yt = y1t + (y2t - y1t) * (k - x1a) / (x2a - x1a);
					yb = y1b + (y2b - y1b) * (k - x1a) / (x2a - x1a);
					i = (int)yt;
					while (i < yb)
					{
						if (i >= 0 && i < 1000 && k >= 0 && k < 1600)
							((int*)screen->pixels)[i * 1600 + k] = color;
						i++;
					}
					k++;
				}
			}
		}
		put_fps(fps);
		SDL_UpdateWindowSurface(window);
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
	return (0);
}
