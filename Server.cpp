/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:30:46 by ldinaut           #+#    #+#             */
/*   Updated: 2023/07/03 14:46:24 by ldinaut          ###   ########.fr       */
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

int	Server::set_clients_info(std:: string cmd, Client *client)
{
	size_t i = 0;
	size_t n = cmd.find("PASS");
	if (n != cmd.npos)
	{
		i = cmd.find("\n", n);
		// verifier par rapport a _pass de serveur si c le bon
		// pas besoin de setter
		client->SetPass(cmd.substr(n + 5, i-(n + 5) - 1));
	}
	std::cout << "11111111111111111111 cmd = " << cmd << std::endl;
	n = cmd.find("NICK");
	if (n != cmd.npos)
	{
		i = cmd.find_first_of("\n", n);
		// int r = i-(n + 5) - 1;
		// if (r > 9)
		// {
		// 	//send(fd_co, "432: nickname too long\n", )
		// 	return (0);
		// }
		client->SetNick(cmd.substr(n + 5, i-(n + 5) - 1));
	}
	else
	{
		send(client->_sock, "431 : no nickname given\n", 24, MSG_DONTWAIT);
		return (0);
	}
	n = cmd.find("USER");
	if (n != cmd.npos)
	{
		i = cmd.find_first_of('\n', n);
		client->SetUser(cmd.substr(n + 5, i - (n + 5) - 1));
		size_t l = cmd.find_first_of(' ', n + 5);
		size_t l2 = cmd.find_first_of(' ', l + 1);
		size_t l3 = cmd.find_first_of(' ', l2 + 1);
		this->network = cmd.substr(l2 + 1, l3- 1 - l2 );
	}
	return (1);
}

void	Server::finish_connection(Client *client)
{
	std::string tmp_pass = "PASS " + this->password + "\n";
	std::string tmp_nick = ":* NICK " + client->getNick() + "\n";
	std::string rpl_wel =  rpl_welcome(client->getNick(), client->getUser(), this->network);
	std::string rpl_yoh = rpl_yourhost(client->getNick(), this->network);
	send(client->_sock, tmp_pass.c_str(), tmp_pass.length(), 0);
	send(client->_sock, tmp_nick.c_str(), tmp_nick.length(), 0);
	send(client->_sock, rpl_wel.c_str(), rpl_wel.length(), 0);
	send(client->_sock, rpl_yoh.c_str(), rpl_yoh.length(), 0);
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

void	Server::parsing_cmd_co(std::string cmd, int clfd)
{
	//std::pair<std::map<int, Client *>::iterator, bool> it = _clients.insert(std::make_pair(clfd, new Client(0)));
	std::map<int, Client *>::iterator it = _clients.find(clfd);
	if (it != _clients.end() && _clients[clfd]->_register == 0)
	{
		if (!set_clients_info(cmd, _clients[clfd]))
		{
			// return error kill la connexion ?? jsais po
		}
		_clients[clfd]->_register = 1;
		finish_connection(_clients[clfd]);
	}
	else
	{
		std::cout << "j;ai aps trouve le client " << std::endl;
	}
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
			else if (ev[k].data.fd)
			{
				std::vector<char>	buffer(4096);
				int ret;
				if ((ret = recv(ev[k].data.fd, &buffer[0], 4096, MSG_DONTWAIT)) <= 0)
				{
					ft_error("error recv\n");
					continue ;
				}
				std::string	cmd_str(&buffer[0], ret);
				std::cout << "dans la boucle = " << &buffer[0] << std::endl << std::endl;
				//std::size_t found;
				//found = cmd_str.find("CAP");
				//if (found != std::string::npos && (found == 0))
				//{
				//	this->parsing_cmd_co(cmd_str, ev[k].data.fd);
				//}
				//else
				//{
				Commands *cmd = new Commands(cmd_str, ev[k].data.fd);
				_clients[ev[k].data.fd]->_cmd = cmd;
				_clients[ev[k].data.fd]->_cmd->cmd_manager(_clients);
				//}
			}
		}
	}
}
