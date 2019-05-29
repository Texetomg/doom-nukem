/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 20:10:38 by thorker           #+#    #+#             */
/*   Updated: 2019/05/28 18:54:29 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

static void read_gif(t_gif *gif, char *str, int index, int frame, char* extension)
{
	char *folder;
	char *i;
	char *path;
	char *tmp;
	int k;

	folder = ft_strdup(str);
	gif[index].frame = frame;
	gif[index].curr_frame = 0;
	gif[index].array = (SDL_Surface**)malloc(sizeof(SDL_Surface*) * gif[index].frame);
	k = 0;
	while (k < gif[index].frame)
	{
		i = ft_itoa(k);
		tmp = ft_strjoin(folder,i);
		path = ft_strjoin(tmp, extension);
		if (!(*(gif[index].array + k) = IMG_Load(path)))
			check_error_n_exit(1,(char*)SDL_GetError());
		free(path);
		free(tmp);
		free(i);
		k++;
	}
	free(folder);
}

//инициализация sdl
static void	init_sdl(t_game *game)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		check_error_n_exit(1,(char*)SDL_GetError());//закрывать sdl:	
	if (SDL_ShowCursor(SDL_DISABLE) < 0)
		check_error_n_exit(1,(char*)SDL_GetError());
	if ((SDL_GetDesktopDisplayMode(0, &game->display_mode)) != 0)
		check_error_n_exit(1,(char*)SDL_GetError());
	game->window = SDL_CreateWindow(0, 0, 0, 0, 0,
			SDL_WINDOW_FULLSCREEN_DESKTOP);
	if (game->window == 0)
		check_error_n_exit(1,(char*)SDL_GetError());
	if ((game->screen = SDL_GetWindowSurface(game->window)) == 0)
		check_error_n_exit(1,(char*)SDL_GetError());
	if (TTF_Init() < 0)
		check_error_n_exit(1,(char*)SDL_GetError());
	if (Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0) {
        check_error_n_exit(1,(char*)SDL_GetError());
    }
	game->texture = SDL_LoadBMP("imgs/cat.bmp");
}

static void set_player(t_game *game)
{
	game->player.curr_sector = 1;
	game->player.pos.x = 0;
	game->player.pos.y = -3;
	game->player.z_accel = 0;
	game->player.angle = 3.14;
	game->player.foots = (game->sectors + game->player.curr_sector)->floor;
	game->player.knees = game->player.foots + 0.2;
	game->player.pos.z = game->player.foots + 0.5;
	game->player.b_foots = 0.5;
	game->player.b_knees = 0.3;
}

static void set_keystate(t_game *game)
{
	game->keystate.back = 0;
	game->keystate.ctrl = 0;
	game->keystate.forward = 0;
	game->keystate.jump = 0;
	game->keystate.left = 0;
	game->keystate.right = 0;
}

static void set_menu(t_game *game)
{
	game->start_menu.strings[0] = "CHOOSE YOUR DESTINY:";
	game->start_menu.strings[1] = "Loli";
	game->start_menu.strings[2] = "Trump";
	game->start_menu.strings[3] = "Doomguy";
	game->start_menu.strings[4] = "Exit";
	game->start_menu.text_pos = 0;
	game->tab_menu.strings[0] = "Continue";
	game->tab_menu.strings[1] = "New game";
	game->tab_menu.strings[2] = "Exit";
	game->menu_status.start = 1;
	game->menu_status.tab = 0;
	game->menu_status.main = 0;
}

static void	set_sprites(t_game *game)
{
	game->sprites = (t_sprite*)malloc(sizeof(t_sprite));
	(game->sprites)->pos.x = 0;
	(game->sprites)->pos.y = 0;
	(game->sprites)->heigth = 0.5;
	(game->sprites)->width = game->display_mode.w / 10;
	(game->sprites)->pos.z = 0.6;
	(game->sprites)->sector = 0;
	(game->sprites)->angle = 0;
	(game->sprites)->angle_sprite = (t_angle_sprite*)malloc(sizeof(t_angle_sprite));
	(game->sprites)->angle_sprite->start_angle = 0;
	(game->sprites)->angle_sprite->end_angle = 3.14 / 4;
	(game->sprites)->angle_sprite->texture = IMG_Load("imgs/doomguy_forward.png");
	(game->sprites)->angle_sprite->next = (t_angle_sprite*)malloc(sizeof(t_angle_sprite));
	(game->sprites)->angle_sprite->next->start_angle = 3.14 / 4;
	(game->sprites)->angle_sprite->next->end_angle = 3.14 * 3 / 4;
	(game->sprites)->angle_sprite->next->next = (t_angle_sprite*)malloc(sizeof(t_angle_sprite));
	(game->sprites)->angle_sprite->next->texture = IMG_Load("imgs/doomguy_left.png");
	(game->sprites)->angle_sprite->next->next->start_angle = 3 * 3.14 / 4;
	(game->sprites)->angle_sprite->next->next->end_angle = 3.14 * 5 / 4;
	(game->sprites)->angle_sprite->next->next->next = (t_angle_sprite*)malloc(sizeof(t_angle_sprite));
	(game->sprites)->angle_sprite->next->next->texture = IMG_Load("imgs/doomguy_back.png");
	(game->sprites)->angle_sprite->next->next->next->start_angle = 5 * 3.14 / 4;
	(game->sprites)->angle_sprite->next->next->next->end_angle = 3.14 * 7 / 4;
	(game->sprites)->angle_sprite->next->next->next->next = (t_angle_sprite*)malloc(sizeof(t_angle_sprite));
	(game->sprites)->angle_sprite->next->next->next->texture = IMG_Load("imgs/doomguy_right.png");
	(game->sprites)->angle_sprite->next->next->next->next->start_angle = 7 * 3.14 / 4;
	(game->sprites)->angle_sprite->next->next->next->next->end_angle = 3.14 * 2;
	(game->sprites)->angle_sprite->next->next->next->next->next = 0;
	(game->sprites)->angle_sprite->next->next->next->next->texture = IMG_Load("imgs/doomguy_forward.png");
	game->sprites->next = (t_sprite*)malloc(sizeof(t_sprite));
	(game->sprites)->next->pos.x = 1;
	(game->sprites)->next->pos.y = -2;
	(game->sprites)->next->heigth = 0.5;
	(game->sprites)->next->width = game->display_mode.w / 10;
	(game->sprites)->next->pos.z = 0.5;
	(game->sprites)->next->sector = 1;
	(game->sprites)->next->angle = 3.14 / 2;
	(game->sprites)->next->angle_sprite = (t_angle_sprite*)malloc(sizeof(t_angle_sprite));
	(game->sprites)->next->angle_sprite->start_angle = -3.14;
	(game->sprites)->next->angle_sprite->end_angle = 3.14;
	(game->sprites)->next->angle_sprite->next = 0;
	(game->sprites)->next->angle_sprite->texture = *((game->gif)->array + 10);
	(game->sprites)->next->next = 0;
}

static void	set_hood(t_game *game)
{
	game->hud.fps_dest.h = 80;
	game->hud.fps_dest.w = 120;
	game->hud.fps_dest.x = 0;
	game->hud.fps_dest.y = 0;
}

static void load_sounds(t_game *game)
{
	if (!(game->start_menu.music = Mix_LoadMUS( "sounds/GACHI.mp3" )))
		check_error_n_exit(1,(char*)SDL_GetError());
	if (!(game->sounds.music = Mix_LoadMUS( "sounds/Sdc.mp3" )))
		check_error_n_exit(1,(char*)SDL_GetError());
	if (!(game->sounds.bang = Mix_LoadWAV( "sounds/quite_rifle.mp3" )))
		check_error_n_exit(1,(char*)SDL_GetError());
	if (!(game->sounds.bang1 = Mix_LoadWAV( "sounds/not_quite_rifle.mp3" )))
		check_error_n_exit(1,(char*)SDL_GetError());
	if (!(game->start_menu.clap[0] = Mix_LoadWAV( "sounds/loli.mp3" )))
		check_error_n_exit(1,(char*)SDL_GetError());
	if (!(game->start_menu.clap[1] = Mix_LoadWAV( "sounds/trump.mp3" )))
		check_error_n_exit(1,(char*)SDL_GetError());
	if (!(game->start_menu.clap[2] = Mix_LoadWAV( "sounds/doom.mp3" )))
		check_error_n_exit(1,(char*)SDL_GetError());
	if (!(game->start_menu.clap[3] = Mix_LoadWAV( "sounds/gay.mp3" )))
		check_error_n_exit(1,(char*)SDL_GetError());
	if (!(game->sounds.step = Mix_LoadWAV( "sounds/step.mp3" )))
		check_error_n_exit(1,(char*)SDL_GetError());
}

static void load_images(t_game *game)
{
	read_gif(game->gif, "imgs/gif1/", 0, 40, ".bmp");
	read_gif(game->gif, "imgs/rifle/", 1, 2, ".png");
	if (!(game->start_menu.image[0] = IMG_Load("imgs/start_menu/0.jpg")))
		check_error_n_exit(1,(char*)SDL_GetError());
	if (!(game->start_menu.image[1] = IMG_Load("imgs/start_menu/1.jpg")))
		check_error_n_exit(1,(char*)SDL_GetError());
	if (!(game->start_menu.image[2] = IMG_Load("imgs/start_menu/2.jpg")))
		check_error_n_exit(1,(char*)SDL_GetError());
	if (!(game->start_menu.image[3] = IMG_Load("imgs/start_menu/3.jpg")))
		check_error_n_exit(1,(char*)SDL_GetError());
	if (!(game->start_menu.image[4] = IMG_Load("imgs/start_menu/4.jpg")))
		check_error_n_exit(1,(char*)SDL_GetError());
	if (!(game->tab_menu.image[0] = IMG_Load("imgs/tab_menu/1.png")))
		check_error_n_exit(1,(char*)SDL_GetError());
	if (!(game->hud.face[2] = IMG_Load("imgs/hud/doom.png")))
		check_error_n_exit(1,(char*)SDL_GetError());
	if (!(game->skybox = IMG_Load("imgs/sky.jpg")))
		check_error_n_exit(1,(char*)SDL_GetError());
	if (!(game->hud.aim = IMG_Load("imgs/cross_aim.png")))
		check_error_n_exit(1,(char*)SDL_GetError());
	if (!(game->hud.hp_bar = IMG_Load("imgs/hud/hp_bar.png")))
		check_error_n_exit(1,(char*)SDL_GetError());
}

static void set_initial_values(t_game *game)
{
	set_player(game);
	set_keystate(game);
	set_menu(game);
	set_sprites(game);
	game->points_cam = (vec2*)malloc(sizeof(vec2) * game->count_points);
	set_color(&game->hud.color, 255, 255, 0);
	set_hood(game);
	game->line_horiz = 400;
	game->pre_calc.screenw3 = game->screen->w / 3;
	game->pre_calc.screenw2 = game->screen->w / 2;
	game->pre_calc.screenh3 = game->screen->h / 3;
	game->pre_calc.screenw10045 = game->screen->w / 100 * 45;
	game->pre_calc.screenh10065 = game->screen->h / 100 * 65;
	game->pre_calc.dispmodh2 = game->display_mode.h / 2;
	game->pre_calc.dispmodw2 = game->display_mode.w / 2;
	game->pre_calc.dispmodw10 = game->display_mode.w / 10;
	game->pre_calc.dispmodh10 = game->display_mode.h / 10;
	game->pre_calc.dispmodw20 = game->display_mode.w / 20;
	game->pre_calc.dispmodh20 = game->display_mode.h / 20;
	game->rifle_state = 0;
	game->rifle_angle = game->player.angle;
}

void	add_sprites_wall(t_game *game)
{
	game->sectors->sprite_wall = (t_sprite_wall*)malloc(sizeof(t_sprite_wall));
	game->sectors->sprite_wall->top = 0.5;
	game->sectors->sprite_wall->bot = 0.9;
	game->sectors->sprite_wall->right = 0.87;
	game->sectors->sprite_wall->left = 0.3;
	game->sectors->sprite_wall->wall = 0;
	game->sectors->sprite_wall->texture = *((game->gif)->array + 30);
	game->sectors->sprite_wall->next = 0;
}

t_game	*create_struct(void)
{
	t_game	*game;
	
	if ((game = (t_game*)malloc(sizeof(t_game))) == 0)
		check_error_n_exit(1,"malloc error");
	init_sdl(game);
	gettimeofday(&game->time, NULL);
	read_map("src/map2", game);
	load_sounds(game);
	load_images(game);
	set_initial_values(game);
	add_sprites_wall(game);
	return (game);
}
