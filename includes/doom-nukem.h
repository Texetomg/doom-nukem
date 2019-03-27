/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom-nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:56:03 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/03/27 22:26:32 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H
# include "libft.h"
# include <math.h>
# include <SDL.h>
#include <sys/time.h>
# define SCREEN_WIDTH 1000
# define SCREEN_HEIGHT 500
# define MOUSE_POS_X display_mode.w / 4
# define MOUSE_POS_Y display_mode.h / 4

typedef	struct	s_mouse
{
	int			prev_x;
	int			prev_y;
	int			curr_x;
	int			curr_y;
}				t_mouse;


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

typedef struct	s_vec2int
{
	int			x;
	int			y;
}				vec2int;
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
	int			curr_sector;
}				t_player;
typedef struct	s_wall
{
	vec2		pos1;
	vec2		pos2;
	int			color;
}				t_wall;
typedef struct	s_sector
{
	vec2		*points;
	double		floor;
	double		ceil;
	int			*neighbors;
	int			count_wall;
}				t_sector;

typedef struct	s_game
{
	t_player	player;
	t_sector	*sectors;
	SDL_Window	*window;
	SDL_Surface	*screen;
	SDL_DisplayMode	display_mode;
	struct timeval  time;
	vec2int			mouse;
}				t_game;

t_game  *create_struct(void);
void    draw_minimap(t_game *game, t_wall *world_wall);
SDL_Texture*    load_image(char *file, SDL_Renderer *ren);
void            apply_surface(int x, int y, SDL_Texture *tex, SDL_Renderer *ren);
void			put_sdl_error(char *str);
int				put_fps(t_fps *fps);
#endif
