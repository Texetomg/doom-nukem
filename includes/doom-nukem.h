/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom-nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:56:03 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/03/14 16:34:34 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H
# include "libft.h"
# include <math.h>
# include <SDL.h>
# define SCREEN_WIDTH = 640;
# define SCREEN_HEIGHT = 480;

SDL_Texture* load_image(char *file, SDL_Renderer *ren);

#endif