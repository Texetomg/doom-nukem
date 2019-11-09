/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 16:23:33 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/11/09 16:37:37 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	sprite_wall2_sup(t_dw_a *dw_a, t_dw *dw, double *dw_new,
	int *dw_border)
{
	dw->x = ((1 - dw->a) * dw_a->x1 + dw->a * dw_a->x2);
	dw->a = (dw->x / dw_a->y1 - dw_a->x1 / dw_a->y1) / (dw_a->x2 /
	dw_a->y2 - dw->x / dw_a->y2 + dw->x / dw_a->y1 - dw_a->x1 / dw_a->y1);
	*dw_new = 1 / ((1 - dw->a) / dw_a->y1 + dw->a / dw_a->y2);
	*dw_border = dw_a->for_draw.wall.x1 +
	(dw_a->for_draw.wall.x2 - dw_a->for_draw.wall.x1) * dw->a;
}

void	sprite_wall3_sup(t_game *game, t_dw_a *dw_a, t_dw *dw)
{
	double	some;
	int		some2;

	some = (dw->i - dw_a->for_draw.wall.x1) /
	(dw_a->for_draw.wall.x2 - dw_a->for_draw.wall.x1);
	some2 = dw->yt_wall + (dw->yb_wall - dw->yt_wall);
	dw->i = game->pre_calc.screen_w_div_2;
	dw->k = game->pre_calc.screen_h_div_2;
	dw->yt_wall = (int)(dw_a->for_draw.wall.y1t +
	(dw_a->for_draw.wall.y2t - dw_a->for_draw.wall.y1t) * some);
	dw->yb_wall = (int)(dw_a->for_draw.wall.y1b +
	(dw_a->for_draw.wall.y2b - dw_a->for_draw.wall.y1b) * some);
	dw->top_border = some2 * dw_a->sprite_wall->top;
	dw->bot_border = some2 * dw_a->sprite_wall->bot;
	dw->a = ((double)dw->i - dw->left_border) /
	(dw->right_border - dw->left_border);
	dw->x = (((1 - dw->a) * dw->left_img /
	dw->new_y1 + dw->a * dw->right_img / dw->new_y2)
	/ ((1 - dw->a) / dw->new_y1 + dw->a / dw->new_y2))
	* dw_a->sprite_wall->texture->w;
	dw->y = ((double)dw->k - dw->top_border) /
	(dw->bot_border - dw->top_border) * dw_a->sprite_wall->texture->h;
}
