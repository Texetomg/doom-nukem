/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map-editor.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 11:33:07 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/03/29 13:53:56 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_EDITOR_H
# define MAP_EDITOR_H
# include "libft.h"
# include <math.h>
# include <SDL.h>
#include <sys/time.h>

typedef struct		s_sdl
{
	SDL_Window		*window;
	SDL_Surface		*screen;
	SDL_DisplayMode	display_mode;
    SDL_Renderer    *ren;
}					t_sdl;

SDL_Texture*    	load_image(char *file, SDL_Renderer *ren);
void            	apply_surface(int x, int y, SDL_Texture *tex, SDL_Renderer *ren);

# endif