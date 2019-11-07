/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramory-l <ramory-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 22:26:46 by ramory-l          #+#    #+#             */
/*   Updated: 2019/11/07 22:49:17 by ramory-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"


static void		sprite_id(t_sprite *sprite, TAS *angle_sprite, SDL_Surface *texture)
{
	texture = angle_sprite->texture2;
	angle_sprite = sprite->angle_sprite;
	while (angle_sprite != 0)
	{
		angle_sprite->texture = texture;
		angle_sprite = angle_sprite->next;
	}
}

static void		sprite_move(t_sprite *sprite, TAS *angle_sprite, SDL_Surface *texture, int *k)
{
	if (sprite->health <= angle_sprite->up_health && sprite->health > angle_sprite->down_health)
	{
		if (sprite->id == 0)
			sprite_id(sprite, angle_sprite, texture);
		else
			texture = angle_sprite->texture;
		*k = 0;
	}
}

static void		sprite_angle(t_sprite *sprite, TAS *angle_sprite, SDL_Surface *texture, int *k)
{
	if (sprite->angle_in_cam >= angle_sprite->start_angle &&
		sprite->angle_in_cam < angle_sprite->end_angle &&
		sprite->health == 100)
	{
		texture = angle_sprite->texture;
		*k = 0;
	}
	else
		texture = angle_sprite->texture;
}

SDL_Surface		*check_sprite(t_sprite *sprite)
{
	int				k;
	t_angle_sprite	*angle_sprite;
	SDL_Surface		*texture;

	k = 1;
	angle_sprite = sprite->angle_sprite;
	texture = sprite->angle_sprite->texture;
	while (angle_sprite != 0 && k != 0)
	{
		if (sprite->move)
			sprite_move(sprite, angle_sprite, texture, &k);
		else if (sprite->health > 85)
			sprite_angle(sprite, angle_sprite, texture, &k);
		else
			sprite_move(sprite, angle_sprite, texture, &k);
		angle_sprite = angle_sprite->next;
	}
	return (texture);
}