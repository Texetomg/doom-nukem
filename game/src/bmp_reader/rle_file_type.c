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

void			rle_r1(u_char *im_a, u_int **im, t_rle_rool *rle_r, t_bmp *bmp)
{
	t_bmpinfo	*bmpinfo;
	u_int		*col_array;

	bmpinfo = bmp->bmpinfo_v5;
	col_array = bmp->color->col_array;
	rle_r->j = 0;
	while (rle_r->j < im_a[rle_r->i])
	{
		if (bmpinfo->compression == 1)
		{
			im[rle_r->y][rle_r->x] =
					col_array[im_a[rle_r->i + 1]];
			rle_r->x++;
		}
		rle_r->j++;
	}
}

void			rle_rool3(u_char *im_a, u_int **im, t_rle_rool *r, u_int *c_a)
{
	r->j = 0;
	while (r->j < im_a[r->i + 1])
	{
		im[r->y][r->x] = c_a[im_a[r->i + 2]];
		r->x++;
		r->j++;
	}
	r->i++;
}

void			rle_rool2(u_char *im_array, t_rle_rool *rle_rool)
{
	rle_rool->x += im_array[rle_rool->i + 2];
	rle_rool->y += im_array[rle_rool->i + 3];
	rle_rool->i += 2;
}

void			rle_imread(t_bmp *bmp, u_char *i_a, u_int **im, u_int *c_a)
{
	t_rle_rool	*rle_rool;
	t_bmpinfo	*b_i;

	sub_sets(&bmp, &b_i, &rle_rool);
	while (rle_rool->i < b_i->size_image)
	{
		if (i_a[rle_rool->i] != 0)
			rle_r1(i_a, im, rle_rool, bmp);
		else
		{
			if (i_a[rle_rool->i + 1] == 0)
			{
				rle_rool->x = 0;
				rle_rool->y++;
			}
			else if (i_a[rle_rool->i + 1] == 1)
				break ;
			else if (i_a[rle_rool->i + 1] == 2)
				rle_rool2(i_a, rle_rool);
			else
				rle_rool3(i_a, im, rle_rool, c_a);
		}
		rle_rool->i += 2;
	}
	free(rle_rool);
}

unsigned int	**rle_read(t_bmp *bmp, int inf_size, int fd)
{
	unsigned int	image_shift;
	unsigned char	*im_array;
	unsigned int	im_size;
	unsigned char	*unval_info;
	unsigned int	**image;

	image = im_create(bmp);
	image_shift = bmp->bmphead->bf_off_bits - 14 - inf_size -
			bmp->color->colmap_size - bmp->color->colmap_shift;
	im_size = bmp->bmpinfo_v5->size_image;
	im_array = (unsigned char*)malloc(sizeof(char) * im_size);
	unval_info = (unsigned char*)malloc(sizeof(char) * image_shift);
	read(fd, unval_info, image_shift);
	read(fd, im_array, im_size);
	rle_imread(bmp, im_array, image, bmp->color->col_array);
	free(im_array);
	free(unval_info);
	return (image);
}
