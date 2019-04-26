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

static void key_hook(t_game *game, int **loop)
{
    SDL_Event e;

    while (SDL_PollEvent(&e))
	{
		if(e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_ESCAPE ||
                e.type == SDL_QUIT ||
                (e.key.keysym.sym == SDLK_RETURN && game->tab_menu.text_pos == 2))
				**loop = 0;
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
}

void    tab_menu_render(t_game *game, int *loop)
{
	int i = 0;
	int new_str = 10;
	
	game->tab_menu.dest.h = 80;
	game->tab_menu.dest.w = 120;
	game->tab_menu.dest.x = game->screen->w / 100 * 65;
	game->tab_menu.dest.y = game->screen->h / 100 * 5;
	game->tab_menu.image[1] = NULL;
	game->tab_menu.image[2] = NULL;
	set_color(&game->start_menu.text_color, 255, 255, 0);
	draw_image(game, 0, game->tab_menu.image);
    key_hook(game, &loop);
	game->tab_menu.dest.y = game->screen->h / 100 * new_str;
	new_str += 5;
	while (i < 3)
	{
		if (game->tab_menu.text_pos != i)
			set_color(&game->tab_menu.text_color, 255, 255, 0);
		else
			set_color(&game->tab_menu.text_color, 0, 255, 0);
			
		print_text(game->screen, game->tab_menu.strings[i], "../font/font.otf", 46, game->tab_menu.text_color, game->tab_menu.dest);
		game->tab_menu.dest.y = game->screen->h / 100 * new_str;
		new_str += 5;
		i++;
	}
}