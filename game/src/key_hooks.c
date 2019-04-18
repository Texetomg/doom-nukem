/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 15:29:01 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/04/17 19:37:35 by bfalmer-         ###   ########.fr       */
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
	int		flag;
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
					//добавить проверку других стен
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
		}
		i++;
	}
	if (flag == 0)
	{
		game->player.pos.x = game->player.pos.x + x;
		game->player.pos.y = game->player.pos.y + y;
	}
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
	if (key == SDLK_LCTRL || key == SDLK_RCTRL)
		keystate->ctrl = flag;
}

SDL_Event	key_hooks(t_game *game)
{
	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		
		game->player.angle -= 3.14 / 600 * (game->mouse.x - game->display_mode.w / 2);
		if (e.type == SDL_KEYDOWN)
			change_keystate(&game->keystate, e.key.keysym.sym, 1);
		if (e.type == SDL_KEYUP)
			change_keystate(&game->keystate, e.key.keysym.sym, 0);
	}
	return (e);
}

void	        player_move(t_game *game, int *loop)
{
	SDL_Event e;
	vec2	direct;
	vec2	curve;
	e = key_hooks(game);
	SDL_GetMouseState(&game->mouse.x, &game->mouse.y);
	//перемещать курсор в одну и ту же точку
	SDL_WarpMouseInWindow(game->window, game->display_mode.w / 2, game->display_mode.h / 2); 
	direct.x = STEP * cos(game->player.angle);
	direct.y = STEP * sin(game->player.angle);
	curve.x = STEP * (cos(game->player.angle) * 0.7 - sin(game->player.angle) * 0.7);
	curve.y = STEP * (sin(game->player.angle) * 0.7 + cos(game->player.angle) * 0.7);
	if (e.key.keysym.sym == SDLK_ESCAPE || e.type == SDL_QUIT)
			*loop = 0;
	if (game->keystate.forward && (!game->keystate.right || !game->keystate.left))
		move(game, direct.x, direct.y);
	if (game->keystate.back && (!game->keystate.right || !game->keystate.left))
		move(game, -direct.x, -direct.y);
	if (game->keystate.right && (!game->keystate.forward || !game->keystate.back))
		move(game, direct.y, -direct.x);
	if (game->keystate.left && (!game->keystate.forward || !game->keystate.back))
		move(game, -direct.y, direct.x);
	if (game->keystate.forward && game->keystate.right)
		move(game, curve.x, curve.y);
	if (game->keystate.forward && game->keystate.left)
		move(game, curve.y, -curve.x);
	if (game->keystate.back && game->keystate.right)
		move(game, -curve.y, curve.x);
	if (game->keystate.back && game->keystate.left)
		move(game, -curve.x, -curve.y);
	if (game->keystate.jump && game->player.foots == (game->sectors + game->player.curr_sector)->floor)
	{
		game->player.z_accel = 0.1;
		move(game, 0, 0);
	}
	if (game->keystate.ctrl)
	{
		if (game->keystate.ctrl_flag == 0)
			game->player.pos.z -= 0.2;
		game->keystate.ctrl_flag = 1;
		game->player.b_foots = 0.3;
		game->player.b_knees = 0.1;
	}
	if (!game->keystate.ctrl)
	{
		if (game->keystate.ctrl_flag == 1 && game->player.pos.z + 0.2 <  ((game->sectors + game->player.curr_sector)->ceil))
			game->player.pos.z += 0.2;
		game->keystate.ctrl_flag = 0;
		game->player.b_foots = 0.5;
		game->player.b_knees = 0.3;
	}
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		Mix_PlayChannel( -1, game->sounds.bang, 0);
		if (game->gif[1].curr_frame == 0)
			game->keystate.mouse_l = 1;
	}

}
