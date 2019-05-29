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

void draw_img(SDL_Surface *screen, SDL_Surface *img, vec2 start, vec2 end){
	int		new_x;
	int		new_y;
	int		color;
	int		x;
	int		y;
	
	x = start.x;
	while (x < end.x)
	{
		y = start.y;
		new_x = (x - start.x) / (end.x - start.x) * img->w;
		while (y < end.y)
		{
			new_y = (y - start.y) / (end.y - start.y) * img->h;
			color = ((int*)(img->pixels))[new_y * img->w + new_x];
			if (color != 0x000000 && x >= 0 && y >=0 && x < screen->w && y < screen->h)
				((int*)(screen->pixels))[y * screen->w + x] = color;
			y++;
		}
		y = 0;
		x++;
	}
}

void draw_full_screen_img(SDL_Surface *screen, SDL_Surface *image)
{
    vec2 start;
	vec2 end;

	start.x = 0;
	start.y = 0;
	end.x = screen->w;
	end.y = screen->h;
	draw_img(screen, image, start, end);
}