/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_texture_funks.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 12:50:18 by htorp             #+#    #+#             */
/*   Updated: 2019/10/16 11:29:09 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_doom.h"

unsigned int	get_colmap_shift(unsigned int inf_size, void *bmp_info)
{
	t_bmpinfo	*bmpinfo_v5;

	if (inf_size == 40)
	{
		bmpinfo_v5 = (t_bmpinfo*)bmp_info;
		if (bmpinfo_v5->compression == 3)
			return (12);
		else if (bmpinfo_v5->compression == 6)
			return (16);
		else
			return (0);
	}
	else
		return (0);
}

t_color			*get_c_map(int fd, t_bmpinfo *b_i, unsigned char **rca, int i_s)
{
	t_color				*color;
	unsigned int		i;
	char				c;

	color = (t_color*)malloc(sizeof(t_color));
	color->colmap_shift = get_colmap_shift(i_s, b_i);
	if (b_i->bit_count <= 8)
		color->colmap_size = (unsigned int)pow(2, b_i->bit_count) * 4;
	else if (b_i->clr_used != 0)
		color->colmap_size = (i_s == 12) ?
				b_i->clr_used * 3 : b_i->clr_used * 4;
	else
		color->colmap_size = 0;
	*rca = (unsigned char*)malloc(sizeof(char) * color->colmap_size);
	i = 0;
	while (i < color->colmap_shift)
	{
		read(fd, &c, 1);
		i++;
	}
	read(fd, *rca, color->colmap_size);
	color->col_array = (unsigned int*)(*rca);
	return (color);
}

unsigned int	**get_image(t_bmp *bmp, int inf_size, int fd)
{
	unsigned int	**image;

	if (bmp->bmpinfo_v5->compression == 1)
		image = rle_read(bmp, inf_size, fd);
	else if ((bmp->bmpinfo_v5->compression == 0) ||
		(bmp->bmpinfo_v5->compression == 3) ||
			(bmp->bmpinfo_v5->compression == 6))
	{
		image = array_read(bmp, inf_size, fd);
	}
	else
	{
		if (bmp->bmpinfo_v5->compression == 4)
			print_string("Error: The jpeg type is unsupported!!!\n");
		else if (bmp->bmpinfo_v5->compression == 5)
			print_string("Error: The png type is unsupported!!!\n");
		else if (bmp->bmpinfo_v5->compression == 2)
			printf("Error: 4-bit is unsupported!!!\n");
		else
			print_string("Error: unknown type of file!!!\n");
		exit(0);
	}
	return (image);
}

t_texture1		*get_texture1(char *file_name)
{
	int				fd;
	unsigned char	*raw_col_array;
	t_texture1		*texture;
	t_bmp			*bmp;
	int				inf_type;

	bmp = (t_bmp*)malloc(sizeof(t_bmp));
	texture = (t_texture1*)malloc(sizeof(t_texture1));
	fd = open(file_name, O_RDONLY);
	bmp->bmphead = get_headblock(fd, file_name);
	inf_type = get_inf_type(fd);
	bmp->bmpinfo_v5 = get_infoblock(fd, inf_type);
	bmp->color = get_c_map(fd, bmp->bmpinfo_v5, &raw_col_array, inf_type);
	texture->image = get_image(bmp, inf_type, fd);
	texture->height = bmp->bmpinfo_v5->height;
	texture->width = bmp->bmpinfo_v5->width;
	close(fd);
	free(raw_col_array);
	free(bmp->bmpinfo_v5);
	free(bmp->bmphead);
	free(bmp->color);
	free(bmp);
	return (texture);
}

t_texture		*get_texture(char *file_name)
{
	int				i;
	int				j;
	unsigned int	*image;
	t_texture		*texture;
	t_texture1		*texture1;

	texture1 = get_texture1(file_name);
	image = (unsigned int*)malloc(sizeof(int) * texture1->height *
			texture1->width);
	texture = (t_texture*)malloc(sizeof(t_texture));
	i = -1;
	while (++i < texture1->height)
	{
		j = -1;
		while (++j < texture1->width)
		{
			image[i * texture1->width + j] =
					texture1->image[texture1->height - 1 - i][j];
		}
	}
	texture->w = texture1->width;
	texture->h = texture1->height;
	texture->pixels = image;
	glob_free(texture1);
	return (texture);
}
