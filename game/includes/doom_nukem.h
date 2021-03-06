/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramory-l <ramory-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:56:03 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/11/09 19:32:00 by ramory-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H
# include "my_doom.h"
# include "libft.h"
# include <math.h>
# include <SDL.h>
# include <SDL_mixer.h>
# include <SDL_ttf.h>
# include <SDL_image.h>
# include <sys/time.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <netdb.h>
# define SERVERIP "192.168.22.70"
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
# define next N
# define angle_sprite AS
# define t_angle_sprite TAS

typedef struct				s_gif
{
	int						frame;
	int						curr_frame;
	SDL_Surface				**array;
}							t_gif;

typedef	struct				s_vec2
{
	double					x;
	double					y;
}							t_vec2;

typedef struct				s_window
{
	double					x1;
	double					x2;
	double					y1b;
	double					y1t;
	double					y2b;
	double					y2t;
}							t_window;

typedef struct				s_draw
{
	t_window				window;
	int						last_sector;
	int						curr_sector;
	t_vec2					fov_left;
	t_vec2					fov_right;
	t_window				wall;
}							t_draw;

typedef struct				s_vec2int
{
	int						x;
	int						y;
}							t_vec2int;

typedef struct				s_img_size
{
	int						h;
	int						w;
}							t_img_size;

typedef struct				s_vec3
{
	double					x;
	double					y;
	double					z;
}							t_vec3;

typedef	struct				s_sprite_wall
{
	double					top;
	double					bot;
	double					right;
	double					left;
	SDL_Surface				*texture;
	struct s_sprite_wall	*next;
	int						wall;
}							t_sprite_wall;

typedef struct				s_player
{
	t_vec3					pos;
	int						jetpack;
	int						key;
	double					angle;
	int						curr_sector;
	double					z_accel;
	double					knees;
	double					foots;
	double					b_knees;
	double					b_foots;
}							t_player;

typedef struct				s_wall
{
	t_vec2					pos1;
	t_vec2					pos2;
	int						color;
}							t_wall;

typedef struct				s_sector
{
	double					floor;
	double					ceil;
	int						*neighbors;
	int						*grid;
	int						*index_points;
	int						count_wall;
	double					brightness;
	t_sprite_wall			*sprite_wall;
}							t_sector;

typedef	struct				s_keystate
{
	int						left;
	int						right;
	int						forward;
	int						back;
	int						jump;
	int						ctrl;
	int						ctrl_flag;
	int						mouse_l;
}							t_keystate;

typedef	struct				s_sounds
{
	Mix_Music				*music;
	Mix_Chunk				*bang;
	Mix_Chunk				*bang1;
	Mix_Chunk				*step;
}							t_sounds;

typedef struct				s_angle_sprite
{
	double					start_angle;
	double					end_angle;
	double					up_health;
	double					down_health;
	SDL_Surface				*texture;
	SDL_Surface				*texture2;
	struct s_angle_sprite	*next;
}							t_angle_sprite;

typedef struct				s_sprite
{
	int						id;
	t_vec3					pos;
	int						sector;
	double					heigth;
	double					width;
	t_vec3					pos_in_cam;
	double					angle;
	double					angle_in_cam;
	t_angle_sprite			*angle_sprite;
	int						health;
	int						move;
	struct s_sprite			*next;
}							t_sprite;

typedef	struct				s_hud
{
	SDL_Color				color;
	SDL_Rect				fps_dest;
	SDL_Surface				*face[3];
	SDL_Surface				*aim;
	SDL_Surface				*hp_bar;
	SDL_Surface				*jetpack;
	SDL_Surface				*key;
	SDL_Rect				text_dest;
}							t_hud;

typedef	struct				s_menu
{
	SDL_Surface				*image[6];
	char					*strings[6];
	Mix_Music				*music;
	Mix_Chunk				*clap[5];
	int						text_pos;
	SDL_Color				text_color;
	SDL_Rect				dest;
}							t_menu;

typedef struct				s_menu_status
{
	int						start;
	int						tab;
	int						main;
	int						multi;
}							t_menu_status;

typedef struct				s_pre_calc
{

	int						screen_h_div_2;
	int						screen_w_div_2;
	int						screen_h_div_10;
	int						screen_w_div_10;
	int						screen_h_div_20;
	int						screen_w_div_20;
	int						screen_h_mult_2;
	double					pi_mult_2;
	double					pi_div_4;
}							t_pre_calc;

typedef struct				s_for_udp
{
	t_vec3					pos;
	int						sector;
	double					angle;
	int						sound;
}							t_for_udp;

typedef struct				s_socket
{
	int						sockfd;
	int						numbytes;
}							t_socket;

typedef struct				s_game
{
	t_pre_calc				pre_calc;
	t_hud					hud;
	t_sounds				sounds;
	t_player				player;
	t_sprite				*sprites;
	t_vec2					*points;
	t_sector				*sectors;
	SDL_Window				*window;
	SDL_Surface				*screen;
	t_texture				*texture;
	t_texture				*texture1;
	SDL_Surface				*texture_arr[3];
	t_menu					start_menu;
	t_menu					tab_menu;
	t_menu					multi_menu;
	t_menu_status			menu_status;
	SDL_DisplayMode			display_mode;
	struct timeval			time;
	t_vec2int				mouse;
	int						count_points;
	t_vec2					*points_cam;
	int						count_sectors;
	t_keystate				keystate;
	t_gif					gif[2];
	int						complexity;
	int						line_horiz;
	SDL_Surface				*skybox;
	int						rifle_state;
	int						rifle_angle;
	t_socket				socket_struct;
	t_for_udp				for_udp;
	t_sprite				*cross_flag;
	t_sprite_wall			*sprite_wall;
	t_vec2					spaw1;
	t_vec2					spaw2;
	t_vec2					spaw3;
	char					*server_ip;
}							t_game;

typedef struct				s_draw_sprites
{
	int						y;
	int						x;
	int						x_start;
	int						x_end;
	int						new_x;
	int						new_y;
	int						color;
	int						bot;
	int						top;
	int						t_window;
	int						b_window;
	SDL_Surface				*texture;
	int						cross_flag;
	int						cross_x;
	int						cross_y;
}							t_draw_sprites;

typedef struct				s_draw_skybox
{
	double					left_border;
	double					right_border;
	double					a;
	int						x;
	int						y;
	int						x_texture;
	int						y_texture;
	int						color;
	double					top;
	double					bot;
}							t_draw_skybox;

typedef struct				s_dw_a
{
	t_draw					for_draw;
	double					x1;
	double					x2;
	double					y1;
	double					y2;
	double					ceil;
	double					floor;
	double					bright;
	double					perc1;
	double					perc2;
	t_sprite_wall			*sprite_wall;
}							t_dw_a;

typedef struct				s_dw
{
	int						i;
	int						k;
	int						yb_wall;
	int						yt_wall;
	int						color;
	double					x;
	double					y;
	double					a;
	int						right_border;
	int						top_border;
	int						bot_border;
	int						left_border;
	double					new_y1, new_y2;
	double					left_img;
	double					right_img;
	int						green_flag;
}							t_dw;

typedef struct				s_pds_a
{
	SDL_Surface				*screen;
	SDL_DisplayMode			display_mode;
	t_draw					for_draw;
	double					bright;
	int						grid;
	t_game					*game;
	double					x1;
	double					x2;
	double					y1;
	double					y2;
	double					ceil;
	double					floor;
	t_texture				*bars;
}							t_pds_a;

typedef struct				s_pds
{
	int						i;
	int						k;
	double					yb_wall;
	double					yt_wall;
	double					yb_window;
	double					yt_window;
	int						color;
	double					wall_max_x;
	double					x_start;
	double					dx_left;
	double					dx_right;
	double					x;
	double					y;
	double					a;
}							t_pds;

typedef struct				s_ds
{
	int						i;
	t_draw					for_next_draw;
	t_vec2					first_point;
	t_vec2					second_point;
	double					yscale1;
	double					yscale2;
	double					yceil;
	double					yfloor;
	double					y2ceil;
	double					y2floor;
	double					x1;
	double					x2;
	double					x1a;
	double					x2a;
	double					y1;
	double					y2;
	double					y1a;
	double					y2a;
	double					x1_b4;
	double					x2_b4;
	double					perc1;
	double					perc2;
	t_sprite				*sprite;
}							t_ds;

typedef struct				s_inter
{
	t_ds					*ds;
	t_dw_a					*dw_a;
	t_game					*game;
	t_pds_a					*pds_a;
	t_draw					*for_draw;
}							t_inter;

typedef struct				s_sc
{
	int						i;
	int						j;
	t_vec2					f_point;
	t_vec2					s_point;
	t_sector 				*cur_sec;
	double 					cross;
}							t_sc;

typedef struct				s_sm
{
	t_sprite				*sprite;
	t_sprite				*index;
	t_sprite				*start_sprite;
	double					dx;
	double					dy;
	double					px;
	double					py;
	double					cx;
	double					cy;
	double					new_x;
	double					new_y;
	double					radius;
}							t_sm;

void						draw_floor(t_game *game, t_draw for_draw, double dz,
		double bright);
double						fractial_part(double a);
void						draw_ceil(t_game *game, t_draw for_draw, double dz,
								double bright);
void						play_sound(t_game *game, t_vec3 position,
								int flag_sound, int flag);
int							ft_bright(int color, double bright);
void						draw_sprites(t_game *game, t_draw for_draw,
								t_sprite *sprite, double bright);
void						give_sprites_cam(t_game *game);
void						start_menu_render(t_game *game, int *loop);
void						tab_menu_render(t_game *game, int *loop);
t_game						*create_struct(void);
double						cross_product(t_vec2 first_point,
								t_vec2 second_point);
void						draw_minimap(t_game *game);
void						put_fps(SDL_Surface *screen, t_hud hud,
								struct timeval *time);
void						read_map(char *name, t_game *game);
void						player_hooks(t_game *game, int *loop);
void						change_wall(t_wall *cam_wall);
void						get_pos_z(t_player *player, t_sector *sectors);
SDL_Texture					*load_image(char *file, SDL_Renderer *ren);
void						apply_surface(int x, int y, SDL_Texture *tex,
								SDL_Renderer *ren);
void						clean_buffer(char **buffer);
void						free_sdl(t_game *game);
void						print_text(SDL_Surface *screen, char *text,
								SDL_Color color, SDL_Rect dest);
void						set_color(SDL_Color *color, int r, int g, int b);
void						draw_sector(t_game *game, t_draw for_draw);
t_vec3						get_ceil(t_game *game, int x, int y, double dz);
t_vec3						get_floor(t_game *game, int x, int y, double dz);
void						cross(t_vec2 *first_point, t_vec2 second_point,
								t_vec2 fov);
int							intersection(t_vec2 *first_point,
								t_vec2 *second_point, t_vec2 left_fov,
								t_vec2 right_fov);
void						give_points_cam(t_vec2 *points_cam, t_vec2 *points,
								t_player *player, int count_points);
int							inside_sector(t_game *game, double x, double y,
								t_sector sector);
void						draw_img(SDL_Surface *screen, SDL_Surface *img,
								t_vec2 start, t_vec2 end);
void						draw_hud(t_game *game);
void						draw_full_screen_img(SDL_Surface *screen,
								SDL_Surface *image);
void						init_client(t_game *game, t_socket *socket_struct);
void						client(t_game *game);
void						print_custom_text(t_game *game, char *text);
void						multiplayer_menu_render(t_game *game, int *loop);
void						draw_player_icon(SDL_Surface *screen,
								SDL_Surface *img);
void						draw_aim(SDL_Surface *screen, SDL_Surface *img);
void						draw_hp_bar(SDL_Surface *screen, SDL_Surface *img);
void						draw_hands(SDL_Surface *screen, SDL_Surface *img);
void						draw_jetpack(SDL_Surface *screen, SDL_Surface *img);
void						menu_render(SDL_Surface *screen, t_menu *menu,
								SDL_Surface *image);
void						print_menu_text(SDL_Surface *screen, t_menu *menu,
								int string_count);
void						switch_menu(int *menu_on, int *menu_off);
void						set_player(t_game *game);
void						swap_vec2(t_vec2 *first, t_vec2 *second);
void						get_points(t_game *game, int curr_sector,
								t_vec2 *first_point,
								t_vec2 *second_point, int i);
int							count_wall(char **line);
void						fill_index_points(t_sector *sector, char **buffer);
void						malloc_sector_values(t_sector *sector);
int							count(int fd);
void						load_images(t_game *game);
void						get_first_point(t_game *game, int curr_sector,
								t_vec2 *first_point, int i);
void						get_second_point(t_game *game, int curr_sector,
								t_vec2 *second_point, int i);
void						swap_vec2(t_vec2 *first, t_vec2 *second);
void						player_positioning(t_game *game);
void						move(t_game *game, double x, double y);
void						sprites_move(t_game *game);
void						resp_mobe(t_game *game, t_sprite *sprite);
SDL_Event					key_hooks(t_game *game);
void						shoot_hook(t_game *game, SDL_Event e);
void						tab_hook(t_keystate *keystate,
								t_menu_status *menu_status, SDL_Event e);
void						ctrl_hook(t_keystate *keystate, t_player *player,
								t_sector *sectors);
void						jump_hook(t_game *game);
void						jetpack_hook(t_player *player, SDL_Event e);
void						appoint_points(t_game *game, t_vec2 *f_point,
								t_vec2 *s_point, int i);
void						player_position(t_game *game, double new_x,
								double new_y, int i);
void						count_points(t_vec2 *f_point, t_vec2 *s_point,
								double new_x, double new_y);
void						load_sounds(t_game *game);
void						set_initial_values(t_game *game);
void						add_angle_sprites_end(t_sprite **begin,
								t_angle_sprite sprite);
void						set_sprites(t_game *game);
void						texture_cut(t_texture *texture, unsigned int st_color,
							unsigned int end_color);
void						texture_cut_sdl(SDL_Surface *texture,
								unsigned int st_color, unsigned int end_color);
void						change_temp1(t_angle_sprite *temp);
void						change_temp2(t_angle_sprite *temp);
void						change_temp3(t_angle_sprite *temp);
void						change_temp4(t_angle_sprite *temp);
SDL_Surface					*check_sprite(t_sprite *sprite);
void						draw_sprites(t_game *game, t_draw for_draw,
								t_sprite *sprite, double bright);
void						draw_skybox(t_game *game);
void						draw_wall(t_game *game, t_dw_a dw_a);
void						loop2(t_game *game, t_dw *dw, t_dw_a *dw_a);
void						loop3(t_game *game, t_dw *dw, t_dw_a *dw_a);
void						pre_draw_sector(t_pds_a *pds_a);
void						pre_draw_sec_loop(t_pds_a *pds_a, t_pds *pds);
void						init_intersections(int i, t_inter *inter);
void						check_inter(t_inter *inter);
void						intersections(t_inter *inter);
void						sprite_wall2_sup(t_dw_a *dw_a, t_dw *dw,
								double *dw_new, int *dw_border);
void 						sprite_wall3_sup(t_game *game, t_dw_a *dw_a, t_dw *dw);
void						init1_sup(t_inter *inter);
int							sector_check(t_game *game, t_sprite *sprite);
#endif
