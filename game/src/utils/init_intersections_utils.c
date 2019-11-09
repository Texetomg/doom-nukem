/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_intersections_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 16:45:16 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/11/09 16:46:39 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	init1_sup(t_inter *inter)
{
	inter->ds->yceil = (inter->game->sectors +
	inter->for_draw->curr_sector)->ceil - inter->game->player.pos.z;
	inter->ds->yfloor = (inter->game->sectors +
	inter->for_draw->curr_sector)->floor - inter->game->player.pos.z;
	inter->ds->yscale1 = inter->game->pre_calc.screen_h_div_2 /
	inter->ds->first_point.x;
	inter->ds->yscale2 = inter->game->pre_calc.screen_h_div_2 /
	inter->ds->second_point.x;
	inter->for_draw->wall.x1 = -inter->ds->first_point.y *
	(inter->game->pre_calc.screen_w_div_2) / inter->ds->first_point.x +
	inter->game->pre_calc.screen_w_div_2;
	inter->for_draw->wall.x2 = -inter->ds->second_point.y *
	(inter->game->pre_calc.screen_w_div_2) / inter->ds->second_point.x +
	inter->game->pre_calc.screen_w_div_2;
	inter->for_draw->wall.y2t = -inter->ds->yscale2 * inter->ds->yceil +
	inter->game->line_horiz;
	inter->for_draw->wall.y1t = -inter->ds->yscale1 * inter->ds->yceil +
	inter->game->line_horiz;
	inter->for_draw->wall.y2b = -inter->ds->yscale2 * inter->ds->yfloor +
	inter->game->line_horiz;
	inter->for_draw->wall.y1b = -inter->ds->yscale1 * inter->ds->yfloor +
	inter->game->line_horiz;
}