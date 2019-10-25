/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_menu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 16:57:31 by thorker           #+#    #+#             */
/*   Updated: 2019/10/25 16:58:02 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void	key_hook(t_game *game, int *loop)
{
	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_ESCAPE || e.type == SDL_QUIT ||
				(e.key.keysym.sym == SDLK_RETURN &&
					game->tab_menu.text_pos == 2))
				*loop = 0;
			if (e.key.keysym.sym == SDLK_TAB)
				switch_menu(&game->menu_status.main, &game->menu_status.tab);
			if (e.key.keysym.sym == SDLK_RETURN && game->tab_menu.text_pos == 0)
				switch_menu(&game->menu_status.main, &game->menu_status.tab);
			if (e.key.keysym.sym == SDLK_RETURN && game->tab_menu.text_pos == 1)
			{
				// game start again
				set_player(game);
				game->tab_menu.text_pos = 0;
				game->start_menu.text_pos = 0;
				switch_menu(&game->menu_status.start, &game->menu_status.tab);
				Mix_HaltMusic();
			}
			if (e.key.keysym.sym == SDLK_UP && game->tab_menu.text_pos > 0)
				game->tab_menu.text_pos--;
			if (e.key.keysym.sym == SDLK_DOWN && game->tab_menu.text_pos < 2)
				game->tab_menu.text_pos++;
		}
	}
}

void		tab_menu_render(t_game *game, int *loop)
{
	menu_render(game->screen, &game->tab_menu, game->tab_menu.image[0]);
	key_hook(game, loop);
	print_menu_text(game->screen, &game->tab_menu, 3);
}
