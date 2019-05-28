/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom-nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:56:03 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/05/28 18:52:30 by thorker          ###   ########.fr       */
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
/* server */
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <netdb.h>

# define SERVERIP "192.168.20.58"
# define SERVERPORT "9034" 
# define MAXLINE 1024 

# define HIGH 0.5
# define ACCEL 0.005
# define COLOR_CEIL 0x87CEEB
# define COLOR_FLOOR 0x008080
# define COLOR_WALL 0xDA70D6
# define COLOR_BETW 0xAA0000
# define STEP 0.05
# define STEP_SOUND 1
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

typedef	struct		s_sprite_wall
{
	double			top;
	double			bot;
	double			right;
	double			left;
	SDL_Surface     *texture;
	struct s_sprite_wall *next;
	int				wall;
}					t_sprite_wall;

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
	int				*grid;
	int				*index_points;
	int				count_wall;
	double			brightness;
	t_sprite_wall	*sprite_wall;
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
	Mix_Chunk       *bang1;
	Mix_Chunk		*step;
}					t_sounds;

typedef struct		s_angle_sprite
{
	double			start_angle;
	double			end_angle;
	SDL_Surface		*texture;
	struct s_angle_sprite *next;
}					t_angle_sprite;

typedef struct 		s_sprite
{
	int				id;
	vec3			pos;
	int				sector;
	double			heigth;
	double			width;
	vec3			pos_in_cam;
	double			angle;
	double			angle_in_cam;
	t_angle_sprite	*angle_sprite;
	struct s_sprite *next;
}					t_sprite;

typedef	struct 		s_hud
{
	SDL_Color		color;
	SDL_Rect		fps_dest;
	SDL_Surface		*face[3];
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

typedef struct 		s_pre_calc
{
	int screenw3;
	int screenw2;
	int screenh3;
	int screenw10045;
	int screenh10065;
	int spritesw2;
	int spritesh2;
	int dispmodh2;
	int dispmodw2;
	int dispmodw10;
	int dispmodh10;
	int dispmodw20;
	int dispmodh20; 
} 					t_pre_calc;

typedef struct		s_for_udp
{
	vec3			pos;
	int				sector;
	double			angle;
	int				sound;
}					t_for_udp;

typedef struct		s_game
{
	t_pre_calc		pre_calc;
	t_hud			hud;
	t_sounds		sounds;
	t_player		player;
	t_sprite		*sprites;
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
	int				line_horiz;
	SDL_Surface     *skybox;
	SDL_Surface     *aim;
	int				rifle_state;
	int				rifle_angle;
	t_for_udp		for_udp;
}					t_game;

void				play_sound(t_game *game, vec3 position, int flag_sound, int flag);
int					ft_bright(int color, double bright);
void        		draw_sprites(t_game *game, t_draw for_draw, t_sprite sprite, double bright);
void           		give_sprites_cam(t_game *game);
void    			start_menu_render(t_game *game, int *loop);
void    			tab_menu_render(t_game *game, int *loop);
t_game  			*create_struct(void);
double   			cross_product(vec2 first_point, vec2 second_point);
void				draw_minimap(t_game *game);
void    			put_fps(SDL_Surface *screen, t_hud hud, struct timeval *time);
void				read_map(char *name, t_game *game);
void				player_move(t_game *game, int *loop);
void				change_wall(t_wall *cam_wall);
void    			get_pos_z(t_player *player, t_sector *sectors );
SDL_Texture* 		load_image(char *file, SDL_Renderer *ren);
void        		apply_surface(int x, int y, SDL_Texture *tex, SDL_Renderer *ren);
void				clean_buffer(char **buffer);
void    			free_SDL(t_game *game);
void    			print_text(SDL_Surface *screen, char *text, char *font, int size, SDL_Color color, SDL_Rect dest);
void				set_color(SDL_Color *color, int r, int g, int b);
void    			draw_sector(t_game *game, t_draw for_draw);
vec3    			get_ceil(t_game *game, int x, int y, double dz);
vec3    			get_floor(t_game *game, int x, int y, double dz);
void     			cross(vec2 *first_point, vec2 second_point, vec2 fov);
int             	intersection(vec2 *first_point, vec2 *second_point, vec2 left_fov, vec2 right_fov);
void           		give_points_cam(vec2 *points_cam, vec2 *points, t_player *player, int count_points);
int             	inside_sector(t_game *game, double x, double y, t_sector sector);
void				draw_image(t_game *game, int i, SDL_Surface *image[]);
void 				draw_player_icon(SDL_Surface *screen, SDL_Surface *face);
int					talker();
#endif
