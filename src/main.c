/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:38:27 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/03/14 17:54:06 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

int main(void)
{
	SDL_Window      *win;
	SDL_Renderer    *ren;
	SDL_Texture     *image;
	SDL_Texture     *background;
	int             b_w;
	int             b_h;
	int				i_w;
	int				i_h;
	int				x;
	int				y;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		check_error_n_exit(1, "SDL_Init Error");
	if ((win = SDL_CreateWindow("Doom-nukem", SDL_WINDOWPOS_CENTERED,
												SDL_WINDOWPOS_CENTERED,
												SCREEN_WIDTH,
												SCREEN_HEIGHT,
												SDL_WINDOW_SHOWN))== NULL)
		check_error_n_exit(1, "SDL_CreateWindow Error");
	if ((ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC))== NULL)
		check_error_n_exit(1, "SDL_CreateRenderer Error");
	
	background = load_image("imgs/blocks.bmp", ren);
	image = load_image("imgs/doom.bmp", ren);
	
	if (background == NULL || image == NULL)
		check_error_n_exit(1, "load_image Error");
	
	SDL_RenderClear(ren);

	SDL_QueryTexture(background, NULL, NULL, &b_w, &b_h);
	apply_surface(0, 0, background, ren);
	apply_surface(b_w, 0, background, ren);

	SDL_QueryTexture(image, NULL, NULL, &i_w, &i_h);
	x = SCREEN_WIDTH / 2 - i_w / 2;
	y = SCREEN_HEIGHT / 2 - i_h / 2;
	apply_surface(x, y, image, ren);
	SDL_RenderPresent(ren);
	SDL_Delay(5000);

	SDL_DestroyTexture(image);
	SDL_DestroyTexture(background);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
	
	return(0);
}