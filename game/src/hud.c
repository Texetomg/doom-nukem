/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 16:38:34 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/10/25 17:01:53 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void	draw_key(SDL_Surface *screen, SDL_Surface *img)
{
	t_vec2 start;
	t_vec2 end;

	start.x = screen->w / 100 * 90;
	start.y = screen->h / 100 * 5;
	end.x = screen->w / 100 * 99;
	end.y = screen->h / 100 * 15;
	draw_img(screen, img, start, end);
}

void		draw_hud(t_game *game)
{
	draw_player_icon(game->screen, game->hud.face[2]);
	draw_aim(game->screen, game->hud.aim);
	draw_hp_bar(game->screen, game->hud.hp_bar);
	draw_hands(game->screen, *(game->gif[1].array + game->gif[1].curr_frame));
	if (game->player.jetpack)
		draw_jetpack(game->screen, game->hud.jetpack);
	if (game->player.key)
		draw_key(game->screen, game->hud.key);
}
