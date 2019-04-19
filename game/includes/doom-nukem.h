/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom-nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:56:03 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/04/18 18:56:29 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H
# include "libft.h"
# include <math.h>
# include <SDL.h>
# include <SDL_mixer.h>
# include <sys/time.h>
# define HIGH 0.5
# define ACCEL 0.0005
# define COLOR_CEIL 0x87CEEB
# define COLOR_FLOOR 0x008080
# define COLOR_WALL 0xDA70D6
# define COLOR_BETW 0xAA0000
# define STEP 0.05

typedef struct		s_gif
{
	int				frame;
	int				curr_frame;
	SDL_Surface     **array;
}					t_gif;

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
	double			b_knees;
	double			b_foots;
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
	int				ctrl_flag;
	int				mouse_l;
}					t_keystate;

typedef	struct 		s_sounds
{
	Mix_Music		*music;
	Mix_Chunk		*bang;
}					t_sounds;

typedef struct 		s_sprites
{
	vec3			pos;
	int				sector;
	int				w;
	int				h;
	vec3			new_pos;
	double			shift;
}					t_sprites;


typedef struct		s_game
{
	t_sounds		sounds;
	t_player		player;
	t_sprites		sprites;
	vec2			*points;
	t_sector		*sectors;
	SDL_Window		*window;
	SDL_Surface		*screen;
	SDL_Surface		*texture;
	SDL_Surface		*texture_arr[3];
	SDL_DisplayMode	display_mode;
	struct timeval  time;
	vec2int			mouse;
	int				count_points;
	vec2   			*points_cam;
	int				count_sectors;
	t_keystate		keystate;	
	t_gif			gif[2];
}					t_game;

t_game  			*create_struct(void);
double				cross_product(vec2 first_point, vec2 second_point);
void    			draw_minimap(t_game *game);
int					put_fps(t_game *game);
void				read_map(char *name, t_game *game);
void				player_move(t_game *game, int *loop);
void				change_wall(t_wall *cam_wall);
void				get_pos_z(t_game *game);
SDL_Texture* 		load_image(char *file, SDL_Renderer *ren);
void        		apply_surface(int x, int y, SDL_Texture *tex, SDL_Renderer *ren);
void				clean_buffer(char **buffer);
void    			free_SDL(t_game *game);
#endif
