/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:38:27 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/04/25 13:29:15 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

//запускает отрисовку всех стен
static void	draw_3d_wall(t_game *game, SDL_Surface *screen,
							SDL_Surface *texture,
							vec2 *points,
							int count_points,
							vec2 *points_cam,
							SDL_DisplayMode display_mode,
							t_player *player,
							t_sector *sectors,
							int count_sectors,
							t_gif *gif)
{
	t_draw	for_draw;
	
	//ft_putendl("draw_3d_wall");
	for_draw.fov_left.x = 5;
	for_draw.fov_left.y = 5;
	for_draw.fov_right.x = 5;
	for_draw.fov_right.y = -5;
	for_draw.window.x1 = 0;
	for_draw.window.x2 = display_mode.w;
	for_draw.window.y1b = display_mode.h;
	for_draw.window.y1t = 0;
	for_draw.window.y2b = display_mode.h;
	for_draw.window.y2t = 0;
	for_draw.last_sector = -2;
	for_draw.curr_sector = player->curr_sector;

	give_points_cam(points_cam, points, player, count_points);
	draw_sector(game, gif, texture, screen, player, display_mode, sectors, points_cam, for_draw);
	draw_minimap(screen, display_mode, sectors, points_cam, count_sectors);
}
//отрисовка рук/оружия 
static void		draw_hands(SDL_Surface *screen, t_gif *gif)
{
	int		x = 0;
	int		y = 0;
	int		new_x = 0;
	int		new_y = 0;
	int		color;

	while (y < screen->h / 3)
	{
		new_y = (double)y / (screen->h / 3) * (*(gif[1].array + ((int)(gif[1].curr_frame))))->h;
		while (x < screen->w / 3)
		{
			new_x = (double)x / (screen->w / 3) * (*(gif[1].array + gif[1].curr_frame))->w;
			color = ((int*)((*(gif[1].array + ((int)(gif[1].curr_frame))))->pixels))[new_y * (*(gif[1].array + ((int)(gif[1].curr_frame))))->w + new_x];
			if (color != 0x000000)
				((int*)(screen->pixels))[(int)(y + screen->h / 100 * 65) * screen->w + x + (screen->w / 100 * 45)] = color;
			x++;
		}
		x = 0;
		y++;
	}
}

static void		draw_sprites(SDL_Surface *screen, t_sector *sectors, t_sprites sprites, t_player player, SDL_DisplayMode display_mode)
{
	int y;
	int x;
	int		new_x = 0;
	int		new_y = 0;
	int color;
	(void)sectors;
	sprites.new_pos.x = (sprites.pos.y - player.pos.y) * sin(player.angle) + (sprites.pos.x - player.pos.x) * cos(player.angle);
	sprites.new_pos.y = (sprites.pos.y - player.pos.y) * cos(player.angle) - (sprites.pos.x - player.pos.x) * sin(player.angle);
	sprites.shift = (-sprites.new_pos.y / sprites.new_pos.x) * (screen->w / 2) + screen->w / 2;
	sprites.h = 200 / sprites.new_pos.x;
	sprites.w = 200 / sprites.new_pos.x;
	(y = display_mode.h / 2 - sprites.h / 2) < 0 ? y = 0 : y;
	while (y <= display_mode.h / 2 + sprites.h / 2 && y < display_mode.h)
	{
		(x = (sprites.shift ) - sprites.w / 2) < 0 ? x = 0 : x;
		new_y = ((double)y - display_mode.h / 2 + sprites.h / 2) / ((display_mode.h / 2 + sprites.h / 2) - (display_mode.h / 2 - sprites.h / 2)) * sprites.texture->h;
		while (x < (sprites.shift) + sprites.w / 2 && x < display_mode.w)
		{
			new_x = ((double)x - ((sprites.shift ) - sprites.w / 2)) / (((sprites.shift) + sprites.w / 2) - ((sprites.shift) - sprites.w / 2)) * sprites.texture->w;
			if (y >= 0 && y < screen->h && x >= 0 && x < screen->w )
			{
				color = ((int*)(sprites.texture->pixels))[sprites.texture->w * new_y + new_x];
				((int*)(screen->pixels))[(int)(screen->w * y + (int)(x))] = color;
			}
			x++;
		}
		y++;
	}
}

static void		gif_loop(t_gif *gif, t_keystate *keystate, int *k)
{
	if(keystate->mouse_l == 1)
	{
		gif[1].curr_frame++;
		if (gif[1].curr_frame == gif[1].frame)
		{
			gif[1].curr_frame = 0;
			keystate->mouse_l = 0;
		}
	}
	if (*k == 0)
	{
		gif[0].curr_frame++;
		if (gif[0].curr_frame == gif[0].frame)
			gif[0].curr_frame = 0;
		*k = -3;
	}
	else
		*k += 1;
}

int			main(void)
{
	t_game		*game;
	int loop;
	int k;
	game = create_struct();
	loop = 1;		
	k = -3;
	
	while (loop)
	{

		if (game->menu_status.start == 1)
		{
			if( Mix_PlayingMusic() == 0 )
				Mix_PlayMusic(game->start_menu.music, -1);
			start_menu_render(game, &loop);
		}
		if(game->menu_status.tab == 1)
		{
			if( Mix_PlayingMusic() == 0 )
				Mix_PlayMusic(game->sounds.music, -1);
			tab_menu_render(game, &loop);
		}
		if (game->menu_status.main == 1)
		{	
			if( Mix_PlayingMusic() == 0 )
				Mix_PlayMusic(game->sounds.music, -1);
			player_move(game, game->display_mode, &game->mouse, game->window, game->sounds, game->gif, &game->keystate, game->points, game->sectors, &game->player, &loop, &game->menu_status);
			SDL_WarpMouseInWindow(game->window, game->display_mode.w / 2, game->display_mode.h / 2);
			get_pos_z(&game->player, game->sectors);
			draw_3d_wall(game, game->screen, game->texture, game->points, game->count_points, game->points_cam, game->display_mode, &game->player, game->sectors, game->count_sectors, game->gif);
			draw_sprites(game->screen, game->sectors, game->sprites, game->player, game->display_mode);
			draw_hands(game->screen, game->gif);
			//запуск гифок
			gif_loop(game->gif, &game->keystate, &k);
		}
		put_fps(game->screen, game->hud, &game->time);
		SDL_UpdateWindowSurface(game->window);
		
	}
	//закрытие sdl
	free_SDL(game);
	return (0);
}
