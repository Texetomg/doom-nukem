#include "doom-nukem.h"

static char *processing_ip(char *ip)
{
	char *temp;

	temp = ft_strdup(&ip[4]);
	return temp;
}

static void	key_hook(t_game *game, int *loop)
{
	SDL_Event e;
	char *temp;

	temp = NULL;
	game->server_ip = ft_strcpy(game->server_ip, game->multi_menu.strings[1]);
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_ESCAPE ||
				e.type == SDL_QUIT)
				*loop = 0;
            else if (e.key.keysym.sym == SDLK_RETURN &&
				game->multi_menu.text_pos == 0)
				{
					game->menu_status.multi = 0;
                    game->menu_status.start = 1;
				}
			else if (e.key.keysym.sym == SDLK_UP && game->multi_menu.text_pos > 0)
				game->multi_menu.text_pos -= 1;
			else if (e.key.keysym.sym == SDLK_DOWN && game->multi_menu.text_pos < 1)
				game->multi_menu.text_pos += 1;
			else if (e.key.keysym.sym == SDLK_BACKSPACE && game->multi_menu.text_pos == 1)
			{
				if (game->server_ip[ft_strlen(game->server_ip) - 1] != ' ')
					game->server_ip[ft_strlen(game->server_ip) - 1] = '\0';
				game->multi_menu.strings[1] = game->server_ip;
			}
			else if (e.key.keysym.sym == SDLK_RETURN && game->multi_menu.text_pos == 1)
			{
				game->server_ip = processing_ip(game->multi_menu.strings[1]);
				init_client(game, &game->socket_struct);
				game->menu_status.multi = 0;
				game->menu_status.main = 1;
			}
		}
		else if(e.type == SDL_TEXTINPUT && game->multi_menu.text_pos == 1)
		{
			temp = game->server_ip;
			game->server_ip = ft_strjoin(temp, e.text.text);
			free(temp);
			game->multi_menu.strings[1] = game->server_ip;
		}
	}
}

void    multiplayer_menu_render(t_game *game, int *loop)
{
	int i;
	int new_str;

	i = 0;
	new_str = 10;
	game->multi_menu.dest.h = 80;
	game->multi_menu.dest.w = 120;
	game->multi_menu.dest.x = game->screen->w / 100 * 65;
	game->multi_menu.dest.y = game->screen->h / 100 * 5;
    key_hook(game, loop);
	set_color(&game->multi_menu.text_color, 255, 255, 0);
	draw_full_screen_img(game->screen, game->multi_menu.image[0]);
	game->multi_menu.dest.y = game->screen->h / 100 * new_str;
	new_str += 5;
	while (i < 2)
	{
		if (game->multi_menu.text_pos != i)
			set_color(&game->multi_menu.text_color, 255, 255, 0);
		else
			set_color(&game->multi_menu.text_color, 0, 255, 0);
			
		print_text(game->screen, game->multi_menu.strings[i],
					"../font/font.otf", 46, game->multi_menu.text_color,
					game->multi_menu.dest);
		game->multi_menu.dest.y = game->screen->h / 100 * new_str;
		new_str += 5;
		i++;
	}
}