/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:38:27 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/10/16 12:55:50 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

//запускает отрисовку всех стен
static void	draw_3d_wall(t_game *game)
{
	t_draw	for_draw;

    game->sprite_wall = NULL;
    game->cross_flag = NULL;
	//ft_putendl("draw_3d_wall");
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

	give_points_cam(game->points_cam, game->points, &game->player, game->count_points);
	give_sprites_cam(game);
	draw_sector(game, for_draw);
	draw_minimap(game);
	if (game->cross_flag != NULL)
	{
		printf("Headshort!!\n");
		printf("Health: %d\n", game->cross_flag->health);
	}
    else
        printf("Looser!!\n");
    if (game->sprite_wall != NULL)
        printf("Find a picture!!\n");
    else
        printf("Don't find!!\n");
}

SDL_Surface		*check_sprite(t_sprite *sprite)
{
	t_angle_sprite *angle_sprite;
	SDL_Surface *texture;

	angle_sprite = sprite->angle_sprite;
	texture = sprite->angle_sprite->texture;
	while (angle_sprite != 0)
	{
		if (sprite->move)
		{
			if (sprite->health <= angle_sprite->up_health && sprite->health > angle_sprite->down_health)
			{
				if (sprite->id == 0)
				{
					texture = angle_sprite->texture2;
					angle_sprite = sprite->angle_sprite;
					while (angle_sprite != 0)
					{
						angle_sprite->texture = texture;
						angle_sprite = angle_sprite->next;
					}
				}
				else
					texture = angle_sprite->texture;
				break;
			}
		}
		else if (sprite->health > 85)
		{
			if (sprite->angle_in_cam >= angle_sprite->start_angle && sprite->angle_in_cam < angle_sprite->end_angle && sprite->health == 100)
			{
				texture = angle_sprite->texture;
				break;
			}
			else
			{
				texture = angle_sprite->texture;
			}
		}
		else
		{
			if (sprite->health <= angle_sprite->up_health && sprite->health > angle_sprite->down_health)
			{
				if (sprite->id == 0)
				{
					texture = angle_sprite->texture2;
					angle_sprite = sprite->angle_sprite;
					while (angle_sprite != 0)
					{
						angle_sprite->texture = texture;
						angle_sprite = angle_sprite->next;
					}
				}
				else
					texture = angle_sprite->texture;
				break;
			}
		}
		angle_sprite = angle_sprite->next;
	}
	return (texture);
}

void		draw_sprites(t_game *game, t_draw for_draw, t_sprite *sprite, double bright)
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
	SDL_Surface *texture;
	int     cross_flag;
	int     cross_x;
	int     cross_y;

	cross_flag = 0;
	texture = check_sprite(sprite);
	x_start = -sprite->pos_in_cam.y * game->pre_calc.screen_w_div_2 / sprite->pos_in_cam.x + game->pre_calc.screen_w_div_2 - sprite->width / 2 / sprite->pos_in_cam.x;
	x_end = x_start + sprite->width / sprite->pos_in_cam.x;
	top = -sprite->pos_in_cam.z * game->pre_calc.screen_h_div_2 / sprite->pos_in_cam.x + game->line_horiz;
    bot = top + sprite->heigth * game->pre_calc.screen_h_div_2 / sprite->pos_in_cam.x;
	if (x_start < 0)
		x = 0;
	else if (x_start < for_draw.window.x1)
		x = for_draw.window.x1;
	else
		x = x_start;
	cross_x = (double)(game->screen->w / 2 - x_start) / (x_end - x_start) * texture->w;
	cross_y = (double)(game->screen->h / 2 - top) / (bot - top) * texture->h;
	if ((cross_x > 0) && (cross_x < texture->w) && (cross_y > 0) && (cross_y < texture->h))
	    if (((int*)texture->pixels)[cross_y * texture->w + cross_x])
        {
            cross_flag = 1;
            game->cross_flag = sprite;
        }

	while (x < x_end && x < for_draw.window.x2 && x < game->screen->w)
	{
		t_window = (int)(for_draw.window.y1t + (for_draw.window.y2t - for_draw.window.y1t) * ((double)x - for_draw.window.x1) / (for_draw.window.x2 - for_draw.window.x1));
		b_window = (int)(for_draw.window.y1b + (for_draw.window.y2b - for_draw.window.y1b) * ((double)x - for_draw.window.x1) / (for_draw.window.x2 - for_draw.window.x1));
		new_x = (double)(x - x_start) / (x_end - x_start) * texture->w;
		if (top < 0)
			y = 0;
		else if (top < t_window)
			y = t_window;
		else
			y = top;
		while (y < bot && y < b_window && y < game->screen->h)
		{
			new_y = (double)(y - top) / (bot - top) * texture->h;
			if (new_y >= 0 && new_y < texture->h && new_x >= 0 && new_x < texture->w)
			{
                color = ((int*)texture->pixels)[new_y * texture->w + new_x];
                if (color != 0)
                {
                    /*if (cross_flag)
                        color = 0xFF0000;*/
                    ((int*)game->screen->pixels)[y * game->screen->w + x] = ft_bright(color, bright);
                }
			}
			y++;
		}
		x++;
	}
}

void			draw_skybox(t_game *game)
{
	double left_border;
	double right_border;
	double a;
	int x;
	int y;
	int x_texture;
	int y_texture;
	int color;
	double top;
	double bot;
	a = fmod(fabs(game->player.angle + game->pre_calc.pi_div_4), game->pre_calc.pi_mult_2);
	if (game->player.angle + game->pre_calc.pi_div_4 < 0)
	{
		left_border = a / (game->pre_calc.pi_mult_2);
	}
	else
		left_border = (game->pre_calc.pi_mult_2 - a) / (game->pre_calc.pi_mult_2);
	a = fmod(fabs(game->player.angle - game->pre_calc.pi_div_4), game->pre_calc.pi_mult_2);
	if (game->player.angle - game->pre_calc.pi_div_4 < 0)
	{
		right_border = a / (game->pre_calc.pi_mult_2);
	}
	else
		right_border = (game->pre_calc.pi_mult_2 - a) / (game->pre_calc.pi_mult_2);
	if (left_border > right_border)
		right_border = right_border + 1;
	x = 0;
	bot = ((double)game->screen->h - game->line_horiz + game->pre_calc.screen_h_div_2 + game->pre_calc.screen_h_div_2) / (game->pre_calc.screen_h_mult_2);
	top = ((double)game->screen->h - game->line_horiz - game->pre_calc.screen_h_div_2 + game->pre_calc.screen_h_div_2) / (game->pre_calc.screen_h_mult_2);
	while (x < game->screen->w)
	{
		a = left_border + (right_border - left_border) * ((double)x / game->screen->w);
		x_texture = (a - (int)a) * game->skybox->w;
		y = 0;
		while ( y < game->screen->h)
		{
			y_texture = (top + (bot - top) * ((double)y / game->screen->h)) * game->skybox->h;
			color = ((int*)game->skybox->pixels)[y_texture * game->skybox->w + x_texture];
			((int*)game->screen->pixels)[y * game->screen->w + x] = color;
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
void		check_rifle_state(t_game *game)
{
	if (game->rifle_state != 1)
	{
		if (fabs(game->rifle_angle - game->player.angle) > game->pre_calc.pi_mult_2)
			game->rifle_state = 1;
	}
}

int			main(void)
{
	t_game		*game;
	int loop;
	int k;
	/* system("make unzip"); */
	game = create_struct();
	loop = 1;		
	k = -3;
	while (loop)
	{
		if(game->menu_status.multi == 1)
		{
			/*if( Mix_PlayingMusic() == 0 )
				Mix_PlayMusic(game->sounds.music, -1);*/
			multiplayer_menu_render(game, &loop);
		}
		if (game->menu_status.start == 1)
		{
			/*if( Mix_PlayingMusic() == 0 )
				Mix_PlayMusic(game->start_menu.music, -1);
				*/
			start_menu_render(game, &loop);
		}
		if(game->menu_status.tab == 1)
		{
			/*if( Mix_PlayingMusic() == 0 )
				Mix_PlayMusic(game->sounds.music, -1);*/
			tab_menu_render(game, &loop);
		}
		if (game->menu_status.main == 1)
		{	
			/*if( Mix_PlayingMusic() == 0 )
				Mix_PlayMusic(game->sounds.music, -1);*/
			check_rifle_state(game);/* усиление ружья при повороте на 360 */
			player_move(game, &loop);
			SDL_WarpMouseInWindow(game->window, game->pre_calc.screen_w_div_2, game->pre_calc.screen_h_div_2);/* центровка мыши */
			get_pos_z(&game->player, game->sectors);/* определение коллизий м полом и потолком */
			draw_skybox(game);
			draw_3d_wall(game);
			draw_hud(game);
			/* запуск гифок */
			gif_loop(game->gif, &game->keystate, &k);/* отвечает за анимировнные стены */
			client(game);/* отвечает за сетевую игру */
		}
		put_fps(game->screen, game->hud, &game->time);
		SDL_UpdateWindowSurface(game->window);
	}
	/* закрытие sdl */
	/* system("make zip"); */
	close(game->socket_struct.sockfd);
	free_SDL(game);
	return (0);
}
