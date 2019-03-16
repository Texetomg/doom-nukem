/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SDL_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 16:23:55 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/03/15 17:10:29 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

SDL_Texture* load_image(char *file, SDL_Renderer *ren)
{
    SDL_Surface *loaded_image;
    SDL_Texture *texture;

    loaded_image = NULL;
    texture = NULL;
    if ((loaded_image = SDL_LoadBMP(file)) != NULL)
    {
        texture = SDL_CreateTextureFromSurface(ren, loaded_image);
        SDL_FreeSurface(loaded_image);
    }
    else
        check_error_n_exit(1, "loaded_image Error");
    return (texture);
}

void        apply_surface(int x, int y, SDL_Texture *tex, SDL_Renderer *ren)
{
    SDL_Rect    pos;

    pos.x = x;
    pos.y = y;
    SDL_QueryTexture(tex, NULL, NULL, &pos.w, &pos.h);
    SDL_RenderCopy(ren, tex, NULL, &pos);
}

void		put_sdl_error(char *str)
{
	if (str == 0)
		ft_putendl(SDL_GetError());
	else
		ft_putendl(str);
	SDL_Quit();
	exit(1);
}
