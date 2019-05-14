/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:38:27 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/05/14 15:19:23 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

//запускает отрисовку всех стен
static void	draw_3d_wall(t_game *game)
{
	t_draw	for_draw;
	
	//ft_putendl("draw_3d_wall");
	for_draw.fov_left.x = 5;
	for_draw.fov_left.y = 5;
	for_draw.fov_right.x = 5;
	for_draw.fov_right.y = -5;
	for_draw.window.x1 = 0;
	for_draw.window.x2 = game->display_mode.w;
	for_draw.window.y1b = game->display_mode.h;
	for_draw.window.y1t = 0;
	for_draw.window.y2b = game->display_mode.h;
	for_draw.window.y2t = 0;
	for_draw.last_sector = -2;
	for_draw.curr_sector = game->player.curr_sector;

	give_points_cam(game->points_cam, game->points, &game->player, game->count_points);
	give_sprites_cam(game);
	draw_sector(game, for_draw);
	draw_minimap(game);
}
//отрисовка рук/оружия 
static void		draw_hands(SDL_Surface *screen, t_gif *gif, t_pre_calc pre_calc)
{
	int		x = 0;
	int		y = 0;
	int		new_x = 0; 
	int		new_y = 0;
	int		color;

	while (y < pre_calc.screenh3 )
	{
		new_y = (double)y / (pre_calc.screenh3 ) * (*(gif[1].array + ((int)(gif[1].curr_frame))))->h;
		while (x < pre_calc.screenw3 )
		{
			new_x = (double)x / (pre_calc.screenw3 ) * (*(gif[1].array + gif[1].curr_frame))->w;
			color = ((int*)((*(gif[1].array + ((int)(gif[1].curr_frame))))->pixels))[new_y * (*(gif[1].array + ((int)(gif[1].curr_frame))))->w + new_x];
			if (color != 0x000000)
				((int*)(screen->pixels))[(int)(y + screen->h - pre_calc.screenh3) * screen->w + x + screen->w / 2 - screen->w / 3 / 2] = color;
			x++;
		}
		x = 0;
		y++;
	}
}

void		draw_sprites(t_game *game, t_draw for_draw, t_sprites sprite)
{
	int		y;
	int		x;
	int		x_start;
	int		x_end;
	int		new_x;
	int		new_y;
	int color;
	int bot;
	int top;
	int t_window;
	int b_window;

	x_start = -sprite.pos_in_cam.y * game->display_mode.w / 2 / sprite.pos_in_cam.x + game->display_mode.w / 2 - sprite.width / 2 / sprite.pos_in_cam.x;
	x_end = x_start + sprite.width / sprite.pos_in_cam.x;
	bot = -(sprite.pos_in_cam.z - sprite.heigth) * game->display_mode.h / 2 / sprite.pos_in_cam.x + game->line_horiz;
	top = -(sprite.pos_in_cam.z) * game->display_mode.h / 2/ sprite.pos_in_cam.x + game->line_horiz;
	
	if (x_start < 0)
		x = 0;
	else if (x_start < for_draw.window.x1)
		x = for_draw.window.x1;
	else
		x = x_start;
	while (x < x_end && x < for_draw.window.x2 && x < game->display_mode.w)
	{
		t_window = (int)(for_draw.window.y1t + (for_draw.window.y2t - for_draw.window.y1t) * ((double)x - for_draw.window.x1) / (for_draw.window.x2 - for_draw.window.x1));
		b_window = (int)(for_draw.window.y1b + (for_draw.window.y2b - for_draw.window.y1b) * ((double)x - for_draw.window.x1) / (for_draw.window.x2 - for_draw.window.x1));
		new_x = (double)(x - x_start) / (x_end - x_start) * sprite.texture->w;
		if (top < 0)
			y = 0;
		else if (top < t_window)
			y = t_window;
		else
			y = top;
		while (y < bot && y < b_window && game->display_mode.h)
		{
			new_y = (double)(y - top) / (bot - top) * sprite.texture->h;
			if (new_y >= 0 && new_y < sprite.texture->h && new_x >= 0 && new_x < sprite.texture->w)
			{
				color = ((int*)sprite.texture->pixels)[new_y * sprite.texture->w + new_x];
				((int*)game->screen->pixels)[y * game->display_mode.w + x] = color;
			}
			y++;
		}
		x++;
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
			player_move(game, &loop);
			SDL_WarpMouseInWindow(game->window, game->pre_calc.dispmodw2, game->pre_calc.dispmodh2);
			get_pos_z(&game->player, game->sectors);
			draw_3d_wall(game);
			draw_hands(game->screen, game->gif, game->pre_calc);
			draw_player_icon(game->screen, game->hud.face[2]);
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
