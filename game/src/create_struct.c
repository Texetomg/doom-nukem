/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 20:10:38 by thorker           #+#    #+#             */
/*   Updated: 2019/03/29 20:07:22 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"
//инициализация sdl
void	init_sdl(t_game *game)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		check_error_n_exit(1,(char*)SDL_GetError());
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
}
//создание главной структуры
t_game	*create_struct(void)
{
	t_game	*game;

	if ((game = (t_game*)malloc(sizeof(t_game))) == 0)
		check_error_n_exit(1,"malloc error");
	init_sdl(game);
	gettimeofday(&game->time, NULL);
	game->sectors = (t_sector*)malloc(sizeof(t_sector));
	game->count_sectors = 1;
	game->points_cam = (vec2*)malloc(sizeof(vec2) * 3);
	//game->sectors->points = read_map("src/map");//функция для чтения карты;
	game->sectors->count_wall = 3;
	game->sectors->neighbors = (int*)malloc(sizeof(int) * 3);
	game->points = (vec2*)malloc(sizeof(vec2) * 3);
	game->points->y = 2;
	game->points->x = 0;
	(game->points + 1)->y = -1;
	(game->points + 1)->x = 2;
	(game->points + 2)->y = -3;
	(game->points + 2)->x = -2;
	game->count_points = 3;
	game->sectors->index_points = (int*)malloc(sizeof(int) * 3);
	*(game->sectors->index_points) = 0;
	*(game->sectors->index_points + 1) = 1;
	*(game->sectors->index_points + 2) = 2;
	*(game->sectors->neighbors) = 0xAA0000;
	*(game->sectors->neighbors + 1) = 0xAA00;
	*(game->sectors->neighbors + 2) = 0xAA;
	game->player.pos.x = 0;
	game->player.pos.y = 0;
	game->player.angle = 0;
	game->player.curr_sector = 0;
	return (game);
}
