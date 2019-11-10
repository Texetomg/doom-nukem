/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 17:22:01 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/11/09 16:53:25 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void	read_gif(t_gif *gif, char *str, int index, int frame)
{
	char	*folder;
	char	*i;
	char	*path;
	char	*tmp;
	int		k;

	folder = ft_strdup(str);
	gif[index].frame = frame;
	gif[index].curr_frame = 0;
	gif[index].array = (SDL_Surface**)
		malloc(sizeof(SDL_Surface*) * gif[index].frame);
	k = 0;
	while (k < gif[index].frame)
	{
		i = ft_itoa(k);
		tmp = ft_strjoin(folder, i);
		path = ft_strjoin(tmp, ".bmp");
		if (!(*(gif[index].array + k) = IMG_Load(path)))
			check_error_n_exit(1, (char*)SDL_GetError());
		free(path);
		free(tmp);
		free(i);
		k++;
	}
	free(folder);
}

static void	load_menu_images(t_game *game)
{
	if (!(game->start_menu.image[0] = IMG_Load("imgs/start_menu/0.bmp")))
		check_error_n_exit(1, (char*)SDL_GetError());
	if (!(game->start_menu.image[1] = IMG_Load("imgs/start_menu/1.bmp")))
		check_error_n_exit(1, (char*)SDL_GetError());
	if (!(game->start_menu.image[2] = IMG_Load("imgs/start_menu/2.bmp")))
		check_error_n_exit(1, (char*)SDL_GetError());
	if (!(game->start_menu.image[3] = IMG_Load("imgs/start_menu/3.bmp")))
		check_error_n_exit(1, (char*)SDL_GetError());
	if (!(game->start_menu.image[4] = IMG_Load("imgs/start_menu/4.bmp")))
		check_error_n_exit(1, (char*)SDL_GetError());
	if (!(game->start_menu.image[5] = IMG_Load("imgs/start_menu/4.bmp")))
		check_error_n_exit(1, (char*)SDL_GetError());
	if (!(game->tab_menu.image[0] = IMG_Load("imgs/tab_menu/1.bmp")))
		check_error_n_exit(1, (char*)SDL_GetError());
	if (!(game->multi_menu.image[0] = IMG_Load("imgs/tab_menu/1.bmp")))
		check_error_n_exit(1, (char*)SDL_GetError());
}

static void	load_hud_images(t_game *game)
{
	if (!(game->hud.face[2] = IMG_Load("imgs/hud/doom.bmp")))
		check_error_n_exit(1, (char*)SDL_GetError());
	if (!(game->skybox = IMG_Load("imgs/textures/space.bmp")))
		check_error_n_exit(1, (char*)SDL_GetError());
	if (!(game->hud.aim = IMG_Load("imgs/hud/cross_aim.bmp")))
		check_error_n_exit(1, (char*)SDL_GetError());
	if (!(game->hud.hp_bar = IMG_Load("imgs/hud/hp_bar.bmp")))
		check_error_n_exit(1, (char*)SDL_GetError());
	if (!(game->hud.jetpack = IMG_Load("imgs/hud/jetpack.bmp")))
		check_error_n_exit(1, (char*)SDL_GetError());
	if (!(game->hud.key = IMG_Load("imgs/hud/key.bmp")))
		check_error_n_exit(1, (char*)SDL_GetError());
}

void		load_images(t_game *game)
{
	read_gif(game->gif, "imgs/gif1/", 0, 40);
	read_gif(game->gif, "imgs/rifle/", 1, 2);
	load_menu_images(game);
	load_hud_images(game);
}
