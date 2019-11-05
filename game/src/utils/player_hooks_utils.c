/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_hooks_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 12:25:47 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/11/05 12:34:28 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	shoot_hook(t_game *game, SDL_Event e)
{
	SDL_GetMouseState(&game->mouse.x, &game->mouse.y);
	game->cross_flag != NULL ? printf("HP: %d\n", game->cross_flag->health) : 0;
	if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
	{
		if (game->cross_flag != NULL)
		{
			if (game->cross_flag->health > 10)
				game->cross_flag->health -= 10;
			if (game->cross_flag->health <= 10)
			{
				game->cross_flag->health = 100;
				resp_mobe(game, game->cross_flag);
				game->cross_flag->move = 0;
			}
			printf("Health: %d\n", game->cross_flag->health);
		}
		Mix_HaltChannel(-1);
		game->rifle_state == 0 ? Mix_PlayChannel(-1, game->sounds.bang, 0) : 0;
		Mix_PlayChannel(-1, game->sounds.bang1, 0);
		game->rifle_angle = game->player.angle;
		game->rifle_state = 0;
		game->gif[1].curr_frame == 0 ? game->keystate.mouse_l = 1 : 0;
	}
}

void	tab_hook(t_keystate *keystate, t_menu_status *menu_status, SDL_Event e)
{
	if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_TAB)
	{
		menu_status->tab = 1;
		menu_status->main = 0;
		keystate->left = 0;
		keystate->right = 0;
		keystate->forward = 0;
		keystate->back = 0;
	}
}

void	ctrl_hook(t_keystate *keystate, t_player *player, t_sector *sectors)
{
	if (keystate->ctrl)
	{
		if (keystate->ctrl_flag == 0)
			player->pos.z -= 0.2;
		keystate->ctrl_flag = 1;
		player->b_foots = 0.3;
		player->b_knees = 0.1;
	}
	if (!keystate->ctrl)
	{
		if (keystate->ctrl_flag == 1 && player->pos.z + 0.2 <
			((sectors + player->curr_sector)->ceil))
			player->pos.z += 0.2;
		keystate->ctrl_flag = 0;
		player->b_foots = 0.5;
		player->b_knees = 0.3;
	}
}

void	jump_hook(t_game *game)
{
	if (game->keystate.jump &&
		((fabs(game->player.foots - (game->sectors +
			game->player.curr_sector)->floor)) <
		0.000001 || game->player.jetpack == 1))
	{
		game->player.z_accel = 0.05;
		move(game, 0, 0);
	}
}

void	jetpack_hook(t_player *player, SDL_Event e)
{
	if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_q)
		player->jetpack = (player->jetpack == 0 ? 1 : 0);
}
