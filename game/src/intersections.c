/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:43:56 by ramory-l          #+#    #+#             */
/*   Updated: 2019/11/09 17:01:05 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	check_inter(t_inter *inter)
{
	if (fabs(inter->ds->x1 - inter->ds->x2) >
		fabs(inter->ds->y1 - inter->ds->y2))
	{
		inter->ds->x1a = inter->ds->x1 + (inter->ds->x2 - inter->ds->x1) *
		(-inter->ds->first_point.y - inter->ds->x1_b4) /
		(inter->ds->x2_b4 - inter->ds->x1_b4);
		inter->ds->x2a = inter->ds->x1 + (inter->ds->x2 - inter->ds->x1) *
		(-inter->ds->second_point.y - inter->ds->x1_b4) /
		(inter->ds->x2_b4 - inter->ds->x1_b4);
	}
	else
	{
		inter->ds->x1a = inter->ds->y1 - (inter->ds->y2 - inter->ds->y1) *
		(-inter->ds->first_point.y - inter->ds->x1_b4) /
		(inter->ds->x2_b4 - inter->ds->x1_b4);
		inter->ds->x2a = inter->ds->y1 - (inter->ds->y2 - inter->ds->y1) *
		(-inter->ds->second_point.y - inter->ds->x1_b4) /
		(inter->ds->x2_b4 - inter->ds->x1_b4);
	}
	if (inter->ds->x1a > inter->ds->x2a)
	{
		inter->ds->x1a = -inter->ds->x1a;
		inter->ds->x2a = -inter->ds->x2a;
	}
}

void	intersections(t_inter *inter)
{
	if (intersection(&inter->ds->first_point, &inter->ds->second_point,
		inter->for_draw->fov_left, inter->for_draw->fov_right) > 0)
	{
		init_intersections(1, inter);
		if (*((inter->game->sectors +
			inter->for_draw->curr_sector)->neighbors + inter->ds->i) >= 0)
		{
			if (*((inter->game->sectors +
				inter->for_draw->curr_sector)->neighbors + inter->ds->i) !=
				inter->for_draw->last_sector)
			{
				init_intersections(2, inter);
				init_intersections(3, inter);
			}
		}
		else
			init_intersections(4, inter);
		draw_floor(inter->game, *inter->for_draw, -inter->ds->yfloor,
		(inter->game->sectors + inter->for_draw->curr_sector)->brightness);
		if (inter->for_draw->curr_sector != 0)
			draw_ceil(inter->game, *inter->for_draw, inter->ds->yceil,
			(inter->game->sectors + inter->for_draw->curr_sector)->brightness);
	}
	inter->ds->i++;
}
