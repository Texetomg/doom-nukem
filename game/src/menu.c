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

void	draw_image(t_game *game, int i, SDL_Surface *image[])
{
	int	x = 0;
	int	y = 0;
	int new_x;
	int new_y;
	int color;

	while (y < game->screen->h)
	{
		new_y = (double)y / game->screen->h * image[i]->h;
		x = 0;
		while (x < game->screen->w)
		{
			new_x = (double)x / game->screen->w * image[i]->w;
			color = ((int*)(image[i]->pixels))[new_y * image[i]->w + new_x];
			((int*)(game->screen->pixels))[y * game->screen->w + x] = color;
			x++;
		}
		y++;
	}
}

void    start_menu_render(t_game *game, int *loop)
{
	int i = 0;
	int new_str = 10;
	SDL_Event e;
	game->start_menu.dest.h = 80;
	game->start_menu.dest.w = 120;
	
	set_color(&game->start_menu.text_color, 255, 255, 0);
	draw_image(game, game->start_menu.text_pos, game->start_menu.image);
	game->start_menu.dest.x = game->screen->w / 100 * 65;
	game->start_menu.dest.y = game->screen->h / 100 * 5;
	while (SDL_PollEvent(&e))
	{
		if(e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_UP && game->start_menu.text_pos > 1)
			{
				game->start_menu.text_pos --;
				Mix_HaltChannel(-1);
				Mix_PlayChannel( -1, game->start_menu.clap[game->start_menu.text_pos - 1], 0);
			}
			if (e.key.keysym.sym == SDLK_DOWN && game->start_menu.text_pos <= 4)
			{
				game->start_menu.text_pos ++;
				Mix_HaltChannel(-1);
				Mix_PlayChannel( -1, game->start_menu.clap[game->start_menu.text_pos - 1], 0);
			}
			if (e.key.keysym.sym == SDLK_ESCAPE || e.type == SDL_QUIT || (e.key.keysym.sym == SDLK_RETURN && game->start_menu.text_pos == 4))
				*loop = 0;
			if (e.key.keysym.sym == SDLK_RETURN && game->start_menu.text_pos != 0 && game->start_menu.text_pos != 4)
			{
				game->complexity = game->start_menu.text_pos;
				game->menu_status.start = 0;
				game->menu_status.main = 1;
				Mix_HaltMusic();
			}

		}
	}
	game->start_menu.dest.y = game->screen->h / 100 * new_str;
	new_str += 5;
	while (i < 5)
	{
		if (game->start_menu.text_pos != i)
			set_color(&game->start_menu.text_color, 255, 255, 0);
		else
			set_color(&game->start_menu.text_color, 0, 255, 0);
			
		print_text(game->screen, game->start_menu.strings[i], "font.otf", 46, game->start_menu.text_color, game->start_menu.dest);
		game->start_menu.dest.y = game->screen->h / 100 * new_str;
		new_str += 5;
		i++;
	}
	//print_text(game->screen, ft_itoa(game->start_menu.text_pos), "font.otf", 46, game->start_menu.color, game->start_menu.dest);
}


void    tab_menu_render(t_game *game, int *loop)
{
	int i = 0;
	int new_str = 10;
	SDL_Event e;
	game->tab_menu.dest.h = 80;
	game->tab_menu.dest.w = 120;
	game->tab_menu.dest.x = game->screen->w / 100 * 65;
	game->tab_menu.dest.y = game->screen->h / 100 * 5;
	game->tab_menu.image[1] = NULL;
	game->tab_menu.image[2] = NULL;
	set_color(&game->start_menu.text_color, 255, 255, 0);
	draw_image(game, 0, game->tab_menu.image);
	while (SDL_PollEvent(&e))
	{
		if(e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_ESCAPE || e.type == SDL_QUIT || (e.key.keysym.sym == SDLK_RETURN && game->tab_menu.text_pos == 2))
				*loop = 0;
			if (e.key.keysym.sym == SDLK_TAB)
			{
				game->menu_status.tab = 0;
				game->menu_status.main = 1;
			}
			if (e.key.keysym.sym == SDLK_RETURN && game->tab_menu.text_pos == 0)
			{
				game->menu_status.tab = 0;
				game->menu_status.main = 1;
			}
			if (e.key.keysym.sym == SDLK_RETURN && game->tab_menu.text_pos == 1)
			{
				game->menu_status.tab = 0;
				game->menu_status.start = 1;
				Mix_HaltMusic();
			}
			if (e.key.keysym.sym == SDLK_UP && game->tab_menu.text_pos > 0)
				game->tab_menu.text_pos --;
			if (e.key.keysym.sym == SDLK_DOWN && game->tab_menu.text_pos < 2)
				game->tab_menu.text_pos ++;
		}
	}
	game->tab_menu.dest.y = game->screen->h / 100 * new_str;
	new_str += 5;
	while (i < 3)
	{
		if (game->tab_menu.text_pos != i)
			set_color(&game->tab_menu.text_color, 255, 255, 0);
		else
			set_color(&game->tab_menu.text_color, 0, 255, 0);
			
		print_text(game->screen, game->tab_menu.strings[i], "font.otf", 46, game->tab_menu.text_color, game->tab_menu.dest);
		game->tab_menu.dest.y = game->screen->h / 100 * new_str;
		new_str += 5;
		i++;
	}

}