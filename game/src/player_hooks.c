/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 11:44:11 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/11/05 12:43:09 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#include <stdio.h>

void	player_hooks(t_game *game, int *loop)
{
	SDL_Event e;

	e = key_hooks(game);
	shoot_hook(game, e);
	tab_hook(&game->keystate, &game->menu_status, e);
	jetpack_hook(&game->player, e);
	player_positioning(game);
	jump_hook(game);
	ctrl_hook(&game->keystate, &game->player, game->sectors);
	sprites_move(game);
	e.key.keysym.sym == SDLK_ESCAPE || e.type == SDL_QUIT ? *loop = 0 : 0;
}
