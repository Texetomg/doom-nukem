/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 16:18:31 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/04/03 16:54:00 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

double  ft_atod(const char *c)
{
    int     i;
    char    **buffer;
    double  result;
    double  fract;

    i = ft_skip(c);
    fract = 1;

    buffer = ft_strsplit((c + i), '.');
    result = ft_atoi(buffer[0]);
    i = 0;
    if (buffer[1])
    {
        while (i < (int)ft_strlen(buffer[1]))
        {
            fract *= 0.1;
            i++;
        }
        result += ft_atoi(buffer[1]) * fract;
    }
    return(result);
}
