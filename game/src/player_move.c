/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 12:41:40 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/11/05 14:14:31 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void	sprite_rotation(t_game *game, double new_x, double new_y, int *flag)
{
	double		radius;
	double		dx;
	double		dy;
	t_sprite	*sprite;

	sprite = game->sprites;
	while (sprite != NULL)
	{
		dx = new_x - sprite->pos.x;
		dy = new_y - sprite->pos.y;
		radius = pow(dx, 2) + pow(dy, 2);
		if (radius < (double)sprite->width * 0.0004)
			*flag = 1;
		sprite = sprite->next;
	}
}

static void	main_cycle(t_game *game, double new_x, double new_y, int *flag)
{
	t_vec2	f_point;
	t_vec2	s_point;
	int		i;

	i = 0;
	while (i < (game->sectors + game->player.curr_sector)->count_wall)
	{
		appoint_points(game, &f_point, &s_point, i);
		count_points(&f_point, &s_point, new_x, new_y);
		if (cross_product(f_point, s_point) < 0)
		{
			if (*((game->sectors + game->player.curr_sector)->neighbors + i) == -1)
				*flag = 1;
			else
			{
				if (game->player.knees > (game->sectors + *((game->sectors + game->player.curr_sector)->neighbors + i))->floor &&
					game->player.pos.z < (game->sectors + *((game->sectors + game->player.curr_sector)->neighbors + i))->ceil)
				{
					if (inside_sector(game, new_x, new_y, *(game->sectors + *((game->sectors + game->player.curr_sector)->neighbors + i))) != 0)
					{
						player_position(game, new_x, new_y, i);
						return ;
					}
					else
						*flag = 1;
				}
				else
					*flag = 1;
			}
		}
		i++;
	}
}

void		move(t_game *game, double x, double y)
{
	double	new_x;
	double	new_y;
	int		flag;

	new_x = game->player.pos.x + x * 1.5;
	new_y = game->player.pos.y + y * 1.5;
	flag = 0;
	main_cycle(game, new_x, new_y, &flag);
	sprite_rotation(game, new_x, new_y, &flag);
	if (flag == 0)
	{
		game->player.pos.x = game->player.pos.x + x;
		game->player.pos.y = game->player.pos.y + y;
	}
}
