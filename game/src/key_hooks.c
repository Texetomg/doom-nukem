/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 15:29:01 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/04/03 20:20:08 by bfalmer-         ###   ########.fr       */
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
}

static void		change_keystate(t_keystate *keystate, SDL_Keycode key, int flag)
{
	if (key == SDLK_w)
		keystate->forward = flag;
	if (key == SDLK_s)
		keystate->back = flag;
	if (key == SDLK_d)
		keystate->right = flag;
	if (key == SDLK_a)
		keystate->left = flag;
	if (key == SDLK_SPACE)
		keystate->jump = flag;
	if (key == SDLK_LSHIFT || key == SDLK_RSHIFT)
		keystate->shift = flag;
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
			change_keystate(&game->keystate, e.key.keysym.sym, 1);
		if (e.type == SDL_KEYUP)
			change_keystate(&game->keystate, e.key.keysym.sym, 0);
		x = step * cos(game->player.angle);
		y = step * sin(game->player.angle);
		if (e.key.keysym.sym == SDLK_ESCAPE || e.type == SDL_QUIT)
			*loop = 0;
		if (game->keystate.forward)
			move(game, x, y);
		if (game->keystate.back)
			move(game, -x, -y);
		if (game->keystate.right)
			move(game, y, -x);
		if (game->keystate.left)
			move(game, -y, x);
		if (game->keystate.jump && game->player.foots == (game->sectors + game->player.curr_sector)->floor)
		{
			game->player.z_accel = 0.1;
			move(game, 0, 0);
		}
	}
}
