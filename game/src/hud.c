/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 16:38:34 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/04/02 21:21:50 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

static void draw_player_icon(SDL_Surface *screen, SDL_Surface *img){
	vec2 start;
	vec2 end;

	start.x = 0;
	start.y = screen->h / 100 * 85;
	end.x = screen->w / 100 * 15;
	end.y = screen->h;
	draw_img(screen, img, start, end);
}

static void draw_aim(SDL_Surface *screen, SDL_Surface *img){
	vec2 start;
	vec2 end;

	start.x = screen->w / 2 - screen->w / 50;
	start.y = screen->h /2  - screen->h / 50;
	end.x = screen->w / 2 + screen->w / 50;
	end.y = screen->h / 2 + screen->h / 50;
	draw_img(screen, img, start, end);
}

static void draw_hp_bar(SDL_Surface *screen, SDL_Surface *img){
	vec2 start;
	vec2 end;

	start.x = screen->w / 100 * 15;
	start.y = screen->h / 100 * 92;
	end.x = screen->w / 100 * 30;
	end.y = screen->h / 100 * 98;
	draw_img(screen, img, start, end);
}

static void draw_hands(SDL_Surface *screen, SDL_Surface *img){
	vec2 start;
	vec2 end;

	start.x = screen->w / 2;
	start.y = screen->h / 2;
	end.x = screen->w;
	end.y = screen->h;
	draw_img(screen, img, start, end);
}

void draw_hud(t_game *game){
	draw_player_icon(game->screen, game->hud.face[2]);
	draw_aim(game->screen, game->hud.aim);
	draw_hp_bar(game->screen, game->hud.hp_bar);
	draw_hands(game->screen, *(game->gif[1].array + game->gif[1].curr_frame));
}
