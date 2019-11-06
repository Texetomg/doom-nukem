/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramory-l <ramory-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 20:10:38 by thorker           #+#    #+#             */
/*   Updated: 2019/11/06 11:03:45 by ramory-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
** инициализация sdl
*/

static void	init_sdl(t_game *game)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		check_error_n_exit(1,(char*)SDL_GetError());//закрывать sdl:
	if (SDL_ShowCursor(SDL_DISABLE) < 0)
		check_error_n_exit(1,(char*)SDL_GetError());
	if ((SDL_GetDesktopDisplayMode(0, &game->display_mode)) != 0)
		check_error_n_exit(1,(char*)SDL_GetError());
	//game->window = SDL_CreateWindow(0, 0, 0, 0, 0,
	//		SDL_WINDOW_FULLSCREEN_DESKTOP);
	game->window = SDL_CreateWindow("Doom-Nukem", 0, 0, 1400, 1000, SDL_WINDOW_SHOWN);
	if (game->window == 0)
		check_error_n_exit(1,(char*)SDL_GetError());
	if ((game->screen = SDL_GetWindowSurface(game->window)) == 0)
		check_error_n_exit(1,(char*)SDL_GetError());
	if (TTF_Init() < 0)
		check_error_n_exit(1,(char*)SDL_GetError());
	if (Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0) {
        check_error_n_exit(1,(char*)SDL_GetError());
    }
	game->texture = get_texture("imgs/textures/cat.bmp");
	game->texture1 = get_texture("imgs/gif1/13.bmp");
	texture_cut(game->texture1, 0, 0x303030);
}

void		add_angle_sprites_end(t_sprite **begin,
		double start_angle,
		double end_angle,
		SDL_Surface *texture,
		double up_health,
		double down_health,
		SDL_Surface *texture2)
{
	t_angle_sprite	*curr;
	t_angle_sprite	*last;

	curr = (*begin)->angle_sprite;
	if (curr != 0)
	{
		while (curr != 0 && curr->next != NULL)
			curr = curr->next;
	}
	last = curr;
	curr = (t_angle_sprite*)malloc(sizeof(t_angle_sprite));
	curr->start_angle = start_angle;
	curr->end_angle = end_angle;
	curr->texture = texture;
	curr->up_health = up_health;
	curr->down_health = down_health;
	curr->texture2 = texture2;
	curr->next = 0;
	if (last != 0)
		last->next = curr;
	else
		(*begin)->angle_sprite = curr;
}

void	add_sprites_wall(t_game *game)
{
	game->sectors->sprite_wall = (t_sprite_wall*)malloc(sizeof(t_sprite_wall));
	game->sectors->sprite_wall->top = 0.5;
	game->sectors->sprite_wall->bot = 0.9;
	game->sectors->sprite_wall->right = 0.87;
	game->sectors->sprite_wall->left = 0.3;
	game->sectors->sprite_wall->wall = 0;
	game->sectors->sprite_wall->texture = *((game->gif)->array + 30);
	game->sectors->sprite_wall->next = 0;
}

t_game	*create_struct(void)
{
	t_game	*game;

	if ((game = (t_game*)malloc(sizeof(t_game))) == 0)
		check_error_n_exit(1,"malloc error");
	init_sdl(game);
	gettimeofday(&game->time, NULL);
	read_map("map2", game);
	load_sounds(game);
	load_images(game);
	set_initial_values(game);
	add_sprites_wall(game);
	game->server_ip = ft_strnew(ft_strlen(game->multi_menu.strings[1]));
	return (game);
}
