/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_draw_sector.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramory-l <ramory-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 13:43:23 by ramory-l          #+#    #+#             */
/*   Updated: 2019/11/08 15:21:53 by ramory-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void init1(t_pds_a *pds_a, t_pds *pds)
{
	pds->i = pds_a->game->screen->w / 2;
	pds->k = pds_a->game->screen->h / 2;
	pds->yt_window = pds_a->for_draw.window.y1t +
	(pds_a->for_draw.window.y2t - pds_a->for_draw.window.y1t) *
	(pds->i - pds_a->for_draw.window.x1) / (pds_a->for_draw.window.x2 - pds_a->for_draw.window.x1);
	pds->yb_window = pds_a->for_draw.window.y1b +
	(pds_a->for_draw.window.y2b - pds_a->for_draw.window.y1b) *
	(pds->i - pds_a->for_draw.window.x1) / (pds_a->for_draw.window.x2 - pds_a->for_draw.window.x1);
	pds->yt_wall = pds_a->for_draw.wall.y1t +
	(pds_a->for_draw.wall.y2t - pds_a->for_draw.wall.y1t) *
	(pds->i - pds_a->for_draw.window.x1) / (pds_a->for_draw.window.x2 - pds_a->for_draw.window.x1);
	pds->yb_wall = pds_a->for_draw.wall.y1b +
	(pds_a->for_draw.wall.y2b - pds_a->for_draw.wall.y1b) *
	(pds->i - pds_a->for_draw.window.x1) / (pds_a->for_draw.window.x2 - pds_a->for_draw.window.x1);
	pds->a = (double)(pds->i - (int)pds_a->for_draw.wall.x1) /
	((int)pds_a->for_draw.wall.x2 - (int)pds_a->for_draw.wall.x1);
	pds->x = ((1 - pds->a) * pds_a->x1 / pds_a->y1 + pds->a *
	pds_a->x2 / pds_a->y2) /((1 - pds->a) / pds_a->y1 + pds->a / pds_a->y2);
	if (pds->x > 0)
		pds->x = (pds->x - (int)pds->x) * pds_a->bars->w;
	else
		pds->x = (pds->x - (int)pds->x + 1) * pds_a->bars->w;
	pds->a = (double)(pds->k - (int)pds->yt_wall) / ((int)pds->yb_wall - (int)pds->yt_wall);
	pds->y = -((1 - pds->a) * pds_a->ceil + pds->a * pds_a->floor);
}

static void init2(t_pds_a *pds_a, t_pds *pds)
{
	if (pds->y > 0)
		pds->y = (pds->y - (int)pds->y) * pds_a->bars->h;
	else
		pds->y = (pds->y - (int)pds->y + 1) * pds_a->bars->h;
	if (pds->x >= 0 && pds->x < pds_a->bars->w &&
		pds->y >= 0 && pds->y < pds_a->bars->h)
	{
		pds->color = (pds_a->bars->pixels)[(int)pds->y *
		pds_a->bars->w + (int)pds->x];
		if (pds->color != 0)
		{
			pds_a->game->cross_flag = NULL;
			pds_a->game->sprite_wall = NULL;
		}
	}
}

void    pre_draw_sector(t_pds_a *pds_a)
{
	t_pds pds;

	init1(pds_a, &pds);
	init2(pds_a, &pds);
	(void)pds_a->display_mode;
	pds.i = (int)pds_a->for_draw.wall.x1;
	pds.x_start = (int)pds_a->for_draw.wall.x1;
	pds.dx_left = 0;
	pds.dx_right = 0;
	if (pds.i < 0)
	{
		pds.dx_left = -pds.i;
		pds.i = 0;
	}
	pds.wall_max_x = pds_a->for_draw.wall.x2 - pds_a->for_draw.wall.x1;
	if (pds_a->for_draw.wall.x2 > pds_a->screen->w)
	{
		pds.dx_right = pds_a->for_draw.wall.x2 - pds_a->screen->w;
	}
	pre_draw_sec_loop(pds_a, &pds);
}