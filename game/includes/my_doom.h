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

#ifndef MY_DOOM_MY_DOOM_H
# define MY_DOOM_MY_DOOM_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <mlx.h>
# include <math.h>

typedef unsigned int	u_int;
typedef unsigned char	u_char;

typedef struct			s_color
{
	unsigned int		colmap_shift;
	unsigned int		colmap_size;
	unsigned int		*col_array;
}						t_color;

typedef struct			s_bmphead
{
	unsigned short int	bf_type;
	unsigned int		bf_size;
	unsigned short int	bf_reserved1;
	unsigned short int	bf_reserved2;
	unsigned int		bf_off_bits;
}						t_bmphead;

typedef struct			s_texture1
{
	int					width;
	int					height;
	unsigned int		**image;
}						t_texture1;

typedef struct			s_texture
{
	int					width;
	int					height;
	unsigned int		*image;
}						t_texture;

typedef struct			s_ar_params
{
	unsigned char		mask;
	unsigned char		step;
	unsigned int		image_shift;
	unsigned int		im_size;
	unsigned char		*pixel_array;
	unsigned char		*im_array;
	unsigned int		**image;
}						t_ar_params;

typedef struct			s_bmpinfo
{
	int					width;
	int					height;
	unsigned short int	planes;
	unsigned short int	bit_count;
	int					compression;
	unsigned int		size_image;
	unsigned int		x_pels_per_meter;
	unsigned int		y_pels_per_meter;
	unsigned int		clr_used;
	unsigned int		clr_important;
	unsigned int		red_mask;
	unsigned int		green_mask;
	unsigned int		blue_mask;
	unsigned int		alpha_mask;
	unsigned int		cs_type;
	unsigned char		endpoints[36];
	unsigned int		gamma_red;
	unsigned int		gamma_green;
	unsigned int		gamma_blue;
	unsigned int		v5_intent;
	unsigned int		v5_profile_data;
	unsigned int		v5_profile_size;
	unsigned int		v5_reserved;
}						t_bmpinfo;

typedef struct			s_bmp
{
	t_bmphead			*bmphead;
	t_bmpinfo			*bmpinfo_v5;
	t_color				*color;
}						t_bmp;

typedef struct			s_rle_rool
{
	u_int					i;
	u_int					j;
	int 					k;
	int					x;
	int					y;
}						t_rle_rool;

unsigned int			**rle_read(t_bmp *bmp, int inf_size, int fd);
unsigned int			**array_read(t_bmp *bmp, int inf_size, int fd);
void					set_bmpinfo_v3(t_bmpinfo *bmpinfo, int fd);
void					set_bmpinfo_v4(t_bmpinfo *bmpinfo, int fd);
void					set_bmpinfo_v5(t_bmpinfo *bmpinfo, int fd);
void					print_string(char *s);
t_bmphead				*get_headblock(int fd, char *file_name);
t_bmpinfo				*get_infoblock(int fd, int inf_size);
int						get_inf_type(int fd);
t_texture1				*get_texture1(char *file_name);
void					sub_sets(t_bmp **b, t_bmpinfo **b_i, t_rle_rool **r_r);
unsigned int			**im_create(t_bmp *bmp);
t_texture				*get_texture(char *file_name);
void					glob_free(t_texture1 *texture1);

#endif
