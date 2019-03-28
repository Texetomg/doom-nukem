/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 20:10:38 by thorker           #+#    #+#             */
/*   Updated: 2019/03/28 16:15:38 by bfalmer-         ###   ########.fr       */
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
	game->sectors = (t_sector*)malloc(sizeof(t_sector));
	read_map("src/map", game->sectors->points);//функция для чтения карты;
	game->sectors->count_wall = 3;
	game->sectors->neighbors = (int*)malloc(sizeof(int) * 3);
	*(game->sectors->neighbors) = 0xAA0000;
	*(game->sectors->neighbors + 1) = 0xAA00;
	*(game->sectors->neighbors + 2) = 0xAA;
	game->player.pos.x = 0;
	game->player.pos.y = 0;
	game->player.angle = 0;
	game->player.curr_sector = 0;
	return (game);
}
