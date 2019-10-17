/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 20:10:38 by thorker           #+#    #+#             */
/*   Updated: 2019/10/17 16:37:04 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

void		set_color(SDL_Color *color, int r, int g, int b)
{
	color->r = r;
	color->g = g;
	color->b = b;
}

static void read_gif(t_gif *gif, char *str, int index, int frame, char* extension)
{
	char *folder;
	char *i;
	char *path;
	char *tmp;
	int k;

	folder = ft_strdup(str);
	gif[index].frame = frame;
	gif[index].curr_frame = 0;
	gif[index].array = (SDL_Surface**)malloc(sizeof(SDL_Surface*) * gif[index].frame);
	k = 0;
	while (k < gif[index].frame)
	{
		i = ft_itoa(k);
		tmp = ft_strjoin(folder,i);
		path = ft_strjoin(tmp, extension);
		if (!(*(gif[index].array + k) = IMG_Load(path)))
			check_error_n_exit(1,(char*)SDL_GetError());
		free(path);
		free(tmp);
		free(i);
		k++;
	}
	free(folder);
}

void	texture_cut(t_texture *texture, unsigned int st_color, unsigned int end_color)
{
	int i;
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;

	i = 0;
	while (i < texture->w * texture->h)
	{
		red = texture->pixels[i] & 0xFF0000;
		green = texture->pixels[i] & 0xFF00;
		blue =  texture->pixels[i] & 0xFF;
		if (((red > (st_color & 0xFF0000)) && (red < (end_color & 0xFF0000)))
			&& ((green > (st_color & 0xFF00)) && (green < (end_color & 0xFF00)))
			&& ((blue > (st_color & 0xFF)) && (blue < (end_color & 0xFF))))
			texture->pixels[i] = 0;
		i++;
	}
}

void	texture_cut_sdl(SDL_Surface *texture, unsigned int st_color, unsigned int end_color)
{
    int i;
    unsigned int	red;
    unsigned int	green;
    unsigned int	blue;
    unsigned int    *pixels;

    pixels = (unsigned int*)texture->pixels;
    i = 0;
    while (i < texture->w * texture->h)
    {
        red = pixels[i] & 0xFF0000;
        green = pixels[i] & 0xFF00;
        blue =  pixels[i] & 0xFF;
        if (((red > (st_color & 0xFF0000)) && (red < (end_color & 0xFF0000)))
			&& ((green > (st_color & 0xFF00)) && (green < (end_color & 0xFF00)))
			&& ((blue > (st_color & 0xFF)) && (blue < (end_color & 0xFF))))
            pixels[i] = 0;
        i++;
    }
}

//инициализация sdl
static void	init_sdl(t_game *game)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		check_error_n_exit(1,(char*)SDL_GetError());//закрывать sdl:
	if (SDL_ShowCursor(SDL_DISABLE) < 0)
		check_error_n_exit(1,(char*)SDL_GetError());
	if ((SDL_GetDesktopDisplayMode(0, &game->display_mode)) != 0)
		check_error_n_exit(1,(char*)SDL_GetError());
	//game->window = SDL_CreateWindow(0, 0, 0, 0, 0,
	//		SDL_WINDOW_FULLSCREEN_DESKTOP);
	game->window = SDL_CreateWindow("Doom-Nukem", 0, 0, 1400, 1000, SDL_WINDOW_SHOWN);
	if (game->window == 0)
		check_error_n_exit(1,(char*)SDL_GetError());
	if ((game->screen = SDL_GetWindowSurface(game->window)) == 0)
		check_error_n_exit(1,(char*)SDL_GetError());
	if (TTF_Init() < 0)
		check_error_n_exit(1,(char*)SDL_GetError());
	if (Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0) {
        check_error_n_exit(1,(char*)SDL_GetError());
    }
	game->texture = get_texture("imgs/textures/cat.bmp");
	game->texture1 = get_texture("imgs/gif1/13.bmp");
	texture_cut(game->texture1, 0, 0x303030);
}

void set_player(t_game *game)
{
	game->player.jetpack = 0;
	game->player.key = 1;
	game->player.curr_sector = 1;
	game->player.pos.x = 0;
	game->player.pos.y = -3;
	game->player.z_accel = 0;
	game->player.angle = 3.14;
	game->player.foots = (game->sectors + game->player.curr_sector)->floor;
	game->player.knees = game->player.foots + 0.2;
	game->player.pos.z = game->player.foots + 0.5;
	game->player.b_foots = 0.5;
	game->player.b_knees = 0.3;
}

static void set_keystate(t_game *game)
{
	game->keystate.back = 0;
	game->keystate.ctrl = 0;
	game->keystate.forward = 0;
	game->keystate.jump = 0;
	game->keystate.left = 0;
	game->keystate.right = 0;
}

static void set_menu(t_game *game)
{
	game->menu_status.start = 1;
	game->start_menu.strings[0] = "CHOOSE YOUR DESTINY:";
	game->start_menu.strings[1] = "Loli";
	game->start_menu.strings[2] = "Trump";
	game->start_menu.strings[3] = "Doomguy";
	game->start_menu.strings[4] = "Setevaya igra";
	game->start_menu.strings[5] = "Exit";
	game->multi_menu.strings[0] = "Back";
	game->multi_menu.strings[1] = "IP: 192.168.";
	game->start_menu.text_pos = 0;
	game->multi_menu.text_pos = 0;
	game->tab_menu.text_pos = 0;
	game->tab_menu.strings[0] = "Continue";
	game->tab_menu.strings[1] = "New game";
	game->tab_menu.strings[2] = "Exit";
	game->menu_status.tab = 0;
	game->menu_status.main = 0;
	game->menu_status.multi = 0;
}

static void	set_sprites(t_game *game)
{
    t_angle_sprite *start_sprite;

	game->sprites = (t_sprite*)malloc(sizeof(t_sprite));
	(game->sprites)->id = 0;
	(game->sprites)->pos.x = 0;
	(game->sprites)->pos.y = 0;
	(game->sprites)->heigth = 0.5;
	(game->sprites)->width = game->screen->w / 10;
	(game->sprites)->pos.z = 0.6;
	(game->sprites)->sector = 0;
	(game->sprites)->angle = 0;
	(game->sprites)->health = 100;
    //##################################################################################################################
//	(game->sprites)->angle_sprite = (t_angle_sprite*)malloc(sizeof(t_angle_sprite));
//	(game->sprites)->angle_sprite->start_angle = 0;
//	(game->sprites)->angle_sprite->end_angle = 3.14 / 4;
//	(game->sprites)->angle_sprite->texture = IMG_Load("imgs/sprites/doomguy/doomguy_forward.bmp");
//	(game->sprites)->angle_sprite->up_health = -1;
//	//------------------------------------------------------------------------------------------------------------------
//	(game->sprites)->angle_sprite->next = (t_angle_sprite*)malloc(sizeof(t_angle_sprite));
//	(game->sprites)->angle_sprite->next->start_angle = 3.14 / 4;
//	(game->sprites)->angle_sprite->next->end_angle = 3.14 * 3 / 4;
//    (game->sprites)->angle_sprite->next->texture = IMG_Load("imgs/sprites/doomguy/doomguy_left.bmp");
//	(game->sprites)->angle_sprite->next->up_health = -1;
//    //------------------------------------------------------------------------------------------------------------------
//	(game->sprites)->angle_sprite->next->next = (t_angle_sprite*)malloc(sizeof(t_angle_sprite));
//	(game->sprites)->angle_sprite->next->next->start_angle = 3 * 3.14 / 4;
//	(game->sprites)->angle_sprite->next->next->end_angle = 3.14 * 5 / 4;
//    (game->sprites)->angle_sprite->next->next->texture = IMG_Load("imgs/sprites/doomguy/doomguy_back.bmp");
//	(game->sprites)->angle_sprite->next->next->up_health = -1;
//    //------------------------------------------------------------------------------------------------------------------
//	(game->sprites)->angle_sprite->next->next->next = (t_angle_sprite*)malloc(sizeof(t_angle_sprite));
//	(game->sprites)->angle_sprite->next->next->next->start_angle = 5 * 3.14 / 4;
//	(game->sprites)->angle_sprite->next->next->next->end_angle = 3.14 * 7 / 4;
//    (game->sprites)->angle_sprite->next->next->next->texture = IMG_Load("imgs/sprites/doomguy/doomguy_right.bmp");
//	(game->sprites)->angle_sprite->next->next->next->up_health = -1;
//    //------------------------------------------------------------------------------------------------------------------
//	(game->sprites)->angle_sprite->next->next->next->next = (t_angle_sprite*)malloc(sizeof(t_angle_sprite));
//	(game->sprites)->angle_sprite->next->next->next->next->start_angle = 7 * 3.14 / 4;
//	(game->sprites)->angle_sprite->next->next->next->next->end_angle = 3.14 * 2;
//    (game->sprites)->angle_sprite->next->next->next->next->texture = IMG_Load("imgs/sprites/doomguy/doomguy_forward.bmp");
//	(game->sprites)->angle_sprite->next->next->next->next->up_health = -1;
//    //------------------------------------------------------------------------------------------------------------------
//	(game->sprites)->angle_sprite->next->next->next->next->next = 0;
	(game->sprites)->angle_sprite = (t_angle_sprite*)malloc(sizeof(t_angle_sprite));
	(game->sprites)->angle_sprite->start_angle = 0;
	(game->sprites)->angle_sprite->end_angle = 2 * 3.14 / 9;
	(game->sprites)->angle_sprite->texture = IMG_Load("imgs/sprites/doomguy/1/1/1.bmp");
	(game->sprites)->angle_sprite->up_health = 100;
	(game->sprites)->angle_sprite->down_health = 85;
	(game->sprites)->angle_sprite->texture2 = IMG_Load("imgs/sprites/doomguy/1/1/1.bmp");
	//------------------------------------------------------------------------------------------------------------------
	(game->sprites)->angle_sprite->next = (t_angle_sprite*)malloc(sizeof(t_angle_sprite));
	(game->sprites)->angle_sprite->next->start_angle = 2 * 3.14 / 9;
	(game->sprites)->angle_sprite->next->end_angle = 2 * 3.14 * 2 / 9;
	(game->sprites)->angle_sprite->next->texture = IMG_Load("imgs/sprites/doomguy/1/1/2.bmp");
	(game->sprites)->angle_sprite->next->up_health = 85;
	(game->sprites)->angle_sprite->next->down_health = 70;
	(game->sprites)->angle_sprite->next->texture2 = IMG_Load("imgs/sprites/doomguy/1/2/1.bmp");
	//------------------------------------------------------------------------------------------------------------------
	(game->sprites)->angle_sprite->next->next = (t_angle_sprite*)malloc(sizeof(t_angle_sprite));
	(game->sprites)->angle_sprite->next->next->start_angle = 2 * 3.14 * 2 / 9;
	(game->sprites)->angle_sprite->next->next->end_angle = 2 * 3.14 * 3 / 9;
	(game->sprites)->angle_sprite->next->next->texture = IMG_Load("imgs/sprites/doomguy/1/1/3.bmp");
	(game->sprites)->angle_sprite->next->next->up_health = 70;
	(game->sprites)->angle_sprite->next->next->down_health = 55;
	(game->sprites)->angle_sprite->next->next->texture2 = IMG_Load("imgs/sprites/doomguy/1/2/2.bmp");
	//------------------------------------------------------------------------------------------------------------------
	(game->sprites)->angle_sprite->next->next->next = (t_angle_sprite*)malloc(sizeof(t_angle_sprite));
	(game->sprites)->angle_sprite->next->next->next->start_angle = 2 * 3.14 * 3 / 9;
	(game->sprites)->angle_sprite->next->next->next->end_angle = 2 * 3.14 * 4 / 9;
	(game->sprites)->angle_sprite->next->next->next->texture = IMG_Load("imgs/sprites/doomguy/1/1/4.bmp");
	(game->sprites)->angle_sprite->next->next->next->up_health = 55;
	(game->sprites)->angle_sprite->next->next->next->down_health = 40;
	(game->sprites)->angle_sprite->next->next->next->texture2 = IMG_Load("imgs/sprites/doomguy/1/2/3.bmp");
	//------------------------------------------------------------------------------------------------------------------
	(game->sprites)->angle_sprite->next->next->next->next = (t_angle_sprite*)malloc(sizeof(t_angle_sprite));
	(game->sprites)->angle_sprite->next->next->next->next->start_angle = 2 * 3.14 * 4 / 9;
	(game->sprites)->angle_sprite->next->next->next->next->end_angle = 2 * 3.14 * 5 / 9;
	(game->sprites)->angle_sprite->next->next->next->next->texture = IMG_Load("imgs/sprites/doomguy/1/1/5.bmp");
	(game->sprites)->angle_sprite->next->next->next->next->up_health = 40;
	(game->sprites)->angle_sprite->next->next->next->next->down_health = 25;
	(game->sprites)->angle_sprite->next->next->next->next->texture2 = IMG_Load("imgs/sprites/doomguy/1/2/4.bmp");
	//------------------------------------------------------------------------------------------------------------------
	(game->sprites)->angle_sprite->next->next->next->next->next = (t_angle_sprite*)malloc(sizeof(t_angle_sprite));
	(game->sprites)->angle_sprite->next->next->next->next->next->start_angle = 2 * 3.14 * 5 / 9;
	(game->sprites)->angle_sprite->next->next->next->next->next->end_angle = 2 * 3.14 * 6 / 9;
	(game->sprites)->angle_sprite->next->next->next->next->next->texture = IMG_Load("imgs/sprites/doomguy/1/1/6.bmp");
	(game->sprites)->angle_sprite->next->next->next->next->next->up_health = 25;
	(game->sprites)->angle_sprite->next->next->next->next->next->down_health = 10;
	(game->sprites)->angle_sprite->next->next->next->next->next->texture2 = IMG_Load("imgs/sprites/doomguy/1/2/5.bmp");
	//------------------------------------------------------------------------------------------------------------------
	(game->sprites)->angle_sprite->next->next->next->next->next->next = (t_angle_sprite*)malloc(sizeof(t_angle_sprite));
	(game->sprites)->angle_sprite->next->next->next->next->next->next->start_angle = 2 * 3.14 * 6 / 9;
	(game->sprites)->angle_sprite->next->next->next->next->next->next->end_angle = 2 * 3.14 * 7 / 9;
	(game->sprites)->angle_sprite->next->next->next->next->next->next->texture = IMG_Load("imgs/sprites/doomguy/1/1/7.bmp");
	(game->sprites)->angle_sprite->next->next->next->next->next->next->up_health = 10;
	(game->sprites)->angle_sprite->next->next->next->next->next->next->down_health = 0;
	(game->sprites)->angle_sprite->next->next->next->next->next->next->texture2 = IMG_Load("imgs/sprites/doomguy/1/2/6.bmp");
	//------------------------------------------------------------------------------------------------------------------
	(game->sprites)->angle_sprite->next->next->next->next->next->next->next = (t_angle_sprite*)malloc(sizeof(t_angle_sprite));
	(game->sprites)->angle_sprite->next->next->next->next->next->next->next->start_angle = 2 * 3.14 * 7 / 9;
	(game->sprites)->angle_sprite->next->next->next->next->next->next->next->end_angle = 2 * 3.14 * 8 / 9;
	(game->sprites)->angle_sprite->next->next->next->next->next->next->next->texture = IMG_Load("imgs/sprites/doomguy/1/1/8.bmp");
	(game->sprites)->angle_sprite->next->next->next->next->next->next->next->up_health = 10;
	(game->sprites)->angle_sprite->next->next->next->next->next->next->next->down_health = 0;
	(game->sprites)->angle_sprite->next->next->next->next->next->next->next->texture2 = IMG_Load("imgs/sprites/doomguy/1/2/6.bmp");
	//------------------------------------------------------------------------------------------------------------------
	(game->sprites)->angle_sprite->next->next->next->next->next->next->next->next = (t_angle_sprite*)malloc(sizeof(t_angle_sprite));
	(game->sprites)->angle_sprite->next->next->next->next->next->next->next->next->start_angle = 2 * 3.14 * 8 / 9;
	(game->sprites)->angle_sprite->next->next->next->next->next->next->next->next->end_angle = 2 * 3.14;
	(game->sprites)->angle_sprite->next->next->next->next->next->next->next->next->texture = IMG_Load("imgs/sprites/doomguy/1/1/1.bmp");
	(game->sprites)->angle_sprite->next->next->next->next->next->next->next->next->up_health = 10;
	(game->sprites)->angle_sprite->next->next->next->next->next->next->next->next->down_health = 0;
	(game->sprites)->angle_sprite->next->next->next->next->next->next->next->next->texture2 = IMG_Load("imgs/sprites/doomguy/1/2/6.bmp");
	//------------------------------------------------------------------------------------------------------------------
	(game->sprites)->angle_sprite->next->next->next->next->next->next->next->next->next = 0;
    //##################################################################################################################
	game->sprites->next = (t_sprite*)malloc(sizeof(t_sprite));
	(game->sprites)->next->id = 1;
	(game->sprites)->next->pos.x = 1;
	(game->sprites)->next->pos.y = -2;
	(game->sprites)->next->heigth = 0.5;
	(game->sprites)->next->width = game->screen->w / 10;
	(game->sprites)->next->pos.z = 0.5;
	(game->sprites)->next->sector = 1;
	(game->sprites)->next->angle = 3.14 / 2;
	//------------------------------------------------------------------------------------------------------------------
	(game->sprites)->next->angle_sprite = (t_angle_sprite*)malloc(sizeof(t_angle_sprite));
	(game->sprites)->next->angle_sprite->start_angle = -3.14;
	(game->sprites)->next->angle_sprite->end_angle = 3.14;
	(game->sprites)->next->angle_sprite->texture = *((game->gif)->array + 10);
	(game->sprites)->next->angle_sprite->texture2 = *((game->gif)->array + 10);
	(game->sprites)->next->angle_sprite->up_health = 100;
	(game->sprites)->next->angle_sprite->down_health = 85;
	//------------------------------------------------------------------------------------------------------------------
	(game->sprites)->next->angle_sprite->next = (t_angle_sprite*)malloc(sizeof(t_angle_sprite));
	(game->sprites)->next->angle_sprite->next->start_angle = -3.14;
	(game->sprites)->next->angle_sprite->next->end_angle = 3.14;
	(game->sprites)->next->angle_sprite->next->texture = *((game->gif)->array + 11);
	(game->sprites)->next->angle_sprite->next->texture2 = *((game->gif)->array + 11);
	(game->sprites)->next->angle_sprite->next->up_health = 85;
	(game->sprites)->next->angle_sprite->next->down_health = 70;
	//------------------------------------------------------------------------------------------------------------------
	(game->sprites)->next->angle_sprite->next->next = (t_angle_sprite*)malloc(sizeof(t_angle_sprite));
	(game->sprites)->next->angle_sprite->next->next->start_angle = -3.14;
	(game->sprites)->next->angle_sprite->next->next->end_angle = 3.14;
	(game->sprites)->next->angle_sprite->next->next->texture = *((game->gif)->array + 12);
	(game->sprites)->next->angle_sprite->next->next->texture2 = *((game->gif)->array + 12);
	(game->sprites)->next->angle_sprite->next->next->up_health = 70;
	(game->sprites)->next->angle_sprite->next->next->down_health = 55;
	//------------------------------------------------------------------------------------------------------------------
	(game->sprites)->next->angle_sprite->next->next->next = (t_angle_sprite*)malloc(sizeof(t_angle_sprite));
	(game->sprites)->next->angle_sprite->next->next->next->start_angle = -3.14;
	(game->sprites)->next->angle_sprite->next->next->next->end_angle = 3.14;
	(game->sprites)->next->angle_sprite->next->next->next->texture = *((game->gif)->array + 13);
	(game->sprites)->next->angle_sprite->next->next->next->texture2 = *((game->gif)->array + 13);
	(game->sprites)->next->angle_sprite->next->next->next->up_health = 55;
	(game->sprites)->next->angle_sprite->next->next->next->down_health = 40;
	//------------------------------------------------------------------------------------------------------------------
	(game->sprites)->next->angle_sprite->next->next->next->next = (t_angle_sprite*)malloc(sizeof(t_angle_sprite));
	(game->sprites)->next->angle_sprite->next->next->next->next->start_angle = -3.14;
	(game->sprites)->next->angle_sprite->next->next->next->next->end_angle = 3.14;
	(game->sprites)->next->angle_sprite->next->next->next->next->texture = *((game->gif)->array + 14);
	(game->sprites)->next->angle_sprite->next->next->next->next->texture2 = *((game->gif)->array + 14);
	(game->sprites)->next->angle_sprite->next->next->next->next->up_health = 40;
	(game->sprites)->next->angle_sprite->next->next->next->next->down_health = 25;
	//------------------------------------------------------------------------------------------------------------------
	(game->sprites)->next->angle_sprite->next->next->next->next->next = (t_angle_sprite*)malloc(sizeof(t_angle_sprite));
	(game->sprites)->next->angle_sprite->next->next->next->next->next->start_angle = -3.14;
	(game->sprites)->next->angle_sprite->next->next->next->next->next->end_angle = 3.14;
	(game->sprites)->next->angle_sprite->next->next->next->next->next->texture = *((game->gif)->array + 15);
	(game->sprites)->next->angle_sprite->next->next->next->next->next->texture2 = *((game->gif)->array + 15);
	(game->sprites)->next->angle_sprite->next->next->next->next->next->up_health = 25;
	(game->sprites)->next->angle_sprite->next->next->next->next->next->down_health = 0;
	//------------------------------------------------------------------------------------------------------------------
	(game->sprites)->next->angle_sprite->next->next->next->next->next->next = 0;
	//------------------------------------------------------------------------------------------------------------------
	(game->sprites)->next->health = 100;
	(game->sprites)->next->next = 0;
	//##################################################################################################################
	start_sprite = (game->sprites)->angle_sprite;
	while (start_sprite != NULL)
    {
	    texture_cut_sdl(start_sprite->texture, 0x71FAFC, 0x73FCFE);
	    start_sprite = start_sprite->next;
    }
}

static void	set_hood(t_game *game)
{
	game->hud.fps_dest.h = 80;
	game->hud.fps_dest.w = 120;
	game->hud.fps_dest.x = 0;
	game->hud.fps_dest.y = 0;
	game->hud.text_dest.h = 800;
	game->hud.text_dest.w = 800;
	game->hud.text_dest.x = game->screen->w / 8;
	game->hud.text_dest.y = game->screen->h / 8;
}

static void load_sounds(t_game *game)
{
	if (!(game->start_menu.music = Mix_LoadMUS( "sounds/GACHI.mp3" )))
		check_error_n_exit(1,(char*)SDL_GetError());
	if (!(game->sounds.music = Mix_LoadMUS( "sounds/Sdc.mp3" )))
		check_error_n_exit(1,(char*)SDL_GetError());
	if (!(game->sounds.bang = Mix_LoadWAV( "sounds/quite_rifle.mp3" )))
		check_error_n_exit(1,(char*)SDL_GetError());
	if (!(game->sounds.bang1 = Mix_LoadWAV( "sounds/not_quite_rifle.mp3" )))
		check_error_n_exit(1,(char*)SDL_GetError());
	if (!(game->start_menu.clap[0] = Mix_LoadWAV( "sounds/loli.mp3" )))
		check_error_n_exit(1,(char*)SDL_GetError());
	if (!(game->start_menu.clap[1] = Mix_LoadWAV( "sounds/trump.mp3" )))
		check_error_n_exit(1,(char*)SDL_GetError());
	if (!(game->start_menu.clap[2] = Mix_LoadWAV( "sounds/doom.mp3" )))
		check_error_n_exit(1,(char*)SDL_GetError());
	if (!(game->start_menu.clap[3] = Mix_LoadWAV( "sounds/gay.mp3" )))
		check_error_n_exit(1,(char*)SDL_GetError());
	if (!(game->start_menu.clap[4] = Mix_LoadWAV( "sounds/gay.mp3" )))
		check_error_n_exit(1,(char*)SDL_GetError());
	if (!(game->sounds.step = Mix_LoadWAV( "sounds/step.mp3" )))
		check_error_n_exit(1,(char*)SDL_GetError());
}

static void load_images(t_game *game)
{
	read_gif(game->gif, "imgs/gif1/", 0, 40, ".bmp");
	read_gif(game->gif, "imgs/rifle/", 1, 2, ".bmp");
	if (!(game->start_menu.image[0] = IMG_Load("imgs/start_menu/0.bmp")))
		check_error_n_exit(1,(char*)SDL_GetError());
	if (!(game->start_menu.image[1] = IMG_Load("imgs/start_menu/1.bmp")))
		check_error_n_exit(1,(char*)SDL_GetError());
	if (!(game->start_menu.image[2] = IMG_Load("imgs/start_menu/2.bmp")))
		check_error_n_exit(1,(char*)SDL_GetError());
	if (!(game->start_menu.image[3] = IMG_Load("imgs/start_menu/3.bmp")))
		check_error_n_exit(1,(char*)SDL_GetError());
	if (!(game->start_menu.image[4] = IMG_Load("imgs/start_menu/4.bmp")))
		check_error_n_exit(1,(char*)SDL_GetError());
	if (!(game->start_menu.image[5] = IMG_Load("imgs/start_menu/4.bmp")))
		check_error_n_exit(1,(char*)SDL_GetError());
	if (!(game->tab_menu.image[0] = IMG_Load("imgs/tab_menu/1.bmp")))
		check_error_n_exit(1,(char*)SDL_GetError());
	if (!(game->multi_menu.image[0] = IMG_Load("imgs/tab_menu/1.bmp")))
		check_error_n_exit(1,(char*)SDL_GetError());
	if (!(game->hud.face[2] = IMG_Load("imgs/hud/doom.bmp")))
		check_error_n_exit(1,(char*)SDL_GetError());
	if (!(game->skybox = IMG_Load("imgs/textures/space.bmp")))
		check_error_n_exit(1,(char*)SDL_GetError());
	if (!(game->hud.aim = IMG_Load("imgs/hud/cross_aim.bmp")))
		check_error_n_exit(1,(char*)SDL_GetError());
	if (!(game->hud.hp_bar = IMG_Load("imgs/hud/hp_bar.bmp")))
		check_error_n_exit(1,(char*)SDL_GetError());
	if (!(game->hud.jetpack = IMG_Load("imgs/hud/jetpack.bmp")))
		check_error_n_exit(1,(char*)SDL_GetError());
	if (!(game->hud.key = IMG_Load("imgs/hud/key.bmp")))
		check_error_n_exit(1,(char*)SDL_GetError());
}

static void pre_calc_screen(t_pre_calc *pre_calc, SDL_Surface  screen)
{
	pre_calc->screen_h_div_2 = screen.h / 2;
	pre_calc->screen_w_div_2 = screen.w / 2;
	pre_calc->screen_w_div_10 = screen.w / 10;
	pre_calc->screen_h_div_10 = screen.h / 10;
	pre_calc->screen_w_div_20 = screen.w / 20;
	pre_calc->screen_h_div_20 = screen.h / 20;
	pre_calc->screen_h_mult_2 = screen.h * 2;
	pre_calc->pi_div_4 = 3.14 / 4;
	pre_calc->pi_mult_2 = 3.14 * 2;
}
static void set_spaw(vec2 *spaw1, vec2 *spaw2, vec2 *spaw3)
{
	spaw1->x = -1;
	spaw1->y = -5;
	spaw2->x = 1.5;
	spaw2->y = -5.5;
	spaw3->x = 0.75;
	spaw3->y = -7.5;
}
static void set_initial_values(t_game *game)
{
	set_player(game);
	set_keystate(game);
	set_menu(game);
	set_sprites(game);
	game->points_cam = (vec2*)malloc(sizeof(vec2) * game->count_points);
	set_color(&game->hud.color, 255, 255, 0);
	set_hood(game);
	game->line_horiz = 400;
	pre_calc_screen(&game->pre_calc, *game->screen);
	game->rifle_state = 0;
	game->rifle_angle = game->player.angle;
	set_spaw(&game->spaw1, &game->spaw2, &game->spaw3);
}

void	add_sprites_wall(t_game *game)
{
	game->sectors->sprite_wall = (t_sprite_wall*)malloc(sizeof(t_sprite_wall));
	game->sectors->sprite_wall->top = 0.5;
	game->sectors->sprite_wall->bot = 0.9;
	game->sectors->sprite_wall->right = 0.87;
	game->sectors->sprite_wall->left = 0.3;
	game->sectors->sprite_wall->wall = 0;
	game->sectors->sprite_wall->texture = *((game->gif)->array + 30);
	game->sectors->sprite_wall->next = 0;
}

t_game	*create_struct(void)
{
	t_game	*game;

	if ((game = (t_game*)malloc(sizeof(t_game))) == 0)
		check_error_n_exit(1,"malloc error");
	init_sdl(game);
	gettimeofday(&game->time, NULL);
	read_map("map2", game);
	load_sounds(game);
	load_images(game);
	set_initial_values(game);
	add_sprites_wall(game);
	game->server_ip = ft_strnew(ft_strlen(game->multi_menu.strings[1]));
	return (game);
}
