/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 20:10:38 by thorker           #+#    #+#             */
/*   Updated: 2019/04/26 13:03:16 by thorker          ###   ########.fr       */
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
	game->sprites.texture = SDL_LoadBMP("imgs/cat.bmp");
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
	game->sprites.pos.x = 1;
	game->sprites.pos.y = -2;
	game->sprites.pos.z = 0;
	game->sprites.sector = 1;
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
	if (!(game->sounds.bang = Mix_LoadWAV( "sounds/gunshot.mp3" )))
		check_error_n_exit(1,(char*)SDL_GetError());
	if (!(game->start_menu.clap[0] = Mix_LoadWAV( "sounds/loli.mp3" )))
		check_error_n_exit(1,(char*)SDL_GetError());
	if (!(game->start_menu.clap[1] = Mix_LoadWAV( "sounds/trump.mp3" )))
		check_error_n_exit(1,(char*)SDL_GetError());
	if (!(game->start_menu.clap[2] = Mix_LoadWAV( "sounds/doom.mp3" )))
		check_error_n_exit(1,(char*)SDL_GetError());
	if (!(game->start_menu.clap[3] = Mix_LoadWAV( "sounds/gay.mp3" )))
		check_error_n_exit(1,(char*)SDL_GetError());
}

static void load_images(t_game *game)
{
	read_gif(game->gif, "imgs/gif1/", 0, 40, ".bmp");
	read_gif(game->gif, "imgs/hands/", 1, 3, ".png");
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
	return (game);
}
