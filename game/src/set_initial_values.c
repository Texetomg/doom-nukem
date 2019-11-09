/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_initial_values.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 10:52:01 by ramory-l          #+#    #+#             */
/*   Updated: 2019/11/09 17:16:58 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		set_player(t_game *game)
{
	game->player.jetpack = 0;
	game->player.key = 1;
	game->player.z_accel = 0;
	game->player.foots = (game->sectors + game->player.curr_sector)->floor;
	game->player.knees = game->player.foots + 0.2;
	game->player.pos.z = game->player.foots + 0.5;
	game->player.b_foots = 0.5;
	game->player.b_knees = 0.3;
	game->keystate.back = 0;
	game->keystate.ctrl = 0;
	game->keystate.forward = 0;
	game->keystate.jump = 0;
	game->keystate.left = 0;
	game->keystate.right = 0;
}

static void	set_menu(t_game *game)
{
	game->menu_status.start = 1;
	game->start_menu.strings[0] = "CHOOSE YOUR DESTINY:";
	game->start_menu.strings[1] = "Loli";
	game->start_menu.strings[2] = "Trump";
	game->start_menu.strings[3] = "Doomguy";
	game->start_menu.strings[4] = "Setevaya igra";
	game->start_menu.strings[5] = "Exit";
	game->multi_menu.strings[0] = "Back";
	game->multi_menu.strings[1] = "IP: 192.168.";
	game->start_menu.text_pos = 0;
	game->multi_menu.text_pos = 0;
	game->tab_menu.text_pos = 0;
	game->tab_menu.strings[0] = "Continue";
	game->tab_menu.strings[1] = "New game";
	game->tab_menu.strings[2] = "Exit";
	game->menu_status.tab = 0;
	game->menu_status.main = 0;
	game->menu_status.multi = 0;
}

void		set_color(SDL_Color *color, int r, int g, int b)
{
	color->r = r;
	color->g = g;
	color->b = b;
}

static void	pre_calc_screen(t_pre_calc *pre_calc, SDL_Surface screen)
{
	pre_calc->screen_h_div_2 = screen.h / 2;
	pre_calc->screen_w_div_2 = screen.w / 2;
	pre_calc->screen_w_div_10 = screen.w / 10;
	pre_calc->screen_h_div_10 = screen.h / 10;
	pre_calc->screen_w_div_20 = screen.w / 20;
	pre_calc->screen_h_div_20 = screen.h / 20;
	pre_calc->screen_h_mult_2 = screen.h * 2;
	pre_calc->pi_div_4 = 3.14 / 4;
	pre_calc->pi_mult_2 = 3.14 * 2;
}

void		set_initial_values(t_game *game)
{
	set_player(game);
	set_menu(game);
	set_sprites(game);
	game->points_cam = (t_vec2*)malloc(sizeof(t_vec2) * game->count_points);
	set_color(&game->hud.color, 255, 255, 0);
	game->hud.fps_dest.h = 80;
	game->hud.fps_dest.w = 120;
	game->hud.fps_dest.x = 0;
	game->hud.fps_dest.y = 0;
	game->hud.text_dest.h = 800;
	game->hud.text_dest.w = 800;
	game->hud.text_dest.x = game->screen->w / 8;
	game->hud.text_dest.y = game->screen->h / 8;
	game->line_horiz = 400;
	pre_calc_screen(&game->pre_calc, *game->screen);
	game->rifle_state = 0;
	game->rifle_angle = game->player.angle;
	game->spaw1.x = -1;
	game->spaw1.y = -5;
	game->spaw2.x = 1.5;
	game->spaw2.y = -5.5;
	game->spaw3.x = 0.75;
	game->spaw3.y = -7.5;
}
