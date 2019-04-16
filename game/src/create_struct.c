/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 20:10:38 by thorker           #+#    #+#             */
/*   Updated: 2019/04/16 16:45:38 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

static void read_gif(t_game *game)
{
	char *folder;
	char *i;
	char *extension;
	char *path;
	char *tmp;
	int k;

	folder = ft_strdup("imgs/gif1/");
	extension = ft_strdup(".bmp");
	path = ft_strnew(20);
	game->gif.frame = 40;
	game->gif.curr_frame = 0;
	game->gif.array = (SDL_Surface**)malloc(sizeof(SDL_Surface*) * game->gif.frame);
	k = 0;
	while (k < game->gif.frame)
	{
		i = ft_itoa(k);
		tmp = ft_strjoin(folder,i);
		path = ft_strjoin(tmp, extension);
		*(game->gif.array + k) = SDL_LoadBMP(path);
		ft_putendl(path);
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
	game->texture_arr[0] = SDL_LoadBMP("imgs/hand_1.bmp");
	game->texture = SDL_LoadBMP("imgs/cat.bmp");
	read_gif(game);
}

t_game	*create_struct(void)
{
	t_game	*game;
	

	if ((game = (t_game*)malloc(sizeof(t_game))) == 0)
		check_error_n_exit(1,"malloc error");
	init_sdl(game);
	gettimeofday(&game->time, NULL);
	read_map("src/map2", game);
	game->player.pos.x = 0;
	game->player.pos.y = -3;
	game->player.z_accel = 0;
	game->player.angle = 0;
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
	return (game);
}
