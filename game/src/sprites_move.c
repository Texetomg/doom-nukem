/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramory-l <ramory-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 11:33:51 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/11/09 19:37:05 by ramory-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void			resp_mobe(t_game *game, t_sprite *sprite)
{
	if (game->player.curr_sector == 0)
	{
		sprite->pos.x = game->spaw1.x;
		sprite->pos.y = game->spaw1.y;
		sprite->pos.z = sprite->heigth + (game->sectors + 1)->floor;
		sprite->sector = 1;
	}
	else if (game->player.curr_sector == 1)
	{
		sprite->pos.x = game->spaw2.x;
		sprite->pos.y = game->spaw2.y;
		sprite->pos.z = sprite->heigth + (game->sectors + 2)->floor;
		sprite->sector = 2;
	}
	else if (game->player.curr_sector == 2)
	{
		sprite->pos.x = game->spaw3.x;
		sprite->pos.y = game->spaw3.y;
		sprite->pos.z = sprite->heigth + (game->sectors + 4)->floor;
		sprite->sector = 4;
	}
	sprite->health = 100;
	sprite->move = 0;
}

static t_sprite	*sort(t_sprite *sortlist)
{
	t_sprite *new_list;
	t_sprite *node;
	t_sprite *current;

	new_list = NULL;
	while (sortlist != NULL)
	{
		node = sortlist;
		sortlist = sortlist->next;
		if (new_list == NULL || node->pos_in_cam.x > new_list->pos_in_cam.x)
		{
			node->next = new_list;
			new_list = node;
		}
		else
		{
			current = new_list;
			while (current->next != NULL &&
				!(node->pos_in_cam.x > current->next->pos_in_cam.x))
				current = current->next;
			node->next = current->next;
			current->next = node;
		}
	}
	return (new_list);
}

static void		loop(t_sm *sm)
{
	while (sm->start_sprite != NULL)
	{
		if (sm->start_sprite != sm->index)
		{
			sm->dx = sm->new_x - sm->start_sprite->pos.x;
			sm->dy = sm->new_y - sm->start_sprite->pos.y;
			sm->radius = pow(sm->dx, 2) + pow(sm->dy, 2);
			if (sm->radius > ((double)sm->sprite->width) * 0.0008)
			{
				if (sm->sprite->health > 30)
				{
					sm->sprite->pos.x = sm->new_x;
					sm->sprite->pos.y = sm->new_y;
				}
				sm->sprite->move = 1;
			}
			else
				sm->sprite->move = 0;
		}
		sm->start_sprite = sm->start_sprite->next;
	}
}

static void		check_radius(t_game *game, t_sm *sm)
{
	if (sm->radius > (double)sm->sprite->width * 0.0004)
	{
		sm->dx = sm->dx * (1 - 0.01);
		sm->dy = sm->dy * (1 - 0.01);
		sm->new_x = sm->px - sm->dx;
		sm->new_y = sm->py - sm->dy;
		sm->radius = pow(sm->dx, 2) + pow(sm->dy, 2);
		if ((sm->radius < ((double)sm->sprite->width) * 0.01) &&
			((sm->radius > ((double)sm->sprite->width) * 0.0004)))
		{
			sm->index = sm->sprite;
			sm->start_sprite = game->sprites;
			loop(sm);
		}
		else
			sm->sprite->move = 0;
	}
}

void			sprites_move(t_game *game)
{
	t_sm		sm;

	sm.px = game->player.pos.x;
	sm.py = game->player.pos.y;
	sm.sprite = game->sprites;
	while (sm.sprite != NULL)
	{
		sector_check(game, sm.sprite);
		sm.cx = sm.sprite->pos.x;
		sm.cy = sm.sprite->pos.y;
		sm.dx = sm.px - sm.cx;
		sm.dy = sm.py - sm.cy;
		sm.radius = pow(sm.dx, 2) + pow(sm.dy, 2);
		check_radius(game, &sm);
		sm.sprite = sm.sprite->next;
	}
	game->sprites = sort(game->sprites);
}
