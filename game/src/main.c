/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:38:27 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/11/09 17:07:47 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void	draw_3d_wall(t_game *game)
{
	t_draw	for_draw;

	game->sprite_wall = NULL;
	game->cross_flag = NULL;
	for_draw.fov_left.x = 5;
	for_draw.fov_left.y = 5;
	for_draw.fov_right.x = 5;
	for_draw.fov_right.y = -5;
	for_draw.window.x1 = 0;
	for_draw.window.x2 = game->screen->w;
	for_draw.window.y1b = game->screen->h;
	for_draw.window.y1t = 0;
	for_draw.window.y2b = game->screen->h;
	for_draw.window.y2t = 0;
	for_draw.last_sector = -2;
	for_draw.curr_sector = game->player.curr_sector;
	give_points_cam(game->points_cam, game->points, &game->player,
		game->count_points);
	give_sprites_cam(game);
	draw_sector(game, for_draw);
	draw_minimap(game);
	if (game->sprite_wall != NULL)
		printf("Find a picture!!\n");
}

static void	gif_loop(t_gif *gif, t_keystate *keystate, int *k)
{
	if (keystate->mouse_l == 1)
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

void		check_rifle_state(t_game *game)
{
	if (game->rifle_state != 1)
	{
		if (fabs(game->rifle_angle - game->player.angle) >
			game->pre_calc.pi_mult_2)
			game->rifle_state = 1;
	}
}

static void	start_game(t_game *game, int *loop, int *k)
{
	check_rifle_state(game);
	player_hooks(game, loop);
	SDL_WarpMouseInWindow(game->window,
	game->pre_calc.screen_w_div_2, game->pre_calc.screen_h_div_2);
	get_pos_z(&game->player, game->sectors);
	draw_skybox(game);
	draw_3d_wall(game);
	draw_hud(game);
	gif_loop(game->gif, &game->keystate, k);
	client(game);
}

int			main(void)
{
	t_game	*game;
	int		loop;
	int		k;

	game = create_struct();
	loop = 1;
	k = -3;
	while (loop)
	{
		if (game->menu_status.multi == 1)
			multiplayer_menu_render(game, &loop);
		if (game->menu_status.start == 1)
			start_menu_render(game, &loop);
		if (game->menu_status.tab == 1)
			tab_menu_render(game, &loop);
		if (game->menu_status.main == 1)
			start_game(game, &loop, &k);
		put_fps(game->screen, game->hud, &game->time);
		SDL_UpdateWindowSurface(game->window);
	}
	close(game->socket_struct.sockfd);
	free_sdl(game);
	return (0);
}
