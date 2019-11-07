/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_temp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramory-l <ramory-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 21:48:49 by ramory-l          #+#    #+#             */
/*   Updated: 2019/11/07 21:58:39 by ramory-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	change_temp1(t_angle_sprite *temp)
{
	temp[0].start_angle = 0;
	temp[0].end_angle = 2 * 3.14 / 9;
	temp[0].texture = IMG_Load("imgs/sprites/doomguy/1/1/1.bmp");
	temp[0].up_health = 100;
	temp[0].down_health = 85;
	temp[0].texture2 = IMG_Load("imgs/sprites/doomguy/1/1/1.bmp");
	temp[1].start_angle = 2 * 3.14 / 9;
	temp[1].end_angle = 4 * 3.14 / 9;
	temp[1].texture = IMG_Load("imgs/sprites/doomguy/1/1/2.bmp");
	temp[1].up_health = 85;
	temp[1].down_health = 70;
	temp[1].texture2 = IMG_Load("imgs/sprites/doomguy/1/2/1.bmp");
	temp[2].start_angle = 4 * 3.14 / 9;
	temp[2].end_angle = 6 * 3.14 / 9;
	temp[2].texture = IMG_Load("imgs/sprites/doomguy/1/1/3.bmp");
	temp[2].up_health = 70;
	temp[2].down_health = 55;
	temp[2].texture2 = IMG_Load("imgs/sprites/doomguy/1/2/2.bmp");
}

void	change_temp2(t_angle_sprite *temp)
{
	temp[3].start_angle = 6 * 3.14 / 9;
	temp[3].end_angle = 8 * 3.14 / 9;
	temp[3].texture = IMG_Load("imgs/sprites/doomguy/1/1/4.bmp");
	temp[3].up_health = 55;
	temp[3].down_health = 40;
	temp[3].texture2 = IMG_Load("imgs/sprites/doomguy/1/2/3.bmp");
	temp[4].start_angle = 8 * 3.14 / 9;
	temp[4].end_angle = 10 * 3.14 / 9;
	temp[4].texture = IMG_Load("imgs/sprites/doomguy/1/1/5.bmp");
	temp[4].up_health = 40;
	temp[4].down_health = 25;
	temp[4].texture2 = IMG_Load("imgs/sprites/doomguy/1/2/4.bmp");
	temp[5].start_angle = 10 * 3.14 / 9;
	temp[5].end_angle = 12 * 3.14 / 9;
	temp[5].texture = IMG_Load("imgs/sprites/doomguy/1/1/6.bmp");
	temp[5].up_health = 25;
	temp[5].down_health = 10;
	temp[5].texture2 = IMG_Load("imgs/sprites/doomguy/1/2/5.bmp");
}

void	change_temp3(t_angle_sprite *temp)
{
	temp[6].start_angle = 12 * 3.14 / 9;
	temp[6].end_angle = 14 * 3.14 / 9;
	temp[6].texture = IMG_Load("imgs/sprites/doomguy/1/1/7.bmp");
	temp[6].up_health = 10;
	temp[6].down_health = 0;
	temp[6].texture2 = IMG_Load("imgs/sprites/doomguy/1/2/6.bmp");
	temp[7].start_angle = 14 * 3.14 / 9;
	temp[7].end_angle = 16 * 3.14 / 9;
	temp[7].texture = IMG_Load("imgs/sprites/doomguy/1/1/8.bmp");
	temp[7].up_health = 10;
	temp[7].down_health = 0;
	temp[7].texture2 = IMG_Load("imgs/sprites/doomguy/1/2/6.bmp");
	temp[8].start_angle = 16 * 3.14 / 9;
	temp[8].end_angle = 18 * 3.14 / 9;
	temp[8].texture = IMG_Load("imgs/sprites/doomguy/1/1/1.bmp");
	temp[8].up_health = 10;
	temp[8].down_health = 0;
	temp[8].texture2 = IMG_Load("imgs/sprites/doomguy/1/2/6.bmp");
}
void	change_temp4(t_angle_sprite *temp)
{
	temp[9].start_angle = 12 * 3.14 / 9;
	temp[9].end_angle = 14 * 3.14 / 9;
	temp[9].texture = IMG_Load("imgs/sprites/doomguy/1/1/7.bmp");
	temp[9].up_health = 10;
	temp[9].down_health = 0;
	temp[9].texture2 = IMG_Load("imgs/sprites/doomguy/1/2/6.bmp");
	temp[10].start_angle = 14 * 3.14 / 9;
	temp[10].end_angle = 16 * 3.14 / 9;
	temp[10].texture = IMG_Load("imgs/sprites/doomguy/1/1/8.bmp");
	temp[10].up_health = 10;
	temp[10].down_health = 0;
	temp[10].texture2 = IMG_Load("imgs/sprites/doomguy/1/2/6.bmp");
	temp[11].start_angle = 16 * 3.14 / 9;
	temp[11].end_angle = 2 * 3.14;
	temp[11].texture = IMG_Load("imgs/sprites/doomguy/1/1/1.bmp");
	temp[11].up_health = 10;
	temp[11].down_health = 0;
	temp[11].texture2 = IMG_Load("imgs/sprites/doomguy/1/2/6.bmp");
}