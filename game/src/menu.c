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

void	draw_image(t_game *game, int i)
{
	int	x = 0;
	int	y = 0;
	int new_x;
	int new_y;
	int color;

	while (y < game->screen->h)
	{
		new_y = (double)y / game->screen->h * game->menu.image[i]->h;
		x = 0;
		while (x < game->screen->w)
		{
			new_x = (double)x / game->screen->w * game->menu.image[i]->w;
			color = ((int*)(game->menu.image[i]->pixels))[new_y * game->menu.image[i]->w + new_x];
			((int*)(game->screen->pixels))[y * game->screen->w + x] = color;
			x++;
		}
		y++;
	}
}

void    menu_render(t_game *game, int *loop)
{
	int i = 0;
	int new_str = 10;
	SDL_Event e;
	game->menu.dest.h = 80;
	game->menu.dest.w = 120;
	game->menu.image[0] = IMG_Load("imgs/destiny/1.jpg");
	game->menu.image[1] = IMG_Load("imgs/destiny/2.jpg");
	game->menu.image[2] = IMG_Load("imgs/destiny/3.jpg");
	
	if (!(game->menu.clap[0] = Mix_LoadWAV( "sounds/loli.mp3" )))
		check_error_n_exit(1,(char*)SDL_GetError());
	if (!(game->menu.clap[1] = Mix_LoadWAV( "sounds/trump.mp3" )))
		check_error_n_exit(1,(char*)SDL_GetError());
	if (!(game->menu.clap[2] = Mix_LoadWAV( "sounds/doom.mp3" )))
		check_error_n_exit(1,(char*)SDL_GetError());
	
	set_color(&game->menu.text_color, 255, 255, 0);
	draw_image(game, game->menu.text_pos);
	game->menu.dest.x = game->screen->w / 100 * 65;
	game->menu.dest.y = game->screen->h / 100 * 5;
	while (SDL_PollEvent(&e))
	{
		if(e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_UP && game->menu.text_pos > 0)
			{
				game->menu.text_pos --;
				Mix_HaltChannel(-1);
				Mix_PlayChannel( -1, game->menu.clap[game->menu.text_pos], 0);
			}
			if (e.key.keysym.sym == SDLK_DOWN && game->menu.text_pos < 2)
			{
				game->menu.text_pos ++;
				Mix_HaltChannel(-1);
				Mix_PlayChannel( -1, game->menu.clap[game->menu.text_pos], 0);
			}
			if (e.key.keysym.sym == SDLK_ESCAPE || e.type == SDL_QUIT)
				*loop = 0;
			if (e.key.keysym.sym == SDLK_RETURN)
			{
				game->complexity = game->menu.text_pos;
				game->menu.status = 0;
			}
			if (e.key.keysym.sym == SDLK_TAB)
			{
				game->menu.status = 0;
				Mix_HaltMusic();
			}
		}
	}
	print_text(game->screen, "CHOOSE YOUR DESTINY:", "font.otf", 46, game->menu.text_color, game->menu.dest);
	game->menu.dest.y = game->screen->h / 100 * new_str;
	new_str += 5;
	while (i < 3)
	{
		if (game->menu.text_pos != i)
			set_color(&game->menu.text_color, 255, 255, 0);
		else
			set_color(&game->menu.text_color, 0, 255, 0);
			
		print_text(game->screen, game->menu.strings[i], "font.otf", 46, game->menu.text_color, game->menu.dest);
		game->menu.dest.y = game->screen->h / 100 * new_str;
		new_str += 5;
		i++;
	}
	//print_text(game->screen, ft_itoa(game->menu.text_pos), "font.otf", 46, game->menu.color, game->menu.dest);
}
