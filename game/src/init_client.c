/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_client.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfalmer- <bfalmer-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:38:27 by bfalmer-          #+#    #+#             */
/*   Updated: 2019/05/28 05:10:13 by thorker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom-nukem.h"

static struct addrinfo init_hint()
{
	struct addrinfo	hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	return(hints);
}


void	init_client(t_socket *socket_struct)
{
	struct addrinfo	hints;
	struct addrinfo	*p;
	struct addrinfo	*servinfo;
	int				rv;

	hints = init_hint();
	if ((rv = getaddrinfo(SERVERIP, SERVERPORT, &hints, &servinfo)) != 0)
		perror("getaddrinfo error: ");
	p = servinfo;
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
	if (p == NULL)
		ft_putstr("client: failed to bind socket\n");
}
