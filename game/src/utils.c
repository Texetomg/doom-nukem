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

void    get_pos_z(t_player *player, t_sector *sectors )
{  
    if (player->z_accel > 0)
    {
        if (player->pos.z + player->z_accel  >= (sectors + player->curr_sector)->ceil)
        {
            player->z_accel = 0;
        }
        else
        {
            player->pos.z += player->z_accel;
            player->z_accel -= ACCEL;
        }
        
    }
    else if (player->z_accel == 0 && player->foots > (sectors + player->curr_sector)->floor)
    {
        player->z_accel -= ACCEL;
    }
    else if (player->z_accel < 0)
    {
        if (player->foots + player->z_accel < (sectors + player->curr_sector)->floor)
        {
            player->z_accel = 0;
            player->pos.z = (sectors + player->curr_sector)->floor + player->b_foots;
        }
        else
        {
            player->pos.z += player->z_accel;
            player->z_accel -= ACCEL;   
        }
    }

    player->foots = player->pos.z - player->b_foots;
    player->knees = player->pos.z - player->b_knees;
}

void    print_text(SDL_Surface *screen, char *text, char *font, int size, SDL_Color color, SDL_Rect dest)
{
	TTF_Font *fnt;
    SDL_Surface *sText;

	if ((fnt = TTF_OpenFont(font, size)) == NULL)
		check_error_n_exit(1,(char*)SDL_GetError());
	if ((sText = TTF_RenderText_Blended(fnt, text, color)) == NULL)
        check_error_n_exit(1,(char*)SDL_GetError());
	SDL_BlitSurface(sText, NULL, screen, &dest);
	SDL_FreeSurface(sText);
	TTF_CloseFont(fnt);
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
    atexit(TTF_Quit);
	SDL_DestroyWindow(game->window);
	game->window = NULL;
	SDL_Quit();
}
