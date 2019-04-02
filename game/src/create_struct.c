/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 20:10:38 by thorker           #+#    #+#             */
/*   Updated: 2019/04/02 17:48:48 by bfalmer-         ###   ########.fr       */
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
t_game	*create_struct(void)
{
	t_game	*game;

	if ((game = (t_game*)malloc(sizeof(t_game))) == 0)
		check_error_n_exit(1,"malloc error");
	init_sdl(game);
	gettimeofday(&game->time, NULL);
	game->points_cam = (vec2*)malloc(sizeof(vec2) * 3);
	read_map("src/map", game);
	/*
	ft_putnbrln(*((game->sectors + 1)->index_points));
	ft_putnbrln(*((game->sectors + 1)->index_points + 1));
	ft_putnbrln(*((game->sectors + 1)->index_points + 2));
	ft_putnbrln(*((game->sectors + 1)->index_points + 3));
	*/
	*((game->sectors + 1)->neighbors) = 0xAA0000;
	*((game->sectors + 1)->neighbors + 1) = 0xAA00;
	*((game->sectors + 1)->neighbors + 2) = 0xAA;
	*((game->sectors + 1)->neighbors + 3) = 0xAA;
	game->player.pos.x = -3;
	game->player.pos.y = 0;
	game->player.angle = 0;
	game->player.curr_sector = 0;
	return (game);
}
