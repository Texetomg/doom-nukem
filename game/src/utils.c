/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 17:54:54 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/04/03 18:27:12 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

void    get_pos_z(t_game *game)
{
    double foots;

    foots = game->player.pos.z - HIGH;
    if (game->player.z_accel > 0)
    {
        if (game->player.pos.z + game->player.z_accel  >= game->sectors->ceil)
        {
            game->player.z_accel = 0;
        }
        else
        {
            game->player.pos.z += game->player.z_accel;
            game->player.z_accel -= 0.05;
        }
        
    }
    else if (game->player.z_accel == 0 && foots > game->sectors->floor)
    {
        game->player.z_accel -= 0.05;
    }
    else if (game->player.z_accel < 0)
    {
        if (foots + game->player.z_accel < game->sectors->floor)
        {
            game->player.z_accel = 0;
            game->player.pos.z = game->sectors->floor + HIGH;
        }
        else
        {
            game->player.pos.z += game->player.z_accel;
            game->player.z_accel -= 0.05;   
        }
    }
}