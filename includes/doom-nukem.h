/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom-nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:56:03 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/03/26 15:58:43 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H
# include "libft.h"
# include <math.h>
# include <SDL.h>
# define SCREEN_WIDTH 1000
# define SCREEN_HEIGHT 500

typedef	struct	s_vec2
{
	double		x;
	double		y;
}				vec2;

typedef struct	s_wall
{
	vec2		point1;
	vec2		point2;
	int			color;
}				t_wall;

SDL_Texture*    load_image(char *file, SDL_Renderer *ren);
void            apply_surface(int x, int y, SDL_Texture *tex, SDL_Renderer *ren);
void			put_sdl_error(char *str);
#endif
