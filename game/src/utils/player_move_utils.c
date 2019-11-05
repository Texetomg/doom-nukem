/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 14:02:46 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/11/05 14:06:17 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	appoint_points(t_game *game, t_vec2 *f_point, t_vec2 *s_point, int i)
{
	*f_point = *(game->points + *((game->sectors +
		game->player.curr_sector)->index_points + i));
	if (i == (game->sectors + game->player.curr_sector)->count_wall - 1)
		*s_point = *(game->points + *((game->sectors +
			game->player.curr_sector)->index_points));
	else
		*s_point = *(game->points + *((game->sectors +
			game->player.curr_sector)->index_points + i + 1));
}

void	player_position(t_game *game, double new_x, double new_y, int i)
{
	game->player.curr_sector =
		*((game->sectors + game->player.curr_sector)->neighbors + i);
	game->player.pos.x = new_x;
	game->player.pos.y = new_y;
	if (game->player.foots < (game->sectors + game->player.curr_sector)->floor)
	{
		game->player.pos.z =
			(game->sectors + game->player.curr_sector)->floor + 0.5;
		game->player.z_accel = 0;
	}
}

void	ount_points(t_vec2 *f_point, t_vec2 *s_point, double new_x,
	double new_y)
{
	s_point->x = s_point->x - f_point->x;
	s_point->y = s_point->y - f_point->y;
	f_point->x = new_x - f_point->x;
	f_point->y = new_y - f_point->y;
}
