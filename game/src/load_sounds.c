/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sounds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramory-l <ramory-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 20:10:38 by thorker           #+#    #+#             */
/*   Updated: 2019/11/06 10:50:37 by ramory-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void load_sounds(t_game *game)
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
	if (!(game->start_menu.clap[4] = Mix_LoadWAV( "sounds/gay.mp3" )))
		check_error_n_exit(1,(char*)SDL_GetError());
	if (!(game->sounds.step = Mix_LoadWAV( "sounds/step.mp3" )))
		check_error_n_exit(1,(char*)SDL_GetError());
}