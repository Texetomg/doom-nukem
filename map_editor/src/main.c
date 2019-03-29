/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 11:31:53 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/03/29 14:08:38 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map-editor.h"

int main()
{
	t_sdl		*editor;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		check_error_n_exit(1,(char*)SDL_GetError());

	if ((editor = (t_sdl*)malloc(sizeof(t_sdl))) == 0)
		check_error_n_exit(1,"malloc error");

	if (SDL_ShowCursor(SDL_DISABLE) < 0)
		check_error_n_exit(1,(char*)SDL_GetError());

	if ((SDL_GetDesktopDisplayMode(0, &editor->display_mode)) != 0)
		check_error_n_exit(1,(char*)SDL_GetError());
//create window
	if ((editor->window = SDL_CreateWindow("map_editor", 100, 100, 640, 480, SDL_WINDOW_SHOWN)) == 0)
		check_error_n_exit(1,(char*)SDL_GetError());
//create screen	
	if ((editor->screen = SDL_GetWindowSurface(editor->window)) == 0)
		check_error_n_exit(1,(char*)SDL_GetError());
//create renderer
	if ((editor->ren = SDL_CreateRenderer(editor->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)) == 0)
		check_error_n_exit(1,(char*)SDL_GetError());
	return(0);
}