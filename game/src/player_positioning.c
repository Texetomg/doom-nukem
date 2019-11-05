/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_positioning.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 11:24:42 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/11/05 11:29:43 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void	player_positionig_sup(t_game *game, double first_pos,
	double second_pos)
{
	game->for_udp.sound = STEP_SOUND;
	move(game, first_pos, second_pos);
}

static void	make_step_sound(t_game *game, t_vec2 direct, t_vec2 curve)
{
	if (game->keystate.forward && (!game->keystate.right &&
		!game->keystate.left))
		player_positionig_sup(game, direct.x, direct.y);
	else if (game->keystate.back && (!game->keystate.right &&
		!game->keystate.left))
		player_positionig_sup(game, -direct.x, -direct.y);
	else if (game->keystate.right && (!game->keystate.forward &&
		!game->keystate.back))
		player_positionig_sup(game, direct.y, -direct.x);
	else if (game->keystate.left && (!game->keystate.forward &&
		!game->keystate.back))
		player_positionig_sup(game, -direct.y, direct.x);
	else if (game->keystate.forward && game->keystate.right)
		player_positionig_sup(game, curve.y, -curve.x);
	else if (game->keystate.forward && game->keystate.left)
		player_positionig_sup(game, curve.x, curve.y);
	else if (game->keystate.back && game->keystate.right)
		player_positionig_sup(game, -curve.x, -curve.y);
	else if (game->keystate.back && game->keystate.left)
		player_positionig_sup(game, -curve.y, curve.x);
	else
		game->for_udp.sound = 0;
}

void		player_positioning(t_game *game)
{
	t_vec2	direct;
	t_vec2	curve;

	direct.x = STEP * cos(game->player.angle);
	direct.y = STEP * sin(game->player.angle);
	curve.x = STEP * (cos(game->player.angle) * 0.7 -
		sin(game->player.angle) * 0.7);
	curve.y = STEP * (sin(game->player.angle) * 0.7 +
		cos(game->player.angle) * 0.7);
	make_step_sound(game, direct, curve);
}
