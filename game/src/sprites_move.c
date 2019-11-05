/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 11:33:51 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/11/05 11:43:26 by bfalmer-         ###   ########.fr       */
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

static int				one_sec_check(t_game *game, t_sprite *sprite, int num)
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

static int		sector_check(t_game *game, t_sprite *sprite)
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

static t_sprite *sort(t_sprite *sortlist)
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

void			sprites_move(t_game *game)
{
	t_sprite	*sprite;
	t_sprite	*index;
	t_sprite	*start_sprite;
	double  dx;
	double  dy;
	double	px;
	double	py;
	double	cx;
	double	cy;
	double	new_x;
	double	new_y;
	double	radius;

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
