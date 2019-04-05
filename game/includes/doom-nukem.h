/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom-nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:56:03 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/04/05 14:58:19 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H
# include "libft.h"
# include <math.h>
# include <SDL.h>
#include <sys/time.h>
# define HIGH 0.5
# define ACCEL 0.0005
# define COLOR_CEIL 0x87CEEB
# define COLOR_FLOOR 0x008080
# define COLOR_WALL 0xDA70D6
# define COLOR_BETW 0xAA0000
# define STEP 0.05

typedef	struct		s_vec2
{
	double			x;
	double			y;
}					vec2;
typedef struct		s_window
{
	double          x1;
	double          x2;
	double          y1b;
	double          y1t;
	double          y2b;
	double          y2t;
}					t_window;
typedef struct		s_draw
{
	t_window		window;
	int				last_sector;
	int				curr_sector;
	vec2			fov_left;
	vec2			fov_right;
	t_window		wall;
}					t_draw;

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
	double			z_accel;
	double			knees;
	double			foots;
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

typedef	struct 		s_keystate
{
	int				left;
	int				right;
	int				forward;
	int				back;
	int				jump;
	int				ctrl;
}					t_keystate;

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
	t_keystate		keystate;
	
}					t_game;

t_game  			*create_struct(void);
double				cross_product(vec2 first_point, vec2 second_point);
void    			draw_minimap(t_game *game);
int					put_fps(t_game *game);
void				read_map(char *name, t_game *game);
void				player_move(t_game *game, int *loop);
void				change_wall(t_wall *cam_wall);
void				get_pos_z(t_game *game);
#endif
