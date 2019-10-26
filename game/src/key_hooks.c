/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 15:29:01 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/10/25 17:00:32 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#include <stdio.h>
static void    move(t_game *game, double x, double y)
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

int				one_sec_check(t_game *game, t_sprite *sprite, int num)
{
	int			i;
	t_vec2		f_point;
	t_vec2		s_point;
	t_sector 	*cur_sec;
	double 		cross;

	cur_sec = game->sectors + num;
	i = 0;
	while (i < cur_sec->count_wall)
	{
		f_point = *(game->points + *(cur_sec->index_points + i));
		if (i == cur_sec->count_wall - 1)
			s_point = *(game->points + *(cur_sec->index_points));
		else
			s_point = *(game->points + *(cur_sec->index_points + i + 1));
		s_point.x = s_point.x - f_point.x;
		s_point.y = s_point.y - f_point.y;
		f_point.x = sprite->pos.x - f_point.x;
		f_point.y = sprite->pos.y - f_point.y;
		cross = cross_product(f_point, s_point);
		if (cross < 0)
			return (0);
		i++;
	}
	return (1);
}

int				sector_check(t_game *game, t_sprite *sprite)
{
	int			i;
	int			j;
	t_vec2		f_point;
	t_vec2		s_point;
	t_sector 	*cur_sec;
	double 		cross;

	cur_sec = game->sectors + sprite->sector;
	i = 0;
	while (i < cur_sec->count_wall)
	{
		f_point = *(game->points + *(cur_sec->index_points + i));
		if (i == cur_sec->count_wall - 1)
			s_point = *(game->points + *(cur_sec->index_points));
		else
			s_point = *(game->points + *(cur_sec->index_points + i + 1));
		s_point.x = s_point.x - f_point.x;
		s_point.y = s_point.y - f_point.y;
		f_point.x = sprite->pos.x - f_point.x;
		f_point.y = sprite->pos.y - f_point.y;
		cross = cross_product(f_point, s_point);
		if (cross < -0.0001)
		{
			j = 0;
			while (j < cur_sec->count_wall)
			{
				if (cur_sec->neighbors[j] == -1)
				{
					j++;
					continue;
				}
				if (one_sec_check(game, sprite, cur_sec->neighbors[j]))
				{
					sprite->sector = cur_sec->neighbors[j];
					sprite->pos.z = sprite->heigth + (game->sectors + cur_sec->neighbors[j])->floor;
					return (0);
				}
				j++;
			}
		}
		i++;
	}
	return (0);
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
	int new_horizon;

	while (SDL_PollEvent(&e))
	{
		
		game->player.angle -= 3.14 / 600 * (game->mouse.x - game->pre_calc.screen_w_div_2);
		new_horizon = game->line_horiz - 2 * (game->mouse.y - game->pre_calc.screen_h_div_2);
		if (new_horizon >= 0 && new_horizon < game->screen->h)
			game->line_horiz = new_horizon;
		if (e.type == SDL_KEYDOWN)
			change_keystate(&game->keystate, e.key.keysym.sym, 1);
		if (e.type == SDL_KEYUP)
			change_keystate(&game->keystate, e.key.keysym.sym, 0);
	}
	return (e);
}

t_sprite *sort(t_sprite *sortlist)
{
	t_sprite *new_list = NULL;

	while (sortlist != NULL)
	{
		t_sprite *node = sortlist;
		sortlist = sortlist->next;

		if (new_list == NULL || node->pos_in_cam.x > new_list->pos_in_cam.x)
		{
			node->next = new_list;
			new_list = node;
		}
		else
		{
			t_sprite *current = new_list;
			while (current->next != NULL && !(node->pos_in_cam.x > current->next->pos_in_cam.x))
				current = current->next;
			node->next = current->next;
			current->next = node;
		}
	}
	return (new_list);
}

void			resp_mobe(t_game *game, t_sprite *sprite)
{
	if (game->player.curr_sector == 0)
	{
		sprite->pos.x = game->spaw1.x;
		sprite->pos.y = game->spaw1.y;
		sprite->sector = 1;
	}
	else if (game->player.curr_sector == 1)
	{
		sprite->pos.x = game->spaw2.x;
		sprite->pos.y = game->spaw2.y;
		sprite->sector = 2;
	}
	else if (game->player.curr_sector == 2)
	{
		sprite->pos.x = game->spaw3.x;
		sprite->pos.y = game->spaw3.y;
		sprite->sector = 4;
	}
	sprite->health = 100;
	sprite->move = 0;
}

void	        player_move(t_game *game, int *loop)
{
	SDL_Event e;
	t_vec2	direct;
	t_vec2	curve;
	double  dx;
	double  dy;
	double	px;
	double	py;
	double	cx;
	double	cy;
	double	new_x;
	double	new_y;
	double	radius;
	t_sprite	*sprite;
	t_sprite	*index;
	t_sprite	*start_sprite;

	e = key_hooks(game);
	SDL_GetMouseState(&game->mouse.x, &game->mouse.y);
	direct.x = STEP * cos(game->player.angle);
	direct.y = STEP * sin(game->player.angle);
	curve.x = STEP * (cos(game->player.angle) * 0.7 - sin(game->player.angle) * 0.7);
	curve.y = STEP * (sin(game->player.angle) * 0.7 + cos(game->player.angle) * 0.7);
	if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
	{
		if (game->cross_flag != NULL)
		{
			if (game->cross_flag->health > 10)
				game->cross_flag->health -= 10;
			if (game->cross_flag->health <= 10)
			{
				game->cross_flag->health = 100;
				game->cross_flag->move = 0;
			}
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
	if (game->keystate.forward && (!game->keystate.right && !game->keystate.left))
	{
		game->for_udp.sound = STEP_SOUND;
		move(game, direct.x, direct.y);
	}
	else if (game->keystate.back && (!game->keystate.right && !game->keystate.left))
	{
		game->for_udp.sound = STEP_SOUND;
		move(game, -direct.x, -direct.y);
	}
	else if (game->keystate.right && (!game->keystate.forward && !game->keystate.back))
	{
		game->for_udp.sound = STEP_SOUND;
		move(game, direct.y, -direct.x);
	}
	else if (game->keystate.left && (!game->keystate.forward && !game->keystate.back))
	{
		game->for_udp.sound = STEP_SOUND;
		move(game, -direct.y, direct.x);
	}
	else if (game->keystate.forward && game->keystate.right)
	{
		game->for_udp.sound = STEP_SOUND;
		move(game, curve.y, -curve.x);
	}
	else if (game->keystate.forward && game->keystate.left)
	{
		game->for_udp.sound = STEP_SOUND;
		move(game, curve.x, curve.y);
	}
	else if (game->keystate.back && game->keystate.right)
	{
		game->for_udp.sound = STEP_SOUND;
		move(game, -curve.x, -curve.y);
	}
	else if (game->keystate.back && game->keystate.left)
	{
		game->for_udp.sound = STEP_SOUND;
		move(game, -curve.y, curve.x);
	}
	else
		game->for_udp.sound = 0;
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

	px = game->player.pos.x;
	py = game->player.pos.y;
	sprite = game->sprites;
	while (sprite != NULL)
	{
		sector_check(game, sprite);
		cx = sprite->pos.x;
		cy = sprite->pos.y;
		dx = px - cx;
		dy = py - cy;
		radius = pow(dx, 2) + pow(dy, 2);
		if (radius > (double) sprite->width * 0.0004)
		{

			dx = dx * (1 - 0.01);
			dy = dy * (1 - 0.01);
			new_x = px - dx;
			new_y = py - dy;
			radius = pow(dx, 2) + pow(dy, 2);
			if ((radius < ((double) sprite->width) * 0.01) && ((radius > ((double) sprite->width) * 0.0004)))
			{
				index = sprite;
				start_sprite = game->sprites;
				while (start_sprite != NULL)
				{
					if (start_sprite != index)
					{
						dx = new_x - start_sprite->pos.x;
						dy = new_y - start_sprite->pos.y;
						radius = pow(dx, 2) + pow(dy, 2);
						if (radius > ((double) sprite->width) * 0.0008)
						{
							if (sprite->health > 30)
							{
								sprite->pos.x = new_x;
								sprite->pos.y = new_y;
							}
							sprite->move = 1;
						}
						else
							sprite->move = 0;
					}
					start_sprite = start_sprite->next;
				}
			}
			else
				sprite->move = 0;
		}
		sprite = sprite->next;
	}
	game->sprites = sort(game->sprites);
}
