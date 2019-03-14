/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SDL_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 16:23:55 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/03/14 16:36:31 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

SDL_Texture* load_image(char *file, SDL_Renderer *ren)
{
    SDL_Surface *loaded_image;
    SDL_Texture *texture;

    loaded_image = NULL;
    texture = NULL;
    loaded_image = SDL_LoadBMP(file);
    if (loaded_image != NULL)
    {
        texture = SDL_CreateTextureFromSurface(ren, loaded_image);
        SDL_FreeSurface(loaded_image);
    }
    else
        check_error_n_exit(1, "loaded_image Error");
    return (texture);
}