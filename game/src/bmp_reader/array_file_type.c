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

void			image_set2(int i, int j, t_bmp *bmp, t_ar_params *ar_params)
{
	int				pos;
	int				k;
	unsigned int	*pixel;

	pos = (i * bmp->bmpinfo_v5->width + j) * (ar_params->step) + i;
	k = 0;
	while (k < ar_params->step)
	{
		ar_params->pixel_array[k] = ar_params->im_array[pos + k];
		k++;
	}
	pixel = (unsigned int*)(ar_params->pixel_array);
	pixel[0] = pixel[0] & 0xFFFFFF;
	if (bmp->bmpinfo_v5->clr_used == 0)
		ar_params->image[i][j] = pixel[0];
	else
		ar_params->image[i][j] = bmp->color->col_array[pixel[0]];
}

void			image_set1(int i, int j, t_bmp *bmp, t_ar_params *ar_params)
{
	int	k;
	int	pos;
	int	symbol;

	k = (i * bmp->bmpinfo_v5->width + j) % ar_params->step;
	pos = (i * bmp->bmpinfo_v5->width + j) / ar_params->step;
	symbol = ((ar_params->im_array[pos]) &
			((ar_params->mask) << (k * bmp->bmpinfo_v5->bit_count))) >>
					(k * bmp->bmpinfo_v5->bit_count);
	if (k == 0)
		ar_params->image[i][j + 1] = bmp->color->col_array[symbol];
	if (k == 1)
		ar_params->image[i][j - 1] = bmp->color->col_array[symbol];
}

void			im_presets(t_ar_params *ar_p, t_bmpinfo *bmpinfo,
		t_bmp *bmp, int inf_size)
{
	int i;

	ar_p->pixel_array = NULL;
	if (bmpinfo->bit_count <= 8)
	{
		ar_p->mask = (int)pow(2, bmpinfo->bit_count) - 1;
		ar_p->step = 8 / bmpinfo->bit_count;
	}
	else
	{
		ar_p->step = bmpinfo->bit_count / 8;
		ar_p->pixel_array = (u_char*)malloc(sizeof(char) * ar_p->step);
	}
	ar_p->image = (unsigned int**)malloc(sizeof(int*) * bmpinfo->height);
	i = 0;
	while (i < bmpinfo->height)
	{
		ar_p->image[i] = (u_int *)malloc(sizeof(int) * bmpinfo->width);
		i++;
	}
	ar_p->image_shift = bmp->bmphead->bf_off_bits - 14 - inf_size -
			bmp->color->colmap_size - bmp->color->colmap_shift;
	ar_p->im_size = bmpinfo->size_image;
	ar_p->im_array = (u_char *)malloc(sizeof(char) * ar_p->im_size);
}

void			create_image(t_ar_params *ar_p, t_bmpinfo *bmpinfo, t_bmp *bmp)
{
	int i;
	int j;

	i = 0;
	while (i < bmpinfo->height)
	{
		j = 0;
		while (j < bmpinfo->width)
		{
			if (bmpinfo->bit_count <= 8)
				image_set1(i, j, bmp, ar_p);
			else
				image_set2(i, j, bmp, ar_p);
			j++;
		}
		i++;
	}
}

unsigned int	**array_read(t_bmp *bmp, int inf_size, int fd)
{
	unsigned char	*unval_info;
	t_bmpinfo		*bmpinfo;
	t_ar_params		*ar_params;

	ar_params = (t_ar_params*)malloc(sizeof(t_ar_params));
	bmpinfo = bmp->bmpinfo_v5;
	im_presets(ar_params, bmpinfo, bmp, inf_size);
	unval_info = (unsigned char*)malloc(sizeof(char) * ar_params->image_shift);
	read(fd, unval_info, ar_params->image_shift);
	read(fd, ar_params->im_array, ar_params->im_size);
	create_image(ar_params, bmpinfo, bmp);
	free(ar_params->im_array);
	free(unval_info);
	if (ar_params->pixel_array == NULL)
		free(ar_params->pixel_array);
	free(ar_params);
	return (ar_params->image);
}
