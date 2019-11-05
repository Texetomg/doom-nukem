/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 16:23:55 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/11/01 15:01:26 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

SDL_Texture	*load_image(char *file, SDL_Renderer *ren)
{
	SDL_Surface	*loaded_image;
	SDL_Texture	*texture;

	loaded_image = NULL;
	texture = NULL;
	if ((loaded_image = SDL_LoadBMP(file)) != NULL)
	{
		texture = SDL_CreateTextureFromSurface(ren, loaded_image);
		SDL_FreeSurface(loaded_image);
	}
	check_error_n_exit(1, "loaded_image Error");
	return (texture);
}

void		apply_surface(int x, int y, SDL_Texture *tex, SDL_Renderer *ren)
{
	SDL_Rect	pos;

	pos.x = x;
	pos.y = y;
	SDL_QueryTexture(tex, NULL, NULL, &pos.w, &pos.h);
	SDL_RenderCopy(ren, tex, NULL, &pos);
}

void		free_sdl(t_game *game)
{
	Mix_FreeChunk(game->sounds.bang);
	game->sounds.bang = NULL;
	Mix_FreeMusic(game->sounds.music);
	game->sounds.music = NULL;
	Mix_Quit();
	SDL_FreeSurface(game->screen);
	game->screen = NULL;
	free(game->texture);
	game->texture = NULL;
	atexit(TTF_Quit);
	SDL_DestroyWindow(game->window);
	game->window = NULL;
	SDL_Quit();
}
