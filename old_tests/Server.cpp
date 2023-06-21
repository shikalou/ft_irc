/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:30:46 by ldinaut           #+#    #+#             */
/*   Updated: 2023/06/18 18:36:38 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Client.hpp"

Server::Server(int port, std::string pass):password(pass), port(port)
{
}

Server::~Server()
{
}

void	Server::new_connection(struct epoll_event ev, sockaddr_in sockaddr)
{
	std::cout << LIGHT_BLUE << "[DEBUG]\nici le old fd est : " << ev.data.fd << RESET << std::endl;
	int addrlen = sizeof(sockaddr);
	int new_fd = accept(this->sock, (struct sockaddr*)&sockaddr, (socklen_t*)&addrlen);
	fcntl(new_fd, F_SETFL, O_NONBLOCK);
	ev.data.fd = new_fd;
	ev.events = EPOLLIN;
	epoll_ctl(this->epoll_fd, EPOLL_CTL_ADD, new_fd, &ev);

	std::cout << LIGHT_BLUE << "[DEBUG]\nici le new fd créé par accept() est : " << ev.data.fd << RESET << std::endl;
//	tentative de creer un client hihi
	Client	new_client(ev.data.fd);
//	mais genre sa duree de vie equivaut a l'execution de cette fonction hoho
}
