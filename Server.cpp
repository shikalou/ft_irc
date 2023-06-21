/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:30:46 by ldinaut           #+#    #+#             */
/*   Updated: 2023/06/21 17:47:03 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(int port, std::string pass):password(pass), port(port)
{
}

Server::~Server()
{
}

void	Server::set_clients_info(std:: string cmd, Client *client)
{
	size_t i = 0;
	size_t n = cmd.find("PASS");
	if (n != cmd.npos)
	{
		i = cmd.find("\n", n);
		client->SetPass(cmd.substr(n + 5, i-(n + 5) - 1));
	}
	n = cmd.find("NICK");
	if (n != cmd.npos)
	{
		i = cmd.find_first_of("\n", n);
		
		client->SetNick(cmd.substr(n + 5, i-(n + 5) - 1));
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
}

void	Server::finish_connection(Client *client)
{
	std::string tmp_pass = "PASS " + client->getPass() + "\n";
	std::string tmp_nick = ":* NICK " + client->getNick() + "\n";
	std::string rpl_wel = "001 " + client->getNick() + " :Welcome to the " + network + " Network, " + client->getNick() + "\n";
	std::string	rpl_yoh = "002 " + client->getNick() + " :Your host is " + network + ", running version 2.4\n";
	send(fd_co, tmp_pass.c_str(), tmp_pass.length(), 0);
	send(fd_co, tmp_nick.c_str(), tmp_nick.length(), 0);
	send(fd_co, rpl_wel.c_str(), rpl_wel.length(), 0);
	send(fd_co, rpl_yoh.c_str(), rpl_yoh.length(), 0);
}

std::map<std::string, Client*>	Server::parsing_cmd_co(std::string cmd, struct epoll_event ev, sockaddr_in sockaddr)
{
	int addrlen = sizeof(sockaddr);
	int new_fd = accept(this->sock, (struct sockaddr*)&sockaddr, (socklen_t*)&addrlen);
	ev.data.fd = new_fd;
	ev.events = EPOLLIN;
	epoll_ctl(this->epoll_fd, EPOLL_CTL_ADD, new_fd, &ev);
	
	_clients[NICK_TOOBIG] = new Client(new_fd);

	set_clients_info(cmd, _clients[NICK_TOOBIG]);

	std::string nick_tmp = _clients[NICK_TOOBIG]->getNick();

	_clients.insert(std::make_pair(nick_tmp, new Client(0)));
	_clients[nick_tmp] = _clients[NICK_TOOBIG];
	_clients.erase(NICK_TOOBIG);
	finish_connection(_clients[nick_tmp]);
	return (this->_clients);
}
