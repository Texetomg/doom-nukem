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

void		set_bmphead(t_bmphead *bmphead, int fd)
{
	unsigned short int	*si_var;
	unsigned int		*i_var;
	unsigned char		init_data[14];

	read(fd, init_data, 14);
	si_var = (unsigned short int*)(&(init_data[0]));
	bmphead->bf_type = si_var[0];
	i_var = (unsigned int*)(&(init_data[2]));
	bmphead->bf_size = i_var[0];
	si_var = (unsigned short int*)(&(init_data[6]));
	bmphead->bf_reserved1 = si_var[0];
	si_var = (unsigned short int*)(&(init_data[8]));
	bmphead->bf_reserved2 = si_var[0];
	i_var = (unsigned int*)(&(init_data[10]));
	bmphead->bf_off_bits = i_var[0];
}

t_bmphead	*get_headblock(int fd, char *file_name)
{
	t_bmphead *bmphead;

	bmphead = (t_bmphead*)malloc(14 * sizeof(char));
	if (fd < 0)
	{
		print_string("Error: The file ");
		print_string(file_name);
		print_string(" is unexist!!!\n");
		exit(0);
	}
	set_bmphead(bmphead, fd);
	if ((bmphead->bf_type != 0x4D42) && (bmphead->bf_type != 0x424D))
	{
		print_string("Error: Unvalid type of fyle!!!\n");
		exit(0);
	}
	return (bmphead);
}

t_bmpinfo	*get_infoblock(int fd, int inf_size)
{
	t_bmpinfo *bmpinfo_v5;

	bmpinfo_v5 = (t_bmpinfo*)malloc(sizeof(t_bmpinfo));
	if (inf_size == 12)
	{
		printf("Error: Unsupported core-version of bmp file!!!\n");
		exit(0);
	}
	if (inf_size == 40)
		set_bmpinfo_v3(bmpinfo_v5, fd);
	if (inf_size == 108)
		set_bmpinfo_v4(bmpinfo_v5, fd);
	if (inf_size == 124)
		set_bmpinfo_v5(bmpinfo_v5, fd);
	if (bmpinfo_v5->bit_count == 16)
	{
		printf("Error: 16-bit is unsupported!!!\n");
		exit(0);
	}
	return (bmpinfo_v5);
}
