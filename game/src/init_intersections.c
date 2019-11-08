/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_intersections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramory-l <ramory-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 16:36:29 by ramory-l          #+#    #+#             */
/*   Updated: 2019/11/08 16:42:40 by ramory-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void init1(t_inter *inter)
{
	inter->ds->perc1 = (-inter->ds->first_point.y - inter->ds->x1_b4) /
	(inter->ds->x2_b4 - inter->ds->x1_b4);
	inter->ds->perc2 = (-inter->ds->second_point.y - inter->ds->x1_b4) /
	(inter->ds->x2_b4 - inter->ds->x1_b4);
	inter->ds->y1a = inter->ds->first_point.x;
	inter->ds->y2a =inter-> ds->second_point.x;
	check_inter(inter);
	inter->ds->yceil = (inter->game->sectors +
	inter->for_draw->curr_sector)->ceil - inter->game->player.pos.z;
	inter->ds->yfloor = (inter->game->sectors +
	inter->for_draw->curr_sector)->floor - inter->game->player.pos.z;
	inter->ds->yscale1 =  inter->game->pre_calc.screen_h_div_2 /
	inter->ds->first_point.x;
	inter->ds->yscale2 =  inter->game->pre_calc.screen_h_div_2 /
	inter->ds->second_point.x;
	inter->for_draw->wall.x1 = -inter->ds->first_point.y *
	(inter->game->pre_calc.screen_w_div_2) / inter->ds->first_point.x +
	inter->game->pre_calc.screen_w_div_2;
	inter->for_draw->wall.x2 = -inter->ds->second_point.y *
	(inter->game->pre_calc.screen_w_div_2) / inter->ds->second_point.x +
	inter->game->pre_calc.screen_w_div_2;
	inter->for_draw->wall.y2t = -inter->ds->yscale2 * inter->ds->yceil + inter->game->line_horiz;
	inter->for_draw->wall.y1t = -inter->ds->yscale1 * inter->ds->yceil + inter->game->line_horiz;
	inter->for_draw->wall.y2b = -inter->ds->yscale2 * inter->ds->yfloor + inter->game->line_horiz;
	inter->for_draw->wall.y1b = -inter->ds->yscale1 * inter->ds->yfloor + inter->game->line_horiz;
}

static void init2(t_inter *inter)
{
	inter->ds->for_next_draw.wall = inter->for_draw->wall;
	inter->ds->y2ceil = (inter->game->sectors + *((inter->game->sectors +
	inter->for_draw->curr_sector)->neighbors + inter->ds->i))->ceil -
	inter->game->player.pos.z;
	inter->ds->y2floor = (inter->game->sectors + *((inter->game->sectors +
	inter->for_draw->curr_sector)->neighbors + inter->ds->i))->floor -
	inter->game->player.pos.z;
	inter->ds->for_next_draw.window.y1t = -inter->ds->yscale1 *
	inter->ds->y2ceil + inter->game->line_horiz;
	inter->ds->for_next_draw.window.y1b = -inter->ds->yscale1 *
	inter->ds->y2floor + inter->game->line_horiz;
	inter->ds->for_next_draw.window.y2t = -inter->ds->yscale2 *
	inter->ds->y2ceil + inter->game->line_horiz;
	inter->ds->for_next_draw.window.y2b = -inter->ds->yscale2 *
	inter->ds->y2floor + inter->game->line_horiz;
	inter->ds->for_next_draw.window.x1 = inter->ds->for_next_draw.wall.x1;
	inter->ds->for_next_draw.window.x2 = inter->ds->for_next_draw.wall.x2;
	inter->ds->for_next_draw.curr_sector = *((inter->game->sectors +
	inter->for_draw->curr_sector)->neighbors + inter->ds->i);
	inter->ds->for_next_draw.last_sector = inter->for_draw->curr_sector;
	inter->ds->for_next_draw.fov_left = inter->ds->first_point;
	inter->ds->for_next_draw.fov_right = inter->ds->second_point;
	draw_sector(inter->game, inter->ds->for_next_draw);
}

static void init3(t_inter *inter)
{
	inter->pds_a->screen = inter->game->screen;
	inter->pds_a->display_mode = inter->game->display_mode;
	inter->pds_a->for_draw = inter->ds->for_next_draw;
	inter->pds_a->bright = (inter->game->sectors +
	inter->for_draw->curr_sector)->brightness;
	inter->pds_a->grid = *((inter->game->sectors +
	inter->for_draw->curr_sector)->grid + inter->ds->i);
	inter->pds_a->game = inter->game;
	inter->pds_a->x1 = inter->ds->x1a;
	inter->pds_a->x2 = inter->ds->x2a;
	inter->pds_a->y1 = inter->ds->y1a;
	inter->pds_a->y2 = inter->ds->y2a;
	inter->pds_a->ceil = (inter->game->sectors +
	inter->for_draw->curr_sector)->ceil;
	inter->pds_a->floor = (inter->game->sectors +
	inter->for_draw->curr_sector)->floor;
	inter->pds_a->bars = inter->game->texture1;
	pre_draw_sector(inter->pds_a);
}

static void init4(t_inter *inter)
{
	inter->dw_a->for_draw = *inter->for_draw;
	inter->dw_a->x1 = inter->ds->x1a;
	inter->dw_a->x2 = inter->ds->x2a;
	inter->dw_a->y1 = inter->ds->y1a;
	inter->dw_a->y2 = inter->ds->y2a;
	inter->dw_a->ceil = (inter->game->sectors +
	inter->for_draw->curr_sector)->ceil;
	inter->dw_a->floor = (inter->game->sectors +
	inter->for_draw->curr_sector)->floor;
	inter->dw_a->bright = (inter->game->sectors +
	inter->for_draw->curr_sector)->brightness;
	inter->dw_a->perc1 = inter->ds->perc1;
	inter->dw_a->perc2 = inter->ds->perc2;
	inter->dw_a->sprite_wall = inter->game->sectors->sprite_wall;
	if (inter->for_draw->curr_sector == 0 && inter->ds->i == 0)
		draw_wall(inter->game, *inter->dw_a);
	else
	{
		inter->dw_a->sprite_wall = 0;
		draw_wall(inter->game, *inter->dw_a);
	}
}

void init_intersections(int i, t_inter *inter)
{
	if (i == 1)
		init1(inter);
	if (i == 2)
		init2(inter);
	if (i == 3)
		init3(inter);
	if (i == 4)
		init4(inter);
}