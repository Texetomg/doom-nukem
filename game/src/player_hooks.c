/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 11:44:11 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/11/05 12:26:00 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#include <stdio.h>

void	        player_hooks(t_game *game, int *loop)
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
	if (e.key.keysym.sym == SDLK_ESCAPE || e.type == SDL_QUIT)
		*loop = 0;
}

void    move(t_game *game, double x, double y)
{
	double	new_x;
	double	new_y;
	int		i;
	t_vec2	f_point;
	t_vec2	s_point;
	int		flag;
	double  radius;
	double  dx;
	double  dy;
    t_sprite *sprite;

    new_x = game->player.pos.x + x * 1.5;
	new_y = game->player.pos.y + y * 1.5;
	i = 0;
	flag = 0;
	while (i < (game->sectors + game->player.curr_sector)->count_wall)
	{
		
		f_point = *(game->points + *((game->sectors + game->player.curr_sector)->index_points + i));
		if (i == (game->sectors + game->player.curr_sector)->count_wall - 1)
			s_point = *(game->points + *((game->sectors + game->player.curr_sector)->index_points));
		else
			s_point = *(game->points + *((game->sectors + game->player.curr_sector)->index_points + i + 1));

		s_point.x = s_point.x - f_point.x;
		s_point.y = s_point.y - f_point.y;
		f_point.x = new_x - f_point.x;
		f_point.y = new_y - f_point.y;
		if (cross_product(f_point, s_point) < 0)
		{
			if (*((game->sectors + game->player.curr_sector)->neighbors + i) == -1)
				flag = 1;
			else
			{
				if (game->player.knees > (game->sectors + *((game->sectors + game->player.curr_sector)->neighbors + i))->floor &&
					game->player.pos.z < (game->sectors + *((game->sectors + game->player.curr_sector)->neighbors + i))->ceil)
				{
					if (inside_sector(game, new_x, new_y, *(game->sectors + *((game->sectors + game->player.curr_sector)->neighbors + i))) != 0)
					{
						game->player.curr_sector = *((game->sectors + game->player.curr_sector)->neighbors + i);
						game->player.pos.x = new_x;
						game->player.pos.y = new_y;
						if (game->player.foots < (game->sectors + game->player.curr_sector)->floor)
						{
							game->player.pos.z = (game->sectors + game->player.curr_sector)->floor + 0.5;
							game->player.z_accel = 0;
						}
						return ;
					}
					else
						flag = 1;
				}
				else
					flag = 1;
			}
		}
		i++;
	}
	sprite = game->sprites;
	while (sprite != NULL)
    {
	    dx = new_x - sprite->pos.x;
	    dy = new_y - sprite->pos.y;
	    radius = pow(dx, 2) + pow(dy, 2);
	    if (radius < (double)sprite->width * 0.0004)
			flag = 1;
	    sprite = sprite->next;
    }

	if (flag == 0)
	{
		game->player.pos.x = game->player.pos.x + x;
		game->player.pos.y = game->player.pos.y + y;
	}
}