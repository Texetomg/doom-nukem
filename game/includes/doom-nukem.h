/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom-nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:56:03 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/04/02 17:35:08 by thorker          ###   ########.fr       */
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

typedef	struct		s_mouse
{
	int				prev_x;
	int				prev_y;
	int				curr_x;
	int				curr_y;
}					t_mouse;


typedef	struct		s_fps
{
	struct timeval	time;
	struct timeval	old_time;
}					t_fps;

typedef	struct		s_vec2
{
	double			x;
	double			y;
}					vec2;

typedef struct		s_vec2int
{
	int				x;
	int				y;
}					vec2int;
typedef struct		s_vec3
{
	double			x;
	double			y;
	double			z;
}					vec3;

typedef struct		s_player
{
	vec3			pos;
	double			angle;
	int				curr_sector;
}					t_player;
typedef struct		s_wall
{
	vec2			pos1;
	vec2			pos2;
	int				color;
}					t_wall;
typedef struct		s_sector
{
	double			floor;
	double			ceil;
	int				*neighbors;
	int				*index_points;
	int				count_wall;
}					t_sector;

typedef struct		s_game
{
	t_player		player;
	vec2			*points;
	t_sector		*sectors;
	SDL_Window		*window;
	SDL_Surface		*screen;
	SDL_DisplayMode	display_mode;
	struct timeval  time;
	vec2int			mouse;
	int				count_points;
	vec2   			*points_cam;
	int				count_sectors;
}					t_game;

t_game  			*create_struct(void);
void    			draw_minimap(t_game *game);
int					put_fps(t_fps *fps);
void				read_map(char *name, t_game *game);
void				player_move(t_game *game, int *loop);
void				change_wall(t_wall *cam_wall);
#endif
