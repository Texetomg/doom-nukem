/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_text.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 16:06:32 by thorker           #+#    #+#             */
/*   Updated: 2019/11/01 15:00:24 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	print_custom_text(t_game *game, char *text)
{
	print_text(game->screen,
				text,
				game->hud.color,
				game->hud.text_dest);
}

void	print_menu_text(SDL_Surface *screen, t_menu *menu, int string_count)
{
	int i;
	int new_str;

	i = 0;
	new_str = 15;
	while (i < string_count)
	{
		if (menu->text_pos != i)
			set_color(&menu->text_color, 255, 255, 0);
		else
			set_color(&menu->text_color, 0, 255, 0);
		print_text(screen, menu->strings[i],
					menu->text_color,
					menu->dest);
		menu->dest.y = screen->h / 100 * new_str;
		new_str += 5;
		i++;
	}
}

void	print_text(SDL_Surface *screen, char *text, SDL_Color color,
	SDL_Rect dest)
{
	TTF_Font	*fnt;
	SDL_Surface	*s_text;

	if ((fnt = TTF_OpenFont("../font/font.otf", 46)) == NULL)
		check_error_n_exit(1, (char*)SDL_GetError());
	if ((s_text = TTF_RenderText_Blended(fnt, text, color)) == NULL)
		check_error_n_exit(1, (char*)SDL_GetError());
	SDL_BlitSurface(s_text, NULL, screen, &dest);
	SDL_FreeSurface(s_text);
	TTF_CloseFont(fnt);
}
