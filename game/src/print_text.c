/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_text.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 16:06:32 by thorker           #+#    #+#             */
/*   Updated: 2019/05/31 14:01:37 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

void print_custom_text(t_game *game, char *text){
    print_text(game->screen, text, "../font/font.otf", 46, game->hud.color, game->hud.text_dest);
}