/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:38:27 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/03/29 11:17:44 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

void		change_wall(t_wall *cam_wall)
{
	cam_wall->pos1.x = (5 + cam_wall->pos1.x) * 20;
	cam_wall->pos2.x = (5 + cam_wall->pos2.x) * 20;
	cam_wall->pos1.y = (5 - cam_wall->pos1.y) * 20;
	cam_wall->pos2.y = (5 - cam_wall->pos2.y) * 20;
}
static void	change_world_in_cam(t_wall *world_wall, t_wall *cam_wall, t_player player)
{
	cam_wall->pos1.x = (world_wall->pos1.y - player.pos.y) * sin(player.angle) + (world_wall->pos1.x - player.pos.x) * cos(player.angle);
	cam_wall->pos2.x = (world_wall->pos2.y - player.pos.y) * sin(player.angle) + (world_wall->pos2.x - player.pos.x) * cos(player.angle);
	cam_wall->pos1.y = (world_wall->pos1.y - player.pos.y) * cos(player.angle) - (world_wall->pos1.x - player.pos.x) * sin(player.angle);
	cam_wall->pos2.y = (world_wall->pos2.y - player.pos.y) * cos(player.angle) - (world_wall->pos2.x - player.pos.x) * sin(player.angle);
	cam_wall->color = world_wall->color;
}

static void	draw_3d_wall(t_game *game, t_wall wall)
{
	double x1a;
	double y1t;
	double y1b;
	double x2a;
	double y2t;
	double y2b;
	int i;
	int k;
	double yt;
	double yb;
	double for_swap;

	if (wall.pos1.x < 0 && wall.pos2.x < 0)
		return ;
	if (intersection(&wall.pos1.x, &wall.pos1.y, &wall.pos2.x, &wall.pos2.y) != 0)
	{
		x1a = -wall.pos1.y * 1400 / wall.pos1.x + game->display_mode.w / 2;
		y1t = -500 / wall.pos1.x + game->display_mode.h / 2;
		y1b = 500 / wall.pos1.x + game->display_mode.h / 2;
		x2a = -wall.pos2.y * 1400 / wall.pos2.x + game->display_mode.w / 2;
		y2t = -500 / wall.pos2.x + game->display_mode.h / 2;
		y2b = 500 / wall.pos2.x + game->display_mode.h / 2;
		if (x1a > x2a)
		{
			for_swap = x1a;
			x1a = x2a;
			x2a = for_swap;
			for_swap = y1b;
			y1b = y2b;
			y2b = for_swap;
			for_swap = y1t;
			y1t = y2t;
			y2t = for_swap;
		}
		
		k = (int)x1a;
		while (k < x2a)
		{
			yt = y1t + (y2t - y1t) * (k - x1a) / (x2a - x1a);
			yb = y1b + (y2b - y1b) * (k - x1a) / (x2a - x1a);
			i = (int)yt;
			while (i < yb)
			{
				if (i >= 0 && i < game->display_mode.h && k >= 0 && k < game->display_mode.w)
					((int*)game->screen->pixels)[i * game->display_mode.w + k] = wall.color;
				i++;
			}
			k++;
		}
	}
}

int 		main(void)
{
	t_game		*game;
	int loop;
	int i;
	t_wall	*world_wall;
	t_wall	*cam_wall;
	t_fps	*fps;
	fps = (t_fps*)malloc(sizeof(t_fps));
	world_wall = (t_wall*)malloc(sizeof(t_wall) * 4);
	cam_wall = (t_wall*)malloc(sizeof(t_wall) * 4);
	world_wall->pos1.y = 2;
	world_wall->pos1.x = 0;
	world_wall->pos2.y = -1;
	world_wall->pos2.x = 2;
	world_wall->color = 0xAA0000;
	(world_wall + 1)->pos1.y = -1;
	(world_wall + 1)->pos1.x = 2;
	(world_wall + 1)->pos2.y = -3;
	(world_wall + 1)->pos2.x = -2;
	(world_wall + 1)->color = 0xAA00;
	(world_wall + 2)->pos1.y = -3;
	(world_wall + 2)->pos1.x = -2;
	(world_wall + 2)->pos2.y = 2;
	(world_wall + 2)->pos2.x = 0;
	(world_wall + 2)->color = 0xAA;
	game = create_struct();
	loop = 1;
	while (loop)
	{
		player_move(game, &loop);
		SDL_FillRect(game->screen, 0, 0);
		i = -1;
		while (++i < 3)
		{
			change_world_in_cam(world_wall + i, cam_wall + i, game->player);
			draw_3d_wall(game, *(cam_wall + i));
		}
		//put_fps(fps);
		i = 0;
		draw_minimap(game, cam_wall);
		SDL_UpdateWindowSurface(game->window);
	}
	SDL_DestroyWindow(game->window);
	SDL_Quit();
	return (0);
}
