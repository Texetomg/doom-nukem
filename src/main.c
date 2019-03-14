/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:38:27 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/03/14 16:37:22 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

int main(void)
{
    SDL_Window      *win;
    SDL_Renderer    *ren;
    SDL_Texture     *tex;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        check_error_n_exit(1, "SDL_Init Error");
    win = SDL_CreateWindow("Doom-nukem", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    if (win == NULL)
        check_error_n_exit(1, "SDL_CreateWindow Error");
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == NULL)
        check_error_n_exit(1, "SDL_CreateRenderer Error");
    tex = load_image("/imgs/test.bmp", ren);
    if (tex == NULL)
        check_error_n_exit(1, "SDL_CreateTextureFromSurface Error");
    SDL_RenderClear(ren);
    SDL_RenderCopy(ren, tex, NULL, NULL);
    SDL_RenderPresent(ren);
    SDL_Delay(8000);
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    SDL_Quit();
    
    return(0);
}