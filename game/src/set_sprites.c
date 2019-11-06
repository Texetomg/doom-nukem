/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_sprites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramory-l <ramory-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 11:01:31 by ramory-l          #+#    #+#             */
/*   Updated: 2019/11/06 11:01:44 by ramory-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	set_sprites(t_game *game)
{
    t_angle_sprite *start_sprite;

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
	add_angle_sprites_end(&(game->sprites), 0, 2 * 3.14 / 9, IMG_Load("imgs/sprites/doomguy/1/1/1.bmp"), 100, 85, IMG_Load("imgs/sprites/doomguy/1/1/1.bmp"));
	//------------------------------------------------------------------------------------------------------------------
	add_angle_sprites_end(&(game->sprites), 2 * 3.14 / 9, 4 * 3.14 / 9, IMG_Load("imgs/sprites/doomguy/1/1/2.bmp"), 85, 70, IMG_Load("imgs/sprites/doomguy/1/2/1.bmp"));
	//------------------------------------------------------------------------------------------------------------------
	add_angle_sprites_end(&(game->sprites), 4 * 3.14 / 9, 6 * 3.14 / 9, IMG_Load("imgs/sprites/doomguy/1/1/3.bmp"), 70, 55, IMG_Load("imgs/sprites/doomguy/1/2/2.bmp"));
	//------------------------------------------------------------------------------------------------------------------
	add_angle_sprites_end(&(game->sprites), 6 * 3.14 / 9, 8 * 3.14 / 9, IMG_Load("imgs/sprites/doomguy/1/1/4.bmp"), 55, 40, IMG_Load("imgs/sprites/doomguy/1/2/3.bmp"));
	//------------------------------------------------------------------------------------------------------------------
	add_angle_sprites_end(&(game->sprites), 8 * 3.14 / 9, 10 * 3.14 / 9, IMG_Load("imgs/sprites/doomguy/1/1/5.bmp"), 40, 25, IMG_Load("imgs/sprites/doomguy/1/2/4.bmp"));
	//------------------------------------------------------------------------------------------------------------------
	add_angle_sprites_end(&(game->sprites), 10 * 3.14 / 9, 12 * 3.14 / 9, IMG_Load("imgs/sprites/doomguy/1/1/6.bmp"), 25, 10, IMG_Load("imgs/sprites/doomguy/1/2/5.bmp"));
	//------------------------------------------------------------------------------------------------------------------
	add_angle_sprites_end(&(game->sprites), 12 * 3.14 / 9, 14 * 3.14 / 9, IMG_Load("imgs/sprites/doomguy/1/1/7.bmp"), 10, 0, IMG_Load("imgs/sprites/doomguy/1/2/6.bmp"));

	add_angle_sprites_end(&(game->sprites), 14 * 3.14 / 9, 16 * 3.14 / 9, IMG_Load("imgs/sprites/doomguy/1/1/8.bmp"), 10, 0, IMG_Load("imgs/sprites/doomguy/1/2/6.bmp"));
	add_angle_sprites_end(&(game->sprites), 16 * 3.14 / 9, 18 * 3.14 / 9, IMG_Load("imgs/sprites/doomguy/1/1/1.bmp"), 10, 0, IMG_Load("imgs/sprites/doomguy/1/2/6.bmp"));
	add_angle_sprites_end(&(game->sprites), 12 * 3.14 / 9, 14 * 3.14 / 9, IMG_Load("imgs/sprites/doomguy/1/1/7.bmp"), 10, 0, IMG_Load("imgs/sprites/doomguy/1/2/6.bmp"));
	//------------------------------------------------------------------------------------------------------------------
    add_angle_sprites_end(&(game->sprites), 14 * 3.14 / 9, 16 * 3.14 / 9, IMG_Load("imgs/sprites/doomguy/1/1/8.bmp"), 10, 0, IMG_Load("imgs/sprites/doomguy/1/2/6.bmp"));
	//------------------------------------------------------------------------------------------------------------------
    add_angle_sprites_end(&(game->sprites), 16 * 3.14 / 9, 2 * 3.14, IMG_Load("imgs/sprites/doomguy/1/1/1.bmp"), 10, 0, IMG_Load("imgs/sprites/doomguy/1/2/6.bmp"));
    printf("18\n");
	//------------------------------------------------------------------------------------------------------------------
	(game->sprites)->angle_sprite->next->next->next->next->next->next->next->next->next = 0;
    //##################################################################################################################
	game->sprites->next = (t_sprite*)malloc(sizeof(t_sprite));
	(game->sprites)->next->id = 1;
	(game->sprites)->next->pos.x = 1;
	(game->sprites)->next->pos.y = -2;
	(game->sprites)->next->heigth = 0.5;
	(game->sprites)->next->width = game->screen->w / 10;
	(game->sprites)->next->pos.z = 0.5;
	(game->sprites)->next->sector = 1;
	(game->sprites)->next->angle = 3.14 / 2;
	//------------------------------------------------------------------------------------------------------------------
	(game->sprites)->next->angle_sprite = (t_angle_sprite*)malloc(sizeof(t_angle_sprite));
	(game->sprites)->next->angle_sprite->start_angle = -3.14;
	(game->sprites)->next->angle_sprite->end_angle = 3.14;
	(game->sprites)->next->angle_sprite->texture = *((game->gif)->array + 10);
	(game->sprites)->next->angle_sprite->texture2 = *((game->gif)->array + 10);
	(game->sprites)->next->angle_sprite->up_health = 100;
	(game->sprites)->next->angle_sprite->down_health = 85;
	//------------------------------------------------------------------------------------------------------------------
	(game->sprites)->next->angle_sprite->next = (t_angle_sprite*)malloc(sizeof(t_angle_sprite));
	(game->sprites)->next->angle_sprite->next->start_angle = -3.14;
	(game->sprites)->next->angle_sprite->next->end_angle = 3.14;
	(game->sprites)->next->angle_sprite->next->texture = *((game->gif)->array + 11);
	(game->sprites)->next->angle_sprite->next->texture2 = *((game->gif)->array + 11);
	(game->sprites)->next->angle_sprite->next->up_health = 85;
	(game->sprites)->next->angle_sprite->next->down_health = 70;
	//------------------------------------------------------------------------------------------------------------------
	(game->sprites)->next->angle_sprite->next->next = (t_angle_sprite*)malloc(sizeof(t_angle_sprite));
	(game->sprites)->next->angle_sprite->next->next->start_angle = -3.14;
	(game->sprites)->next->angle_sprite->next->next->end_angle = 3.14;
	(game->sprites)->next->angle_sprite->next->next->texture = *((game->gif)->array + 12);
	(game->sprites)->next->angle_sprite->next->next->texture2 = *((game->gif)->array + 12);
	(game->sprites)->next->angle_sprite->next->next->up_health = 70;
	(game->sprites)->next->angle_sprite->next->next->down_health = 55;
	//------------------------------------------------------------------------------------------------------------------
	(game->sprites)->next->angle_sprite->next->next->next = (t_angle_sprite*)malloc(sizeof(t_angle_sprite));
	(game->sprites)->next->angle_sprite->next->next->next->start_angle = -3.14;
	(game->sprites)->next->angle_sprite->next->next->next->end_angle = 3.14;
	(game->sprites)->next->angle_sprite->next->next->next->texture = *((game->gif)->array + 13);
	(game->sprites)->next->angle_sprite->next->next->next->texture2 = *((game->gif)->array + 13);
	(game->sprites)->next->angle_sprite->next->next->next->up_health = 55;
	(game->sprites)->next->angle_sprite->next->next->next->down_health = 40;
	//------------------------------------------------------------------------------------------------------------------
	(game->sprites)->next->angle_sprite->next->next->next->next = (t_angle_sprite*)malloc(sizeof(t_angle_sprite));
	(game->sprites)->next->angle_sprite->next->next->next->next->start_angle = -3.14;
	(game->sprites)->next->angle_sprite->next->next->next->next->end_angle = 3.14;
	(game->sprites)->next->angle_sprite->next->next->next->next->texture = *((game->gif)->array + 14);
	(game->sprites)->next->angle_sprite->next->next->next->next->texture2 = *((game->gif)->array + 14);
	(game->sprites)->next->angle_sprite->next->next->next->next->up_health = 40;
	(game->sprites)->next->angle_sprite->next->next->next->next->down_health = 25;
	//------------------------------------------------------------------------------------------------------------------
	(game->sprites)->next->angle_sprite->next->next->next->next->next = (t_angle_sprite*)malloc(sizeof(t_angle_sprite));
	(game->sprites)->next->angle_sprite->next->next->next->next->next->start_angle = -3.14;
	(game->sprites)->next->angle_sprite->next->next->next->next->next->end_angle = 3.14;
	(game->sprites)->next->angle_sprite->next->next->next->next->next->texture = *((game->gif)->array + 15);
	(game->sprites)->next->angle_sprite->next->next->next->next->next->texture2 = *((game->gif)->array + 15);
	(game->sprites)->next->angle_sprite->next->next->next->next->next->up_health = 25;
	(game->sprites)->next->angle_sprite->next->next->next->next->next->down_health = 0;
	//------------------------------------------------------------------------------------------------------------------
	(game->sprites)->next->angle_sprite->next->next->next->next->next->next = 0;
	//------------------------------------------------------------------------------------------------------------------
	(game->sprites)->next->health = 100;
	(game->sprites)->next->next = 0;
	//##################################################################################################################
	start_sprite = (game->sprites)->angle_sprite;
	while (start_sprite != NULL)
    {
	    texture_cut_sdl(start_sprite->texture, 0x71FAFC, 0x73FCFE);
	    start_sprite = start_sprite->next;
    }
}