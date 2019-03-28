/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 20:10:38 by thorker           #+#    #+#             */
/*   Updated: 2019/03/27 22:57:50 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"
//инициализация sdl
void	init_sdl(t_game *game)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		put_sdl_error(0);
	if (SDL_ShowCursor(SDL_DISABLE) < 0)
		put_sdl_error(0);
	if ((SDL_GetDesktopDisplayMode(0, &game->display_mode)) != 0)
		put_sdl_error(0);
	game->window = SDL_CreateWindow(0, 0, 0, 0, 0,
			SDL_WINDOW_FULLSCREEN_DESKTOP);
	if (game->window == 0)
		put_sdl_error(0);
	if ((game->screen = SDL_GetWindowSurface(game->window)) == 0)
		put_sdl_error(0);
}
//создание главной структуры
t_game	*create_struct(void)
{
	t_game	*game;

	if ((game = (t_game*)malloc(sizeof(t_game))) == 0)
		put_sdl_error("Don't malloc t_game");
	init_sdl(game);
	gettimeofday(&game->time, NULL);
	//read_map(game, "map");функция для чтения карты;
	game->sectors = (t_sector*)malloc(sizeof(t_sector));
	game->sectors->count_wall = 3;
	game->sectors->neighbors = (int*)malloc(sizeof(int) * 3);
	*(game->sectors->neighbors) = 0xAA0000;
	*(game->sectors->neighbors + 1) = 0xAA00;
	*(game->sectors->neighbors + 2) = 0xAA;
	game->sectors->points = (vec2*)malloc(sizeof(vec2) * 3);
	game->sectors->points->y = 2;
	game->sectors->points->x = 0;
	(game->sectors->points + 1)->y = -1;
	(game->sectors->points + 1)->x = 2;
	(game->sectors->points + 2)->y = -3;
	(game->sectors->points + 2)->x = -2;
	game->player.pos.x = 0;
	game->player.pos.y = 0;
	game->player.angle = 0;
	game->player.curr_sector = 0;
	return (game);
}
