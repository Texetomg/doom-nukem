/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 15:29:01 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/04/03 17:42:49 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

static void    move(vec3 *pos, double x, double y)
{
    pos->x += x;
	pos->y += y;
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
                    move(&(game->player.pos), x, y);
				if (e.key.keysym.sym == SDLK_s)
					move(&(game->player.pos), -x, -y);
				if (e.key.keysym.sym == SDLK_d)
					move(&(game->player.pos), y, -x);
				if (e.key.keysym.sym == SDLK_a)
					move(&(game->player.pos), -y, x);
			}
		}
}
