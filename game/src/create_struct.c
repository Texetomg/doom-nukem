/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 20:10:38 by thorker           #+#    #+#             */
/*   Updated: 2019/04/23 16:56:34 by thorker          ###   ########.fr       */
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
		*(gif[index].array + k) = IMG_Load(path);
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
//	game->menu.image = IMG_Load("imgs/destiny/normal.jpg");
}

static void load_sounds(t_game *game)
{
	if (!(game->menu.music = Mix_LoadMUS( "sounds/GACHI.mp3" )))
		check_error_n_exit(1,(char*)SDL_GetError());
	if (!(game->sounds.music = Mix_LoadMUS( "sounds/Sdc.mp3" )))
		check_error_n_exit(1,(char*)SDL_GetError());
	if (!(game->sounds.bang = Mix_LoadWAV( "sounds/gunshot.mp3" )))
		check_error_n_exit(1,(char*)SDL_GetError());
}

static void load_images(t_gif *gif)
{
	read_gif(gif, "imgs/gif1/", 0, 40, ".bmp");
	read_gif(gif, "imgs/hands/", 1, 3, ".png");
}

static void set_initial_values(t_game *game)
{
	game->player.pos.x = 0;
	game->player.pos.y = -3;
	game->player.z_accel = 0;
	game->player.angle = 3.14;
	game->points_cam = (vec2*)malloc(sizeof(vec2) * game->count_points);
	game->player.curr_sector = 1;
	game->player.foots = (game->sectors + game->player.curr_sector)->floor;
	game->player.knees = game->player.foots + 0.2;
	game->player.pos.z = game->player.foots + 0.5;
	game->keystate.back = 0;
	game->keystate.ctrl = 0;
	game->keystate.forward = 0;
	game->keystate.jump = 0;
	game->keystate.left = 0;
	game->keystate.right = 0;
	game->player.b_foots = 0.5;
	game->player.b_knees = 0.3;
	game->sprites.pos.x = 1;
	game->sprites.pos.y = -2;
	game->sprites.pos.z = 0;
	game->sprites.sector = 1;
	set_color(&game->hud.color, 255, 255, 0);
	game->hud.fps_dest.h = 80;
	game->hud.fps_dest.w = 120;
	game->hud.fps_dest.x = 0;
	game->hud.fps_dest.y = 0;
	game->menu.status = 1;
	game->menu.strings[0] = "Loli";
	game->menu.strings[1] = "Trump";
	game->menu.strings[2] = "Doomguy";
	game->menu.text_pos = 0;
}

/* static void load_images()	*/
t_game	*create_struct(void)
{
	t_game	*game;
	
	if ((game = (t_game*)malloc(sizeof(t_game))) == 0)
		check_error_n_exit(1,"malloc error");
	init_sdl(game);
	gettimeofday(&game->time, NULL);
	read_map("src/map2", game);
	load_sounds(game);
	load_images(game->gif);
	set_initial_values(game);
	
	return (game);
}
