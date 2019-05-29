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

static void arrows(t_game *game, int pos)
{
	game->start_menu.text_pos += pos;
	Mix_HaltChannel(-1);
	Mix_PlayChannel( -1, game->start_menu.clap[game->start_menu.text_pos - 1], 0);
}

static void key_hook(t_game *game, int **loop)
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if(e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_UP && game->start_menu.text_pos > 1)
				arrows(game, -1);
			if (e.key.keysym.sym == SDLK_DOWN && game->start_menu.text_pos < 4)
				arrows(game, 1);
			if (e.key.keysym.sym == SDLK_ESCAPE ||
				e.type == SDL_QUIT ||
				(e.key.keysym.sym == SDLK_RETURN && game->start_menu.text_pos == 4))
				**loop = 0;
			if (e.key.keysym.sym == SDLK_RETURN &&
				game->start_menu.text_pos != 0 &&
				game->start_menu.text_pos != 4)
			{
				game->complexity = game->start_menu.text_pos;
				game->menu_status.start = 0;
				game->menu_status.main = 1;
				Mix_HaltMusic();
			}
		}
	}
}

void    start_menu_render(t_game *game, int *loop)
{
	int i = 0;
	int new_str = 10;
	
	game->start_menu.dest.h = 80;
	game->start_menu.dest.w = 120;
	
	set_color(&game->start_menu.text_color, 255, 255, 0);
	draw_full_screen_img(game->screen, game->start_menu.image[game->start_menu.text_pos]);
	game->start_menu.dest.x = game->screen->w / 100 * 65;
	game->start_menu.dest.y = game->screen->h / 100 * 5;
	key_hook(game, &loop);
	game->start_menu.dest.y = game->screen->h / 100 * new_str;
	new_str += 5;
	while (i < 5)
	{
		if (game->start_menu.text_pos != i)
			set_color(&game->start_menu.text_color, 255, 255, 0);
		else
			set_color(&game->start_menu.text_color, 0, 255, 0);
			
		print_text(game->screen, game->start_menu.strings[i], "../font/font.otf", 46, game->start_menu.text_color, game->start_menu.dest);
		game->start_menu.dest.y = game->screen->h / 100 * new_str;
		new_str += 5;
		i++;
	}
}
