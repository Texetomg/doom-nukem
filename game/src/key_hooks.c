/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 15:29:01 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/04/18 16:13:19 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"
#include <stdio.h>
static void    move(vec2 *points, t_sector *sectors, t_player *player, double x, double y)
{
	double	new_x;
	double	new_y;
	int		i;
	vec2	f_point;
	vec2	s_point;
	int		flag;
    new_x = player->pos.x + x * 1.5;
	new_y = player->pos.y + y * 1.5;
	i = 0;
	flag = 0;
	while (i < (sectors + player->curr_sector)->count_wall)
	{
		
		f_point = *(points + *((sectors + player->curr_sector)->index_points + i));
		if (i == (sectors + player->curr_sector)->count_wall - 1)
			s_point = *(points + *((sectors + player->curr_sector)->index_points));
		else
			s_point = *(points + *((sectors + player->curr_sector)->index_points + i + 1));

		s_point.x = s_point.x - f_point.x;
		s_point.y = s_point.y - f_point.y;
		f_point.x = new_x - f_point.x;
		f_point.y = new_y - f_point.y;
		if (cross_product(f_point, s_point) < 0)
		{
			if (*((sectors + player->curr_sector)->neighbors + i) == -1)
				flag = 1;
			else
			{
				if (player->knees > (sectors + *((sectors + player->curr_sector)->neighbors + i))->floor &&
					player->pos.z < (sectors + *((sectors + player->curr_sector)->neighbors + i))->ceil)
				{
					//добавить проверку других стен
					player->curr_sector = *((sectors + player->curr_sector)->neighbors + i);
					player->pos.x = new_x;
					player->pos.y = new_y;
					if (player->foots < (sectors + player->curr_sector)->floor)
					{
						player->pos.z = (sectors + player->curr_sector)->floor + 0.5;
						player->z_accel = 0;
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
		player->pos.x = player->pos.x + x;
		player->pos.y = player->pos.y + y;
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

SDL_Event	key_hooks(t_player *player, SDL_DisplayMode display_mode, t_keystate *keystate, vec2int *mouse)
{
	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		
		player->angle -= 3.14 / 600 * (mouse->x - display_mode.w / 2);
		if (e.type == SDL_KEYDOWN)
			change_keystate(keystate, e.key.keysym.sym, 1);
		if (e.type == SDL_KEYUP)
			change_keystate(keystate, e.key.keysym.sym, 0);
	}
	return (e);
}

void	        player_move(SDL_DisplayMode display_mode,
							vec2int *mouse,
							SDL_Window *window,
							t_sounds sounds,
							t_gif *gif,
							t_keystate *keystate,
							vec2 *points,
							t_sector *sectors,
							t_player *player,
							int *loop)
{
	SDL_Event e;
	vec2	direct;
	vec2	curve;
	e = key_hooks(player, display_mode, keystate, mouse);
	SDL_GetMouseState(&mouse->x, &mouse->y);
	//перемещать курсор в одну и ту же точку
	SDL_WarpMouseInWindow(window, display_mode.w / 2, display_mode.h / 2); 
	direct.x = STEP * cos(player->angle);
	direct.y = STEP * sin(player->angle);
	curve.x = STEP * (cos(player->angle) * 0.7 - sin(player->angle) * 0.7);
	curve.y = STEP * (sin(player->angle) * 0.7 + cos(player->angle) * 0.7);
	if (e.key.keysym.sym == SDLK_ESCAPE || e.type == SDL_QUIT)
			*loop = 0;
	if (keystate->forward && (!keystate->right && !keystate->left))
		move(points, sectors, player, direct.x, direct.y);
	if (keystate->back && (!keystate->right && !keystate->left))
		move(points, sectors, player, -direct.x, -direct.y);
	if (keystate->right && (!keystate->forward && !keystate->back))
		move(points, sectors, player, direct.y, -direct.x);
	if (keystate->left && (!keystate->forward && !keystate->back))
		move(points, sectors, player, -direct.y, direct.x);
	if (keystate->forward && keystate->right)
		move(points, sectors, player, curve.y, -curve.x);
	if (keystate->forward && keystate->left)
		move(points, sectors, player, curve.x, curve.y);
	if (keystate->back && keystate->right)
		move(points, sectors, player, -curve.x, -curve.y);
	if (keystate->back && keystate->left)
		move(points, sectors, player, -curve.y, curve.x);
	if (keystate->jump && player->foots == (sectors + player->curr_sector)->floor)
	{
		player->z_accel = 0.1;
		move(points, sectors, player, 0, 0);
	}
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
		if (keystate->ctrl_flag == 1 && player->pos.z + 0.2 <  ((sectors + player->curr_sector)->ceil))
			player->pos.z += 0.2;
		keystate->ctrl_flag = 0;
		player->b_foots = 0.5;
		player->b_knees = 0.3;
	}
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		Mix_PlayChannel( -1, sounds.bang, 0);
		if (gif[1].curr_frame == 0)
			keystate->mouse_l = 1;
	}

}
