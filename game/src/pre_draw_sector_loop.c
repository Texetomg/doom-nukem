/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_draw_sector_loop.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramory-l <ramory-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:14:00 by ramory-l          #+#    #+#             */
/*   Updated: 2019/11/08 15:29:30 by ramory-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void init(t_pds_a *pds_a, t_pds *pds)
{
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
	if (pds->yt_wall < 0)
		pds->k = 0;
	else
		pds->k = pds->yt_wall;
	pds->a = (double)(pds->i - (int)pds_a->for_draw.wall.x1) /
	((int)pds_a->for_draw.wall.x2 - (int)pds_a->for_draw.wall.x1);
	pds->x = ((1 - pds->a) * pds_a->x1 /
	pds_a->y1 + pds->a * pds_a->x2 / pds_a->y2) /((1 - pds->a) / pds_a->y1 + pds->a / pds_a->y2);
	if (pds->x > 0)
		pds->x = (pds->x - (int)pds->x) * pds_a->game->texture->w;
	else
		pds->x = (pds->x - (int)pds->x + 1) * pds_a->game->texture->w;
}

static void check_grid(t_pds_a *pds_a, t_pds *pds)
{
	if (pds_a->grid == 1)
	{
		pds->a = (double) (pds->i - (int) pds_a->for_draw.wall.x1) /
		((int) pds_a->for_draw.wall.x2 - (int) pds_a->for_draw.wall.x1);
		pds->x = ((1 - pds->a) * pds_a->x1 / pds_a->y1 +
		pds->a * pds_a->x2 / pds_a->y2) / ((1 - pds->a) / pds_a->y1 + pds->a / pds_a->y2);
		if (pds->x > 0)
			pds->x = (pds->x - (int)pds->x) * pds_a->bars->w;
		else
			pds->x = (pds->x - (int) pds->x + 1) * pds_a->bars->w;
		pds->a = (double) (pds->k - (int) pds->yt_wall) /
		((int)pds->yb_wall - (int)pds->yt_wall);
		pds->y = -((1 - pds->a) * pds_a->ceil + pds->a * pds_a->floor);
		if (pds->y > 0)
			pds->y = (pds->y - (int)pds->y) * pds_a->bars->h;
		else
			pds->y = (pds->y - (int)pds->y + 1) * pds_a->bars->h;
		if (pds->x >= 0 && pds->x < pds_a->bars->w &&
			pds->y >= 0 && pds->y < pds_a->bars->h) {
			pds->color = (pds_a->bars->pixels)[(int)pds->y * pds_a->bars->w + (int)pds->x];
			if (pds->color != 0)
				((int *) pds_a->game->screen->pixels)
				[pds->k * pds_a->game->screen->w + pds->i] = ft_bright(pds->color, pds_a->bright);
		}
	}
}

static void check_window(t_pds_a *pds_a, t_pds *pds)
{
	if (pds->k < pds->yt_window || pds->k > pds->yb_window)
	{
		pds->a = (double)(pds->k - (int)pds->yt_wall) /
		((int)pds->yb_wall - (int)pds->yt_wall);
		pds->y = -((1 - pds->a) * pds_a->ceil + pds->a * pds_a->floor);
		if (pds->y > 0)
			pds->y = (pds->y - (int)pds->y) * pds_a->game->texture->h;
		else
			pds->y = (pds->y - (int)pds->y + 1) * pds_a->game->texture->h;
		if (pds->x >= 0 && pds->x < pds_a->game->texture->w &&
			pds->y >= 0 && pds->y < pds_a->game->texture->h)
		{
			pds->color = (pds_a->game->texture->pixels)
			[(int)pds->y * pds_a->game->texture->w + (int)pds->x];
			((int*)pds_a->game->screen->pixels)
			[pds->k * pds_a->game->screen->w + pds->i] = ft_bright(pds->color, pds_a->bright);
		}
		((int*)pds_a->screen->pixels)
		[pds->k * pds_a->screen->w + pds->i] = ft_bright(pds->color, pds_a->bright);
	}
}

void pre_draw_sec_loop(t_pds_a *pds_a, t_pds *pds)
{
	while (pds->i < pds_a->for_draw.wall.x2 && pds->i < pds_a->screen->w)
	{
		init(pds_a, pds);
		while (pds->k < pds->yb_wall && pds->k < pds_a->screen->h)
		{
			if (pds->k < pds->yt_window || pds->k > pds->yb_window)
				check_window(pds_a, pds);
			else
				check_grid(pds_a, pds);
			pds->k++;
		}
		pds->i++;
	}
}