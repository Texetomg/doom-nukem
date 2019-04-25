/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom-nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:56:03 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/04/25 13:29:38 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H
# include "libft.h"
# include <math.h>
# include <SDL.h>
# include <SDL_mixer.h>
# include <SDL_ttf.h>
# include <SDL_image.h>
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

typedef struct 		s_img_size
{
	int				h;
	int				w;
}					t_img_size;


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
	SDL_Surface 	*texture;
}					t_sprites;

typedef	struct 		s_hud
{
	SDL_Color		color;
	SDL_Rect		fps_dest;
}					t_hud;

typedef	struct 		s_menu
{
	SDL_Surface		*image[5];
	char			*strings[5];
	Mix_Music		*music;
	Mix_Chunk		*clap[4];
	int				text_pos;
	SDL_Color		text_color;
	SDL_Rect		dest;
}					t_menu;

typedef struct 		s_menu_status
{
	int				start;
	int				tab;
	int				main;
}					t_menu_status;


typedef struct		s_game
{
	t_hud			hud;
	t_sounds		sounds;
	t_player		player;
	t_sprites		sprites;
	vec2			*points;
	t_sector		*sectors;
	SDL_Window		*window;
	SDL_Surface		*screen;
	SDL_Surface		*texture;
	SDL_Surface		*texture_arr[3];
	t_menu			start_menu;
	t_menu			tab_menu;
	t_menu_status	menu_status;
	SDL_DisplayMode	display_mode;
	struct timeval  time;
	vec2int			mouse;
	int				count_points;
	vec2   			*points_cam;
	int				count_sectors;
	t_keystate		keystate;	
	t_gif			gif[2];
	int				complexity;
}					t_game;

void    			start_menu_render(t_game *game, int *loop);
void    			tab_menu_render(t_game *game, int *loop);
t_game  			*create_struct(void);
double   			cross_product(vec2 first_point, vec2 second_point);
void				draw_minimap(SDL_Surface *screen, SDL_DisplayMode display_mode, t_sector *sectors, vec2 *points_cam, int count_sectors);
void    			put_fps(SDL_Surface *screen, t_hud hud, struct timeval *time);
void				read_map(char *name, t_game *game);
void				player_move(t_game *game, SDL_DisplayMode display_mode, vec2int *mouse, SDL_Window *window, t_sounds sounds, t_gif *gif, t_keystate *keystate, vec2 *points, t_sector *sectors, t_player *player, int *loop, t_menu_status *menu_status);
void				change_wall(t_wall *cam_wall);
void    			get_pos_z(t_player *player, t_sector *sectors );
SDL_Texture* 		load_image(char *file, SDL_Renderer *ren);
void        		apply_surface(int x, int y, SDL_Texture *tex, SDL_Renderer *ren);
void				clean_buffer(char **buffer);
void    			free_SDL(t_game *game);
void    			print_text(SDL_Surface *screen, char *text, char *font, int size, SDL_Color color, SDL_Rect dest);
void				set_color(SDL_Color *color, int r, int g, int b);
void    			draw_sector(t_game *game, t_gif *gif, SDL_Surface *texture, SDL_Surface *screen,t_player *player, SDL_DisplayMode display_mode, t_sector *sectors, vec2 *points_cam, t_draw for_draw);
vec3    			get_ceil(t_game *game, int x, int y, double dz);
vec3    			get_floor(t_game *game, int x, int y, double dz);
void     			cross(vec2 *first_point, vec2 second_point, vec2 fov);
int             	intersection(vec2 *first_point, vec2 *second_point, vec2 left_fov, vec2 right_fov);
void           		give_points_cam(vec2 *points_cam, vec2 *points, t_player *player, int count_points);
int             inside_sector(t_game *game, double x, double y, t_sector sector);
#endif
