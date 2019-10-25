/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 13:37:49 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/10/25 16:59:16 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	draw_player_icon(SDL_Surface *screen, SDL_Surface *img)
{
	t_vec2 start;
	t_vec2 end;

	start.x = 0;
	start.y = screen->h / 100 * 85;
	end.x = screen->w / 100 * 15;
	end.y = screen->h;
	draw_img(screen, img, start, end);
}

void	draw_aim(SDL_Surface *screen, SDL_Surface *img)
{
	t_vec2 start;
	t_vec2 end;

	start.x = screen->w / 2 - screen->w / 50;
	start.y = screen->h / 2 - screen->h / 50;
	end.x = screen->w / 2 + screen->w / 50;
	end.y = screen->h / 2 + screen->h / 50;
	draw_img(screen, img, start, end);
}

void	draw_hp_bar(SDL_Surface *screen, SDL_Surface *img)
{
	t_vec2 start;
	t_vec2 end;

	start.x = screen->w / 100 * 15;
	start.y = screen->h / 100 * 92;
	end.x = screen->w / 100 * 30;
	end.y = screen->h / 100 * 98;
	draw_img(screen, img, start, end);
}

void	draw_hands(SDL_Surface *screen, SDL_Surface *img)
{
	t_vec2 start;
	t_vec2 end;

	start.x = screen->w / 100 * 40;
	start.y = screen->h / 100 * 50;
	end.x = screen->w / 100 * 90;
	end.y = screen->h;
	draw_img(screen, img, start, end);
}

void	draw_jetpack(SDL_Surface *screen, SDL_Surface *img)
{
	t_vec2 start;
	t_vec2 end;

	start.x = screen->w / 100 * 35;
	start.y = screen->h / 100 * 91;
	end.x = screen->w / 100 * 45;
	end.y = screen->h / 100 * 99;
	draw_img(screen, img, start, end);
}
