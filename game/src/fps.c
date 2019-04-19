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

static int	count_fps(struct timeval *time)
{
	struct timeval old_time;
    old_time = *time;
    gettimeofday(time, NULL);
    if(time->tv_sec > old_time.tv_sec)
	{
        return((int)(1000000 / (time->tv_usec + 1000000 - old_time.tv_usec)));
	}
	return ((int)(1000000 / (time->tv_usec - old_time.tv_usec)));
}

void    put_fps(SDL_Surface *screen, t_hud hud, struct timeval *time)
{
    char *fps;
    fps = ft_itoa(count_fps(time));
	print_text(screen, fps, "font.otf", 46, hud.color, hud.fps_dest);
	free(fps);
}