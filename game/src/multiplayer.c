#include "doom-nukem.h"

void draw_multiplayer_screen(t_game *game)
{
    game->start_menu.text_pos = 0;
    draw_full_screen_img(game->screen,
						game->start_menu.image[game->start_menu.text_pos]);
}