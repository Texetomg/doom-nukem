/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom-nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:56:03 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/03/26 17:36:33 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H
# include "libft.h"
# include <math.h>
# include <SDL.h>
# define SCREEN_WIDTH 1000
# define SCREEN_HEIGHT 500

typedef	struct	s_fps
{
	struct timeval	time;
	struct timeval	old_time;
}				t_fps;

typedef	struct	s_vec2
{
	double		x;
	double		y;
}				vec2;

typedef struct	s_vec3
{
	double		x;
	double		y;
	double		z;
}				vec3;

typedef struct	s_player
{
	vec3		pos;
	double		angle;
}				t_player;
typedef struct	s_wall
{
	vec2		pos1;
	vec2		pos2;
	int			color;
}				t_wall;

typedef struct	t_game
{
	t_player	player;
}				t_game;

SDL_Texture*    load_image(char *file, SDL_Renderer *ren);
void            apply_surface(int x, int y, SDL_Texture *tex, SDL_Renderer *ren);
void			put_sdl_error(char *str);
int				put_fps(t_fps *fps);
#endif
