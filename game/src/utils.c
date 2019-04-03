/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 17:54:54 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/04/03 19:08:41 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

void    get_pos_z(t_game *game)
{  
    game->player.foots = game->player.pos.z - HIGH;
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
}