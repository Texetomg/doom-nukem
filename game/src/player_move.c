/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 11:44:11 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/11/05 11:45:48 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	        player_move(t_game *game, int *loop)
{
	SDL_Event e;

	e = key_hooks(game);
	SDL_GetMouseState(&game->mouse.x, &game->mouse.y);
    if (game->cross_flag != NULL)
        printf("Health: %d\n", game->cross_flag->health);
	if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
	{
		if (game->cross_flag != NULL)
		{
			if (game->cross_flag->health > 10)
				game->cross_flag->health -= 10;
			if (game->cross_flag->health <= 10)
			{
				game->cross_flag->health = 100;
				resp_mobe(game, game->cross_flag);
				game->cross_flag->move = 0;
			}
			printf("Health: %d\n", game->cross_flag->health);
		}
		Mix_HaltChannel(-1);
		if (game->rifle_state == 0)
			Mix_PlayChannel( -1, game->sounds.bang, 0);
		else
			Mix_PlayChannel( -1, game->sounds.bang1, 0);
		game->rifle_angle = game->player.angle;
		game->rifle_state = 0;
		if (game->gif[1].curr_frame == 0)
			game->keystate.mouse_l = 1;
	}
	if (e.key.keysym.sym == SDLK_ESCAPE || e.type == SDL_QUIT)
		*loop = 0;
	if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_TAB)
	{
		game->menu_status.tab = 1;
		game->menu_status.main = 0;
		game->keystate.left = 0;
		game->keystate.right = 0;
		game->keystate.forward = 0;
		game->keystate.back = 0;

	}
	if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_q)
		game->player.jetpack = (game->player.jetpack == 0 ? 1 : 0);
	player_positioning(game);
	if (game->keystate.jump && ((fabs(game->player.foots - (game->sectors + game->player.curr_sector)->floor)) < 0.000001 || game->player.jetpack == 1))
	{
		game->player.z_accel = 0.05;
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
	sprites_move(game);
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