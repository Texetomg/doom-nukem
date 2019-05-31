/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htorp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 12:50:18 by htorp             #+#    #+#             */
/*   Updated: 2019/05/30 12:50:23 by htorp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_doom.h"

void			print_string(char *s)
{
	while (*s)
	{
		write(1, s, 1);
		s++;
	}
}

int				get_inf_type(int fd)
{
	unsigned char	*inf_type;
	int				*inf_size;
	int				res;

	inf_type = (unsigned char*)malloc(sizeof(char) * 4);
	read(fd, inf_type, 4);
	inf_size = (int*)inf_type;
	res = inf_size[0];
	free(inf_type);
	return (res);
}

void			sub_sets(t_bmp **bmp, t_bmpinfo **b_i, t_rle_rool **rle_rool)
{
	*b_i = (*bmp)->bmpinfo_v5;
	*rle_rool = (t_rle_rool*)malloc(sizeof(t_rle_rool));
	(*rle_rool)->i = 0;
	(*rle_rool)->y = 0;
	(*rle_rool)->x = 0;
}

unsigned int	**im_create(t_bmp *bmp)
{
	t_bmpinfo		*bmpinfo;
	unsigned int	**image;
	int				i;

	bmpinfo = bmp->bmpinfo_v5;
	image = (unsigned int**)malloc(sizeof(int*) * bmpinfo->height);
	i = 0;
	while (i < bmpinfo->height)
	{
		image[i] = (unsigned int*)malloc(sizeof(int) * bmpinfo->width);
		i++;
	}
	return (image);
}

void			glob_free(t_texture1 *texture1)
{
	int i;

	i = 0;
	while (i < texture1->height)
	{
		free(texture1->image[i]);
		i++;
	}
	free(texture1->image);
	free(texture1);
}
