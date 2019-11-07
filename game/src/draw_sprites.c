/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramory-l <ramory-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 22:53:05 by ramory-l          #+#    #+#             */
/*   Updated: 2019/11/07 23:24:04 by ramory-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void	init(t_draw_sprites *draw_sprites, t_sprite *sprite,
t_game *game, t_draw *for_draw)
{
	draw_sprites->cross_flag = 0;
	draw_sprites->texture = check_sprite(sprite);
	draw_sprites->x_start = -sprite->pos_in_cam.y *
	game->pre_calc.screen_w_div_2 / sprite->pos_in_cam.x +
	game->pre_calc.screen_w_div_2 - sprite->width / 2 / sprite->pos_in_cam.x;
	draw_sprites->x_end = draw_sprites->x_start +
	sprite->width / sprite->pos_in_cam.x;
	draw_sprites->top = -sprite->pos_in_cam.z *
	game->pre_calc.screen_h_div_2 / sprite->pos_in_cam.x + game->line_horiz;
    draw_sprites->bot = draw_sprites->top + sprite->heigth *
	game->pre_calc.screen_h_div_2 / sprite->pos_in_cam.x;
	if (draw_sprites->x_start < 0)
		draw_sprites->x = 0;
	else if (draw_sprites->x_start < for_draw->window.x1)
		draw_sprites->x = for_draw->window.x1;
	else
		draw_sprites->x = draw_sprites->x_start;
	draw_sprites->cross_x = (double)(game->screen->w / 2 - draw_sprites->x_start) /
	(draw_sprites->x_end - draw_sprites->x_start) * draw_sprites->texture->w;
	draw_sprites->cross_y = (double)(game->screen->h / 2 - draw_sprites->top) /
	(draw_sprites->bot - draw_sprites->top) * draw_sprites->texture->h;
}

static void loop(t_game *game, t_draw_sprites *draw_sprites, double bright)
{
	while (draw_sprites->y < draw_sprites->bot &&
			draw_sprites->y < draw_sprites->b_window &&
			draw_sprites->y < game->screen->h)
	{
		draw_sprites->new_y = (double)(draw_sprites->y - draw_sprites->top) /
		(draw_sprites->bot - draw_sprites->top) * draw_sprites->texture->h;
		if (draw_sprites->new_y >= 0 &&
			draw_sprites->new_y < draw_sprites->texture->h &&
			draw_sprites->new_x >= 0 &&
			draw_sprites->new_x < draw_sprites->texture->w)
		{
			draw_sprites->color = ((int*)draw_sprites->texture->pixels)
			[draw_sprites->new_y * draw_sprites->texture->w +
			draw_sprites->new_x];
			if (draw_sprites->color != 0)
				((int*)game->screen->pixels)
				[draw_sprites->y * game->screen->w + draw_sprites->x] =
				ft_bright(draw_sprites->color, bright);
		}
		draw_sprites->y++;
	}
}

static void main_loop(t_game *game, t_draw_sprites *draw_sprites,
t_draw *for_draw, double bright)
{
	while (draw_sprites->x < draw_sprites->x_end &&
			draw_sprites->x < for_draw->window.x2 &&
			draw_sprites->x < game->screen->w)
	{
		draw_sprites->t_window = (int)(for_draw->window.y1t +
		(for_draw->window.y2t - for_draw->window.y1t) *
		((double)draw_sprites->x - for_draw->window.x1) /
		(for_draw->window.x2 - for_draw->window.x1));
		draw_sprites->b_window = (int)(for_draw->window.y1b +
		(for_draw->window.y2b - for_draw->window.y1b) *
		((double)draw_sprites->x - for_draw->window.x1) /
		(for_draw->window.x2 - for_draw->window.x1));
		draw_sprites->new_x = (double)(draw_sprites->x - draw_sprites->x_start) /
		(draw_sprites->x_end - draw_sprites->x_start) * draw_sprites->texture->w;
		if (draw_sprites->top < 0)
			draw_sprites->y = 0;
		else if (draw_sprites->top < draw_sprites->t_window)
			draw_sprites->y = draw_sprites->t_window;
		else
			draw_sprites->y = draw_sprites->top;
		loop(game, draw_sprites, bright);
		draw_sprites->x++;
	}
}

void		draw_sprites(t_game *game, t_draw for_draw, t_sprite *sprite, double bright)
{
	t_draw_sprites draw_sprites;

	init(&draw_sprites, sprite, game, &for_draw);
	if ((draw_sprites.cross_x > 0) &&
		(draw_sprites.cross_x < draw_sprites.texture->w) && (draw_sprites.cross_y > 0) &&
		(draw_sprites.cross_y < draw_sprites.texture->h))
	    if (((int*)draw_sprites.texture->pixels)[draw_sprites.cross_y *
			draw_sprites.texture->w + draw_sprites.cross_x])
        {
            draw_sprites.cross_flag = 1;
            game->cross_flag = sprite;
        }
	main_loop(game, &draw_sprites, &for_draw, bright);
}