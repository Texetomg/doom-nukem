/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thorker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 16:12:49 by thorker           #+#    #+#             */
/*   Updated: 2019/04/23 16:55:21 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"
/*
 * Отрисовывает потолок
 */
void    draw_ceil(t_game *game, t_draw for_draw, double dz)
{
    int i;
    int k;
    vec3 first;
    vec3 second;
    int yt_window;
    int yt_wall;
    int color;
    double a;
    double x;
    double y;
    vec3 first_left;
    vec3 first_right;
    vec3 second_left;
    vec3 second_right;
    
    i = (int)for_draw.wall.x1;
    if (i < 0)
        i = 0;
    second_left = get_ceil(game, for_draw.wall.x1, for_draw.wall.y1t, dz);
    first_left = get_ceil(game, for_draw.window.x1, for_draw.window.y1t, dz);
    second_right = get_ceil(game, for_draw.wall.x2, for_draw.wall.y2t, dz);
    first_right = get_ceil(game, for_draw.window.x2, for_draw.window.y2t, dz);
    while (i < for_draw.wall.x2 && i < game->display_mode.w)
    {
        a = (i - for_draw.window.x1) / (for_draw.window.x2 - for_draw.window.x1);
		first.x = ((1 - a) * first_left.x / first_left.z + a * first_right.x / first_right.z) / ((1 - a) / first_left.z + a / first_right.z);
		first.y = ((1 - a) * first_left.y / first_left.z + a * first_right.y / first_right.z) / ((1 - a) / first_left.z + a / first_right.z);
		first.z = 1 / ((1 - a) / first_left.z + a / first_right.z);
        a = (i - for_draw.wall.x1) / (for_draw.wall.x2 - for_draw.wall.x1);
		second.x = ((1 - a) * second_left.x / second_left.z + a * second_right.x / second_right.z) / ((1 - a) / second_left.z + a / second_right.z);
		second.y = ((1 - a) * second_left.y / second_left.z + a * second_right.y / second_right.z) / ((1 - a) / second_left.z + a / second_right.z);
        second.z = 1 / ((1 - a) / second_left.z + a / second_right.z);
        yt_wall = (int)(for_draw.wall.y1t + (for_draw.wall.y2t - for_draw.wall.y1t) * (i - for_draw.wall.x1) / (for_draw.wall.x2 - for_draw.wall.x1));
        yt_window = (int)(for_draw.window.y1t + (for_draw.window.y2t - for_draw.window.y1t) * (i - for_draw.window.x1) / (for_draw.window.x2 - for_draw.window.x1));
        if (yt_window < 0)
            k = 0;
        else
            k = yt_window;
        while (k < yt_wall && k < game->display_mode.h / 2)
        {
            a = (double)(k - yt_window) / (yt_wall - yt_window);
            x = ((1 - a) * first.x / first.z + a * second.x / second.z) / ((1 - a) / first.z + a / second.z);
            if (x < 0)
                x = (x - (int)x + 1) * game->texture->w;
            else
                x = (x - (int)x) * game->texture->w;
            y = ((1 - a) * first.y / first.z + a * second.y / second.z) / ((1 - a) / first.z + a / second.z);
            if (y < 0)
                y = (y - (int)y + 1) * game->texture->h;
            else
                y = (y - (int)y) * game->texture->h;
            if (x > 0 && x < game->texture->w && y > 0 && y < game->texture->h)
            {
                color = ((int*)game->texture->pixels)[((int)y) * game->texture->w + ((int)x)];
                ((int*)game->screen->pixels)[k * game->display_mode.w + i] = color;
            }
            k++;
        }
        i++;
    }
}
/*
 * Отрисовывает пол
 */
void    draw_floor(t_game *game, t_draw for_draw, double dz)
{
    int i;
    int k;
    vec3 first;
    vec3 second;
    int yb_window;
    int yb_wall;
    int color;
    double a;
    double x;
    double y;
    vec3 first_left;
    vec3 first_right;
    vec3 second_left;
    vec3 second_right;
    
    i = (int)for_draw.wall.x1;
    if (i < 0)
        i = 0;
    first_left = get_floor(game, for_draw.wall.x1, for_draw.wall.y1b, dz);
    second_left = get_floor(game, for_draw.window.x1, for_draw.window.y1b, dz);
    first_right = get_floor(game, for_draw.wall.x2, for_draw.wall.y2b, dz);
    second_right = get_floor(game, for_draw.window.x2, for_draw.window.y2b, dz);
    while (i < for_draw.wall.x2 && i < game->display_mode.w)
    {
        a = (i - for_draw.wall.x1) / (for_draw.wall.x2 - for_draw.wall.x1);
        first.x = ((1 - a) * first_left.x / first_left.z + a * first_right.x / first_right.z) / ((1 - a) / first_left.z + a / first_right.z);
        first.y = ((1 - a) * first_left.y / first_left.z + a * first_right.y / first_right.z) / ((1 - a) / first_left.z + a / first_right.z);
        first.z = 1 / ((1 - a) / first_left.z + a / first_right.z);
        a = (i - for_draw.window.x1) / (for_draw.window.x2 - for_draw.window.x1);
        second.x = ((1 - a) * second_left.x / second_left.z + a * second_right.x / second_right.z) / ((1 - a) / second_left.z + a / second_right.z);
        second.y = ((1 - a) * second_left.y / second_left.z + a * second_right.y / second_right.z) / ((1 - a) / second_left.z + a / second_right.z);
        second.z = 1 / ((1 - a) / second_left.z + a / second_right.z);
        yb_wall = (int)(for_draw.wall.y1b + (for_draw.wall.y2b - for_draw.wall.y1b) * (i - for_draw.wall.x1) / (for_draw.wall.x2 - for_draw.wall.x1));
        yb_window = (int)(for_draw.window.y1b + (for_draw.window.y2b - for_draw.window.y1b) * (i - for_draw.window.x1) / (for_draw.window.x2 - for_draw.window.x1));
        if (yb_wall < game->display_mode.h / 2)
            k = game->display_mode.h / 2;
        else
            k = yb_wall;
        while (k < yb_window && k < game->display_mode.h)
        {
            a = (double)(k - yb_wall) / (yb_window - yb_wall);
            x = ((1 - a) * first.x / first.z + a * second.x / second.z) / ((1 - a) / first.z + a / second.z);
            if (x < 0)
                x = (x - (int)x + 1) * game->texture->w;
            else
                x = (x - (int)x) * game->texture->w;
            y = ((1 - a) * first.y / first.z + a * second.y / second.z) / ((1 - a) / first.z + a / second.z);
            if (y < 0)
                y = (y - (int)y + 1) * game->texture->h;
            else
                y = (y - (int)y) * game->texture->h;
            if (x >= 0 && x < game->texture->w && y >= 0 && y < game->texture->h)
            {
                color = ((int*)game->texture->pixels)[((int)y) * game->texture->w + ((int)x)];
                ((int*)game->screen->pixels)[k * game->display_mode.w + i] = color;
            }
            k++;
        }
        i++;
    }
}

//отрисовывает стену
static void    draw_wall(t_game *game,
                         SDL_DisplayMode display_mode,
                         SDL_Surface *texture,
                         t_draw for_draw,
                         SDL_Surface *screen,
                         double x1,
                         double x2,
                         double y1,
                         double y2)
{
    int i;
    int k;
    int yb_wall;
    int yt_wall;
    int color;
    int x;
    int y;
    double a;
    
    i = (int)for_draw.wall.x1;
    if (i < 0)
        i = 0;
    while (i < for_draw.wall.x2 && i < display_mode.w)
    {
        yt_wall = (int)(for_draw.wall.y1t + (for_draw.wall.y2t - for_draw.wall.y1t) * (i - for_draw.wall.x1) / (for_draw.wall.x2 - for_draw.wall.x1));
        yb_wall = (int)(for_draw.wall.y1b + (for_draw.wall.y2b - for_draw.wall.y1b) * (i - for_draw.wall.x1) / (for_draw.wall.x2 - for_draw.wall.x1));
        if (yt_wall < 0)
            k = 0;
        else
            k = yt_wall;
		a = (double)(i - (int)for_draw.wall.x1) / ((int)for_draw.wall.x2 - (int)for_draw.wall.x1);
		x = ((1 - a) * x1 / y1 + a * x2 / y2) / ((1 - a) / y1 + a / y2) * texture->w;
        while (k < yb_wall && k < game->display_mode.h)
        {
            y = (double)(k - yt_wall) / (yb_wall - yt_wall) * texture->h;
            if (x >= 0 && x < game->texture->w && y >= 0 && y < game->texture->h)
                    color = ((int*)texture->pixels)[y * texture->w + x];
            ((int*)screen->pixels)[k * display_mode.w + i] = color;
            k++;
        }
        i++;
    }
}

//отрисовывет промежутки между потолком/полом и сектором. И пол и потолок портала.
static void    pre_draw_sector(SDL_Surface *screen,
                               SDL_DisplayMode display_mode,
                               t_draw for_draw)
{
    int i;
    int k;
    double yb_wall;
    double yt_wall;
    double yb_window;
    double yt_window;
    int color;
    
    i = (int)for_draw.wall.x1;
    if (i < 0)
        i = 0;
    while (i < for_draw.wall.x2 && i < display_mode.w)
    {
        yt_window = for_draw.window.y1t + (for_draw.window.y2t - for_draw.window.y1t) * (i - for_draw.window.x1) / (for_draw.window.x2 - for_draw.window.x1);
        yb_window = for_draw.window.y1b + (for_draw.window.y2b - for_draw.window.y1b) * (i - for_draw.window.x1) / (for_draw.window.x2 - for_draw.window.x1);
        yt_wall = for_draw.wall.y1t + (for_draw.wall.y2t - for_draw.wall.y1t) * (i - for_draw.window.x1) / (for_draw.window.x2 - for_draw.window.x1);
        yb_wall = for_draw.wall.y1b + (for_draw.wall.y2b - for_draw.wall.y1b) * (i - for_draw.window.x1) / (for_draw.window.x2 - for_draw.window.x1);
        if (yt_wall < 0)
            k = 0;
        else
            k = yt_wall;
        while (k < yb_wall && k < display_mode.h)
        {
            if (k < yt_window || k > yb_window)
            {
                color = COLOR_BETW;
                ((int*)screen->pixels)[k * display_mode.w + i] = color;
            }
            k++;
        }
        i++;
    }
}


//рекурсивная функция, которая отрисовывает сектор;
void    draw_sector(t_game *game,
                    t_gif *gif,
                    SDL_Surface *texture,
                    SDL_Surface *screen,
                    t_player *player,
                    SDL_DisplayMode display_mode,
                    t_sector *sectors,
                    vec2 *points_cam,
                    t_draw for_draw)
{
    int i;
    t_draw    for_next_draw;
    vec2    first_point;
    vec2    second_point;
    double yscale1;
    double yscale2;
    double yceil;
    double yfloor;
    double    y2ceil;
    double    y2floor;
    double x1, x2;
    double x1a, x2a;
    double y1, y2;
    i = 0;
    while (i < (sectors + for_draw.curr_sector)->count_wall)
    {
        first_point = *(points_cam + *((sectors + for_draw.curr_sector)->index_points + i));
        if (i == (sectors + for_draw.curr_sector)->count_wall - 1)
            second_point = *(points_cam + *((sectors + for_draw.curr_sector)->index_points));
        else
            second_point = *(points_cam + *((sectors + for_draw.curr_sector)->index_points + i + 1));
        if (first_point.x < 0 && second_point.x < 0)
        {
            i++;
            continue;
        }
        x1 = -first_point.y;
        x2 = -second_point.y;
        if (intersection(&first_point, &second_point, for_draw.fov_left, for_draw.fov_right) > 0)
        {
            x1a = (-first_point.y - x1) / (x2 - x1);
            x2a = (-second_point.y - x1) / (x2 - x1);
            y1 = first_point.x;
            y2 = second_point.x;
            yceil = (sectors + for_draw.curr_sector)->ceil - player->pos.z;
            yfloor = (sectors + for_draw.curr_sector)->floor - player->pos.z;
            yscale1 =  display_mode.h / 2 / first_point.x;
            yscale2 =  display_mode.h / 2 / second_point.x;
            for_draw.wall.x1 = -first_point.y * (display_mode.w / 2) / first_point.x + display_mode.w / 2;
            for_draw.wall.x2 = -second_point.y * (display_mode.w / 2) / second_point.x + display_mode.w / 2;
            for_draw.wall.y2t = -yscale2 * yceil + display_mode.h / 2;
            for_draw.wall.y1t = -yscale1 * yceil + display_mode.h / 2;
            for_draw.wall.y2b = -yscale2 * yfloor + display_mode.h / 2;
            for_draw.wall.y1b = -yscale1 * yfloor + display_mode.h / 2;
            if (*((sectors + for_draw.curr_sector)->neighbors + i) >= 0)
            {
                if (*((sectors + for_draw.curr_sector)->neighbors + i) != for_draw.last_sector)
                {
                    for_next_draw.wall = for_draw.wall;
                    y2ceil = (sectors + *((sectors + for_draw.curr_sector)->neighbors + i))->ceil - player->pos.z;
                    y2floor = (sectors + *((sectors + for_draw.curr_sector)->neighbors + i))->floor - player->pos.z;
                    for_next_draw.window.y1t = -yscale1 * y2ceil + display_mode.h / 2;
                    for_next_draw.window.y1b = -yscale1 * y2floor + display_mode.h / 2;
                    for_next_draw.window.y2t = -yscale2 * y2ceil + display_mode.h / 2;
                    for_next_draw.window.y2b = -yscale2 * y2floor + display_mode.h / 2;
                    for_next_draw.window.x1 = for_next_draw.wall.x1;
                    for_next_draw.window.x2 = for_next_draw.wall.x2;
                    for_next_draw.curr_sector = *((sectors + for_draw.curr_sector)->neighbors + i);
                    for_next_draw.last_sector = for_draw.curr_sector;
                    for_next_draw.fov_left = first_point;
                    for_next_draw.fov_right = second_point;
                    draw_sector(game, gif, texture, screen, player, display_mode, sectors, points_cam, for_next_draw);
                    pre_draw_sector(screen, display_mode, for_next_draw);
                }
            }
            else
                draw_wall(game, display_mode, texture, for_draw, screen, x1a, x2a, y1, y2);
            draw_floor(game, for_draw, -yfloor);
            draw_ceil(game, for_draw, yceil);
        }
        i++;
    }
}
