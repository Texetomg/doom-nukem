/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:38:27 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/05/13 15:08:29 by thorker          ###   ########.fr       */
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
				((int*)(screen->pixels))[(int)(y + pre_calc.screenh10065) * screen->w + x + (pre_calc.screenw10045)] = color;
			x++;
		}
		x = 0;
		y++;
	}
}

static void		draw_sprites(t_game *game)
{
	int y;
	int x;
	int		new_x = 0;
	int		new_y = 0;
	int color;
	int bot;
	int top;
	game->sprites.new_pos.x = (game->sprites.pos.y - game->player.pos.y) * sin(game->player.angle) + (game->sprites.pos.x - game->player.pos.x) * cos(game->player.angle);
	game->sprites.new_pos.y = (game->sprites.pos.y - game->player.pos.y) * cos(game->player.angle) - (game->sprites.pos.x - game->player.pos.x) * sin(game->player.angle);
	game->sprites.shift = (-game->sprites.new_pos.y / game->sprites.new_pos.x) * (game->pre_calc.screenw2) + game->pre_calc.screenw2;
	bot = -(0 - game->player.pos.z) * game->display_mode.h / 2 / game->sprites.new_pos.x + game->line_horiz;
	top = -(0.5 - game->player.pos.z) * game->display_mode.h / 2/ game->sprites.new_pos.x + game->line_horiz;
	game->sprites.w = 200 / game->sprites.new_pos.x;
	(y = top) < 0 ? y = 0 : y;
	while (y <= bot && y < game->display_mode.h)
	{
		(x = (game->sprites.shift ) - game->sprites.w / 2) < 0 ? x = 0 : x;
		new_y = (double)(y - top) / (bot - top) * game->sprites.texture->h;
		while (x < (game->sprites.shift) + game->sprites.w / 2 && x < game->display_mode.w)
		{
			new_x = ((double)x - ((game->sprites.shift ) - game->sprites.w / 2)) / (((game->sprites.shift) + game->sprites.w / 2) - ((game->sprites.shift) - game->sprites.w / 2)) * game->sprites.texture->w;
			if (y >= 0 && y < game->screen->h && x >= 0 && x < game->screen->w )
			{
				color = ((int*)(game->sprites.texture->pixels))[game->sprites.texture->w * new_y + new_x];
				((int*)(game->screen->pixels))[(int)(game->screen->w * y + (int)(x))] = color;
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
			player_move(game, &loop);
			SDL_WarpMouseInWindow(game->window, game->pre_calc.dispmodw2, game->pre_calc.dispmodh2);
			get_pos_z(&game->player, game->sectors);
			draw_3d_wall(game);
			draw_sprites(game);
			draw_hands(game->screen, game->gif, game->pre_calc);
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
