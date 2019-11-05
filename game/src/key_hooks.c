/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 15:29:01 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/11/05 11:48:24 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void	change_keystate(t_keystate *keystate, SDL_Keycode key, int flag)
{
	if (key == SDLK_w)
		keystate->forward = flag;
	if (key == SDLK_s)
		keystate->back = flag;
	if (key == SDLK_d)
		keystate->right = flag;
	if (key == SDLK_a)
		keystate->left = flag;
	if (key == SDLK_SPACE)
		keystate->jump = flag;
	if (key == SDLK_LCTRL || key == SDLK_RCTRL)
		keystate->ctrl = flag;
}

SDL_Event	key_hooks(t_game *game)
{
	SDL_Event	e;
	int			new_horizon;

	while (SDL_PollEvent(&e))
	{
		game->player.angle -= 3.14 / 600 * (game->mouse.x -
			game->pre_calc.screen_w_div_2);
		new_horizon = game->line_horiz - 2 * (game->mouse.y -
			game->pre_calc.screen_h_div_2);
		if (new_horizon >= 0 && new_horizon < game->screen->h)
			game->line_horiz = new_horizon;
		if (e.type == SDL_KEYDOWN)
			change_keystate(&game->keystate, e.key.keysym.sym, 1);
		if (e.type == SDL_KEYUP)
			change_keystate(&game->keystate, e.key.keysym.sym, 0);
	}
	return (e);
}
