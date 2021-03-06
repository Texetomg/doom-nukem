/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ramory-l <ramory-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 21:38:17 by twitting          #+#    #+#             */
/*   Updated: 2019/10/27 14:50:46 by ramory-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "edit.h"

void	putsectstofile(t_edit *edit, int fd)
{
	int	i;
	int j;

	i = -1;
	while (++i < edit->sectnum)
	{
		j = -1;
		sectinfotofile(edit, fd, i);
		while (++j < (int)edit->sectors[i].npoints)
		{
			ft_putnbr_fd(edit->sectors[i].vertex[j], fd);
			if (j + 1 < (int)edit->sectors[i].npoints)
				ft_putchar_fd(' ', fd);
		}
		ft_putstr_fd("\t\t", fd);
		j = -1;
		while (++j < (int)edit->sectors[i].npoints)
		{
			ft_putnbr_fd(edit->sectors[i].neighbors[j], fd);
			if (j + 1 < (int)edit->sectors[i].npoints)
				ft_putchar_fd(' ', fd);
		}
		ft_putchar_fd('\n', fd);
	}
	ft_putchar_fd('\n', fd);
}

void	putplayertofile(t_edit *edit, int fd)
{
	ft_putstr_fd("p\t", fd);
	ft_putnbr_fd(edit->player.x, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(edit->player.y, fd);
	ft_putchar_fd('\t', fd);
	ft_putnbr_fd(edit->playerangle, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(edit->playersect, fd);
	ft_putchar_fd('\n', fd);
	ft_putchar_fd('\n', fd);
}

void	putspritestofile(t_edit *edit, int fd)
{
	int	i;

	i = -1;
	while (++i < edit->sprnum)
	{
		ft_putstr_fd("object\t", fd);
		ft_putnbr_fd(edit->sprites[i].x, fd);
		ft_putchar_fd(' ', fd);
		ft_putnbr_fd(edit->sprites[i].y, fd);
		ft_putchar_fd('\t', fd);
		ft_putnbr_fd(edit->sprites[i].type, fd);
		ft_putchar_fd(' ', fd);
		ft_putnbr_fd(edit->sprites[i].sector, fd);
		ft_putchar_fd('\n', fd);
	}
	if (edit->sprnum)
		ft_putchar_fd('\n', fd);
}

void	putbarstofile(t_edit *edit, int fd)
{
	int	i;

	i = -1;
	while (++i < edit->barsnum)
	{
		ft_putstr_fd("wallsp\t", fd);
		ft_putnbr_fd(edit->bars[i].vert1, fd);
		ft_putchar_fd(' ', fd);
		ft_putnbr_fd(edit->bars[i].vert2, fd);
		ft_putchar_fd('\t', fd);
		ft_putnbr_fd(edit->bars[i].sect1, fd);
		ft_putchar_fd(' ', fd);
		ft_putnbr_fd(edit->bars[i].sect2, fd);
		ft_putchar_fd('\n', fd);
	}
}

void	savemap(t_edit *edit)
{
	int	fd;

	if ((fd = open("created.map", O_WRONLY | O_CREAT | O_TRUNC,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
		perror("open failed\n");
	putvertstofile(edit, fd);
	putsectstofile(edit, fd);
	putplayertofile(edit, fd);
	putspritestofile(edit, fd);
	putbarstofile(edit, fd);
}
