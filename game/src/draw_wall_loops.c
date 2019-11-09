/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_loops.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 10:29:30 by ramory-l          #+#    #+#             */
/*   Updated: 2019/11/09 17:04:10 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void	loop1(t_game *game, t_dw *dw, t_dw_a *dw_a)
{
	while (dw->k < dw->yb_wall && dw->k < game->screen->h)
	{
		dw->a = (double)(dw->k - (int)dw->yt_wall) /
		((int)dw->yb_wall - (int)dw->yt_wall);
		dw->y = -((1 - dw->a) * dw_a->ceil + dw->a * dw_a->floor);
		if (dw->y > 0)
			dw->y = (dw->y - (int)dw->y) * game->texture->h;
		else
			dw->y = (dw->y - (int)dw->y + 1) * game->texture->h;
		if (dw->x >= 0 && dw->x < game->texture->w &&
			dw->y >= 0 && dw->y < game->texture->h)
		{
			dw->color = (game->texture->pixels)[(int)dw->y *
			game->texture->w + (int)dw->x];
			((int*)game->screen->pixels)[dw->k *
			game->screen->w + dw->i] = ft_bright(dw->color, dw_a->bright);
		}
		dw->k++;
	}
}

void		loop2(t_game *game, t_dw *dw, t_dw_a *dw_a)
{
	while (dw->i < dw_a->for_draw.wall.x2 && dw->i < game->screen->w)
	{
		dw->yt_wall = (int)(dw_a->for_draw.wall.y1t +
		(dw_a->for_draw.wall.y2t - dw_a->for_draw.wall.y1t) *
		(dw->i - dw_a->for_draw.wall.x1) /
		(dw_a->for_draw.wall.x2 - dw_a->for_draw.wall.x1));
		dw->yb_wall = (int)(dw_a->for_draw.wall.y1b +
		(dw_a->for_draw.wall.y2b - dw_a->for_draw.wall.y1b) *
		(dw->i - dw_a->for_draw.wall.x1) /
		(dw_a->for_draw.wall.x2 - dw_a->for_draw.wall.x1));
		if (dw->yt_wall < 0)
			dw->k = 0;
		else
			dw->k = dw->yt_wall;
		dw->a = (double)(dw->i - (int)dw_a->for_draw.wall.x1) /
		((int)dw_a->for_draw.wall.x2 - (int)dw_a->for_draw.wall.x1);
		dw->x = ((1 - dw->a) * dw_a->x1 / dw_a->y1 + dw->a *
		dw_a->x2 / dw_a->y2) / ((1 - dw->a) / dw_a->y1 + dw->a / dw_a->y2);
		if (dw->x > 0)
			dw->x = (dw->x - (int)dw->x) * game->texture->w;
		else
			dw->x = (dw->x - (int)dw->x + 1) * game->texture->w;
		loop1(game, dw, dw_a);
		dw->i++;
	}
}

static void	loop4(t_game *game, t_dw *dw, t_dw_a *dw_a)
{
	while (dw->k < dw->bot_border && dw->k < game->screen->h)
	{
		dw->y = ((double)dw->k - dw->top_border) /
		(dw->bot_border - dw->top_border) * dw_a->sprite_wall->texture->h;
		if (dw->x >= 0 && dw->x < dw_a->sprite_wall->texture->w &&
			dw->y >= 0 && dw->y < dw_a->sprite_wall->texture->h)
		{
			dw->color = ((int*)dw_a->sprite_wall->texture->pixels)
			[(int)dw->y * dw_a->sprite_wall->texture->w + (int)dw->x];
			((int*)game->screen->pixels)[dw->k * game->screen->w + dw->i] =
			ft_bright(dw->color, dw_a->bright);
		}
		dw->k++;
	}
}

void		loop3(t_game *game, t_dw *dw, t_dw_a *dw_a)
{
	while (dw->i < dw->right_border && dw->i <
			game->screen->w && dw->i < dw_a->for_draw.wall.x2)
	{
		dw->yt_wall = (int)(dw_a->for_draw.wall.y1t + (dw_a->for_draw.wall.y2t -
		dw_a->for_draw.wall.y1t) * (dw->i - dw_a->for_draw.wall.x1) /
		(dw_a->for_draw.wall.x2 - dw_a->for_draw.wall.x1));
		dw->yb_wall = (int)(dw_a->for_draw.wall.y1b + (dw_a->for_draw.wall.y2b -
		dw_a->for_draw.wall.y1b) * (dw->i - dw_a->for_draw.wall.x1) /
		(dw_a->for_draw.wall.x2 - dw_a->for_draw.wall.x1));
		dw->top_border = dw->yt_wall + (dw->yb_wall -
		dw->yt_wall) * dw_a->sprite_wall->top;
		dw->bot_border = dw->yt_wall + (dw->yb_wall -
		dw->yt_wall) * dw_a->sprite_wall->bot;
		dw->top_border < 0 ? dw->k = 0 : dw->top_border;
		dw->a = ((double)dw->i - dw->left_border) /
			(dw->right_border - dw->left_border);
		dw->x = (((1 - dw->a) * dw->left_img /
		dw->new_y1 + dw->a * dw->right_img / dw->new_y2) /
		((1 - dw->a) / dw->new_y1 + dw->a / dw->new_y2)) *
		dw_a->sprite_wall->texture->w;
		loop4(game, dw, dw_a);
		dw->i++;
	}
}
