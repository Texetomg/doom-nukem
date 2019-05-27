/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 17:54:54 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/05/27 15:29:20 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

int				inside_sector(t_game *game, double x, double y, t_sector sector)
{
	vec2	f_point;
	vec2	s_point;
	int		i;

	i = 0;
	while (i < sector.count_wall)
	{
		f_point = *(game->points + *(sector.index_points + i));
		if (i == sector.count_wall - 1)
			s_point = *(game->points + *(sector.index_points));
		else
			s_point = *(game->points + *(sector.index_points + i + 1));

		s_point.x = s_point.x - f_point.x;
		s_point.y = s_point.y - f_point.y;
		f_point.x = x - f_point.x;
		f_point.y = y - f_point.y;
		if (cross_product(f_point, s_point) < 0)
			return (0);
		i++;
	}
	return (1);
}

//поварачивает точки в систему координат игрока
void            give_points_cam(vec2 *points_cam, vec2 *points, t_player *player, int count_points)
{
    int        i;
    //ft_putendl("give_point_cam");
    i = 0;
    while (i < count_points)
    {
        (points_cam + i)->x = ((points + i)->y - player->pos.y) * sin(player->angle) + ((points + i)->x - player->pos.x) * cos(player->angle);
        (points_cam + i)->y = ((points + i)->y - player->pos.y) * cos(player->angle) - ((points + i)->x - player->pos.x) * sin(player->angle);
        i++;
    }
}

void			give_sprites_cam(t_game *game)
{
	int i;
	double angle;
	double tangens;
	double x;
	double y;
	i = 0;
	while (i < game->count_sprites)
	{
		(game->sprites + i)->pos_in_cam.x = ((game->sprites + i)->pos.y - game->player.pos.y) * sin(game->player.angle) + ((game->sprites + i)->pos.x - game->player.pos.x) * cos(game->player.angle);
		(game->sprites + i)->pos_in_cam.y = ((game->sprites + i)->pos.y - game->player.pos.y) * cos(game->player.angle) - ((game->sprites + i)->pos.x - game->player.pos.x) * sin(game->player.angle);
		(game->sprites + i)->pos_in_cam.z = (game->sprites + i)->pos.z - game->player.pos.z;
		y = -(game->sprites + i)->pos.y + game->player.pos.y;
		x = -(game->sprites + i)->pos.x + game->player.pos.x;
		tangens = x / y;
		angle = atan(tangens);
		if (x < 0)
			angle = angle - 3.14;
		(game->sprites + i)->angle_in_cam = angle;
		angle = angle - (game->sprites + i)->angle;
		if (angle < 0)
			angle = angle + 3.14 * 2;
		if (angle > 3.14 * 2)
			angle = angle - 3.14 * 2;
		i++;
	}
}

void    get_pos_z(t_player *player, t_sector *sectors )
{	
    if (player->z_accel > 0)
    {
        if (player->pos.z + player->z_accel  >= (sectors + player->curr_sector)->ceil)
		{
            player->z_accel = 0;
		}
        else
        {
            player->pos.z += player->z_accel;
            player->z_accel -= ACCEL;
        }
        
    }
    else if (player->z_accel == 0)
	{
			if (player->foots > (sectors + player->curr_sector)->floor)
        		player->z_accel -= ACCEL;
	}
    else if (player->z_accel < 0)
    {
        	if (player->foots + player->z_accel < (sectors + player->curr_sector)->floor)
        	{
        	    player->z_accel = 0;
        	    player->pos.z = (sectors + player->curr_sector)->floor + player->b_foots;
        	}
        	else
        	{
        	    player->pos.z += player->z_accel;
        	    player->z_accel -= ACCEL;   
        	}
    }
    player->foots = player->pos.z - 0.5;
    player->knees = player->pos.z - player->b_knees;
}

void    print_text(SDL_Surface *screen, char *text, char *font, int size, SDL_Color color, SDL_Rect dest)
{
	TTF_Font *fnt;
    SDL_Surface *sText;

	if ((fnt = TTF_OpenFont(font, size)) == NULL)
		check_error_n_exit(1,(char*)SDL_GetError());
	if ((sText = TTF_RenderText_Blended(fnt, text, color)) == NULL)
        check_error_n_exit(1,(char*)SDL_GetError());
	SDL_BlitSurface(sText, NULL, screen, &dest);
	SDL_FreeSurface(sText);
	TTF_CloseFont(fnt);
}

void    free_SDL(t_game *game)
{
    Mix_FreeChunk(game->sounds.bang);
	game->sounds.bang = NULL;
	Mix_FreeMusic(game->sounds.music);
	game->sounds.music = NULL;
	Mix_Quit();
	SDL_FreeSurface(game->screen);
	game->screen = NULL;
	SDL_FreeSurface(game->texture);
	game->texture = NULL;
	/*
	while (game->texture_arr[i])
	{
		SDL_FreeSurface(game->texture_arr[i]);
		game->texture_arr[i] = NULL;
		i++;
	}
	i = 0;
	
	while (game->gif->array[i])
	{
		SDL_FreeSurface(game->gif->array[i]);
		game->gif->array[i] = NULL;
		i++;
	}
	*/
    atexit(TTF_Quit);
	SDL_DestroyWindow(game->window);
	game->window = NULL;
	SDL_Quit();
}
