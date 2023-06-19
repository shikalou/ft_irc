/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:30:46 by ldinaut           #+#    #+#             */
/*   Updated: 2023/06/19 17:41:45 by ldinaut          ###   ########.fr       */
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
	int addrlen = sizeof(sockaddr);
	int new_fd = accept(this->sock, (struct sockaddr*)&sockaddr, (socklen_t*)&addrlen);
	// fcntl(new_fd, F_SETFL, O_NONBLOCK);
	this->_clients.push_back(new Client(new_fd));
	ev.data.fd = new_fd;
	ev.events = EPOLLIN;
	epoll_ctl(this->epoll_fd, EPOLL_CTL_ADD, new_fd, &ev);
}

std::vector<Client*>	Server::parsing_cmd(std::string cmd)
{
	size_t i;
	size_t n = cmd.find("PASS");
	if (n != cmd.npos)
	{
		i = cmd.find('\n', n);
		_clients[0]->SetPass(cmd.substr(n+5, i));
	}
	n = cmd.find("NICK");
	if (n != cmd.npos)
	{
		i = cmd.find('\n', n);
		_clients[0]->SetNick(cmd.substr(n+5, i));
		//nick = cmd.substr(n+5, i);
	}
	n = cmd.find("USER");
	if (n != cmd.npos)
	{
		i = cmd.find('\n', n);
		_clients[0]->SetUser(cmd.substr(n+5, i));
		//nick = cmd.substr(n+5, i);
	}
	return (this->_clients);
}
