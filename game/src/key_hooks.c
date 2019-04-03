/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 15:29:01 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/04/03 18:30:30 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"
#include <stdio.h>
static void    move(t_game *game, double x, double y)
{
	double	new_x;
	double	new_y;
	int		i;
	vec2	f_point;
	vec2	s_point;

    new_x = game->player.pos.x + x;
	new_y = game->player.pos.y + y;
	i = 0;
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
				return ;
			else
			{
				game->player.curr_sector = *((game->sectors + game->player.curr_sector)->neighbors + i);
				break ;
			}
		}
		i++;
	}
	game->player.pos.x = new_x;
	game->player.pos.y = new_y;
	get_pos_z(game);
	printf("%f", game->player.pos.z);
//	game->player.pos.z = (game->sectors + game->player.curr_sector)->floor + 0.5;
}

void	        player_move(t_game *game, int *loop)
{
	SDL_Event e;
	double x;
	double y;
	double step;
	step = 0.1;
	
	while (SDL_PollEvent( &e))
		{
			SDL_GetMouseState(&game->mouse.x, &game->mouse.y);
            //перемещать курсор в одну и ту же точку
			SDL_WarpMouseInWindow(game->window, game->display_mode.w / 2, game->display_mode.h / 2); 
			game->player.angle -= 3.14 / 600 * (game->mouse.x - game->display_mode.w / 2);
			if (e.type == SDL_KEYDOWN)
			{
				x = step * cos(game->player.angle);
				y = step * sin(game->player.angle);
				if (e.key.keysym.sym == SDLK_ESCAPE || e.type == SDL_QUIT)
					*loop = 0;
				if (e.key.keysym.sym == SDLK_e)
					game->player.angle -= 3.14 / 60;
				if (e.key.keysym.sym == SDLK_q)
					game->player.angle += 3.14 / 60;
				if (e.key.keysym.sym == SDLK_w)
                    move(game, x, y);
				if (e.key.keysym.sym == SDLK_s)
					move(game, -x, -y);
				if (e.key.keysym.sym == SDLK_d)
					move(game, y, -x);
				if (e.key.keysym.sym == SDLK_a)
					move(game, -y, x);
				if (e.key.keysym.sym == SDLK_SPACE)
				{
					game->player.z_accel = 0.3;
					move(game, 0, 0);
				}
			}
		}
}
