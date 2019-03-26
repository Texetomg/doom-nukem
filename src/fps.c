/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 16:38:34 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/03/26 17:51:07 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"
#include <sys/time.h>

int	put_fps(t_fps *fps)
{
    fps->old_time = fps->time;
    gettimeofday(&fps->time, NULL);
    if(fps->time.tv_sec > fps->old_time.tv_sec)
        ft_putnbrln((int)(1000000 / (fps->time.tv_usec + 1000000 - fps->old_time.tv_usec)));
    else
        ft_putnbrln((int)(1000000 / (fps->time.tv_usec - fps->old_time.tv_usec)));
	return (1);
}