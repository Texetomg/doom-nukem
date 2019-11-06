/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_cut.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramory-l <ramory-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 11:04:04 by ramory-l          #+#    #+#             */
/*   Updated: 2019/11/06 11:04:09 by ramory-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	texture_cut(t_texture *texture, unsigned int st_color, unsigned int end_color)
{
	int				i;
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;

	i = 0;
	while (i < texture->w * texture->h)
	{
		red = texture->pixels[i] & 0xFF0000;
		green = texture->pixels[i] & 0xFF00;
		blue =  texture->pixels[i] & 0xFF;
		if (((red > (st_color & 0xFF0000)) && (red < (end_color & 0xFF0000)))
			&& ((green > (st_color & 0xFF00)) && (green < (end_color & 0xFF00)))
			&& ((blue > (st_color & 0xFF)) && (blue < (end_color & 0xFF))))
			texture->pixels[i] = 0;
		i++;
	}
}

void	texture_cut_sdl(SDL_Surface *texture, unsigned int st_color, unsigned int end_color)
{
    int				i;
    unsigned int	red;
    unsigned int	green;
    unsigned int	blue;
    unsigned int    *pixels;

    pixels = (unsigned int*)texture->pixels;
    i = 0;
    while (i < texture->w * texture->h)
    {
        red = pixels[i] & 0xFF0000;
        green = pixels[i] & 0xFF00;
        blue =  pixels[i] & 0xFF;
        if (((red > (st_color & 0xFF0000)) && (red < (end_color & 0xFF0000)))
			&& ((green > (st_color & 0xFF00)) && (green < (end_color & 0xFF00)))
			&& ((blue > (st_color & 0xFF)) && (blue < (end_color & 0xFF))))
            pixels[i] = 0;
        i++;
    }
}