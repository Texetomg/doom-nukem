/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:38:27 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/03/29 16:58:59 by thorker          ###   ########.fr       */
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

vec2			*give_points_cam(game)
{
	vec		*point_cam;
	int		i;

	i = 0;
	while (i < game->count_points)
	{
		(point_cam + i)->x = ((game->points + i)->y - game->player.pos.y) * sin(game->player.pos.angle) + ((game->points + i)->x - game->player.pos.x) * cos(game->player.pos.angle);
		(point_cam + i)->y = ((game->points + i)->y - game->player.pos.y) * cos(game->player.pos.angle) - ((game->points + i)->x - game->player.pos.x) * sin(game->player.pos.angle);
		i++;
	}
	return (point_cam);
}

void	draw_sector(t_game *game, int curr_sector, vec2 fov_left, vec2 fov_right)
{

}

static void	draw_3d_wall(t_game *game)
{
	vec2	fov_left;
	vec2	fov_right;
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
	
	fov_left.x = 8.66;
	fov_left.y = 5;
	fov_rigth.x = 8.66;
	fov_right.y = -5;
	give_point_cam(game);
	draw_sector(game, game->player.curr_sector, fov_left, fov_right);
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
	game = create_struct();
	loop = 1;
	while (loop)
	{
		player_move(game, &loop);
		SDL_FillRect(game->screen, 0, 0);
		draw_3d_wall(game, *(cam_wall + i));
		//put_fps(fps);
		draw_minimap(game, cam_wall);
		SDL_UpdateWindowSurface(game->window);
	}
	SDL_DestroyWindow(game->window);
	SDL_Quit();
	return (0);
}
