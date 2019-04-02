/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 16:38:34 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/04/02 21:21:50 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"
#include <sys/time.h>

int	put_fps(t_game *game)
{
	struct timeval old_time;
    old_time = game->time;
    gettimeofday(&game->time, NULL);
    if(game->time.tv_sec > old_time.tv_sec)
	{
		ft_putstr("fps = ");
        ft_putnbrln((int)(1000000 / (game->time.tv_usec + 1000000 - old_time.tv_usec)));
	}
    /*else
        ft_putnbrln((int)(1000000 / (game->time.tv_usec - old_time.tv_usec)));*/
	return (1);
}
