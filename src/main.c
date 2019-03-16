/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:38:27 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/03/16 11:39:20 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

int main(void)
{
	SDL_Window	*window; //окно
	SDL_Surface	*screen; //поверхность
	int i;
	int loop;
	SDL_Event e;
	int color;
	double x;
	double y;
	double step;
	double x_p;
	double y_p;
	double x1;
	double x2;
	double y1;
	double y2;
	double angle;
	double tx1;
	double tx2;
	double ty1;
	double ty2;
	double x1a;
	double y1b;
	double y1t;
	double x2a;
	double y2b;
	double y2t;
	int k;
	double for_swap;
	double yb;
	double yt;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		put_sdl_error(0);
	window = SDL_CreateWindow("SDL2. Lessons 02",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			1000,
			1000,
			SDL_WINDOW_SHOWN);
	if (window == 0)
		put_sdl_error(0);
	screen = SDL_GetWindowSurface(window);
	loop = 1;
	color = 0;
	step = 0.1;
	angle = 0;
	x_p = 0;
	y_p = 0;
	x1 = 5;
	y1 = 5;
	x2 = 7;
	y2 = 10;
	while (loop)
	{
		while (SDL_PollEvent( &e))
		{
			if (e.type == SDL_QUIT)
				loop = 0;
			if (e.type == SDL_KEYDOWN)
			{
				x = step * cos(angle);
				y = step * sin(angle);
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
		ty1 = (x1 - x_p) * cos(angle) - (y1 - y_p) * sin(angle);
		ty2 = (x2 - x_p) * cos(angle) - (y2 - y_p) * sin(angle);
		tx1 = (x1 - x_p) * sin(angle) + (y1 - y_p) * cos(angle);
		tx2 = (x2 - x_p) * sin(angle) + (y2 - y_p) * cos(angle);
		x1a = tx1 * 300 / ty1 + 500;
		y1t = -500 / ty1 + 500;
		y1b = +500 / ty1 + 500;
		x2a = tx2 * 300 / ty2 + 500;
		y2t = -500 / ty2 + 500;
		y2b = +500 / ty2 + 500;
		ft_putnbrln(angle * 1000);
		ft_putnbrln(x_p);
		ft_putnbrln(y_p);
		SDL_FillRect(screen, 0, 0);
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
					((int*)screen->pixels)[i * 1000 + k] = 0xAA0000;
				i++;
			}
			k++;
		}
		SDL_UpdateWindowSurface(window);
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
	return (0);
}
