/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 12:26:44 by thorker           #+#    #+#             */
/*   Updated: 2019/05/27 15:08:11 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

void	play_sound(t_game *game, vec3 position, int flag_sound, int flag)
{
	double dist;
	int right;
	int left;
	double delta_x;
	double delta_y;
	int channel;

	(void)flag_sound;
	if (flag == 0)
	{
		right = 255;
		left = 255;
	}
	else
	{
		dist = (position.x - game->player.pos.x) * (position.x - game->player.pos.x) + (position.y - game->player.pos.y) * (position.y - game->player.pos.y) + (position.z - game->player.pos.z) * (position.z - game->player.pos.z);
		delta_y = (position.y - game->player.pos.y) * sin(game->player.angle) + (position.x - game->player.pos.x) * cos(game->player.angle);
		delta_x = -(position.y - game->player.pos.y) * cos(game->player.angle) + (position.x - game->player.pos.x) * sin(game->player.angle);
		if (delta_y < 0)
			delta_y = -delta_y;
		if (delta_x > 0)
		{
			right = 255;
			left = 255 * sqrt(1 /( 1 + delta_x * delta_x / (delta_y * delta_y)));
		}
		else
		{
			left = 255;
			right = 255 * sqrt(1 /( 1 + delta_x * delta_x / (delta_y * delta_y)));
		}
		dist = 1 / ((dist + 1) * (dist + 1));
		left = left * dist;
		right = right * dist;
	}
	channel = Mix_PlayChannel(-1, game->sounds.step, 0);
	Mix_SetPanning(channel, left, right);
}
