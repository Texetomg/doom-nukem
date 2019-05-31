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

void	v3_inf_read(unsigned char *init_data, t_bmpinfo *bmpinfo)
{
	unsigned short int	*usi_var;
	unsigned int		*ui_var;
	int					*i_var;

	i_var = (int*)(&(init_data[0]));
	bmpinfo->width = i_var[0];
	i_var = (int*)(&(init_data[4]));
	bmpinfo->height = i_var[0];
	usi_var = (unsigned short int*)(&(init_data[8]));
	bmpinfo->planes = usi_var[0];
	usi_var = (unsigned short int*)(&(init_data[10]));
	bmpinfo->bit_count = usi_var[0];
	i_var = (int*)(&(init_data[12]));
	bmpinfo->compression = i_var[0];
	ui_var = (unsigned int*)(&(init_data[16]));
	bmpinfo->size_image = ui_var[0];
	ui_var = (unsigned int*)(&(init_data[20]));
	bmpinfo->x_pels_per_meter = ui_var[0];
	ui_var = (unsigned int*)(&(init_data[24]));
	bmpinfo->y_pels_per_meter = ui_var[0];
	ui_var = (unsigned int*)(&(init_data[28]));
	bmpinfo->clr_used = ui_var[0];
	ui_var = (unsigned int*)(&(init_data[32]));
	bmpinfo->clr_important = ui_var[0];
}

void	v4_inf_read(unsigned char *init_data, t_bmpinfo *bmpinfo)
{
	unsigned int		*ui_var;
	int					i;

	ui_var = (unsigned int*)(&(init_data[36]));
	bmpinfo->red_mask = ui_var[0];
	ui_var = (unsigned int*)(&(init_data[40]));
	bmpinfo->green_mask = ui_var[0];
	ui_var = (unsigned int*)(&(init_data[44]));
	bmpinfo->blue_mask = ui_var[0];
	ui_var = (unsigned int*)(&(init_data[48]));
	bmpinfo->alpha_mask = ui_var[0];
	ui_var = (unsigned int*)(&(init_data[52]));
	bmpinfo->cs_type = ui_var[0];
	i = 0;
	while (i < 36)
	{
		bmpinfo->endpoints[i] = init_data[i + 56];
		i++;
	}
	ui_var = (unsigned int*)(&(init_data[92]));
	bmpinfo->gamma_red = ui_var[0];
	ui_var = (unsigned int*)(&(init_data[96]));
	bmpinfo->gamma_green = ui_var[0];
	ui_var = (unsigned int*)(&(init_data[100]));
	bmpinfo->gamma_blue = ui_var[0];
}

void	set_bmpinfo_v3(t_bmpinfo *bmpinfo, int fd)
{
	unsigned char		*init_data;

	init_data = (unsigned char*)malloc(sizeof(char) * 120);
	read(fd, init_data, 36);
	v3_inf_read(init_data, bmpinfo);
	free(init_data);
}

void	set_bmpinfo_v4(t_bmpinfo *bmpinfo, int fd)
{
	unsigned char		*init_data;

	init_data = (unsigned char*)malloc(sizeof(char) * 120);
	read(fd, init_data, 104);
	v3_inf_read(init_data, bmpinfo);
	v4_inf_read(init_data, bmpinfo);
	free(init_data);
}

void	set_bmpinfo_v5(t_bmpinfo *bmpinfo, int fd)
{
	unsigned int		*ui_var;
	unsigned char		*init_data;

	init_data = (unsigned char*)malloc(sizeof(char) * 120);
	read(fd, init_data, 120);
	v3_inf_read(init_data, bmpinfo);
	v4_inf_read(init_data, bmpinfo);
	ui_var = (unsigned int*)(&(init_data[104]));
	bmpinfo->v5_intent = ui_var[0];
	ui_var = (unsigned int*)(&(init_data[108]));
	bmpinfo->v5_profile_data = ui_var[0];
	ui_var = (unsigned int*)(&(init_data[112]));
	bmpinfo->v5_profile_size = ui_var[0];
	ui_var = (unsigned int*)(&(init_data[116]));
	bmpinfo->v5_reserved = ui_var[0];
	free(init_data);
	printf("Red: %X\n", bmpinfo->red_mask);
}
