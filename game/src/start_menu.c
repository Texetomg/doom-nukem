/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_menu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 16:57:31 by thorker           #+#    #+#             */
/*   Updated: 2019/10/25 16:58:02 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void	arrows(t_game *game, int pos)
{
	game->start_menu.text_pos += pos;
	Mix_HaltChannel(-1);
	Mix_PlayChannel(-1,
					game->start_menu.clap[game->start_menu.text_pos - 1],
					0);
}

static void	key_hook_sup(t_game *game, int *loop, SDL_Event e)
{
	if (e.key.keysym.sym == SDLK_UP && game->start_menu.text_pos > 1)
		arrows(game, -1);
	else if (e.key.keysym.sym == SDLK_DOWN && game->start_menu.text_pos < 5)
		arrows(game, 1);
	else if (e.key.keysym.sym == SDLK_RETURN && game->start_menu.text_pos == 4)
		switch_menu(&game->menu_status.multi, &game->menu_status.start);
	else if (e.key.keysym.sym == SDLK_ESCAPE || e.type == SDL_QUIT ||
		(e.key.keysym.sym == SDLK_RETURN && game->start_menu.text_pos == 5))
		*loop = 0;
	else if (e.key.keysym.sym == SDLK_RETURN &&
		game->start_menu.text_pos != 0 && game->start_menu.text_pos != 5)
	{
		game->complexity = game->start_menu.text_pos;
		switch_menu(&game->menu_status.main, &game->menu_status.start);
		Mix_HaltMusic();
	}
}

static void	key_hook(t_game *game, int *loop)
{
	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_KEYDOWN)
			key_hook_sup(game, loop, e);
	}
}

void		start_menu_render(t_game *game, int *loop)
{
	menu_render(game->screen,
				&game->start_menu,
				game->start_menu.image[game->start_menu.text_pos]);
	key_hook(game, loop);
	print_menu_text(game->screen, &game->start_menu, 6);
}
