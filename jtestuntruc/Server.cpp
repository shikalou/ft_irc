/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:30:46 by ldinaut           #+#    #+#             */
/*   Updated: 2023/06/19 00:55:02 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(int port, std::string pass):password(pass), port(port)
{
}

Server::~Server()
{
}

int	Server::new_connection(void){
	struct	sockaddr_in	cli_addr;
	int					new_sock_cli;
	int					addrlen;

	addrlen = sizeof(cli_addr);
	std::cout << RED << "bonjour" << RESET << std::endl;
	new_sock_cli = accept(this->sock, (struct sockaddr *)&cli_addr, (socklen_t*)&addrlen);
//	fcntl(new_sock_cli, F_SETFL, O_NONBLOCK);
	if (new_sock_cli < 0)
		return (ft_error("accept new cli oups", -1));
	this->_clients.push_back(new Client(new_sock_cli));
	std::cout << LIGHT_PINK << "[NEW CLIENT]" << RESET << std::endl;
	return (new_sock_cli);
}

int	Server::client_request(int fd_main){
	char	buffer[1000];

	bzero(buffer, 1000);
	int ret = recv(fd_main, buffer, 1000, MSG_DONTWAIT);
// si mauvais retour --> deconnexion ?
	if (ret == 0)
		return (ft_error("Disconnected", -1));
	std::cout << GREEN << "[MSG RCV]\n" << buffer << RESET << std::endl;
//	il faut un check si le fd_main correspond au fd d'un user deja co
//	si non --> le co ?
//	si oui --> executer sa commande ?
	return (0);
}
/*
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
}*/

int	ft_error(std::string msg, int ret){
	std::cout << RED << msg << RESET << std::endl;
	return (ret);
}


