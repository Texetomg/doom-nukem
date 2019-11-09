/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 09:33:36 by ramory-l          #+#    #+#             */
/*   Updated: 2019/11/09 16:37:43 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static int	sprite_wall1(t_dw_a *dw_a, t_dw *dw)
{
	if (dw_a->sprite_wall == 0)
		return (1);
	if (dw_a->sprite_wall->left < dw_a->perc1)
	{
		dw->a = 0;
		dw->left_img = (dw_a->perc1 - dw_a->sprite_wall->left) /
		(dw_a->sprite_wall->right - dw_a->sprite_wall->left);
	}
	else
	{
		dw->a = (dw_a->sprite_wall->left - dw_a->perc1) /
		(dw_a->perc2 - dw_a->perc1);
		dw->left_img = 0;
	}
	return (0);
}

static void	sprite_wall2(t_dw_a *dw_a, t_dw *dw)
{
	sprite_wall2_sup(dw_a, dw, &dw->new_y1, &dw->left_border);
	if (dw_a->sprite_wall->right > dw_a->perc2)
	{
		dw->a = 1;
		dw->right_img = (dw_a->perc2 - dw_a->sprite_wall->left) /
		(dw_a->sprite_wall->right - dw_a->sprite_wall->left);
	}
	else
	{
		dw->a = (dw_a->sprite_wall->right - dw_a->perc1) /
		(dw_a->perc2 - dw_a->perc1);
		dw->right_img = 1;
	}
	sprite_wall2_sup(dw_a, dw, &dw->new_y2, &dw->right_border);
}

static void	sprite_wall3(t_game *game, t_dw_a *dw_a, t_dw *dw)
{
	sprite_wall3_sup(game, dw_a, dw);
	if (dw->x >= 0 && dw->x < dw_a->sprite_wall->texture->w &&
		dw->y >= 0 && dw->y < dw_a->sprite_wall->texture->h)
	{
		dw->green_flag = 1;
		game->sprite_wall = dw_a->sprite_wall;
	}
}

void		draw_wall(t_game *game, t_dw_a dw_a)
{
	t_dw	dw;

	dw.green_flag = 0;
	dw.i = (int)dw_a.for_draw.wall.x1;
	if (dw.i < 0)
		dw.i = 0;
	loop2(game, &dw, &dw_a);
	if (sprite_wall1(&dw_a, &dw))
		return ;
	sprite_wall2(&dw_a, &dw);
	sprite_wall3(game, &dw_a, &dw);
	if (dw.left_border < 0)
		dw.i = 0;
	else if (dw.left_border < dw_a.for_draw.wall.x1)
		dw.i = dw_a.for_draw.wall.x1;
	else
		dw.i = dw.left_border;
	loop3(game, &dw, &dw_a);
}
