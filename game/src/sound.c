/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 12:26:44 by thorker           #+#    #+#             */
/*   Updated: 2019/10/24 15:28:41 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

static void	get_right_and_left(t_game *game,
		vec3 position,
		int *right,
		int *left)
{
	double dist;
	double d_x;
	double d_y;

	dist = (position.x - game->player.pos.x) * (position.x -
			game->player.pos.x) + (position.y - game->player.pos.y) *
		(position.y - game->player.pos.y) + (position.z -
				game->player.pos.z) * (position.z - game->player.pos.z);
	d_y = (position.y - game->player.pos.y) * sin(game->player.angle) +
		(position.x - game->player.pos.x) * cos(game->player.angle);
	d_x = -(position.y - game->player.pos.y) * cos(game->player.angle) +
		(position.x - game->player.pos.x) * sin(game->player.angle);
	d_y = fabs(d_y);
	*right = 255;
	*left = 255;
	if (d_x > 0)
		*left = 255 * sqrt(1 / (1 + d_x * d_x / (d_y * d_y)));
	else
		*right = 255 * sqrt(1 / (1 + d_x * d_x / (d_y * d_y)));
	dist = 1 / ((dist + 1) * (dist + 1));
	*left = *left * dist;
	*right = *right * dist;
}

void		play_sound(t_game *game, vec3 position, int flag_sound, int flag)
{
	int right;
	int left;

	(void)flag_sound;
	if (flag == 0)
	{
		right = 255;
		left = 255;
	}
	else
		get_right_and_left(game, position, &right, &left);
	Mix_SetPanning(Mix_PlayChannel(-1, game->sounds.step, 0), left, right);
}
