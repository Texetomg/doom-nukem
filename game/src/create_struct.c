/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 20:10:38 by thorker           #+#    #+#             */
/*   Updated: 2019/04/18 18:57:01 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

static void read_gif(t_gif *gif, char *str, int index, int frame)
{
	char *folder;
	char *i;
	char *extension;
	char *path;
	char *tmp;
	int k;

	folder = ft_strdup(str);
	extension = ft_strdup(".bmp");
	gif[index].frame = frame;
	gif[index].curr_frame = 0;
	gif[index].array = (SDL_Surface**)malloc(sizeof(SDL_Surface*) * gif[index].frame);
	k = 0;
	while (k < gif[index].frame)
	{
		i = ft_itoa(k);
		tmp = ft_strjoin(folder,i);
		path = ft_strjoin(tmp, extension);
		*(gif[index].array + k) = SDL_LoadBMP(path);
		free(path);
		free(tmp);
		free(i);
		k++;
	}
	free(folder);
	free(extension);
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
	if (Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0) {
        check_error_n_exit(1,(char*)SDL_GetError());
    }
	game->texture = SDL_LoadBMP("imgs/cat.bmp");
}

static void load_sounds(t_sounds *sounds)
{
	if (!(sounds->music = Mix_LoadMUS( "sounds/Sdc.mp3" )))
		check_error_n_exit(1,(char*)SDL_GetError());
	if (!(sounds->bang = Mix_LoadWAV( "sounds/WOO.mp3" )))
		check_error_n_exit(1,(char*)SDL_GetError());
}

static void load_images(t_gif *gif)
{
	read_gif(gif, "imgs/gif1/", 0, 40);
	read_gif(gif, "imgs/gif_damage/", 1, 29);
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
	load_sounds(&game->sounds);
	load_images(game->gif);
	set_initial_values(game);
	Mix_PlayMusic( game->sounds.music, -1 );
	return (game);
}
