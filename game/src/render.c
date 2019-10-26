/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 16:12:49 by thorker           #+#    #+#             */
/*   Updated: 2019/10/26 03:56:10 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int	ft_bright(int color, double bright)
{
	int r;
	int g;
	int b;
	int new_color;

	r = (color & 0xFF0000) >> 16;
	r = r * bright;
	g = (color & 0xFF00) >> 8;
	g = g * bright;
	b = (color & 0xFF);
	b = b * bright;
	new_color = r * 256 * 256 + g * 256 + b;
	return (new_color);
}


/*
 * Отрисовывает пол
 */
void    draw_floor(t_game *game, t_draw for_draw, double dz, double bright)
{
    int i;
    int k;
    t_vec3 first;
    t_vec3 second;
    int yb_window;
    int yb_wall;
    int color;
    double a;
    double x;
    double y;
    t_vec3 first_left;
    t_vec3 first_right;
    t_vec3 second_left;
    t_vec3 second_right;
    
    i = (int)for_draw.wall.x1;
    if (i < 0)
        i = 0;
    first_left = get_floor(game, for_draw.wall.x1, for_draw.wall.y1b, dz);
    second_left = get_floor(game, for_draw.window.x1, for_draw.window.y1b, dz);
    first_right = get_floor(game, for_draw.wall.x2, for_draw.wall.y2b, dz);
    second_right = get_floor(game, for_draw.window.x2, for_draw.window.y2b, dz);
    while (i < for_draw.wall.x2 && i < game->screen->w)
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
        if (yb_wall < game->line_horiz)
            k = game->line_horiz;
        else
            k = yb_wall;
        while (k < yb_window && k < game->screen->h)
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
                ((int*)game->screen->pixels)[k * game->screen->w + i] = ft_bright(color, bright);
            }
            k++;
        }
        i++;
    }
}

//отрисовывает стену
static void    draw_wall(t_game *game,
                         t_draw for_draw,
                         double x1,
                         double x2,
                         double y1,
                         double y2,
						 double ceil,
						 double floor,
						 double bright,
						 double perc1,
						 double perc2,
						 t_sprite_wall *sprite_wall)
{
    int i;
    int k;
    int yb_wall;
    int yt_wall;
    int color;
    double x;
    double y;
    double a;
	int right_border;
	int top_border;
	int bot_border;
	int left_border;
	double new_y1, new_y2;
	double left_img, right_img;
	int     green_flag;

	green_flag = 0;
    //game->cross_flag = NULL;
    //game->sprite_wall = NULL;
    i = (int)for_draw.wall.x1;
    if (i < 0)
        i = 0;
    while (i < for_draw.wall.x2 && i < game->screen->w)
    {
        yt_wall = (int)(for_draw.wall.y1t + (for_draw.wall.y2t - for_draw.wall.y1t) * (i - for_draw.wall.x1) / (for_draw.wall.x2 - for_draw.wall.x1));
        yb_wall = (int)(for_draw.wall.y1b + (for_draw.wall.y2b - for_draw.wall.y1b) * (i - for_draw.wall.x1) / (for_draw.wall.x2 - for_draw.wall.x1));
        if (yt_wall < 0)
            k = 0;
        else
            k = yt_wall;
		a = (double)(i - (int)for_draw.wall.x1) / ((int)for_draw.wall.x2 - (int)for_draw.wall.x1);
		x = ((1 - a) * x1 / y1 + a * x2 / y2) /((1 - a) / y1 + a / y2);
		if (x > 0)
			x = (x - (int)x) * game->texture->w;
		else
			x = (x - (int)x + 1) * game->texture->w;
        while (k < yb_wall && k < game->screen->h)
        {
			a = (double)(k - (int)yt_wall) / ((int)yb_wall - (int)yt_wall);
           	y = -((1 - a) * ceil + a * floor);
			if (y > 0)
				y = (y - (int)y) * game->texture->h;
			else
				y = (y - (int)y + 1) * game->texture->h;
			if (x >= 0 && x < game->texture->w && y >= 0 && y < game->texture->h)
			{
				color = (game->texture->pixels)[(int)y * game->texture->w + (int)x];
				((int*)game->screen->pixels)[k * game->screen->w + i] = ft_bright(color, bright);
			}
            k++;
        }
        i++;
    }
    //######################################################################################################
	if (sprite_wall == 0)
		return ;
	if (sprite_wall->left < perc1)
	{
		a = 0;
		left_img = (perc1 - sprite_wall->left) / (sprite_wall->right - sprite_wall->left);
	}
	else
	{
		a = (sprite_wall->left - perc1) / (perc2 - perc1);
		left_img = 0;
	}
	x = ((1 - a) * x1 + a * x2);
	a = (x / y1 - x1 / y1) / (x2 / y2 - x / y2 + x / y1 - x1 / y1);
	new_y1 = 1 / ((1 - a) / y1 + a / y2);
	left_border = for_draw.wall.x1 + (for_draw.wall.x2 - for_draw.wall.x1) * a;
	if (sprite_wall->right > perc2)
	{
		a = 1;
		right_img = (perc2 - sprite_wall->left) / (sprite_wall->right - sprite_wall->left);
	}
	else
	{
		a = (sprite_wall->right - perc1) / (perc2 - perc1);
		right_img = 1;
	}
	x = ((1 - a) * x1 + a * x2);
	a = (x / y1 - x1 / y1) / (x2 / y2 - x / y2 + x / y1 - x1 / y1);
	new_y2 = 1 / ((1 - a) / y1 + a / y2);
	right_border = for_draw.wall.x1 + (for_draw.wall.x2 - for_draw.wall.x1) * a;
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    i = game->screen->w / 2;
    k = game->screen->h / 2;
    yt_wall = (int)(for_draw.wall.y1t + (for_draw.wall.y2t - for_draw.wall.y1t) * (i - for_draw.wall.x1) / (for_draw.wall.x2 - for_draw.wall.x1));
    yb_wall = (int)(for_draw.wall.y1b + (for_draw.wall.y2b - for_draw.wall.y1b) * (i - for_draw.wall.x1) / (for_draw.wall.x2 - for_draw.wall.x1));
    top_border = yt_wall + (yb_wall - yt_wall) * sprite_wall->top;
    bot_border = yt_wall + (yb_wall - yt_wall) * sprite_wall->bot;
    a = ((double)i - left_border) / (right_border - left_border);
    x = (((1 - a) * left_img / new_y1 + a * right_img / new_y2 )/ ((1 - a) / new_y1 + a / new_y2) )* sprite_wall->texture->w;
    y = ((double)k - top_border) / (bot_border - top_border) * sprite_wall->texture->h;
    if (x >= 0 && x < sprite_wall->texture->w && y >= 0 && y < sprite_wall->texture->h)
    {
        green_flag = 1;
        game->sprite_wall = sprite_wall;
    }
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (left_border < 0)
		i = 0;
	else if ( left_border < for_draw.wall.x1)
		i = for_draw.wall.x1;
	else
		i = left_border;
	while (i < right_border && i < game->screen->w && i < for_draw.wall.x2)
	{
		yt_wall = (int)(for_draw.wall.y1t + (for_draw.wall.y2t - for_draw.wall.y1t) * (i - for_draw.wall.x1) / (for_draw.wall.x2 - for_draw.wall.x1));
		yb_wall = (int)(for_draw.wall.y1b + (for_draw.wall.y2b - for_draw.wall.y1b) * (i - for_draw.wall.x1) / (for_draw.wall.x2 - for_draw.wall.x1));
		top_border = yt_wall + (yb_wall - yt_wall) * sprite_wall->top;
		bot_border = yt_wall + (yb_wall - yt_wall) * sprite_wall->bot;
		if (top_border < 0)
			k = 0;
		else
			k = top_border;
		a = ((double)i - left_border) / (right_border - left_border);
		x = (((1 - a) * left_img / new_y1 + a * right_img / new_y2 )/ ((1 - a) / new_y1 + a / new_y2) )* sprite_wall->texture->w;
		while (k < bot_border && k < game->screen->h)
		{
			y = ((double)k - top_border) / (bot_border - top_border) * sprite_wall->texture->h;
			if (x >= 0 && x < sprite_wall->texture->w && y >= 0 && y < sprite_wall->texture->h)
			{
				color = ((int*)sprite_wall->texture->pixels)[(int)y * sprite_wall->texture->w + (int)x];
				/*if (green_flag)
				    color = 0xFF00;*/
				((int*)game->screen->pixels)[k * game->screen->w + i] = ft_bright(color, bright);
			}
			k++;
		}
		i++;
	}
}

//отрисовывет промежутки между потолком/полом и сектором. И пол и потолок портала.
static void    pre_draw_sector(SDL_Surface *screen,
                               SDL_DisplayMode display_mode,
                               t_draw for_draw,
							   double bright,
							   int grid,
							   t_game *game,
							   double x1,
							   double x2,
							   double y1,
							   double y2,
							   double ceil,
							   double floor,
							   t_texture *bars)
{
    int i;
    int k;
    double yb_wall;
    double yt_wall;
    double yb_window;
    double yt_window;
    int color;
    double	wall_max_x;
    double	x_start;
	double	dx_left;
	double	dx_right;
	double	x;
	double	y;
	double	a;


    /////////////////////////////////////////////////////////////////////////////////////////////////////
    i = game->screen->w / 2;
    k = game->screen->h / 2;
    yt_window = for_draw.window.y1t + (for_draw.window.y2t - for_draw.window.y1t) * (i - for_draw.window.x1) / (for_draw.window.x2 - for_draw.window.x1);
    yb_window = for_draw.window.y1b + (for_draw.window.y2b - for_draw.window.y1b) * (i - for_draw.window.x1) / (for_draw.window.x2 - for_draw.window.x1);
    yt_wall = for_draw.wall.y1t + (for_draw.wall.y2t - for_draw.wall.y1t) * (i - for_draw.window.x1) / (for_draw.window.x2 - for_draw.window.x1);
    yb_wall = for_draw.wall.y1b + (for_draw.wall.y2b - for_draw.wall.y1b) * (i - for_draw.window.x1) / (for_draw.window.x2 - for_draw.window.x1);
    a = (double)(i - (int)for_draw.wall.x1) / ((int)for_draw.wall.x2 - (int)for_draw.wall.x1);
    x = ((1 - a) * x1 / y1 + a * x2 / y2) /((1 - a) / y1 + a / y2);
    if (x > 0)
        x = (x - (int)x) * bars->w;
    else
        x = (x - (int)x + 1) * bars->w;
    a = (double)(k - (int)yt_wall) / ((int)yb_wall - (int)yt_wall);
    y = -((1 - a) * ceil + a * floor);
    if (y > 0)
        y = (y - (int)y) * bars->h;
    else
        y = (y - (int)y + 1) * bars->h;
    if (x >= 0 && x < bars->w && y >= 0 && y < bars->h)
    {
        color = (bars->pixels)[(int)y * bars->w + (int)x];
        if (color != 0)
        {
            game->cross_flag = NULL;
            game->sprite_wall = NULL;
        }
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////
    (void)display_mode;
    (void)grid; //остваил ребятам доделать решетку между секторами
    i = (int)for_draw.wall.x1;
    x_start = (int)for_draw.wall.x1;
    dx_left = 0;
    dx_right = 0;
    if (i < 0)
    {
        dx_left = -i;
        i = 0;
    }
    wall_max_x = for_draw.wall.x2 - for_draw.wall.x1;
    if (for_draw.wall.x2 > screen->w)
    {
        dx_right = for_draw.wall.x2 - screen->w;
    }
	while (i < for_draw.wall.x2 && i < screen->w)
    {
        yt_window = for_draw.window.y1t + (for_draw.window.y2t - for_draw.window.y1t) * (i - for_draw.window.x1) / (for_draw.window.x2 - for_draw.window.x1);
        yb_window = for_draw.window.y1b + (for_draw.window.y2b - for_draw.window.y1b) * (i - for_draw.window.x1) / (for_draw.window.x2 - for_draw.window.x1);
        yt_wall = for_draw.wall.y1t + (for_draw.wall.y2t - for_draw.wall.y1t) * (i - for_draw.window.x1) / (for_draw.window.x2 - for_draw.window.x1);
        yb_wall = for_draw.wall.y1b + (for_draw.wall.y2b - for_draw.wall.y1b) * (i - for_draw.window.x1) / (for_draw.window.x2 - for_draw.window.x1);
        if (yt_wall < 0)
            k = 0;
        else
            k = yt_wall;
		a = (double)(i - (int)for_draw.wall.x1) / ((int)for_draw.wall.x2 - (int)for_draw.wall.x1);
		x = ((1 - a) * x1 / y1 + a * x2 / y2) /((1 - a) / y1 + a / y2);
		if (x > 0)
			x = (x - (int)x) * game->texture->w;
		else
			x = (x - (int)x + 1) * game->texture->w;
        while (k < yb_wall && k < screen->h)
        {
            if (k < yt_window || k > yb_window)
            {
            	if (k < yb_window)
				{
					a = (double)(k - (int)yt_wall) / ((int)yb_wall - (int)yt_wall);
					y = -((1 - a) * ceil + a * floor);
					if (y > 0)
						y = (y - (int)y) * game->texture->h;
					else
						y = (y - (int)y + 1) * game->texture->h;
					if (x >= 0 && x < game->texture->w && y >= 0 && y < game->texture->h)
					{
						color = (game->texture->pixels)[(int)y * game->texture->w + (int)x];
						((int*)game->screen->pixels)[k * game->screen->w + i] = ft_bright(color, bright);
					}
				}
            	else
            		color = 0x1FFF;
                ((int*)screen->pixels)[k * screen->w + i] = ft_bright(color, bright);
            }
			else
			{
				a = (double)(i - (int)for_draw.wall.x1) / ((int)for_draw.wall.x2 - (int)for_draw.wall.x1);
				x = ((1 - a) * x1 / y1 + a * x2 / y2) /((1 - a) / y1 + a / y2);
				if (x > 0)
					x = (x - (int)x) * bars->w;
				else
					x = (x - (int)x + 1) * bars->w;
				a = (double)(k - (int)yt_wall) / ((int)yb_wall - (int)yt_wall);
				y = -((1 - a) * ceil + a * floor);
				if (y > 0)
					y = (y - (int)y) * bars->h;
				else
					y = (y - (int)y + 1) * bars->h;
				if (x >= 0 && x < bars->w && y >= 0 && y < bars->h)
				{
					color = (bars->pixels)[(int)y * bars->w + (int)x];
					if (color != 0)
						((int*)game->screen->pixels)[k * game->screen->w + i] = ft_bright(color, bright);
				}
			}
            k++;
        }
        i++;
    }
}


//рекурсивная функция, которая отрисовывает сектор;
void    draw_sector(t_game *game, t_draw for_draw)
{
    int i;
    t_draw    for_next_draw;
    t_vec2    first_point;
    t_vec2    second_point;
    double yscale1;
    double yscale2;
    double yceil;
    double yfloor;
    double    y2ceil;
    double    y2floor;
    double x1, x2;
    double x1a, x2a;
    double y1, y2;
	double y1a, y2a;
	double x1_b4, x2_b4;
	double perc1, perc2;
	t_sprite	*sprite;
	i = 0;
    while (i < (game->sectors + for_draw.curr_sector)->count_wall)
    {
        first_point = *(game->points_cam + *((game->sectors + for_draw.curr_sector)->index_points + i));
		x1 = (game->points + *((game->sectors + for_draw.curr_sector)->index_points + i))->x;
		y1 = (game->points + *((game->sectors + for_draw.curr_sector)->index_points + i))->y;
        if (i == (game->sectors + for_draw.curr_sector)->count_wall - 1)
		{
			x2 = (game->points + *((game->sectors + for_draw.curr_sector)->index_points))->x;
			y2 = (game->points + *((game->sectors + for_draw.curr_sector)->index_points))->y;
            second_point = *(game->points_cam + *((game->sectors + for_draw.curr_sector)->index_points));
		}
        else
		{
			x2 = (game->points + *((game->sectors + for_draw.curr_sector)->index_points + i + 1))->x;
			y2 = (game->points + *((game->sectors + for_draw.curr_sector)->index_points + i + 1))->y;
            second_point = *(game->points_cam + *((game->sectors + for_draw.curr_sector)->index_points + i + 1));
		}
        if (first_point.x < 0 && second_point.x < 0)
        {
            i++;
            continue;
        }
		x1_b4 = -first_point.y;
		x2_b4 = -second_point.y;
		y1a = first_point.x;
		y2a = second_point.x;
        if (intersection(&first_point, &second_point, for_draw.fov_left, for_draw.fov_right) > 0)
        {
			perc1 = (-first_point.y - x1_b4) / (x2_b4 - x1_b4);
			perc2 = (-second_point.y - x1_b4) / (x2_b4 - x1_b4);
			y1a = first_point.x;
			y2a = second_point.x;
			if (fabs(x1 - x2) > fabs(y1 - y2))
			{
				x1a = x1 + (x2 - x1) * (-first_point.y - x1_b4) / (x2_b4 - x1_b4);
				x2a = x1 + (x2 - x1) * (-second_point.y - x1_b4) / (x2_b4 - x1_b4);
			}
			else
			{
				x1a = y1 - (y2 - y1) * (-first_point.y - x1_b4) / (x2_b4 - x1_b4);
				x2a = y1 - (y2 - y1) * (-second_point.y - x1_b4) / (x2_b4 - x1_b4);
			}
			if (x1a > x2a)
			{
				x1a = -x1a;
				x2a = -x2a;
			}
			yceil = (game->sectors + for_draw.curr_sector)->ceil - game->player.pos.z;
            yfloor = (game->sectors + for_draw.curr_sector)->floor - game->player.pos.z;
            yscale1 =  game->pre_calc.screen_h_div_2 / first_point.x;
			yscale2 =  game->pre_calc.screen_h_div_2 / second_point.x;
            for_draw.wall.x1 = -first_point.y * (game->pre_calc.screen_w_div_2) / first_point.x + game->pre_calc.screen_w_div_2;
            for_draw.wall.x2 = -second_point.y * (game->pre_calc.screen_w_div_2) / second_point.x + game->pre_calc.screen_w_div_2;
            for_draw.wall.y2t = -yscale2 * yceil + game->line_horiz;
            for_draw.wall.y1t = -yscale1 * yceil + game->line_horiz;
            for_draw.wall.y2b = -yscale2 * yfloor + game->line_horiz;
            for_draw.wall.y1b = -yscale1 * yfloor + game->line_horiz;
            if (*((game->sectors + for_draw.curr_sector)->neighbors + i) >= 0)
            {
                if (*((game->sectors + for_draw.curr_sector)->neighbors + i) != for_draw.last_sector)
                {
                    for_next_draw.wall = for_draw.wall;
                    y2ceil = (game->sectors + *((game->sectors + for_draw.curr_sector)->neighbors + i))->ceil - game->player.pos.z;
                    y2floor = (game->sectors + *((game->sectors + for_draw.curr_sector)->neighbors + i))->floor - game->player.pos.z;
                    for_next_draw.window.y1t = -yscale1 * y2ceil + game->line_horiz;
                    for_next_draw.window.y1b = -yscale1 * y2floor + game->line_horiz;
                    for_next_draw.window.y2t = -yscale2 * y2ceil + game->line_horiz;
                    for_next_draw.window.y2b = -yscale2 * y2floor + game->line_horiz;
                    for_next_draw.window.x1 = for_next_draw.wall.x1;
                    for_next_draw.window.x2 = for_next_draw.wall.x2;
                    for_next_draw.curr_sector = *((game->sectors + for_draw.curr_sector)->neighbors + i);
                    for_next_draw.last_sector = for_draw.curr_sector;
                    for_next_draw.fov_left = first_point;
                    for_next_draw.fov_right = second_point;
                    draw_sector(game, for_next_draw);
                    pre_draw_sector(game->screen, game->display_mode, for_next_draw, (game->sectors + for_draw.curr_sector)->brightness,
                    		*((game->sectors + for_draw.curr_sector)->grid + i), game, x1a, x2a, y1a, y2a, (game->sectors + for_draw.curr_sector)->ceil, (game->sectors + for_draw.curr_sector)->floor, game->texture1);
                }
            }
            else
			{
				if (for_draw.curr_sector == 0 && i == 0)
					draw_wall(game, for_draw, x1a, x2a, y1a, y2a, (game->sectors + for_draw.curr_sector)->ceil, (game->sectors + for_draw.curr_sector)->floor, (game->sectors + for_draw.curr_sector)->brightness, perc1, perc2,  game->sectors->sprite_wall);
            	else
					draw_wall(game, for_draw, x1a, x2a, y1a, y2a, (game->sectors + for_draw.curr_sector)->ceil, (game->sectors + for_draw.curr_sector)->floor, (game->sectors + for_draw.curr_sector)->brightness, perc1, perc2,  0);
			}
			draw_floor(game, for_draw, -yfloor, (game->sectors + for_draw.curr_sector)->brightness);
            if (for_draw.curr_sector != 0)
				draw_ceil(game, for_draw, yceil, (game->sectors + for_draw.curr_sector)->brightness);
        }
        i++;
    }
	sprite = game->sprites;
	while (sprite != 0)
	{
		if (sprite->sector == for_draw.curr_sector)
		{
			draw_sprites(game, for_draw, sprite, (game->sectors + for_draw.curr_sector)->brightness);
		}
		sprite = sprite->next;
	}
}
