/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:30:46 by ldinaut           #+#    #+#             */
/*   Updated: 2023/06/18 17:37:23 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

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

//	le bail est ici ---> le new_fd --> doit etre le FD associé a un nouveau client (un nouvel objet en soit) (c'est l'objet USER de bryce par exemple)

//	la le probleme c'est qu'ici on a le bon fd mais si on sort de Server::new_connection(), on perd le fd car il est stocké nulle part

// si on le stock dans fd_co, on ecrase le 1er fd du premier client reconnu ou alors fd_co un tableau agrandissable mais galere autant faire un nouvel objet

// + j'ai l'impression que ce fd change regulierement par contre genre a chaque tentative de reconnexion ?

// en gros on capte la new connection, mais on l'ecrase direct du coup meme si le client envoie connect() on en fait rien derriere donc ca doit deconnecter i guess ??
	
	std::cout << LIGHT_BLUE << "[DEBUG]\nici le new fd créé par accept() est : " << ev.data.fd << RESET << std::endl;
}
