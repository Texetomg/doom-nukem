/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 16:57:31 by thorker           #+#    #+#             */
/*   Updated: 2019/04/16 18:14:46 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

void	set_color(SDL_Color *color, int r, int g, int b)
{
	color->r = r;
	color->g = g;
	color->b = b;
}

void    menu_render(t_game *game, int *loop)
{
	int	x = 0;
	int	y = 0;
	int color;
	int new_x;
	int new_y;
	int i = 0;
	int new_str = 10;
	SDL_Event e;
	game->menu.dest.h = 80;
	game->menu.dest.w = 120;
	
	set_color(&game->menu.color, 255, 255, 0);
	while (y < game->screen->h)
	{
		new_y = (double)y / game->screen->h * game->menu.image->h;
		x = 0;
		while (x < game->screen->w)
		{
			new_x = (double)x / game->screen->w * game->menu.image->w;
			color = ((int*)(game->menu.image->pixels))[new_y * game->menu.image->w + new_x];
			((int*)(game->screen->pixels))[y * game->screen->w + x] = color;
			x++;
		}
		y++;
	}
	
	game->menu.dest.x = game->screen->w / 100 * 65;
	game->menu.dest.y = game->screen->h / 100 * 5;
	while (SDL_PollEvent(&e))
	{
		if(e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_UP && game->menu.position > 0)
				game->menu.position --;
			if (e.key.keysym.sym == SDLK_DOWN && game->menu.position < 2)
				game->menu.position ++;
			if (e.key.keysym.sym == SDLK_ESCAPE || e.type == SDL_QUIT)
				*loop = 0;
			if (e.key.keysym.sym == SDLK_RETURN)
			{
				game->complexity = game->menu.position;
				game->menu.status = 0;
			}
			if (e.key.keysym.sym == SDLK_TAB)
				game->menu.status = 0;
		}
	}
	print_text(game->screen, "CHOOSE YOUR GENDER:", "font.otf", 46, game->menu.color, game->menu.dest);
	game->menu.dest.y = game->screen->h / 100 * new_str;
	new_str += 5;
	while (i < 3)
	{
		if (game->menu.position != i)
			set_color(&game->menu.color, 255, 255, 0);
		else
			set_color(&game->menu.color, 0, 255, 0);
		print_text(game->screen, game->menu.strings[i], "font.otf", 46, game->menu.color, game->menu.dest);
		game->menu.dest.y = game->screen->h / 100 * new_str;
		new_str += 5;
		i++;
	}
	//print_text(game->screen, ft_itoa(game->menu.position), "font.otf", 46, game->menu.color, game->menu.dest);
}
