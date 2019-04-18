/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 17:54:54 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/04/18 13:20:47 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

void    get_pos_z(t_game *game)
{  
    if (game->player.z_accel > 0)
    {
        if (game->player.pos.z + game->player.z_accel  >= (game->sectors + game->player.curr_sector)->ceil)
        {
            game->player.z_accel = 0;
        }
        else
        {
            game->player.pos.z += game->player.z_accel;
            game->player.z_accel -= ACCEL;
        }
        
    }
    else if (game->player.z_accel == 0 && game->player.foots > (game->sectors + game->player.curr_sector)->floor)
    {
        game->player.z_accel -= ACCEL;
    }
    else if (game->player.z_accel < 0)
    {
        if (game->player.foots + game->player.z_accel < (game->sectors + game->player.curr_sector)->floor)
        {
            game->player.z_accel = 0;
            game->player.pos.z = (game->sectors + game->player.curr_sector)->floor + game->player.b_foots;
        }
        else
        {
            game->player.pos.z += game->player.z_accel;
            game->player.z_accel -= ACCEL;   
        }
    }

    game->player.foots = game->player.pos.z - game->player.b_foots;
    game->player.knees = game->player.pos.z - game->player.b_knees;
}

void    free_SDL(t_game *game)
{
    Mix_FreeChunk(game->sounds.bang);
	game->sounds.bang = NULL;
	Mix_FreeMusic(game->sounds.music);
	game->sounds.music = NULL;
	Mix_Quit();
	SDL_FreeSurface(game->screen);
	game->screen = NULL;
	SDL_FreeSurface(game->texture);
	game->texture = NULL;
	/*
	while (game->texture_arr[i])
	{
		SDL_FreeSurface(game->texture_arr[i]);
		game->texture_arr[i] = NULL;
		i++;
	}
	i = 0;
	
	while (game->gif->array[i])
	{
		SDL_FreeSurface(game->gif->array[i]);
		game->gif->array[i] = NULL;
		i++;
	}
	*/
	SDL_DestroyWindow(game->window);
	game->window = NULL;
	SDL_Quit();
}
