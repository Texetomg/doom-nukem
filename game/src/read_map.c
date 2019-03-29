/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 19:25:52 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/03/29 14:48:44 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

static void	read_coord(char *line, vec2 *points)
{
	char	point[5];
	int		i;
	int		j;
	int		x;

	i = 0;
	x = 1;
	while (line[i] != 0)
	{
		if (line[i] == '\t')
			++i;
		else
		{
			j = 0;
			while (line[i] && line[i] != '\t')
				point[++j] = line[++i];
		}
		x == 1 ? points->x = ft_atoi(point) : points->x;
		x == 0 ? points->y = ft_atoi(point) : points->y;
		x = 0;
		ft_strclr(point);
	}
}

vec2		*read_map(char *name)
{
	char	*line;
	int		gnl;
	int		fd;
	int		position;
	vec2	*points;
	
	position = 0;
	if ((fd = open(name, O_RDONLY)) < 0)
		check_error_n_exit(1, "file descriptor < 0");
	while ((gnl = get_next_line(fd, &line)) != 0)
	{
		if (gnl == -1)
			check_error_n_exit(1, "gnl -1");
		if (line[0] == '&')
			points = (vec2*)malloc(sizeof(vec2) * ft_atoi(&line[1]));
		if (line[0] == 'v')
		{
			read_coord(line + 1, points + position);
			++position;
		}
		free(line);
	}
	close(fd);
	return(points);
}

void	player_move(t_game *game, int *loop)
{
	SDL_Event e;
	double x;
	double y;
	double step;
	step = 0.1;
	
	while (SDL_PollEvent( &e))
		{
			SDL_GetMouseState(&game->mouse.x, &game->mouse.y);
			SDL_WarpMouseInWindow(game->window, game->display_mode.w / 2, game->display_mode.h / 2); //перемещать курсор в одну и ту же точку
		
			game->player.angle -= 3.14 / 600 * (game->mouse.x - game->display_mode.w / 2);
			if (e.type == SDL_KEYDOWN)
			{
				x = step * cos(game->player.angle);
				y = step * sin(game->player.angle);
				if (e.key.keysym.sym == SDLK_ESCAPE || e.type == SDL_QUIT)
					*loop = 0;
				if (e.key.keysym.sym == SDLK_e)
					game->player.angle -= 3.14 / 60;
				if (e.key.keysym.sym == SDLK_q)
					game->player.angle += 3.14 / 60;
				if (e.key.keysym.sym == SDLK_w)
				{
					game->player.pos.x += x;
					game->player.pos.y += y;
				}
				if (e.key.keysym.sym == SDLK_s)
				{
					game->player.pos.x -= x;
					game->player.pos.y -= y;
				}
				if (e.key.keysym.sym == SDLK_d)
				{
						game->player.pos.x +=  y;
						game->player.pos.y -= x;
				}
				if (e.key.keysym.sym == SDLK_a)
				{
						game->player.pos.x -= y;
						game->player.pos.y += x;
				}
			}
		
		}
}
