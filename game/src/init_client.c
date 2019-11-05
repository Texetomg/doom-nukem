/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_client.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:38:27 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/11/05 15:00:32 by bfalmer-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static struct addrinfo	init_hint(void)
{
	struct addrinfo	hints;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	return (hints);
}

static void				connect_to(t_socket *socket_struct, struct addrinfo *p)
{
	while (p != NULL)
	{
		if ((socket_struct->sockfd = socket(p->ai_family, p->ai_socktype,
				p->ai_protocol)) == -1)
		{
			p = p->ai_next;
			continue;
		}
		if (connect(socket_struct->sockfd, p->ai_addr, p->ai_addrlen) == -1)
		{
			close(socket_struct->sockfd);
			p = p->ai_next;
			continue;
		}
		break ;
	}
}

void					init_client(t_game *game, t_socket *socket_struct)
{
	struct addrinfo	hints;
	struct addrinfo	*p;
	struct addrinfo	*servinfo;
	int				rv;

	hints = init_hint();
	if ((rv = getaddrinfo(game->server_ip, SERVERPORT, &hints, &servinfo)) != 0)
		perror("getaddrinfo error: ");
	p = servinfo;
	connect_to(socket_struct, p);
	if (p == NULL)
	{
		freeaddrinfo(p);
		ft_putstr("client: failed to bind socket\n");
	}
	freeaddrinfo(servinfo);
}

/*
**  баг с мультиплееров здесь
*/

void					client(t_game *game)
{
	game->for_udp.pos = game->player.pos;
	game->for_udp.angle = game->player.angle;
	while (game->for_udp.angle < 0)
		game->for_udp.angle = game->for_udp.angle + game->pre_calc.pi_mult_2;
	while (game->for_udp.angle > game->pre_calc.pi_mult_2)
		game->for_udp.angle = game->for_udp.angle - game->pre_calc.pi_mult_2;
	game->for_udp.sector = game->player.curr_sector;
	game->socket_struct.numbytes = send(game->socket_struct.sockfd,
		&(game->for_udp), sizeof(t_for_udp), 0);
	if (game->socket_struct.numbytes > 0)
	{
		game->sprites->pos = game->for_udp.pos;
		game->sprites->sector = game->for_udp.sector;
		game->sprites->angle = game->for_udp.angle;
		if (game->for_udp.sound != 0)
			play_sound(game, game->for_udp.pos, game->for_udp.sound, -1);
	}
}
