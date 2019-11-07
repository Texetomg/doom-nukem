/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_sprites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramory-l <ramory-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 11:01:31 by ramory-l          #+#    #+#             */
/*   Updated: 2019/11/07 22:16:46 by ramory-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void	init_sprites1(t_game *game, TAS *temp)
{
	game->sprites = (t_sprite*)malloc(sizeof(t_sprite));
	(game->sprites)->id = 0;
	(game->sprites)->pos.x = 0;
	(game->sprites)->pos.y = 0;
	(game->sprites)->heigth = 0.5;
	(game->sprites)->width = game->screen->w / 10;
	(game->sprites)->pos.z = 0.6;
	(game->sprites)->sector = 0;
	(game->sprites)->angle = 0;
	(game->sprites)->health = 100;
	(game->sprites)->angle_sprite = 0;
	change_temp1(temp);
	change_temp2(temp);
	change_temp3(temp);
	change_temp4(temp);
	add_angle_sprites_end(&(game->sprites), temp[0]);
	add_angle_sprites_end(&(game->sprites), temp[1]);
	add_angle_sprites_end(&(game->sprites), temp[2]);
	add_angle_sprites_end(&(game->sprites), temp[3]);
	add_angle_sprites_end(&(game->sprites), temp[4]);
	add_angle_sprites_end(&(game->sprites), temp[5]);
	add_angle_sprites_end(&(game->sprites), temp[6]);
	add_angle_sprites_end(&(game->sprites), temp[7]);
	add_angle_sprites_end(&(game->sprites), temp[8]);
	add_angle_sprites_end(&(game->sprites), temp[9]);
}

static void	init_sprites2(t_game *game)
{
	game->sprites->N = (t_sprite*)malloc(sizeof(t_sprite));
	(game->sprites)->N->id = 1;
	(game->sprites)->N->pos.x = 1;
	(game->sprites)->N->pos.y = -2;
	(game->sprites)->N->heigth = 0.5;
	(game->sprites)->N->width = game->screen->w / 10;
	(game->sprites)->N->pos.z = 0.5;
	(game->sprites)->N->sector = 1;
	(game->sprites)->N->angle = 3.14 / 2;
	(game->sprites)->N->AS = (TAS*)malloc(sizeof(TAS));
	(game->sprites)->N->AS->start_angle = -3.14;
	(game->sprites)->N->AS->end_angle = 3.14;
	(game->sprites)->N->AS->texture = *((game->gif)->array + 10);
	(game->sprites)->N->AS->texture2 = *((game->gif)->array + 10);
	(game->sprites)->N->AS->up_health = 100;
	(game->sprites)->N->AS->down_health = 85;
}

static void init_sprites3(t_game *game)
{
	(game->sprites)->N->AS->N = (TAS*)malloc(sizeof(TAS));
	(game->sprites)->N->AS->N->start_angle = -3.14;
	(game->sprites)->N->AS->N->end_angle = 3.14;
	(game->sprites)->N->AS->N->texture = *((game->gif)->array + 11);
	(game->sprites)->N->AS->N->texture2 = *((game->gif)->array + 11);
	(game->sprites)->N->AS->N->up_health = 85;
	(game->sprites)->N->AS->N->down_health = 70;
	(game->sprites)->N->AS->N->N = (TAS*)malloc(sizeof(TAS));
	(game->sprites)->N->AS->N->N->start_angle = -3.14;
	(game->sprites)->N->AS->N->N->end_angle = 3.14;
	(game->sprites)->N->AS->N->N->texture = *((game->gif)->array + 12);
	(game->sprites)->N->AS->N->N->texture2 = *((game->gif)->array + 12);
	(game->sprites)->N->AS->N->N->up_health = 70;
	(game->sprites)->N->AS->N->N->down_health = 55;
	(game->sprites)->N->AS->N->N->N = (TAS*)malloc(sizeof(TAS));
	(game->sprites)->N->AS->N->N->N->start_angle = -3.14;
	(game->sprites)->N->AS->N->N->N->end_angle = 3.14;
	(game->sprites)->N->AS->N->N->N->texture = *((game->gif)->array + 13);
	(game->sprites)->N->AS->N->N->N->texture2 = *((game->gif)->array + 13);
	(game->sprites)->N->AS->N->N->N->up_health = 55;
	(game->sprites)->N->AS->N->N->N->down_health = 40;
}

static void init_sprites4(t_game *game)
{
	(game->sprites)->N->AS->N->N->N->N = (TAS*)malloc(sizeof(TAS));
	(game->sprites)->N->AS->N->N->N->N->start_angle = -3.14;
	(game->sprites)->N->AS->N->N->N->N->end_angle = 3.14;
	(game->sprites)->N->AS->N->N->N->N->texture = *((game->gif)->array + 14);
	(game->sprites)->N->AS->N->N->N->N->texture2 = *((game->gif)->array + 14);
	(game->sprites)->N->AS->N->N->N->N->up_health = 40;
	(game->sprites)->N->AS->N->N->N->N->down_health = 25;
	(game->sprites)->N->AS->N->N->N->N->N = (TAS*)malloc(sizeof(TAS));
	(game->sprites)->N->AS->N->N->N->N->N->start_angle = -3.14;
	(game->sprites)->N->AS->N->N->N->N->N->end_angle = 3.14;
	(game->sprites)->N->AS->N->N->N->N->N->texture = *((game->gif)->array + 15);
	(game->sprites)->N->AS->N->N->N->N->N->texture2 = *((game->gif)->array + 15);
	(game->sprites)->N->AS->N->N->N->N->N->up_health = 25;
	(game->sprites)->N->AS->N->N->N->N->N->down_health = 0;
}

void		set_sprites(t_game *game)
{
	TAS temp[12];
    TAS *start_sprite;

	init_sprites1(game, temp);
    add_angle_sprites_end(&(game->sprites), temp[10]);
    add_angle_sprites_end(&(game->sprites), temp[11]);
	(game->sprites)->AS->N->N->N->N->N->N->N->N->N = 0;
	init_sprites2(game);
	init_sprites3(game);
	init_sprites4(game);
	(game->sprites)->N->AS->N->N->N->N->N->N = 0;
	(game->sprites)->N->health = 100;
	(game->sprites)->N->N = 0;
	start_sprite = (game->sprites)->AS;
	while (start_sprite != NULL)
    {
	    texture_cut_sdl(start_sprite->texture, 0x71FAFC, 0x73FCFE);
	    start_sprite = start_sprite->N;
    }
}