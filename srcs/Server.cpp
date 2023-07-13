/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:30:46 by ldinaut           #+#    #+#             */
/*   Updated: 2023/07/13 19:11:19 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Client.hpp"

Server::Server()
{
}

Server::Server(int port, std::string pass):password(pass), port(port), ev(5)
{
	_recv = "";
	_end = 1;
	i = 0;
	this->_check_pass = true;
	sigint = false;
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
	this->ev = egal->ev;
	this->_clients = egal->_clients;
	this->_channels = egal->_channels;
	this->_sockaddr = egal->_sockaddr;
	this->i = egal->i;
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
	Client *test = new Client(fd_accept);
	_clients.insert(std::make_pair(fd_accept, test));
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

void	sig_handler(int sig)
{
	if (sig == 2)
	{
		server.kill_cmd(server._clients);
		close(server.epoll_fd);
		close(server.sock);
	}
}


void	Server::deleteClient2(Client *client)
{
	//server._channels// boucle sur ca
	// boucle sur client de chaque channel
	// check si il est dedans - operator ? delete
	std::vector<Channel *>::iterator	servchan_it = server._channels.begin();
	std::vector<Channel *>::iterator	clichan_it = client->_chans.begin();
	std::vector<Client *>::iterator		oper_it;
	std::vector<Client *>::iterator		invit_it;
	for (; servchan_it != server._channels.end(); ++servchan_it)
	{
		for (; clichan_it != client->_chans.end(); ++clichan_it)
		{
			if ((*servchan_it)->getTitle() == (*clichan_it)->getTitle())
			{
				for (oper_it = (*clichan_it)->_operators.begin(); oper_it != (*clichan_it)->_operators.end(); ++oper_it)
				{
					if ((*clichan_it)->_operators.size())
					{
						if ((*oper_it)->getNick() == client->getNick())
							(*clichan_it)->_operators.erase(oper_it);
					}
					else
						break ;
				}
				for (invit_it = (*clichan_it)->_invites.begin(); invit_it != (*clichan_it)->_invites.end(); ++invit_it)
				{
					if ((*clichan_it)->_invites.size())
					{
						if ((*invit_it)->getNick() == client->getNick())
						{
							std::cout << "2 = " << GREEN << client->getNick() << "\n\n\n";
							(*clichan_it)->_invites.erase(invit_it);
						}
					}
					else
						break ;
				}
				for (oper_it = (*servchan_it)->_operators.begin(); oper_it != (*servchan_it)->_operators.end(); ++oper_it)
				{
					if ((*servchan_it)->_operators.size())
					{
						if ((*oper_it)->getNick() == client->getNick())
							(*servchan_it)->_operators.erase(oper_it);
					}
					else
						break ;
				}
				for (invit_it = (*servchan_it)->_invites.begin(); invit_it != (*servchan_it)->_invites.end(); ++invit_it)
				{
					if ((*servchan_it)->_invites.size())
					{
						if ((*invit_it)->getNick() == client->getNick())
						{
							std::cout << "1 = " << GREEN << client->getNick() << "\n\n\n";
							(*servchan_it)->_invites.erase(invit_it);
						}
					}
					else
						break ;
				}
			}
			//std::cout << RED << "deleting chan from clientmap->_chans" << RESET << std::endl;
			delete (*clichan_it);
		}
	}
	int fd = client->_sock;
	close(client->_sock);
	delete client;
	server._clients.erase(fd);
}

int	Server::run_serv()
{
	while (_end)
	{
		signal(SIGPIPE, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sig_handler);
		int event = epoll_wait(this->epoll_fd, ev.data(), 5, 1000);
		if (event < 0)
			return (ft_error(std::string(strerror(errno))));
		for (int k = 0; k < event; k++)
		{
			if (this->sock == ev[k].data.fd)
			{
				this->accept_newclient(_sockaddr);
			}
			else if (ev[k].events)
			{
				std::vector<char>	buffer(4096);
				int ret;
				if ((ret = recv(ev[k].data.fd, &buffer[0], 4096, MSG_DONTWAIT)) <= 0)
				{
					ft_error("error recv\n");
					std::map<int, Client *>::iterator it = server._clients.find(ev[k].data.fd);
					if (it != server._clients.end())
					{
						sigint = true;
						it->second->_recv.clear();
						Commands *cmd_tmp = new Commands();
						Client *tmp = it->second;
						cmd_tmp->quit(it->second);
						delete cmd_tmp;
						delete tmp;
						sigint = false;
					}
					continue ;
				}
				std::string	cmd_str(&buffer[0], ret);
				_clients[ev[k].data.fd]->_recv += cmd_str;
				server._recv += cmd_str;
				std::cout << LAVENDER << "from client [" << cmd_str << "]\n" << RESET << std::endl;
				if (_clients[ev[k].data.fd]->_recv.find('\n') != _clients[ev[k].data.fd]->_recv.npos)
				{
					Commands *cmd = new Commands(_clients[ev[k].data.fd]->_recv, ev[k].data.fd);
					_clients[ev[k].data.fd]->_cmd = cmd;
					_clients[ev[k].data.fd]->_cmd->cmd_manager(_clients);
					if (server._recv.find("QUIT") == server._recv.npos && _check_pass == true)
						delete _clients[ev[k].data.fd]->_cmd;
					try
					{
						server._recv.erase();
						_clients.at(ev[k].data.fd)->_recv.erase();
					}
					catch(const std::exception& e)
					{
					}
				}
				else if (ev[k].events == EPOLLERR)
				{
					std::map<int, Client *>::iterator it = server._clients.find(ev[k].data.fd);
					if (it != server._clients.end())
					{
						Commands *cmd_tmp = new Commands();
						cmd_tmp->quit(it->second);
						delete cmd_tmp;
					}
				}
			}
		}
	}
	return (0);
}
