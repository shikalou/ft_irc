/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:30:46 by ldinaut           #+#    #+#             */
/*   Updated: 2023/07/06 13:10:56 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Client.hpp"

Server::Server()
{
}

Server::Server(int port, std::string pass):password(pass), port(port)
{
}

Server::~Server()
{
}

Server Server::operator=(const Server *egal)
{
	this->sock = egal->sock;
	this->password = egal->password;
	this->port = egal->port;
	this->epoll_fd = egal->epoll_fd;
	this->fd_co = egal->fd_co;
	this->network = egal->network;
	this->_clients = egal->_clients;
	this->_channels = egal->_channels;
	this->_sockaddr = egal->_sockaddr;
	return (*this);
}

void	Server::add_epoll(int new_fd, int i)
{
	struct epoll_event ev;

	memset(&ev, 0, sizeof(ev));
	ev.data.fd = new_fd;
	ev.events = (EPOLLIN | EPOLLRDHUP);
	epoll_ctl(epoll_fd, EPOLL_CTL_ADD, new_fd, &ev);
	if (i == 1)
		this->fd_co = new_fd;
}

void	Server::accept_newclient(sockaddr_in sockaddr)
{
	size_t addrlen = sizeof(sockaddr);
	int fd_accept = accept(this->sock, (struct sockaddr*)&sockaddr, (socklen_t*)&addrlen);
	fcntl(fd_accept, F_GETFL, O_NONBLOCK);
	add_epoll(fd_accept, 2);
	_clients.insert(std::make_pair(fd_accept, new Client(fd_accept)));
}

int	Server::init_serv()
{
	this->epoll_fd = epoll_create1(0);

	this->sock = socket(AF_INET, SOCK_STREAM, 0);
	if (this->sock == -1)
		return (ft_error("socket failed"));
	int	opt = 1;
	if (setsockopt(this->sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
		return (ft_error("setsockopt failed"));
	sockaddr_in sockaddr;
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.s_addr = INADDR_ANY;
	sockaddr.sin_port = htons(this->port);
	_sockaddr = sockaddr;

	if (bind(this->sock, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0)
		return(ft_error("bind failed"));
	if (listen(this->sock, 5) < 0)
		ft_error("listen failed");
	int flags = fcntl(this->sock, F_GETFL, O_NONBLOCK);
	if (flags == -1)
		return (ft_error("fcntl failed"));
	this->add_epoll(this->sock, 1);
	return (0);
}

int	Server::run_serv()
{
	std::vector<epoll_event> ev(5);
	
	while (1)
	{	
		int event = epoll_wait(this->epoll_fd, ev.data(), 5, 1000);
		if (event < 0)
			return (ft_error(std::string(strerror(errno))));
		for (int k = 0; k < event; k++)
		{
			if (this->sock == ev[k].data.fd)
			{
				std::cout << "NOUVEAU CLIENT" << std::endl;
				this->accept_newclient(_sockaddr);
			}
			else if (ev[k].events)
			{
				std::vector<char>	buffer(4096);
				int ret;
				if ((ret = recv(ev[k].data.fd, &buffer[0], 4096, MSG_DONTWAIT)) <= 0)
				{
					ft_error("error recv\n");
					continue ;
				}
				std::string	cmd_str(&buffer[0], ret);
				_clients[ev[k].data.fd]->_recv += cmd_str;
				if (_clients[ev[k].data.fd]->_recv.find('\n') != _clients[ev[k].data.fd]->_recv.npos)
				{
					std::cout << "dans la boucle = " << _clients[ev[k].data.fd]->_recv << std::endl << std::endl;
					Commands *cmd = new Commands(_clients[ev[k].data.fd]->_recv, ev[k].data.fd);
					_clients[ev[k].data.fd]->_cmd = cmd;
					_clients[ev[k].data.fd]->_cmd->cmd_manager(_clients);
					if (read(ev[k].data.fd, &buffer[0], 0) != -1)
						_clients[ev[k].data.fd]->_recv.erase();
				}
			}
		}
	}
}
