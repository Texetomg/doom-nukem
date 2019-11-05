/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 15:22:16 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/11/01 15:01:35 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	switch_menu(int *menu_on, int *menu_off)
{
	*menu_on = 1;
	*menu_off = 0;
}

void	menu_render(SDL_Surface *screen, t_menu *menu, SDL_Surface *image)
{
	menu->dest.h = 80;
	menu->dest.w = 120;
	menu->dest.x = screen->w / 100 * 65;
	menu->dest.y = screen->h / 100 * 5;
	set_color(&menu->text_color, 255, 255, 0);
	draw_full_screen_img(screen, image);
	menu->dest.y = screen->h / 10;
}
