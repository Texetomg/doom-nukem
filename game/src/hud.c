/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 16:38:34 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/04/02 21:21:50 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

void draw_player_icon(SDL_Surface *screen, SDL_Surface *face)
{
	int		x = 0;
	int		y = 0;
	int		new_x = 0;
	int		new_y = 0;
	int		color;

	while (y < screen->h / 5 )
	{
		new_y = (double)y / (screen->h / 5  ) * face->h;
		while (x < screen->w / 5  )
		{
			new_x = (double)x / (screen->w / 5 ) * face->w;
			color = ((int*)(face->pixels))[new_y * face->w + new_x];
			if (color != 0x000000)
				((int*)(screen->pixels))[(int)(y + screen->h - screen->h / 5) * screen->w + x ] = color;
			x++;
		}
		x = 0;
		y++;
	}
}