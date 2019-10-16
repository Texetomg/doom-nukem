/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiplayer_menu.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 16:20:52 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/10/16 16:25:46 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

static char	*processing_ip(char *ip)
{
	char *temp;

	temp = ft_strdup(&ip[4]);
	return (temp);
}

static void	key_hook_sup(t_game *game, int *loop, SDL_Event e)
{
	if (e.key.keysym.sym == SDLK_ESCAPE ||
		e.type == SDL_QUIT)
		*loop = 0;
	else if (e.key.keysym.sym == SDLK_RETURN &&
		game->multi_menu.text_pos == 0)
		switch_menu(&game->menu_status.start, &game->menu_status.multi);
	else if (e.key.keysym.sym == SDLK_UP && game->multi_menu.text_pos > 0)
		game->multi_menu.text_pos -= 1;
	else if (e.key.keysym.sym == SDLK_DOWN && game->multi_menu.text_pos < 1)
		game->multi_menu.text_pos += 1;
	else if (e.key.keysym.sym == SDLK_BACKSPACE &&
		game->multi_menu.text_pos == 1)
	{
		if (game->server_ip[ft_strlen(game->server_ip) - 1] != ' ')
			game->server_ip[ft_strlen(game->server_ip) - 1] = '\0';
		game->multi_menu.strings[1] = game->server_ip;
	}
	else if (e.key.keysym.sym == SDLK_RETURN && game->multi_menu.text_pos == 1)
	{
		game->server_ip = processing_ip(game->multi_menu.strings[1]);
		init_client(game, &game->socket_struct);
		switch_menu(&game->menu_status.main, &game->menu_status.multi);
	}
}

static void	key_hook(t_game *game, int *loop)
{
	SDL_Event	e;
	char		*temp;

	temp = NULL;
	game->server_ip = ft_strcpy(game->server_ip, game->multi_menu.strings[1]);
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_KEYDOWN)
			key_hook_sup(game, loop, e);
		else if (e.type == SDL_TEXTINPUT && game->multi_menu.text_pos == 1)
		{
			temp = game->server_ip;
			game->server_ip = ft_strjoin(temp, e.text.text);
			free(temp);
			game->multi_menu.strings[1] = game->server_ip;
		}
	}
}

void		multiplayer_menu_render(t_game *game, int *loop)
{
	menu_render(game->screen, &game->multi_menu, game->multi_menu.image[0]);
	key_hook(game, loop);
	print_menu_text(game->screen, &game->multi_menu, 2);
}
