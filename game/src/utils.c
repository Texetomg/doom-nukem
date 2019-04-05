/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 17:54:54 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/04/05 17:19:40 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

void    get_pos_z(t_game *game)
{  
    if (game->player.z_accel > 0)
    {
        if (game->player.pos.z + game->player.z_accel  >= (game->sectors + game->player.curr_sector)->ceil)
        {
            game->player.z_accel = 0;
        }
        else
        {
            game->player.pos.z += game->player.z_accel;
            game->player.z_accel -= ACCEL;
        }
        
    }
    else if (game->player.z_accel == 0 && game->player.foots > (game->sectors + game->player.curr_sector)->floor)
    {
        game->player.z_accel -= ACCEL;
    }
    else if (game->player.z_accel < 0)
    {
        if (game->player.foots + game->player.z_accel < (game->sectors + game->player.curr_sector)->floor)
        {
            game->player.z_accel = 0;
            game->player.pos.z = (game->sectors + game->player.curr_sector)->floor + HIGH;
        }
        else
        {
            game->player.pos.z += game->player.z_accel;
            game->player.z_accel -= ACCEL;   
        }
    }
	game->player.foots = game->player.pos.z - 0.5;
	game->player.knees = game->player.pos.z - 0.3;
}
