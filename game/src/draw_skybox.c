/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_skybox.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramory-l <ramory-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 23:24:46 by ramory-l          #+#    #+#             */
/*   Updated: 2019/11/07 23:33:30 by ramory-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void		init_skybox(t_game *game, t_draw_skybox *draw_skybox)
{
	draw_skybox->a = fmod(fabs(game->player.angle +
	game->pre_calc.pi_div_4), game->pre_calc.pi_mult_2);
	if (game->player.angle + game->pre_calc.pi_div_4 < 0)
		draw_skybox->left_border = draw_skybox->a / (game->pre_calc.pi_mult_2);
	else
		draw_skybox->left_border = (game->pre_calc.pi_mult_2 - draw_skybox->a) /
		(game->pre_calc.pi_mult_2);
	draw_skybox->a = fmod(fabs(game->player.angle -
	game->pre_calc.pi_div_4), game->pre_calc.pi_mult_2);
	if (game->player.angle - game->pre_calc.pi_div_4 < 0)
		draw_skybox->right_border = draw_skybox->a / (game->pre_calc.pi_mult_2);
	else
		draw_skybox->right_border = (game->pre_calc.pi_mult_2 - draw_skybox->a) /
		(game->pre_calc.pi_mult_2);
	if (draw_skybox->left_border > draw_skybox->right_border)
		draw_skybox->right_border = draw_skybox->right_border + 1;
	draw_skybox->x = 0;
	draw_skybox->bot = ((double)game->screen->h - game->line_horiz +
	game->pre_calc.screen_h_div_2 + game->pre_calc.screen_h_div_2) /
	(game->pre_calc.screen_h_mult_2);
	draw_skybox->top = ((double)game->screen->h - game->line_horiz -
	game->pre_calc.screen_h_div_2 + game->pre_calc.screen_h_div_2) /
	(game->pre_calc.screen_h_mult_2);
}

void			draw_skybox(t_game *game)
{
	t_draw_skybox draw_skybox;

	init_skybox(game, &draw_skybox);
	while (draw_skybox.x < game->screen->w)
	{
		draw_skybox.a = draw_skybox.left_border +
		(draw_skybox.right_border - draw_skybox.left_border) *
		((double)draw_skybox.x / game->screen->w);
		draw_skybox.x_texture = (draw_skybox.a -
		(int)draw_skybox.a) * game->skybox->w;
		draw_skybox.y = 0;
		while (draw_skybox.y < game->screen->h)
		{
			draw_skybox.y_texture = (draw_skybox.top +
			(draw_skybox.bot - draw_skybox.top) * ((double)draw_skybox.y /
			game->screen->h)) * game->skybox->h;
			draw_skybox.color = ((int*)game->skybox->pixels)
			[draw_skybox.y_texture * game->skybox->w + draw_skybox.x_texture];
			((int*)game->screen->pixels)[draw_skybox.y *
			game->screen->w + draw_skybox.x] = draw_skybox.color;
			draw_skybox.y++;
		}
		draw_skybox.x++;
	}
}