/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 16:57:31 by thorker           #+#    #+#             */
/*   Updated: 2019/04/16 18:14:46 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

void    menu_render(t_game *game)
{
	int	x = 0;
	int	y = 0;
	int color;
	int new_x;
	int new_y;

	while (y < game->screen->h)
	{
		new_y = (double)y / game->screen->h * game->menu.image->h;
		x = 0;
		while (x < game->screen->w)
		{
			new_x = (double)x / game->screen->w * game->menu.image->w;
			color = ((int*)(game->menu.image->pixels))[new_y * game->menu.image->w + new_x];
			((int*)(game->screen->pixels))[y * game->screen->w + x] = color;
			x++;
		}
		y++;
	}
}
